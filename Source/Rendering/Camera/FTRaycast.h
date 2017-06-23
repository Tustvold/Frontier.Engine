#pragma once

#include <Frontier.h>

NS_FT_BEGIN

class FTRaycast {

public:
    virtual ~FTRaycast() {
    }

    FTRaycast(const glm::vec3& origin, const glm::vec3& direction) : origin_(origin), direction_(glm::normalize(direction)) {

    }

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

    bool intersectsSphere(const glm::vec3& sphere_center, float radius_squared, glm::vec3& intersection, float& d_out) const {
        glm::vec3 q = sphere_center - origin_;
        float c2 = glm::length2(q);
        float v = glm::dot(q, direction_);
        float d = radius_squared - (c2 - v*v);

        if (d < 0.0f)
            return false;

        d = v - sqrtf(d);
        if (d < 0.0f)
            return false;

        d_out = d;
        intersection = d_out * direction_ + origin_;
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

NS_FT_END
