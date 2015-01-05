#pragma once
#include <FTObject.h>
#include <GL/glew.h>
#include <FTIndexedArray.h>
#include <Rendering/Scene/FTNode.h>
#include <FTArray.h>
#include <Rendering/Textures/FTTexture.h>

template <typename VertexType>
class FTMeshData : public FTObject {
public:
	explicit FTMeshData(size_t vertexCount) : vertices_(new FTIndexedArray<VertexType>(vertexCount)) {

	}

	explicit FTMeshData(FTIndexedArray<VertexType>* vertices) : vertices_(vertices) {
		vertices_->retain();
	}

	virtual ~FTMeshData() {
		vertices_->release();
	}

	FTIndexedArray<VertexType>* getVertices() const {
		return vertices_;
	}

private:
	FTIndexedArray<VertexType>* vertices_;
};

// Renders an attached mesh - note it does not bind a shader program nor update any matrices
template <typename VertexType>
class FTMesh : public FTNode {
public:
	
	explicit FTMesh(FTTransform* transform, FTVertexShaderProgram* shader_program) : FTNode(transform,shader_program), render_wireframe_(false), is_loaded_(false) {
		
	}

	// Cleanup specifies whether it should unbind the VOA after it has finished creating it
	virtual void loadMeshData(const FTMeshData<VertexType>* data, bool cleanup) {
		// TODO Support changing mesh data during runtime
		FTAssert(!is_loaded_, "FTMesh already loaded!");

		num_vertices_ = (GLint)data->getVertices()->getSize();
		glGenVertexArrays(1, &vertex_array_id_);
		glBindVertexArray(vertex_array_id_);

		glGenBuffers(1, &vertex_buffer_id_);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
		glBufferData(GL_ARRAY_BUFFER, num_vertices_ * sizeof(VertexType), (float*)(data->getVertices()->getData()), GL_STATIC_DRAW);


		/*glVertexAttribPointer(
			0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
			sizeof(VertexType) / sizeof(float), // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);*/

		FTVertexDescriptor<VertexType>::bind();

		if (cleanup)
			glBindVertexArray(0);

		is_loaded_ = true;
	}

	virtual ~FTMesh() {
		//delete[] vertices_;
		if (!is_loaded_)
			return;
		glDeleteVertexArrays(1, &vertex_buffer_id_);
		glDeleteVertexArrays(1, &vertex_array_id_);
	}

	virtual void pre_draw() override {
		if (!is_loaded_) {
			FTLogError("Trying to mesh before calling load!");
			return;
		}

		if (render_wireframe_)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glBindVertexArray(vertex_array_id_);
	}

	virtual void draw() override {
		glDrawArrays(GL_TRIANGLES, 0, num_vertices_);	
	}

	virtual void post_draw() override {
		glBindVertexArray(0);

		if (render_wireframe_)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void setRenderWireframe(bool render_wireframe) {
		render_wireframe_ = render_wireframe;
	}

protected:

	GLuint vertex_array_id_;
	GLuint vertex_buffer_id_;
	GLint num_vertices_;
	bool render_wireframe_;
	bool is_loaded_;
	int vertex_components_;
};
