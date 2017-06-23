#pragma once
#include <vector>
#include <Frontier.h>

NS_FT_BEGIN

class ShaderNode;
class Camera;

// Base class for ShaderProgram Objects
// These encapsulate OpenGl program functionality
// Including binding the program and updating uniforms
class ShaderProgram {
public:

    virtual ~ShaderProgram() {
        if (program_id_ != 0)
        glDeleteProgram(program_id_);
    }

    virtual bool load() {
        return compile();
    }

    virtual bool compile() = 0;

    void use() const {
        glUseProgram(program_id_);
    }

    virtual void updateUniforms(const Camera *camera, ShaderNode *node) {

    }

protected:

    ShaderProgram() : program_id_(0) {

    }

    GLuint program_id_;

protected:

    bool createShaderProgram(const char* vertex_shader_code, const char* fragment_shader_code) {
        program_id_ = 0;
        // Create the shaders
        GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

        /*	// load the vertex shader from the disk
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertexShader, std::ios::in);
		if (VertexShaderStream.is_open()){
		VertexShaderStream.seekg(0, std::ios::end);
		VertexShaderCode.reserve(VertexShaderStream.tellg());
		VertexShaderStream.seekg(0, std::ios::beg);
		VertexShaderCode.assign((std::istreambuf_iterator<char>(VertexShaderStream)), std::istreambuf_iterator<char>());
		VertexShaderStream.close();
		}
		else{
		FTLOG("Couldn't open vertex shader with code %s.", vertexShader);
		return false;
		}

		//load the fragment shader from the disk
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragmentShader, std::ios::in);
		if (FragmentShaderStream.is_open()){
		FragmentShaderStream.seekg(0, std::ios::end);
		FragmentShaderCode.reserve(FragmentShaderStream.tellg());
		FragmentShaderStream.seekg(0, std::ios::beg);
		FragmentShaderCode.assign((std::istreambuf_iterator<char>(FragmentShaderStream)), std::istreambuf_iterator<char>());
		FragmentShaderStream.close();
		}
		else {
		FTLOG("Couldn't open fragment shader with code %s", fragmentShader);
		return false;
		}*/

        //FTLOG("Vertex Shader Code:\n%s\nFragment Shader Code\n%s", VertexShaderCode.c_str(), FragmentShaderCode.c_str());

        GLint result = GL_FALSE;
        int info_log_length;

        //FTLOG("Compiling vertex shader %s", vertexShaderPath);

        char const* vertex_source_pointer = vertex_shader_code;
        glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, nullptr);
        glCompileShader(vertex_shader_id);

        // Check Vertex Shader
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        if (result != GL_TRUE) {
            std::vector<char> vertex_shader_error_message(info_log_length + 1);
            glGetShaderInfoLog(vertex_shader_id, info_log_length, nullptr, &vertex_shader_error_message[0]);
            FTAssert(false, "Vertex shader compilation failed with error: %s", &vertex_shader_error_message[0]);
            return false;
        }

        //FTLog("Compiling fragment shader : %s", fragmentShader);

        char const* fragment_source_pointer = fragment_shader_code;
        glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, nullptr);
        glCompileShader(fragment_shader_id);

        // Check Fragment Shader
        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        if (result != GL_TRUE) {
            std::vector<char> FragmentShaderErrorMessage(info_log_length + 1);
            glGetShaderInfoLog(fragment_shader_id, info_log_length, nullptr, &FragmentShaderErrorMessage[0]);
            FTAssert(false, "Fragment shader compilation failed with error: %s", &FragmentShaderErrorMessage[0]);
            return false;
        }

        //FTLOG("Linking Program");

        program_id_ = glCreateProgram();
        glAttachShader(program_id_, vertex_shader_id);
        glAttachShader(program_id_, fragment_shader_id);
        glLinkProgram(program_id_);

        // Check the program
        glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_log_length);
        if (result != GL_TRUE) {
            std::vector<char> ProgramErrorMessage(info_log_length + 1);
            glGetProgramInfoLog(program_id_, info_log_length, nullptr, &ProgramErrorMessage[0]);
            FTLOG("%s\n", &ProgramErrorMessage[0]);
            return false;
        }


        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);

        //FTLOG("Compilation successful");

        return true;
    }
};

NS_FT_END