#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/IndexedMesh.h>
#include <Rendering/Shader/VertexShaderProgramColor.h>
#include <glm/detail/type_mat.hpp>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <vector>

NS_FT_BEGIN

class Polygon : public Mesh<Vertex<glm::vec2>> {
private:
    typedef Mesh<Vertex<glm::vec2>> FTPolygonBase_;
public:
    explicit Polygon(const glm::vec3& color, VertexShaderProgramColor* shader = ShaderNode::getShaderUtil<VertexShaderProgramColor>());

    static std::unique_ptr<MeshDataType> generateRegularPolygonData(float radius, int n, float start_angle);

    static std::unique_ptr<MeshDataType> generateRegularPolygonData(float radius, int n);

    static std::unique_ptr<MeshDataType> generateFilledPolygonData(std::vector<glm::vec2>&& vertices, const glm::vec2& size);

    static std::unique_ptr<MeshDataType> generateBorderPolygonData(const std::unique_ptr<MeshDataType>& polygon, float border_thickness);

    void loadRegularFilledPolygon(float radius, int n) {
        loadMeshData(generateRegularPolygonData(radius, n).get(),true);
    }

    void loadRegularFilledPolygon(float radius, int n, float start_angle) {
        loadMeshData(generateRegularPolygonData(radius, n, start_angle).get(), true);
    }

    void loadFilledPolygon(std::vector<glm::vec2>&& vertices, const glm::vec2& size) {
        loadMeshData(generateFilledPolygonData(std::move(vertices), size).get(), true);
    }

    void loadRegularBorderPolygon(float radius, int n, float border_thickness) {
        loadMeshData(generateBorderPolygonData(generateRegularPolygonData(radius, n), border_thickness).get(), true);
    }

    void loadRegularBorderPolygon(float radius, int n, float border_thickness, float start_angle) {
        loadMeshData(generateBorderPolygonData(generateRegularPolygonData(radius, n, start_angle), border_thickness).get(), true);
    }

    void loadBorderPolygon(std::vector<glm::vec2>&& vertices, const glm::vec2& size, float border_thickness) {
        loadMeshData(generateBorderPolygonData(generateFilledPolygonData(std::move(vertices), size), border_thickness).get(), true);
    }
};

NS_FT_END