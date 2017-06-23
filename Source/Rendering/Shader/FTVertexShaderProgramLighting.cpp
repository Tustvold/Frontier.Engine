#include "FTVertexShaderProgramLighting.h"
#include "Rendering/FTShaderNode.h"
#include "Rendering/FTView.h"

NS_FT_BEGIN

const char* FTVertexShaderProgramLighting::fragment_shader_source_ = {
        "#version 140\n"
        "uniform vec3 camera_position;"
        "uniform float material_shininess;\n"
        "uniform vec3 material_specular_color;\n"

        "#define MAX_LIGHTS 5\n"
        "uniform int num_lights;\n"
        "uniform struct Light {\n"
            "vec4 position;\n"
            "vec3 intensity; //a.k.a the color of the light\n"
            "float attenuation;\n"
            "float ambient_coefficient;\n"
            "float cone_angle;\n"
            "vec3 cone_direction;\n"
        "} allLights[MAX_LIGHTS];\n"

        "in vec3 N;\n"
        "in vec3 V;\n"
        "in vec3 fragmentColor;\n"

        "out vec4 finalColor;\n"

        "vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 N, vec3 v, vec3 surfaceToCamera) {\n"
            "vec3 L;\n"
            "float attenuation = 1.0;\n"
            "if(light.position.w == 0.0) {\n"
                //directional light
                "L = light.position.xyz;\n"
                "attenuation = 1.0; //no attenuation for directional lights\n"
            "} else {\n"
                //point light
                "L = normalize(light.position.xyz - v);\n"
                "float distanceToLight = length(light.position.xyz - v);\n"
                "attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));\n"

                //cone restrictions (affects attenuation)
                "float lightToSurfaceAngle = degrees(acos(dot(-L, normalize(light.cone_direction))));\n"
                "if(lightToSurfaceAngle > light.cone_angle){\n"
                    "attenuation = 0.0;\n"
                "}\n"
            "}\n"

            //ambient
            "vec3 ambient = light.ambient_coefficient * surfaceColor.rgb * light.intensity;\n"

            //diffuse
            "float diffuseCoefficient = max(0.0, dot(N, L));\n"
            "vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensity;\n"

            //specular
            "float specularCoefficient = 0.0;\n"
            "if(diffuseCoefficient > 0.0)\n"
                "specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-L, N))), material_shininess);\n"
            "vec3 specular = specularCoefficient * material_specular_color * light.intensity;\n"

            //linear color (color before gamma correction)
            "return ambient + attenuation*(diffuse + specular);\n"
        "}\n"

        "void main() {\n"
            "vec4 surfaceColor = vec4(fragmentColor, 1);\n"
            "vec3 surfaceToCamera = normalize(camera_position - V);\n"

            //combine color from all the lights
            "vec3 linearColor = vec3(0);\n"
            "for(int i = 0; i < num_lights; ++i){\n"
                "linearColor += ApplyLight(allLights[i], surfaceColor.rgb, N, V, surfaceToCamera);\n"
            "}\n"

            //final color (after gamma correction)
            "vec3 gamma = vec3(1.0/2.2);\n"
            "finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);\n"
        "}\n"
};

const char* FTVertexShaderProgramLighting::vertex_shader_source_ = {
        "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
    layout(location = 1) in vec3 vertexColor;\n\
    layout(location = 3) in vec3 vertexNormal;\n\
	\n\
    uniform mat4 model;\
	uniform mat4 MVP;\n\
    uniform mat3 normal_matrix;\n\
    out vec3 V;\n\
	out vec3 fragmentColor;\n\
    out vec3 N;\
\
	void main(){\n\
		\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
        fragmentColor = vertexColor;\n\
        N = normal_matrix * vertexNormal;\n\
        V = vec3(model * vec4(vertexPosition_modelspace,1));\n\
		\n\
	}"
};

FTVertexShaderProgramLighting::FTVertexShaderProgramLighting() {

}

FTVertexShaderProgramLighting::~FTVertexShaderProgramLighting() {
}

bool FTVertexShaderProgramLighting::load() {
    if (!FTVertexColorShaderProgram::load())
        return false;

    std::string pos_suffix = "].position";
    std::string intensity_suffix = "].intensity";
    std::string attenuation_suffix = "].attenuation";
    std::string ambient_coefficient_suffix = "].ambient_coefficient";
    std::string cone_angle_suffix = "].cone_angle";
    std::string cone_direction_suffix = "].cone_direction";

    for (int i = 0; i < LightManager::MaxLights; i++) {
        std::string base = "allLights[" + std::to_string(i);
        std::string t;

        t = base + pos_suffix;
        GLint ret = glGetUniformLocation(program_id_, t.c_str());
        if (ret == -1)
            return false;
        position_uniforms_[i] = ret;

        t = base + intensity_suffix;
        ret = glGetUniformLocation(program_id_, t.c_str());
        if (ret == -1)
            return false;
        intensity_uniforms_[i] = ret;

        t = base + attenuation_suffix;
        ret = glGetUniformLocation(program_id_, t.c_str());
        if (ret == -1)
            return false;
        attenuation_uniforms_[i] = ret;

        t = base + ambient_coefficient_suffix;
        ret = glGetUniformLocation(program_id_, t.c_str());
        if (ret == -1)
            return false;
        ambient_coefficient_uniforms_[i] = ret;

        t = base + cone_angle_suffix;
        ret = glGetUniformLocation(program_id_, t.c_str());
        if (ret == -1)
            return false;
        cone_angle_uniforms_[i] = ret;

        t = base + cone_direction_suffix;
        ret = glGetUniformLocation(program_id_, t.c_str());
        if (ret == -1)
            return false;
        cone_direction_uniforms_[i] = ret;
    }

    num_lights_uniform_ = glGetUniformLocation(program_id_, "num_lights");
    material_shininess_uniform_ = glGetUniformLocation(program_id_, "material_shininess");
    material_specular_color_uniform_ = glGetUniformLocation(program_id_, "material_specular_color");
    model_matrix_uniform_ = glGetUniformLocation(program_id_, "model");
    normal_matrix_uniform_ = glGetUniformLocation(program_id_, "normal_matrix");
    camera_position_uniform_ = glGetUniformLocation(program_id_, "camera_position");

    return num_lights_uniform_ != -1 && material_shininess_uniform_ != -1 && material_specular_color_uniform_ != -1 && model_matrix_uniform_ != -1 && camera_position_uniform_ != -1 && normal_matrix_uniform_ != -1;
}

void FTVertexShaderProgramLighting::updateUniforms(const FTCamera *camera, FTShaderNode *node) {
    FTVertexShaderProgram::updateUniforms(camera, node);

    auto material = node->getMaterial();

    auto& lights = node->getView()->getLightManager()->getLights();

    FTAssert(lights.size() < LightManager::MaxLights, "Too Many Lights");

    glUniform1i(num_lights_uniform_, (GLint) lights.size());
    glUniform1f(material_shininess_uniform_, material->shininess);
    glUniform3f(material_specular_color_uniform_, material->specular_color.x, material->specular_color.y, material->specular_color.z);

    glUniformMatrix4fv(model_matrix_uniform_, 1, GL_FALSE, (const GLfloat *)&node->getModelMatrix());
    glUniformMatrix3fv(normal_matrix_uniform_, 1, GL_FALSE, (const GLfloat *)&node->getNormalMatrix());

    auto camera_pos = camera->getPosition();
    glUniform3f(camera_position_uniform_, camera_pos.x, camera_pos.y, camera_pos.z);

    for (int i = 0; i < (int)lights.size(); i++) {
        auto& light = lights[i];
        glUniform4f(position_uniforms_[i], light.position.x, light.position.y, light.position.z, light.position.w);
        glUniform3f(intensity_uniforms_[i], light.intensity.x, light.intensity.y, light.intensity.z);
        glUniform1f(attenuation_uniforms_[i], light.attenuation);
        glUniform1f(ambient_coefficient_uniforms_[i], light.ambientCoefficient);
        glUniform1f(cone_angle_uniforms_[i], light.coneAngle);
        glUniform3f(cone_direction_uniforms_[i], light.coneDirection.x, light.coneDirection.y, light.coneDirection.z);
    }
}

NS_FT_END