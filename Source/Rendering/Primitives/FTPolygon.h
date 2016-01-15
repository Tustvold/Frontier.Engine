#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Shader/FTVertexShaderProgramColor.h>
#include <glm/detail/type_mat.hpp>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <vector>

class FTPolygon : public FTMesh<FTVertex<glm::vec2>> {
private:
    typedef FTMesh<FTVertex<glm::vec2>> FTPolygonBase_;
public:
    explicit FTPolygon(const glm::vec3& color, FTVertexShaderProgramColor* shader = FTShaderNode::getShaderUtil<FTVertexShaderProgramColor>());

    void pre_draw(const glm::mat4& mvp) override;
    
    static std::unique_ptr<MeshData> generateRegularPolygonData(float radius, int n, float start_angle);

    static std::unique_ptr<MeshData> generateRegularPolygonData(float radius, int n);

    static std::unique_ptr<MeshData> generateFilledPolygonData(std::vector<glm::vec2>&& vertices, const glm::vec2& size);

    static std::unique_ptr<MeshData> generateBorderPolygonData(const std::unique_ptr<MeshData>& polygon, float border_thickness);

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

protected:
    glm::vec3 fill_color_;
};
