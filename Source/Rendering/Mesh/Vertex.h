#pragma once

#include <Frontier.h>

NS_FT_BEGIN

namespace details
{
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

enum {
    kVertexAttribLocation = 0,
    kColorAttribLocation = 1,
    kUVAttribLocation = 2,
    kNormalAttribLocation = 3,
};

// TODO: Add alignment specifiers to these to make sure the compiler doesn't insert padding
// Currently MSVC doesn't seem to allow alignas in templates, however...
struct IVertex {

};

template <typename PosType>
struct Vertex : public IVertex {
    PosType position_;

    Vertex() {

    }

    explicit Vertex(const PosType& position) : position_(position) {

    }

    bool operator==(const Vertex& other) const {
        return other.position_ == position_;
    }

    bool operator!=(const Vertex& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation, // attribute
            details::VectorInfo<PosType>::getNumComponents(), // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            sizeof(Vertex), // stride
            (void*)0 // array buffer offset
        );
        glEnableVertexAttribArray(kVertexAttribLocation);
    };
};

template <typename PosType>
struct VertexColor {
    PosType position_;
    glm::vec3 color_;

    VertexColor() {

    }

    VertexColor(const PosType& position, const glm::vec3 color) : position_(position), color_(color) {

    }

    bool operator==(const VertexColor& other) const {
        return other.position_ == position_ && other.color_ == color_;
    }

    bool operator!=(const VertexColor& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation,
            details::VectorInfo<PosType>::getNumComponents(),
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexColor),
            (void*)0
        );

        glVertexAttribPointer(
            kColorAttribLocation,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexColor),
            (void*)(sizeof(PosType))
        );
        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kColorAttribLocation);
    };
};

template <typename PosType>
struct VertexColorNormal {
    PosType position_;
    glm::vec3 color_;
    glm::vec3 normal_;

    VertexColorNormal() {

    }

    VertexColorNormal(const PosType& position, const glm::vec3 color, const glm::vec3 normal) : position_(position), color_(color), normal_(normal) {

    }

    bool operator==(const VertexColorNormal& other) const {
        return other.position_ == position_ && other.color_ == color_ && other.normal_ == normal_;
    }

    bool operator!=(const VertexColorNormal& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
                kVertexAttribLocation,
                details::VectorInfo<PosType>::getNumComponents(),
                GL_FLOAT,
                GL_FALSE,
                sizeof(VertexColorNormal),
                (void*)0
        );

        glVertexAttribPointer(
                kColorAttribLocation,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(VertexColorNormal),
                (void*)(sizeof(PosType))
        );

        glVertexAttribPointer(
                kNormalAttribLocation,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(VertexColorNormal),
                (void*)(sizeof(PosType)+sizeof(glm::vec3))
        );
        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kColorAttribLocation);
        glEnableVertexAttribArray(kNormalAttribLocation);
    };
};


template <typename PosType>
struct VertexTexture {
    PosType position_;
    glm::vec2 uv_;

    VertexTexture() {

    }

    VertexTexture(const PosType& position, const glm::vec2 uv) : position_(position), uv_(uv) {

    }

    bool operator==(const VertexTexture& other) const {
        return other.position_ == position_ && other.uv_ == uv_;
    }

    bool operator!=(const VertexTexture& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation,
            details::VectorInfo<PosType>::getNumComponents(),
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexTexture),
            (void*)0
        );

        glVertexAttribPointer(
            kUVAttribLocation,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexTexture),
            (void*)(sizeof(PosType))
        );

        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kUVAttribLocation);
    };
};

template <typename PosType>
struct VertexColorTexture {
    PosType position_;
    glm::vec3 color_;
    glm::vec2 uv_;

    VertexColorTexture() {

    }

    bool operator==(const VertexColorTexture& other) const {
        return other.position_ == position_ && other.color_ == color_ && other.uv_ == uv_;
    }

    bool operator!=(const VertexColorTexture& other) const {
        return !((*this) == other);
    }

    static void bind() {
        glVertexAttribPointer(
            kVertexAttribLocation,
            details::VectorInfo<PosType>::getNumComponents(),
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexColorTexture),
            (void*)0
        );
        glVertexAttribPointer(
            kColorAttribLocation,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexColorTexture),
            (void*)(sizeof(PosType))
        );

        glVertexAttribPointer(
            kUVAttribLocation,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(VertexColorTexture),
            (void*)(sizeof(PosType) + sizeof(glm::vec3))
        );

        glEnableVertexAttribArray(kVertexAttribLocation);
        glEnableVertexAttribArray(kUVAttribLocation);
        glEnableVertexAttribArray(kColorAttribLocation);
    };
};

NS_FT_END