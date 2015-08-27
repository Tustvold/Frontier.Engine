#pragma once
#include <Rendering/Scene/FTNode.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Rendering/Scene/Transform/FTTransformPosition.h>
#include "FTFont.h"
#include <Rendering/Shader/FTFontShader.h>

class FTLabel : public FTIndexedTexturedMesh<FTTransformPosition, FTFontShader, FTVertexColorTexture, uint16_t> {
public:
	FTLabel(const std::basic_string<char>& fontpath, const std::basic_string<wchar_t>& text, int font_size, bool is_mutable = false);
	virtual ~FTLabel();

	void setPosition(const glm::vec2& pos);

	void setString(const wchar_t* text);

	const glm::vec2& getSize() {
		return label_size_;
	}

	void setAnchorPoint(const glm::vec2& anchor_point) {
		anchor_point_ = anchor_point;
		setPosition(position_);
	}

protected:
	glm::vec2 anchor_point_;
	glm::vec2 position_;
	glm::vec2 label_size_;
	std::shared_ptr<FTIndexedMeshData<FTVertexColorTexture, uint16_t>> mesh_data_;
	std::shared_ptr<FTFont> font_;
	std::basic_string<wchar_t> text_;

	bool is_mutable_;
	int font_size_;
};
