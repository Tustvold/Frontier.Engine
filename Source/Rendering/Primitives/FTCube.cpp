#include "FTCube.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>

FTCube::FTCube(const glm::vec3 face_colors[6]) : FTIndexedMesh(FTShaderCache::getSharedInstance()->getShaderProgram<FTVertexColorShaderProgram>()), transform_(new FTTransformPositionScaleRotation()) {

	auto data = new FTIndexedMeshData<FTVertexColor, uint16_t>(4*6, 36);

	auto vertices = data->getVertices();
	auto indices = data->getIndices();

	FTVertexColor vertex;
	int cur_index = 0;
	vertex.color_ = face_colors[0];

	vertex.position_ = glm::vec3(1, 0, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 0, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 1, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 1, 1);
	vertices->add(vertex);

	indices->add(cur_index);
	indices->add(cur_index + 2);
	indices->add(cur_index + 1);
	indices->add(cur_index + 1);
	indices->add(cur_index + 2);
	indices->add(cur_index + 3);

	cur_index += 4;

	vertex.color_ = face_colors[1];
	vertex.position_ = glm::vec3(0, 0, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 1, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 0, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 1, 1);
	vertices->add(vertex);

	indices->add(cur_index);
	indices->add(cur_index + 2);
	indices->add(cur_index + 1);
	indices->add(cur_index + 1);
	indices->add(cur_index + 2);
	indices->add(cur_index + 3);


	cur_index += 4;

	vertex.color_ = face_colors[2];
	vertex.position_ = glm::vec3(0, 1, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 1, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 1, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 1, 1);
	vertices->add(vertex);

	indices->add(cur_index);
	indices->add(cur_index + 2);
	indices->add(cur_index + 1);
	indices->add(cur_index + 1);
	indices->add(cur_index + 2);
	indices->add(cur_index + 3);


	cur_index += 4;

	vertex.color_ = face_colors[3];
	vertex.position_ = glm::vec3(0, 0, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 0, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 0, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 0, 1);
	vertices->add(vertex);

	indices->add(cur_index);
	indices->add(cur_index + 1);
	indices->add(cur_index + 2);
	indices->add(cur_index + 1);
	indices->add(cur_index + 3);
	indices->add(cur_index + 2);

	cur_index += 4;

	vertex.color_ = face_colors[4];
	vertex.position_ = glm::vec3(0, 0, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 1, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 0, 1);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 1, 1);
	vertices->add(vertex);

	indices->add(cur_index);
	indices->add(cur_index + 2);
	indices->add(cur_index + 1);
	indices->add(cur_index + 1);
	indices->add(cur_index + 2);
	indices->add(cur_index + 3);


	cur_index += 4;

	vertex.color_ = face_colors[5];
	vertex.position_ = glm::vec3(0, 0, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 0, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(0, 1, 0);
	vertices->add(vertex);
	vertex.position_ = glm::vec3(1, 1, 0);
	vertices->add(vertex);

	indices->add(cur_index);
	indices->add(cur_index + 2);
	indices->add(cur_index + 1);
	indices->add(cur_index + 1);
	indices->add(cur_index + 2);
	indices->add(cur_index + 3);

	loadIndexedMeshData(data, true);

	data->release();
}

FTCube::~FTCube() {
	transform_->release();
}
