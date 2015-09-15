#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Scene/Transform/FTTransformUtil.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>

class FTCube : public FTIndexedMesh<FTTransformPositionScaleRotation, FTVertexColorShaderProgram, FTVertexColor, uint16_t> {
public:
    explicit FTCube(const glm::vec3 face_colors[6]);
    ~FTCube();

    void setPosition(const glm::vec3& position) {
        transform_->setPosition(position);
    }

    void setRotationQuaternion(const glm::quat& quat) {
        transform_->setRotationQuaternion(quat);
    }

    void setScale(const glm::vec3& scale) {
        transform_->setScale(scale);
    }

protected:

};
