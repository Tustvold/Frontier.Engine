#include "FTPolygon.h"

FTPolygon::FTPolygon(const glm::vec3& color, FTVertexShaderProgramColor* shader) :
    FTPolygonBase_(shader), fill_color_(color) {
    
}

void FTPolygon::pre_draw(const glm::mat4& mvp) {
    FTPolygonBase_::pre_draw(mvp);

    auto shader = (FTVertexShaderProgramColor*)current_shader_program_;
    glUniform3f(shader->getFillColorUniformID(), fill_color_.x, fill_color_.y, fill_color_.z);
}

std::vector<glm::vec2> FTPolygon::generateRegularPolygonVertices(float radius, int n, float start_angle) {
    FTAssert(n >= 3, "Cannot create a polygon with less than 3 vertices");

    std::vector<glm::vec2> vertices;
    vertices.reserve(n);
    float t = (float)M_PI * 2.0f / (float)n;
    float angle = start_angle;
    auto offset = glm::vec2(radius);

    for (int i = 0; i < n; i++) {
        float cos = cosf(angle);
        vertices.push_back(offset + glm::vec2(radius * cosf(angle), radius * sinf(angle)));
        angle += t;
    }

    return vertices;
}

std::vector<glm::vec2> FTPolygon::generateRegularPolygonVertices(float radius, int n) {
    float angle = (2 - n) * (float)M_PI / (2.0f * n);
    return generateRegularPolygonVertices(radius, n, angle);
}

void FTPolygon::loadFilled(std::vector<glm::vec2>&& vertices, const glm::vec2& size) {
    auto data = std::make_shared<FTMeshData<FTVertex<glm::vec2>>>(vertices.size());
    auto& data_vertices = data->getVertices();

    auto max = glm::vec2(-FLT_MAX);

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        data_vertices.push_back(FTVertex<glm::vec2>(*it));
        max = glm::max(max, *it);
    }

    data->setSize(glm::vec3(max, 0));
    data->setPrimitiveType(GL_TRIANGLE_FAN);

    loadMeshData(data.get(), true);
}

static int wrapSize(size_t size, int i) {
    if (i < 0)
        return i + (int)size;
    if (i >= size)
        return i - (int)size;
    return i;
}

void FTPolygon::loadBorder(std::vector<glm::vec2>&& vertices, const glm::vec2& size, float border_thickness) {
    FTAssert(vertices.size() >= 3, "Cannot create polygon with less than 3 vertices");
    auto data = std::make_shared<FTMeshData<FTVertex<glm::vec2>>>(vertices.size()*2 + 1);
    auto& data_vertices = data->getVertices();

    for (auto i = 0; i < vertices.size(); i++) {
        auto previous_vertex = vertices[wrapSize(vertices.size(), i-1)];
        auto current_vertex = vertices[i];
        auto next_vertex = vertices[wrapSize(vertices.size(), i + 1)];

        auto norm_a = glm::normalize(next_vertex - current_vertex);
        auto norm_b = glm::normalize(previous_vertex - current_vertex);
        auto direction = glm::normalize((norm_a + norm_b) / 2.0f);

        auto costheta = glm::dot(norm_a, norm_b);
        auto offset = direction * border_thickness / sqrtf((1 - costheta) / 2.0f);
            
        
        data_vertices.push_back(FTVertex<glm::vec2>(current_vertex+offset));
        data_vertices.push_back(FTVertex<glm::vec2>(current_vertex));
    }
    data_vertices.push_back(data_vertices[0]);
    data_vertices.push_back(data_vertices[1]);

    data->setPrimitiveType(GL_TRIANGLE_STRIP);
    data->setSize(glm::vec3(size, 0));

    loadMeshData(data.get(), true);
}
