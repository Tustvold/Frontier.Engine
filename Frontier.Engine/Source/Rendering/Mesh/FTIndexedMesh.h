#pragma once
#include <GL/glew.h>
#include "FTMesh.h"
#include <FTIndexedArray.h>

template <typename VertexType, typename IndexType>
class FTIndexedMeshData : public FTMeshData<VertexType> {
public:

	FTIndexedMeshData(size_t vertexCount, size_t indexCount) : FTMeshData(vertexCount), indices_(new FTIndexedArray<IndexType>(indexCount)) {
	}

	FTIndexedMeshData(FTIndexedArray<VertexType>* vertices, FTIndexedArray<IndexType>* indices) : FTMeshData(vertices), indices_(indices) {
		indices_->retain();
	}

	virtual ~FTIndexedMeshData() {
		indices_->release();
	}

	FTIndexedArray<IndexType>* getIndices() const {
		return indices_;
	}

protected:
	FTIndexedArray<IndexType>* indices_;
};

template <typename VertexType, typename IndexType>
class FTIndexedMesh : public FTMesh<VertexType> {
public:
	explicit FTIndexedMesh(FTTransform* transform, FTVertexShaderProgram* shader_program) : FTMesh(transform, shader_program)  {
		
	}

	void loadIndexedMeshData(const FTIndexedMeshData<VertexType, IndexType>* data, bool cleanup = true) {
		loadMeshData(data, false);
		num_indices_ = (GLint)data->getIndices()->getSize();
		glGenBuffers(1, &index_buffer_id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);


		glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_ * sizeof(IndexType), data->getIndices()->getData(), GL_STATIC_DRAW);


		if (cleanup)
			glBindVertexArray(0);
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

	GLint num_indices_;
	GLuint index_buffer_id_;

private:
	virtual void loadMeshData(const FTMeshData<VertexType>* data, bool cleanup) override {
		FTMesh::loadMeshData(data, cleanup);
	}
};
