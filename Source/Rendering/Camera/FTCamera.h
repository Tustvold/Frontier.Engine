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
    FTCamera() : draw_rect_relative_(0, 0, 1, 1), near_clipping_plane_(0.1f), far_clipping_plane_(10000.0f), projection_matrix_dirty_(true), view_matrix_dirty_(true), view_projection_matrix_inv_dirty_(true) {
        auto screensize = FTEngine::getWindowSize();
        draw_rect_abs_ = FTRect<int>(0, 0, screensize.x, screensize.y);
        FTEngine::getEventManager()->registerDelegate<FTWindowEventDispatcher>(this, &FTCamera::screensizeChanged);
    }

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

    virtual void preDraw() {
        glScissor(draw_rect_abs_.x_, draw_rect_abs_.y_, draw_rect_abs_.width_, draw_rect_abs_.height_);
        glViewport(draw_rect_abs_.x_, draw_rect_abs_.y_, draw_rect_abs_.width_, draw_rect_abs_.height_);
    }

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

    glm::vec3 unProject(const glm::vec3& mouse_pos) const {
        auto screensize = FTEngine::getWindowSize();
        glm::vec4 tmp = glm::vec4(mouse_pos, 1);
        tmp.x = (tmp.x - draw_rect_abs_.x_) / (float)draw_rect_abs_.width_;
        tmp.y = (tmp.y - draw_rect_abs_.y_) / (float)draw_rect_abs_.height_;
        tmp = tmp * 2.0f - 1.0f;

        glm::vec4 obj = view_projection_matrix_inv_.getConstData() * tmp;
        obj /= obj.w;

        return glm::vec3(obj);
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
