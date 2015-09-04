#pragma once
#include <GL/glew.h>
#include "FTMesh.h"

template <typename VertexType, typename IndexType>
class FTIndexedMeshData : public FTMeshData<VertexType> {
public:

    FTIndexedMeshData() : index_count_(0) {

    }

    FTIndexedMeshData(size_t vertexCount, size_t indexCount) : FTMeshData(vertexCount), index_count_(0) {
        indices_.reserve(indexCount);
    }

    FTIndexedMeshData(std::vector<VertexType>& vertices, std::vector<IndexType>& indices) : FTMeshData(vertices), index_count_(0) {
        indices_ = std::move(indices);
    }

    virtual ~FTIndexedMeshData() {
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

template <typename Transform, typename ShaderProgram, typename VertexType, typename IndexType>
class FTIndexedMesh : public FTMesh<Transform, ShaderProgram, VertexType> {
public:

    virtual ~FTIndexedMesh() {
        glDeleteBuffers(1, &index_buffer_id_);
    }

    // Creates empty VBOs of the passed size
    // These can then be populated using the setIndexedMeshData functions
    void loadEmptyIndexedMesh(GLuint vertex_count, GLuint index_count, bool cleanup = true) {
        FTMesh::loadEmptyMesh(vertex_count, false);
        max_num_inidices_ = index_count;
        num_indices_ = 0;
        glGenBuffers(1, &index_buffer_id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_num_inidices_ * sizeof(IndexType), nullptr, GL_DYNAMIC_DRAW);

        if (cleanup) {
            glBindVertexArray(0);
            is_loaded_ = true;
        }
    }

    void loadIndexedMeshData(const std::shared_ptr<FTIndexedMeshData<VertexType, IndexType>>& data, bool is_static, bool cleanup = true) {
        loadMeshData(std::static_pointer_cast<FTMeshData<VertexType>>(data), is_static, false);

        num_indices_ = (GLuint)data->getIndexCount();
        max_num_inidices_ = num_indices_;
        glGenBuffers(1, &index_buffer_id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);


        glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_num_inidices_ * sizeof(IndexType), data->getIndices().data(), is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        if (cleanup) {
            glBindVertexArray(0);
            is_loaded_ = true;
        }
    }

    virtual void setIndexedMeshData(const std::shared_ptr<FTIndexedMeshData<VertexType, IndexType>>& data) {
        setMeshData(std::static_pointer_cast<FTMeshData<VertexType>>(data));
        // Update mesh data
        if (max_num_inidices_ >= data->getIndexCount()) {
            num_indices_ = (GLuint)data->getIndexCount();
            // We can update the existing buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, num_indices_ * sizeof(IndexType), data->getIndices().data());
        }
        else {
            num_indices_ = (GLuint)data->getIndexCount();
            max_num_inidices_ = num_indices_;
            // We must re-create the buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_ * sizeof(IndexType), data->getIndices().data(), GL_DYNAMIC_DRAW);
        }
    }

    

    void draw() override {
        glDrawElements(
            GL_TRIANGLES, // mode
                        num_indices_, // count
                        GL_UNSIGNED_SHORT, // type
                        (void*)0 // element array buffer offset
        );
    }

protected:

    GLuint num_indices_;
    GLuint max_num_inidices_;
    GLuint index_buffer_id_;

private:
    virtual void loadMeshData(const std::shared_ptr<FTMeshData<VertexType>>& data, bool is_static, bool cleanup) override {
        FTMesh::loadMeshData(data, is_static, cleanup);
    }

    virtual void setMeshData(const std::shared_ptr<FTMeshData<VertexType>>& data) override {
        FTMesh::setMeshData(data);
    }

    virtual void loadEmptyMesh(GLuint vertex_count, bool cleanup) override {
        FTMesh::loadEmptyMesh(vertex_count, cleanup);
    }
};
