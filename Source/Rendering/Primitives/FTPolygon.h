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

    virtual void pre_draw(const glm::mat4& mvp) override;
    
    static std::vector<glm::vec2> generateRegularPolygonVertices(float radius, int n, float start_angle);

    static std::vector<glm::vec2> generateRegularPolygonVertices(float radius, int n);

    void loadFilled(std::vector<glm::vec2>&& vertices, const glm::vec2& size);

    void loadBorder(std::vector<glm::vec2>&& vertices, const glm::vec2& size, float border_thickness);

protected:
    glm::vec3 fill_color_;
};
