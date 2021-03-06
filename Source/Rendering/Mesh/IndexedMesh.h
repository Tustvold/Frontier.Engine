#pragma once
#include "Mesh.h"

NS_FT_BEGIN

namespace details {
    template <typename IndexType>
    struct IndexTypeDescriptor {

    };

    template <> struct IndexTypeDescriptor<uint8_t> {
        static GLuint getGLIndexType() {
            return GL_UNSIGNED_BYTE;
        }
    };

    template <> struct IndexTypeDescriptor<uint16_t> {
        static GLuint getGLIndexType() {
            return GL_UNSIGNED_SHORT;
        }
    };

    template <> struct IndexTypeDescriptor<uint32_t> {
        static GLuint getGLIndexType() {
            return GL_UNSIGNED_INT;
        }
    };
};



template <typename VertexType, typename IndexType>
class IndexedMeshData : public MeshData<VertexType> {
public:

    IndexedMeshData() : index_count_(0) {

    }

    IndexedMeshData(size_t vertexCount, size_t indexCount) : MeshData<VertexType>(vertexCount), index_count_(0) {
        indices_.reserve(indexCount);
    }

    IndexedMeshData(std::vector<VertexType>&& vertices, std::vector<IndexType>&& indices) : MeshData<VertexType>(std::move(vertices)), index_count_(0) {
        indices_ = std::move(indices);
    }

    virtual ~IndexedMeshData() {
    }

    std::vector<IndexType>& getIndices() {
        return indices_;
    }

    // We store the index_count separately as this allows code to bypass redundant IndexType constructor calls
    void setIndexCount(size_t count) {
        FTAssert(indices_.capacity() > index_count_, "Invalid Index Count");
        index_count_ = count;
    }

    size_t getIndexCount() {
        if (index_count_ != 0)
            return index_count_;
        return indices_.size();
    }

protected:
    std::vector<IndexType> indices_;
    size_t index_count_;
};

template <typename VertexType, typename IndexType>
class IndexedMesh : public Mesh<VertexType> {
public:
    typedef IndexedMeshData<VertexType, IndexType> MeshDataType;

    explicit IndexedMesh(VertexShaderProgram* shader = ShaderNode::getShaderUtil<VertexShaderProgram>()) :
        Mesh<VertexType>(shader),
        num_indices_(0),
        max_num_inidices_(0),
        index_buffer_id_(-1) {

    }

    virtual ~IndexedMesh() {
        glDeleteBuffers(1, &index_buffer_id_);
    }

    // Creates empty VBOs of the passed size
    // These can then be populated using the setIndexedMeshData functions
    void loadEmptyIndexedMesh(GLuint vertex_count, GLuint index_count, bool cleanup = true) {
        Mesh<VertexType>::loadEmptyMesh(vertex_count, false);
        max_num_inidices_ = index_count;
        num_indices_ = 0;
        glGenBuffers(1, &index_buffer_id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_num_inidices_ * sizeof(IndexType), nullptr, GL_DYNAMIC_DRAW);

        if (cleanup) {
            glBindVertexArray(0);
            this->is_loaded_ = true;
        }
    }

    void loadIndexedMeshData(MeshDataType* data, bool is_static, bool cleanup = true) {
        Mesh<VertexType>::loadMeshData(data, is_static, false);

        num_indices_ = (GLuint)data->getIndexCount();
        max_num_inidices_ = num_indices_;
        glGenBuffers(1, &index_buffer_id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);


        glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_num_inidices_ * sizeof(IndexType), data->getIndices().data(), is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        if (cleanup) {
            glBindVertexArray(0);
            this->is_loaded_ = true;
        }
    }

    void setIndexedMeshData(MeshDataType* data) {
        Mesh<VertexType>::setMeshData(data);
        // Update mesh data
        if (max_num_inidices_ >= data->getIndexCount()) {
            num_indices_ = (GLuint)data->getIndexCount();
            // We can update the existing buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, num_indices_ * sizeof(IndexType), data->getIndices().data());
        } else {
            num_indices_ = (GLuint)data->getIndexCount();
            max_num_inidices_ = num_indices_;
            // We must re-create the buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_ * sizeof(IndexType), data->getIndices().data(), GL_DYNAMIC_DRAW);
        }
    }


    void draw() override {
        // TODO use appropriate gl index type for template parameter
        glDrawElements(
            Mesh<VertexType>::primitive_type_, // mode
                        num_indices_, // count
                        details::IndexTypeDescriptor<IndexType>::getGLIndexType(), // type
                        (void*)0 // element array buffer offset
        );
    }

protected:

    GLuint num_indices_;
    GLuint max_num_inidices_;
    GLuint index_buffer_id_;
};

NS_FT_END