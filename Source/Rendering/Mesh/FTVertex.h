#pragma once

namespace details {
    template <typename T>
    struct VectorInfo {
        
    };

    template <>
    struct VectorInfo<glm::vec2> {
        static int getNumComponents() {
            return 2;
        }
    };

    template <>
    struct VectorInfo<glm::vec3> {
        static int getNumComponents() {
            return 3;
        }
    };

    template <>
    struct VectorInfo<glm::vec4> {
        static int getNumComponents() {
            return 4;
        }
    };
}

#include <Frontier.h>

enum {
    kVertexAttribLocation = 0,
    kColorAttribLocation = 1,
    kUVAttribLocation = 2
};

// TODO: Add alignment specifiers to these to make sure the compiler doesn't insert padding
// Currently MSVC doesn't seem to allow alignas in templates, however...
struct IFTVertex {

};

template <typename PosType>
struct FTVertex : public IFTVertex {
    PosType position_;

    FTVertex() {

    }

    explicit FTVertex(const PosType& position) : position_(position) {

    }

    bool operator==(const FTVertex& other) const {
        if (other.position_ != position_)
            return false;
        return true;
    }

    bool operator!=(const FTVertex& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation, // attribute
            details::VectorInfo<PosType>::getNumComponents(), // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            sizeof(FTVertex), // stride
            (void*)0 // array buffer offset
            );
        glEnableVertexAttribArray(kVertexAttribLocation);
    };
};

template <typename PosType>
struct FTVertexColor {
    PosType position_;
    glm::vec3 color_;

    FTVertexColor() {

    }

    FTVertexColor(const PosType& position, const glm::vec3 color) : position_(position), color_(color) {

    }

    bool operator==(const FTVertexColor& other) const {
        if (other.position_ != position_)
            return false;
        if (other.color_ != color_)
            return false;
        return true;
    }

    bool operator!=(const FTVertexColor& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation,
            details::VectorInfo<PosType>::getNumComponents(),
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexColor),
            (void*)0
            );

        glVertexAttribPointer(
            kColorAttribLocation,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexColor),
            (void*)(sizeof(PosType))
            );
        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kColorAttribLocation);
    };
};

template <typename PosType>
struct FTVertexTexture {
    PosType position_;
    glm::vec2 uv_;

    FTVertexTexture() {

    }

    FTVertexTexture(const PosType& position, const glm::vec2 uv) : position_(position), uv_(uv) {

    }

    bool operator==(const FTVertexTexture& other) const {
        if (other.position_ != position_)
            return false;
        if (other.uv_ != uv_)
            return false;
        return true;
    }

    bool operator!=(const FTVertexTexture& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation,
            details::VectorInfo<PosType>::getNumComponents(),
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexTexture),
            (void*)0
            );

        glVertexAttribPointer(
            kUVAttribLocation,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexTexture),
            (void*)(sizeof(PosType))
            );

        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kUVAttribLocation);
    };
};

template <typename PosType>
struct FTVertexColorTexture {
    PosType position_;
    glm::vec3 color_;
    glm::vec2 uv_;

    FTVertexColorTexture() {

    }

    bool operator==(const FTVertexColorTexture& other) const {
        if (other.position_ != position_)
            return false;
        if (other.color_ != color_)
            return false;
        if (other.uv_ != uv_)
            return false;
        return true;
    }

    bool operator!=(const FTVertexColorTexture& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation,
            details::VectorInfo<PosType>::getNumComponents(),
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexColorTexture),
            (void*)0
            );
        glVertexAttribPointer(
            kColorAttribLocation,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexColorTexture),
            (void*)(sizeof(PosType))
            );

        glVertexAttribPointer(
            kUVAttribLocation,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(FTVertexColorTexture),
            (void*)(sizeof(PosType) + sizeof(glm::vec3))
            );

        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kUVAttribLocation);
        glEnableVertexAttribArray(kColorAttribLocation);
    };
};