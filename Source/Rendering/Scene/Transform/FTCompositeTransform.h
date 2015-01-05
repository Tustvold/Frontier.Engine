#include <Rendering/Scene/Transform/FTTransform.h>

// Represents a composite transform
// The transform is calculated as transform1*transform2*transform3
// The normal order of multiplication is translation*scale*rotation
class FTCompositeTransform : public FTTransform {
	
	FTCompositeTransform(FTTransform* transform1, FTTransform* transform2): transform1_(transform1),transform2_(transform2) {
		transform1_->retain();
		transform2_->retain();
	}

	virtual ~FTCompositeTransform() {
		transform1_->release();
		transform2_->release();
	}

	bool getDirty() override {
		return transform1_->getDirty() || transform2_->getDirty();
	}

	void updateMatrices() override {
		if (getDirty()) {
			transform_matrix = transform1_->getTransformMatrix()*transform2_->getTransformMatrix();
		}
	}

protected:
	FTTransform* transform1_;
	FTTransform* transform2_;
};

class FTCompositeTransform3 : public FTTransform {

	FTCompositeTransform3(FTTransform* transform1, FTTransform* transform2, FTTransform* transform3) : transform1_(transform1), transform2_(transform2), transform3_(transform3) {
		transform1_->retain();
		transform2_->retain();
		transform3->retain();
	}

	virtual ~FTCompositeTransform3() {
		transform1_->release();
		transform2_->release();
		transform3_->release();
	}

	bool getDirty() override {
		return transform1_->getDirty() || transform2_->getDirty() || transform3_->getDirty();
	}

	void updateMatrices() override {
		if (getDirty()) {
			transform_matrix = transform1_->getTransformMatrix()*transform2_->getTransformMatrix()*transform3_->getTransformMatrix();
		}
	}

protected:
	FTTransform* transform1_;
	FTTransform* transform2_;
	FTTransform* transform3_;
};