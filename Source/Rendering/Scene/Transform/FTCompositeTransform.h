#include <Rendering/Scene/Transform/FTTransform.h>

// Represents a composite transform
// The transform is calculated as transform1*transform2*transform3
// The normal order of multiplication is translation*scale*rotation
template <typename T1, typename T2>
class FTCompositeTransform : public FTTransform {

	FTCompositeTransform(std::unique_ptr<T1>& transform1, std::unique_ptr<T2>& transform2): transform1_(std::move(transform1)),transform2_(std::move(transform2)) {

	}

	virtual ~FTCompositeTransform() {

	}

	bool getDirty() override {
		return transform1_->getDirty() || transform2_->getDirty();
	}

	void updateMatrices() override {
		if (getDirty()) {
			transform1_->updateMatrices();
			transform2_->updateMatrices();
			transform_matrix = transform1_->getTransformMatrix() * transform2_->getTransformMatrix();
		}
	}

protected:
	std::unique_ptr<T1> transform1_;
	std::unique_ptr<T2> transform2_;
};

template <typename T1, typename T2, typename T3>
class FTCompositeTransform3 : public FTTransform {
public:

	FTCompositeTransform3() :
		transform1_(new T1()),
		transform2_(new T2()),
		transform3_(new T3()) {
	}

	virtual ~FTCompositeTransform3() {

	}

	bool getDirty() override {
		return transform1_->getDirty() || transform2_->getDirty() || transform3_->getDirty();
	}

	void updateMatrices() override {
		if (getDirty()) {
			transform1_->updateMatrices();
			transform2_->updateMatrices();
			transform3_->updateMatrices();
			transform_matrix = transform1_->getTransformMatrix() * transform2_->getTransformMatrix() * transform3_->getTransformMatrix();
		}
	}

protected:
	std::unique_ptr<T1> transform1_;
	std::unique_ptr<T2> transform2_;
	std::unique_ptr<T3> transform3_;
};
