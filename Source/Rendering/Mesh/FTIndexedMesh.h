#pragma once
#include <GL/glew.h>
#include "FTMesh.h"
#include <FTArray.h>

template <typename VertexType, typename IndexType>
class FTIndexedMeshData : public FTMeshData<VertexType> {
public:

	FTIndexedMeshData(size_t vertexCount, size_t indexCount) : FTMeshData(vertexCount), indices_(new FTArray<IndexType>(indexCount)) {
	}

	FTIndexedMeshData(FTArray<VertexType>* vertices, FTArray<IndexType>* indices) : FTMeshData(vertices), indices_(indices) {
		indices_->retain();
	}

	virtual ~FTIndexedMeshData() {
		indices_->release();
	}

	FTArray<IndexType>* getIndices() const {
		return indices_;
	}

protected:
	FTArray<IndexType>* indices_;
};

template <typename VertexType, typename IndexType>
class FTIndexedMesh : public FTMesh<VertexType> {
public:
	explicit FTIndexedMesh(FTVertexShaderProgram* shader_program) : FTMesh(shader_program) {

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

	void loadIndexedMeshData(const FTIndexedMeshData<VertexType, IndexType>* data, bool is_static, bool cleanup = true) {
		loadMeshData(data, is_static, false);

		num_indices_ = data->getIndices()->size();
		max_num_inidices_ = num_indices_;
		glGenBuffers(1, &index_buffer_id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);


		glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_num_inidices_ * sizeof(IndexType), data->getIndices()->getData(), is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

		if (cleanup) {
			glBindVertexArray(0);
			is_loaded_ = true;
		}
	}

	virtual void setIndexedMeshData(const FTIndexedMeshData<VertexType, IndexType>* data) {
		setMeshData(data);
		// Update mesh data
		if (max_num_inidices_ >= data->getIndices()->size()) {
			num_indices_ = data->getIndices()->size();
			// We can update the existing buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, num_indices_ * sizeof(IndexType), data->getIndices()->getData());
		} else {
			num_indices_ = data->getIndices()->size();
			max_num_inidices_ = num_indices_;
			// We must re-create the buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_ * sizeof(IndexType), data->getIndices()->getData(), GL_DYNAMIC_DRAW);
		}
	}

	virtual ~FTIndexedMesh() {
		glDeleteBuffers(1, &index_buffer_id_);
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
	virtual void loadMeshData(const FTMeshData<VertexType>* data, bool is_static, bool cleanup) override {
		FTMesh::loadMeshData(data, is_static, cleanup);
	}

	virtual void setMeshData(const FTMeshData<VertexType>* data) override {
		FTMesh::setMeshData(data);
	}

	virtual void loadEmptyMesh(GLuint vertex_count, bool cleanup) override {
		FTMesh::loadEmptyMesh(vertex_count, cleanup);
	}
};
