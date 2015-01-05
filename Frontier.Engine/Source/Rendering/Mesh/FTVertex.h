#include <glm/glm.hpp>
#include <GL/glew.h>

struct FTVertex {
	glm::vec3 position_;
	FTVertex() {
		
	}
	
	explicit FTVertex(const glm::vec3& position) : position_(position) {
		
	}
};

struct FTVertexColor {
	glm::vec3 position_;
	glm::vec3 color_;
	FTVertexColor() {
		
	}

	FTVertexColor(const glm::vec3& position, const glm::vec3 color) : position_(position), color_(color) {

	}
};

struct FTVertexTexture {
	glm::vec3 position_;
	glm::vec2 uv_;
	FTVertexTexture() {
		
	}

	FTVertexTexture(const glm::vec3& position, const glm::vec2 uv) : position_(position), uv_(uv) {

	}
};

struct FTVertexColorTexture {
	glm::vec3 position_;
	glm::vec3 color_;
	glm::vec2 uv_;

	FTVertexColorTexture() {

	}
};


enum {
	kVertexAttribLocation = 0,
	kColorAttribLocation = 1,
	kUVAttribLocation = 2
};

template <typename VertexType> class FTVertexDescriptor {
public:
	static void bind() {
		FTAssert(false,"Trying to bind unsupported vertex type");
	};

protected:
	FTVertexDescriptor() {
		
	}

	~FTVertexDescriptor() {
	}
};

template <> class FTVertexDescriptor<FTVertex> {
	static void bind() {
		glVertexAttribPointer(
			kVertexAttribLocation, // attribute
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			sizeof(FTVertex), // stride
			(void*)0 // array buffer offset
			);
		glEnableVertexAttribArray(kVertexAttribLocation);
	};
};

template <> class FTVertexDescriptor<FTVertexColor> {
public:
	static void bind() {
		glVertexAttribPointer(
			kVertexAttribLocation, 
			3,
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
			(void*)(3 * sizeof(float))
			);
		glEnableVertexAttribArray(kVertexAttribLocation);
		glEnableVertexAttribArray(kColorAttribLocation);
	};
};

template <> class FTVertexDescriptor<FTVertexTexture> {
public:
	static void bind() {
		glVertexAttribPointer(
			kVertexAttribLocation,
			3,
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
			(void*)(3 * sizeof(float))
			);

		glEnableVertexAttribArray(kVertexAttribLocation);
		glEnableVertexAttribArray(kUVAttribLocation);
	};
};


template <> class FTVertexDescriptor<FTVertexColorTexture> {
public:
	static void bind() {
		glVertexAttribPointer(
			kVertexAttribLocation,
			3,
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
			(void*)(3 * sizeof(float))
			);

		glVertexAttribPointer(
			kUVAttribLocation,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(FTVertexColorTexture),
			(void*)(6 * sizeof(float))
			);

		glEnableVertexAttribArray(kVertexAttribLocation);
		glEnableVertexAttribArray(kUVAttribLocation);
		glEnableVertexAttribArray(kColorAttribLocation);
	};
};