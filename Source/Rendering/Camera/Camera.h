﻿#pragma once
#include <Engine.h>
#include <Frontier.h>
#include <Util/Rect.h>
#include <Event/EventManager.h>
#include <Event/Window/WindowEventDispatcher.h>
#include "Raycast.h"
#include <Util/Math.h>

NS_FT_BEGIN

class Node;

// The base class for all cameras
// Contains properties and functionality common to all cameras
class Camera {
public:
    Camera();

    virtual ~Camera() {
        Engine::getEventManager()->unregisterDelegate<WindowEventDispatcher>(this, &Camera::screensizeChangedEvent);
    }

    const glm::mat4& getViewMatrix() const {
        return view_matrix_;
    }

    const glm::mat4& getProjectionMatrix() const {
        return projection_matrix_;
    }

    const glm::mat4& getViewProjectionMatrix() const {
        return view_projection_matrix_;
    }

    virtual void visit() = 0;

    void preDraw() const;

    virtual bool testBoundingBox(const glm::vec3& aab_origin, const glm::vec3& aab_half_extents) const = 0;

    // Set the draw rect of this camera relative to the size of the screen
    void setDrawRectRelative(const Rect<float>& view_rect) {
        draw_rect_relative_ = view_rect;
        auto screensize = Engine::getWindowSize();
        screensizeChanged((float)screensize.x, (float)screensize.y);
    }

    void setClippingPlanes(float near_plane, float far_plane) {
        projection_matrix_dirty_ = true;
        near_clipping_plane_ = near_plane;
        far_clipping_plane_ = far_plane;
    }

    virtual Raycast generateRaycastForMousePos(double x, double y) = 0;

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

    glm::vec3 convertClipSpaceToNDC(const glm::vec4& clipspace) const {
        return glm::vec3(clipspace.x, clipspace.y, clipspace.z) / clipspace.w;
    }

    glm::vec3 convertNDCToScreenSpace(const glm::vec3& ndc) const {
        float x = (ndc.x + 1) * draw_rect_abs_.width_ / 2.0f + draw_rect_abs_.x_;
        float y = (ndc.y + 1) * draw_rect_abs_.height_ / 2.0f + draw_rect_abs_.y_;
        return glm::vec3(x, y, ndc.z);
    }

    glm::vec3 convertClipSpaceToScreenSpace(const glm::vec4& clipSpace) const {
        return convertNDCToScreenSpace(convertClipSpaceToNDC(clipSpace));
    }

    glm::vec3 convertScreenSpaceToNDC(const glm::vec3& screenSpace) const {
        auto tmp = screenSpace;
        tmp.x = (tmp.x - draw_rect_abs_.x_) / (float)draw_rect_abs_.width_;
        tmp.y = (tmp.y - draw_rect_abs_.y_) / (float)draw_rect_abs_.height_;
        tmp = tmp * 2.0f - 1.0f;

        return tmp;
    }

    const glm::vec3& getPosition() const {
        return position_;
    }

protected:
    glm::mat4 projection_matrix_;
    glm::mat4 view_matrix_;
    glm::mat4 view_projection_matrix_;
    glm::mat4 view_projection_matrix_inv_;

    glm::vec3 position_;

    Rect<float> draw_rect_relative_;
    Rect<int> draw_rect_abs_;
    float near_clipping_plane_;
    float far_clipping_plane_;
    bool projection_matrix_dirty_;
    bool view_matrix_dirty_;
    bool view_projection_matrix_inv_dirty_;
    bool scissor_enabled_;
    bool depth_test_enabled_;
    bool cull_face_enabled_;

    // The absolute pixel rect of the View managing this camera
    void setDrawRectAbs(const Rect<int>& screen_rect) {
        draw_rect_abs_ = screen_rect;
        projection_matrix_dirty_ = true;
    }

    void screensizeChangedEvent(const WindowResizeEvent& event) {
        screensizeChanged((float)event.width_, (float)event.height_);
    }

    void screensizeChanged(float width, float height) {
        setDrawRectAbs(Rect<int>((int)(draw_rect_relative_.x_ * width), (int)(draw_rect_relative_.y_ * height), (int)(draw_rect_relative_.width_ * width), (int)(draw_rect_relative_.height_ * height)));
    }
};

NS_FT_END