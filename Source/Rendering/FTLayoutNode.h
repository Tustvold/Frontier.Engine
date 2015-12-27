#pragma once
#include "FTNode.h"
#include <Util/FTMath.h>

class FTLayoutNode : public FTNode {
public:
    FTLayoutNode() {

    }

    virtual ~FTLayoutNode() {

    }

    void layoutChildrenWithPaddingX(float padding) {

        float x = 0;
        float max_y = 0;
        float max_z = 0;

        for (auto it = children_.begin(); it != children_.end(); ++it) {
            (*it)->setPosition(glm::vec3(x, 0, 0));
            const auto& size = (*it)->getSize();
            x += size.x;
            x += padding;
            max_y = FTMAX(max_y, size.y);
            max_z = FTMAX(max_z, size.z);
        }
        x -= padding;

        setSize(glm::vec3(x, max_y, max_z));

    }

    void layoutChildrenWithPaddingY(float padding) {
        float y = 0;
        float max_x = 0;
        float max_z = 0;

        for (auto it = children_.begin(); it != children_.end(); ++it) {
            (*it)->setPosition(glm::vec3(0, y, 0));
            const auto& size = (*it)->getSize();
            y += size.y;
            y += padding;
            max_x = FTMAX(max_x, size.x);
            max_z = FTMAX(max_z, size.z);
        }
        y -= padding;

        setSize(glm::vec3(max_x, y, max_z));

    }

    void layoutChildrenWithPaddingZ(float padding) {
        float max_y = 0;
        float max_x = 0;
        float z = 0;

        for (auto it = children_.begin(); it != children_.end(); ++it) {
            (*it)->setPosition(glm::vec3(0, 0, z));
            const auto& size = (*it)->getSize();
            z += size.z;
            z += padding;
            max_x = FTMAX(max_x, size.x);
            max_y = FTMAX(max_y, size.y);
        }
        z -= padding;

        setSize(glm::vec3(max_x, max_y, z));

    }

protected:
};
