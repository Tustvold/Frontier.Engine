#pragma once
#include <Frontier.h>
#include <Rendering/FTShaderNode.h>
#include <Util/FTMath.h>
#include <Rendering/Mesh/FTVertex.h>


template <typename VertexType>
class FTMeshData {
public:

    FTMeshData() : vertex_count_(0) {

    }

    explicit FTMeshData(size_t vertex_count) : vertex_count_(0) {
        vertices_.reserve(vertex_count);
    }

    explicit FTMeshData(std::vector<VertexType>& vertices) : vertex_count_(0) {
        vertices_ = std::move(vertices);
    }

    virtual ~FTMeshData() {
    }

    std::vector<VertexType>& getVertices() {
        return vertices_;
    }

    void setVertexCount(size_t count) {
        FTAssert(vertices_.capacity() >= count, "Invalid Vertex Count");
        vertex_count_ = count;
    }

    size_t getVertexCount() {
        if (vertex_count_ != 0)
            return vertex_count_;
        return vertices_.size();
    }

private:
    std::vector<VertexType> vertices_;
    size_t vertex_count_;
};

template <typename ShaderProgram, typename VertexType>
class FTMesh : public FTShaderNode<ShaderProgram> {
public:

    FTMesh() : vertex_array_id_(0), vertex_buffer_id_(0), num_vertices_(0), max_num_vertices_(0), primitive_type_(GL_TRIANGLES), render_wireframe_(false), is_loaded_(false), is_static_(true) {

    }

    virtual ~FTMesh() {
        //delete[] vertices_;
        if (!is_loaded_)
            return;
        glDeleteVertexArrays(1, &vertex_buffer_id_);
        glDeleteVertexArrays(1, &vertex_array_id_);
    }

    // Creates a VBO for the vertices of the specified size
    // The mesh can then be populated using the setMeshData functions
    virtual void loadEmptyMesh(GLuint vertex_count, bool cleanup = true) {
        FTAssert(!is_loaded_, "Trying to load mesh data for already loaded mesh");
        is_static_ = false;
        max_num_vertices_ = vertex_count;
        num_vertices_ = 0;

        glGenVertexArrays(1, &vertex_array_id_);
        glBindVertexArray(vertex_array_id_);

        glGenBuffers(1, &vertex_buffer_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

        glBufferData(GL_ARRAY_BUFFER, max_num_vertices_ * sizeof(VertexType), nullptr, GL_DYNAMIC_DRAW);

        VertexType::bind();

        if (cleanup) {
            glBindVertexArray(0);
            is_loaded_ = true;
        }
    }

    // Loads a mesh described by an FTMesh object
    // Cleanup specifies whether it should unbind the VAO after it has finished creating it
    virtual void loadMeshData(FTMeshData<VertexType>* data, bool is_static, bool cleanup = true) {
        FTAssert(!is_loaded_, "Trying to load mesh data for already loaded mesh");
        is_static_ = is_static;

        num_vertices_ = (GLuint)data->getVertexCount();
        max_num_vertices_ = (GLuint)data->getVertexCount();

        glGenVertexArrays(1, &vertex_array_id_);


        glBindVertexArray(vertex_array_id_);

        glGenBuffers(1, &vertex_buffer_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

        glBufferData(GL_ARRAY_BUFFER, max_num_vertices_ * sizeof(VertexType), (float*)(data->getVertices().data()), is_static_ ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        VertexType::bind();

        if (cleanup) {
            glBindVertexArray(0);
            is_loaded_ = true;
        }
    }

    void modifyVertices(GLuint start_index, GLuint num_vertices, const VertexType* data) {
        FTAssert(is_loaded_, "Trying to set mesh data for unloaded mesh");
        FTAssert(!is_static_, "Trying to edit mesh data for static mesh");
        FTAssert(start_index + num_vertices <= max_num_vertices_, "Maximum buffer size exceeded!");

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);


        glBufferSubData(GL_ARRAY_BUFFER, start_index * sizeof(VertexType), num_vertices * sizeof(VertexType), data);
        num_vertices_ = FTMAX(start_index + num_vertices, num_vertices_);
    }

    void resizeVertexBuffer(size_t num_vertices, const VertexType* data) {
        FTAssert(is_loaded_, "Trying to set mesh data for unloaded mesh");
        FTAssert(!is_static_, "Trying to edit mesh data for static mesh");
        max_num_vertices_ = (GLuint)num_vertices;
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
        glBufferData(GL_ARRAY_BUFFER, max_num_vertices_ * sizeof(VertexType), data, GL_DYNAMIC_DRAW);
    }

    virtual void setMeshData(FTMeshData<VertexType>* data) {
        FTAssert(is_loaded_, "Trying to set mesh data for unloaded mesh - consider using LoadMeshData instead");

        // Update mesh data
        if (max_num_vertices_ >= data->getVertexCount()) {
            num_vertices_ = (GLuint)data->getVertexCount();
            // We can update the existing buffer
            modifyVertices(0, num_vertices_, data->getVertices().data());
        } else {
            num_vertices_ = (GLuint)data->getVertexCount();
            // We must re-create the buffer
            resizeVertexBuffer(num_vertices_, data->getVertices().data());
        }
    }

    virtual void pre_draw(const glm::mat4& mvp) override {
        FTShaderNode<ShaderProgram>::pre_draw(mvp);
        if (!is_loaded_) {
            FTLogError("Trying to draw mesh before calling load!");
            return;
        }

        if (render_wireframe_)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindVertexArray(vertex_array_id_);
    }

    virtual void draw() override {
        glDrawArrays(primitive_type_, 0, num_vertices_);
    }

    virtual void post_draw() override {
        FTShaderNode<ShaderProgram>::post_draw();
        glBindVertexArray(0);

        if (render_wireframe_)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void setRenderWireframe(bool render_wireframe) {
        render_wireframe_ = render_wireframe;
    }

    void setPrimitiveType(GLenum type) {
        primitive_type_ = type;
    }

    GLuint getVertexCapacity() const {
        return max_num_vertices_;
    }

    GLuint getNumVertices() const {
        return num_vertices_;
    }

protected:

    GLuint vertex_array_id_;
    GLuint vertex_buffer_id_;

    // The number of vertices the mesh actually contains
    GLuint num_vertices_;

    // The number of vertices the VBO has space for
    GLuint max_num_vertices_;
    GLenum primitive_type_;

    bool render_wireframe_;
    bool is_loaded_;
    bool is_static_;
};
