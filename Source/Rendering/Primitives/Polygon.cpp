#include "Polygon.h"
#include <Rendering/BoundingShape/BoundingEllipsoid.h>

NS_FT_BEGIN

static int wrapSize(int size, int i) {
    if (i >= size)
        return i - size;
    if (i < 0)
        return i + size;
    return i;
}

Polygon::Polygon(const glm::vec3& color, VertexShaderProgramColor* shader) :
    FTPolygonBase_(shader) {
    material_.diffuse_color = color;
}

std::unique_ptr<Polygon::MeshDataType> Polygon::generateRegularPolygonData(float radius, int n, float start_angle) {
    FTAssert(n >= 3, "Cannot create a polygon with less than 3 vertices");

    auto data = std::make_unique<MeshDataType>(n);
    auto vertices = data->getVertices().data();

    float t = (float)M_PI * 2.0f / (float)n;
    float angle = start_angle;
    auto offset = glm::vec2(radius);

    for (int i = 0; i < n; i++) {
        vertices[i].position_ = offset + glm::vec2(radius * cosf(angle), radius * sinf(angle));
        angle += t;
    }
    data->setVertexCount(n);

    data->setBoundingShape(std::make_unique<BoundingEllipsoid>(glm::vec3(radius, radius, 0)));
    data->setPrimitiveType(GL_TRIANGLE_FAN);
    return data;
}

std::unique_ptr<Polygon::MeshDataType> Polygon::generateRegularPolygonData(float radius, int n) {
    float angle = (2 - n) * (float)M_PI / (2.0f * n);
    return generateRegularPolygonData(radius, n, angle);
}

std::unique_ptr<Polygon::MeshDataType> Polygon::generateFilledPolygonData(std::vector<glm::vec2>&& vertices, const glm::vec2& size) {
    auto data = std::make_unique<MeshDataType>(vertices.size());
    auto& data_vertices = data->getVertices();

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        data_vertices.push_back(Vertex<glm::vec2>(*it));
    }

    data->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(size, 0)));
    data->setPrimitiveType(GL_TRIANGLE_FAN);
    return data;
}

std::unique_ptr<Polygon::MeshDataType> Polygon::generateBorderPolygonData(const std::unique_ptr<MeshDataType>& from_data, float border_thickness) {
    int num_verts = (int) from_data->getVertexCount();
    FTAssert(num_verts >= 3, "Cannot create from data with less than 3 vertices");
    FTAssert(from_data->getPrimitiveType() == GL_TRIANGLE_FAN, "Data not in correct format");
    auto vertices = from_data->getVertices().data();

    auto data = std::make_unique<MeshDataType>(num_verts * 2 + 1);
    auto& data_vertices = data->getVertices();

    for (int i = 0; i < num_verts; i++) {
        auto previous_vertex = vertices[wrapSize(num_verts, i - 1)].position_;
        auto current_vertex = vertices[i].position_;
        auto next_vertex = vertices[wrapSize(num_verts, i + 1)].position_;

        auto norm_a = glm::normalize(next_vertex - current_vertex);
        auto norm_b = glm::normalize(previous_vertex - current_vertex);
        auto direction = glm::normalize((norm_a + norm_b) / 2.0f);

        auto costheta = glm::dot(norm_a, norm_b);
        auto offset = direction * border_thickness / sqrtf((1 - costheta) / 2.0f);


        data_vertices.push_back(Vertex<glm::vec2>(current_vertex + offset));
        data_vertices.push_back(Vertex<glm::vec2>(current_vertex));
    }
    data_vertices.push_back(data_vertices[0]);
    data_vertices.push_back(data_vertices[1]);

    data->setPrimitiveType(GL_TRIANGLE_STRIP);
    data->setBoundingShape(from_data->moveBoundingShape());

    return data;
}

NS_FT_END