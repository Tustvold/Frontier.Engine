#pragma once
#include <Rendering/Scene/FTNode.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>

class FTLabel : public FTIndexedTexturedMesh<FTVertexColorTexture,uint16_t> {
public:
	FTLabel(const char* fontpath, const wchar_t* text, int fontsize);
	virtual ~FTLabel();

	void setPosition(const glm::vec2& pos);

	const glm::vec2& getSize() {
		return label_size_;
	}
protected:
	glm::vec2 label_size_;
};
