#pragma once
#include "FTNode.h"
#include <Util/FTMath.h>
#include "BoundingShape/FTBoundingCuboid.h"

class FTLayoutNode : public FTNode {
public:
    FTLayoutNode() {

    }

    virtual ~FTLayoutNode() {

    }

    void layoutChildrenWithPaddingX(float padding, bool reverse = false) {

        float x = 0;
        float max_y = 0;
        float max_z = 0;

        if (!reverse) {
            for (auto it = children_.begin(); it != children_.end(); ++it) {
                (*it)->setPosition(glm::vec3(x, 0, 0));
                const auto& size = (*it)->getBoundingShape()->getLayoutSize();
                x += size.x;
                x += padding;
                max_y = FTMAX(max_y, size.y);
                max_z = FTMAX(max_z, size.z);
            }
        } else {
            for (auto it = children_.rbegin(); it != children_.rend(); ++it) {
                (*it)->setPosition(glm::vec3(x, 0, 0));
                const auto& size = (*it)->getBoundingShape()->getLayoutSize();
                x += size.x;
                x += padding;
                max_y = FTMAX(max_y, size.y);
                max_z = FTMAX(max_z, size.z);
            }
        }
        
        x -= padding;

        setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(), glm::vec3(x, max_y, max_z)));

    }

    void layoutChildrenWithPaddingY(float padding, bool reverse = false) {
        float y = 0;
        float max_x = 0;
        float max_z = 0;

        if (!reverse) {
            for (auto it = children_.begin(); it != children_.end(); ++it) {
                (*it)->setPosition(glm::vec3(0, y, 0));
                const auto& size = (*it)->getBoundingShape()->getLayoutSize();
                y += size.y;
                y += padding;
                max_x = FTMAX(max_x, size.x);
                max_z = FTMAX(max_z, size.z);
            }
        } else {
            for (auto it = children_.rbegin(); it != children_.rend(); ++it) {
                (*it)->setPosition(glm::vec3(0, y, 0));
                const auto& size = (*it)->getBoundingShape()->getLayoutSize();
                y += size.y;
                y += padding;
                max_x = FTMAX(max_x, size.x);
                max_z = FTMAX(max_z, size.z);
            }
        }
        
        y -= padding;

        setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(), glm::vec3(max_x, y, max_z)));
    }

    void layoutChildrenWithPaddingZ(float padding, bool reverse = false) {
        float max_y = 0;
        float max_x = 0;
        float z = 0;

        if (!reverse) {
            for (auto it = children_.begin(); it != children_.end(); ++it) {
                (*it)->setPosition(glm::vec3(0, 0, z));
                const auto& size = (*it)->getBoundingShape()->getLayoutSize();
                z += size.z;
                z += padding;
                max_x = FTMAX(max_x, size.x);
                max_y = FTMAX(max_y, size.y);
            }
        } else {
            for (auto it = children_.rbegin(); it != children_.rend(); ++it) {
                (*it)->setPosition(glm::vec3(0, 0, z));
                const auto& size = (*it)->getBoundingShape()->getLayoutSize();
                z += size.z;
                z += padding;
                max_x = FTMAX(max_x, size.x);
                max_y = FTMAX(max_y, size.y);
            }
        }
        z -= padding;

        setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(), glm::vec3(max_x, max_y, z)));
    }


    void layoutChildrenInGridXY(float padding, int maxX, int maxY) {
        int i = 0;

        float max_x = 0;

        float ypos = 0;

        FTAssert(maxX == -1 || maxY == -1 || maxX * maxY >= children_.size(), "More children than can fit in grid");

        for (int y = 0; (maxY == -1 || y < maxY) && i < children_.size(); y++) {
            float xpos = 0;
            float max_height = 0.0f;
            for (int x = 0; (maxX == -1 || x < maxX) && i < children_.size(); x++) {
                auto& child = children_[i++];
                child->setPosition(glm::vec2(xpos, ypos));
                const auto& size = child->getBoundingShape()->getLayoutSize();
                xpos += size.x + padding;
                max_height = FTMAX(max_height, size.y);
            }
            ypos += max_height + padding;
            xpos -= padding;
            max_x = FTMAX(max_x, xpos);
        }
        ypos -= padding;

        setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(), glm::vec3(max_x, ypos,0)));
    }

protected:
};
