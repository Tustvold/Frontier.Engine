#pragma once
#include <glm/glm.hpp>
#include <Util/FTAlignedData.h>

// Creates and manages a transform
class FTTransform {
public:
    FTTransform() : transform_dirty_(true) {
        transform_matrix = glm::mat4();
    }

    virtual ~FTTransform() {
    }


    // This matrix should only be accessed and altered from the draw thread
    const glm::mat4& getTransformMatrix() {
        updateMatrices();
        return transform_matrix.getConstData();
    }

    // Update this transform's matrix return true if it needed updating
    virtual bool updateMatrices() {
        auto original_value = transform_dirty_;
        transform_dirty_ = false;
        return original_value;
    }

    virtual bool getDirty() {
        return transform_dirty_;
    }

protected:

    // This matrix should only be accessed and altered from the draw thread
    FTAlignedData<glm::mat4> transform_matrix;
    bool transform_dirty_;
};
