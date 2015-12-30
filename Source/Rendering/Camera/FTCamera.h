#pragma once
#include <Frontier.h>
#include <Util/FTRect.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Window/FTWindowEventDispatcher.h>
#include <Util/FTAlignedData.h>
#include "FTRaycast.h"
#include <Util/FTMath.h>

class FTNode;

// The base class for all cameras
// Contains properties and functionality common to all cameras
class FTCamera {
public:
    FTCamera();

    virtual ~FTCamera() {
        FTEngine::getEventManager()->unregisterDelegate<FTWindowEventDispatcher>(this, &FTCamera::screensizeChanged);
    }

    const glm::mat4& getViewMatrix() const {
        return view_matrix_.getConstData();
    }

    const glm::mat4& getProjectionMatrix() const {
        return projection_matrix_.getConstData();
    }

    const glm::mat4& getViewProjectionMatrix() const {
        return view_projection_matrix_.getConstData();
    }

    virtual void visit() = 0;

    void preDraw() const;

    virtual bool testNodeVisible(const FTNode* node) const = 0;

    // Set the draw rect of this camera relative to the size of the screen
    void setDrawRectRelative(const FTRect<float>& view_rect) {
        draw_rect_relative_ = view_rect;
        auto screensize = FTEngine::getWindowSize();
        screensizeChanged((float)screensize.x, (float)screensize.y);
    }

    void setClippingPlanes(float near_plane, float far_plane) {
        projection_matrix_dirty_ = true;
        near_clipping_plane_ = near_plane;
        far_clipping_plane_ = far_plane;
    }

    virtual FTRaycast generateRaycastForMousePos(double x, double y) = 0;

    virtual glm::vec3 unProject(const glm::vec3& mouse_pos) = 0;

    void setScissorEnabled(bool value) {
        scissor_enabled_ = value;
    }

    void setDepthTestEnabled(bool value) {
        depth_test_enabled_ = value;
    }

    void setCullFaceEnabled(bool value) {
        cull_face_enabled_ = value;
    }

protected:
    FTAlignedData<glm::mat4> projection_matrix_;
    FTAlignedData<glm::mat4> view_matrix_;
    FTAlignedData<glm::mat4> view_projection_matrix_;
    FTAlignedData<glm::mat4> view_projection_matrix_inv_;

    FTRect<float> draw_rect_relative_;
    FTRect<int> draw_rect_abs_;
    float near_clipping_plane_;
    float far_clipping_plane_;
    bool projection_matrix_dirty_;
    bool view_matrix_dirty_;
    bool view_projection_matrix_inv_dirty_;
    bool scissor_enabled_;
    bool depth_test_enabled_;
    bool cull_face_enabled_;

    // The absolute pixel rect of the FTView managing this camera
    void setDrawRectAbs(const FTRect<int>& screen_rect) {
        draw_rect_abs_ = screen_rect;
        projection_matrix_dirty_ = true;
    }

    void screensizeChanged(float width, float height) {
        setDrawRectAbs(FTRect<int>((int)(draw_rect_relative_.x_ * width), (int)(draw_rect_relative_.y_ * height), (int)(draw_rect_relative_.width_ * width), (int)(draw_rect_relative_.height_ * height)));
    }

    void screensizeChanged(const FTWindowResizeEvent& event) {
        screensizeChanged((float)event.width_, (float)event.height_);
    }
};