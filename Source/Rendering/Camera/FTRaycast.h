#pragma once

#include <Frontier.h>

class FTRaycast {

public:
    virtual ~FTRaycast() {
    }

    FTRaycast(const glm::vec3& origin, const glm::vec3& direction) : origin_(origin), direction_(direction) {

    }

    bool intersectsRect2D(const glm::vec2& origin, const glm::vec2& size, glm::vec2& intersection) const {
        if (!(origin.x <= origin_.x && origin.x + size.x >= origin_.x && origin.y <= origin_.y && origin.y + size.y >= origin_.y))
            return false;
        intersection = glm::vec2(origin_.x, origin_.y);
        return true;
    };

    // Whether this ray intersects a given plane. Will return false if no solution exists. If there is a solution intersection will be
    // set to the coressponding value. If the line is in the plane intersection will be set to point_in_plane
    bool intersectsPlane(const glm::vec3& perpendicular, const glm::vec3& point_in_plane, glm::vec3& intersection) const {
        float numerator = glm::dot((point_in_plane - origin_), perpendicular);
        float denom = glm::dot(perpendicular, direction_);
        if (fabsf(denom) < FLT_EPSILON) {
            // Line parallel to the plane
            if (fabsf(numerator) < FLT_EPSILON) {
                // Contained within plane
                intersection = point_in_plane;
                return true;
            }
            return false;
        }
        intersection = origin_ + direction_ * (numerator / denom);
        return true;
    }

    const glm::vec3& getOrigin() const {
        return origin_;
    }

    const glm::vec3& getDirection() const {
        return direction_;
    }


protected:

    glm::vec3 origin_;
    glm::vec3 direction_;
};
