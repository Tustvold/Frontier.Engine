#include <Rendering/Scene/Transform/FTTransform.h>

// Represents a composite transform
// The transform is calculated as transform1*transform2*transform3
// The normal order of multiplication is translation*scale*rotation
template <typename T1, typename T2> class FTCompositeTransform : public FTTransform {
	
	FTCompositeTransform(T1* transform1, T2* transform2): transform1_(transform1),transform2_(transform2) {
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
			transform1_->updateMatrices();
			transform2_->updateMatrices();
			transform_matrix = transform1_->getTransformMatrix()*transform2_->getTransformMatrix();
		}
	}

protected:
	T1* transform1_;
	T2* transform2_;
};

template <typename T1, typename T2, typename T3> class FTCompositeTransform3 : public FTTransform {
public:

	FTCompositeTransform3(T1* transform1, T2* transform2, T3* transform3) : transform1_(transform1), transform2_(transform2), transform3_(transform3) {
		transform1_->retain();
		transform2_->retain();
		transform3_->retain();
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
			transform1_->updateMatrices();
			transform2_->updateMatrices();
			transform3_->updateMatrices();
			transform_matrix = transform1_->getTransformMatrix()*transform2_->getTransformMatrix()*transform3_->getTransformMatrix();
		}
	}

protected:
	T1* transform1_;
	T2* transform2_;
	T3* transform3_;
};