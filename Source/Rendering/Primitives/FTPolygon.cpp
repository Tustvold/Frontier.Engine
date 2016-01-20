#include "FTPolygon.h"
#include <Rendering/BoundingShape/FTBoundingEllipsoid.h>

static int wrapSize(size_t size, int i) {
    if (i < 0)
        return i + (int)size;
    if (i >= size)
        return i - (int)size;
    return i;
}

FTPolygon::FTPolygon(const glm::vec3& color, FTVertexShaderProgramColor* shader) :
    FTPolygonBase_(shader), fill_color_(color) {
    
}

void FTPolygon::pre_draw(const glm::mat4& mvp) {
    FTPolygonBase_::pre_draw(mvp);

    auto shader = (FTVertexShaderProgramColor*)current_shader_program_;
    glUniform3f(shader->getFillColorUniformID(), fill_color_.x, fill_color_.y, fill_color_.z);
}

std::unique_ptr<FTPolygon::MeshData> FTPolygon::generateRegularPolygonData(float radius, int n, float start_angle) {
    FTAssert(n >= 3, "Cannot create a polygon with less than 3 vertices");

    auto data = std::make_unique<MeshData>(n);
    auto vertices = data->getVertices().data();

    float t = (float)M_PI * 2.0f / (float)n;
    float angle = start_angle;
    auto offset = glm::vec2(radius);

    for (int i = 0; i < n; i++) {
        float cos = cosf(angle);
        vertices[i].position_ = offset + glm::vec2(radius * cosf(angle), radius * sinf(angle));
        angle += t;
    }
    data->setVertexCount(n);

    data->setBoundingShape(std::make_unique<FTBoundingEllipsoid>(glm::vec3(radius, radius, 0)));
    data->setPrimitiveType(GL_TRIANGLE_FAN);
    return data;
}

std::unique_ptr<FTPolygon::MeshData> FTPolygon::generateRegularPolygonData(float radius, int n) {
    float angle = (2 - n) * (float)M_PI / (2.0f * n);
    return generateRegularPolygonData(radius, n, angle);
}

std::unique_ptr<FTPolygon::MeshData> FTPolygon::generateFilledPolygonData(std::vector<glm::vec2>&& vertices, const glm::vec2& size) {
    auto data = std::make_unique<MeshData>(vertices.size());
    auto& data_vertices = data->getVertices();

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        data_vertices.push_back(FTVertex<glm::vec2>(*it));
    }

    data->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(size, 0)));
    data->setPrimitiveType(GL_TRIANGLE_FAN);
    return data;
}

std::unique_ptr<FTPolygon::MeshData> FTPolygon::generateBorderPolygonData(const std::unique_ptr<MeshData>& from_data, float border_thickness) {
    size_t num_verts = from_data->getVertexCount();
    FTAssert(num_verts >= 3, "Cannot create from data with less than 3 vertices");
    FTAssert(from_data->getPrimitiveType() == GL_TRIANGLE_FAN, "Data not in correct format");
    auto vertices = from_data->getVertices().data();

    auto data = std::make_unique<MeshData>(num_verts * 2 + 1);
    auto& data_vertices = data->getVertices();

    for (auto i = 0; i < num_verts; i++) {
        auto previous_vertex = vertices[wrapSize(num_verts, i - 1)].position_;
        auto current_vertex = vertices[i].position_;
        auto next_vertex = vertices[wrapSize(num_verts, i + 1)].position_;

        auto norm_a = glm::normalize(next_vertex - current_vertex);
        auto norm_b = glm::normalize(previous_vertex - current_vertex);
        auto direction = glm::normalize((norm_a + norm_b) / 2.0f);

        auto costheta = glm::dot(norm_a, norm_b);
        auto offset = direction * border_thickness / sqrtf((1 - costheta) / 2.0f);


        data_vertices.push_back(FTVertex<glm::vec2>(current_vertex + offset));
        data_vertices.push_back(FTVertex<glm::vec2>(current_vertex));
    }
    data_vertices.push_back(data_vertices[0]);
    data_vertices.push_back(data_vertices[1]);

    data->setPrimitiveType(GL_TRIANGLE_STRIP);
    data->setBoundingShape(from_data->moveBoundingShape());

    return data;
}