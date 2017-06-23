#include "FTCamera.h"

NS_FT_BEGIN

FTCamera::FTCamera() : draw_rect_relative_(0, 0, 1, 1),
                       near_clipping_plane_(0.1f),
                       far_clipping_plane_(10000.0f),
                       projection_matrix_dirty_(true),
                       view_matrix_dirty_(true),
                       view_projection_matrix_inv_dirty_(true),
                       scissor_enabled_(false),
                       depth_test_enabled_(false),
                       cull_face_enabled_(false) {
    auto screensize = FTEngine::getWindowSize();
    draw_rect_abs_ = FTRect<int>(0, 0, screensize.x, screensize.y);
    FTEngine::getEventManager()->registerDelegate<FTWindowEventDispatcher>(this, &FTCamera::screensizeChangedEvent);
}

void FTCamera::preDraw() const {
    glViewport(draw_rect_abs_.x_, draw_rect_abs_.y_, draw_rect_abs_.width_, draw_rect_abs_.height_);

    if (scissor_enabled_) {
        glEnable(GL_SCISSOR_TEST);
        glScissor(draw_rect_abs_.x_, draw_rect_abs_.y_, draw_rect_abs_.width_, draw_rect_abs_.height_);
    } else
        glDisable(GL_SCISSOR_TEST);

    if (depth_test_enabled_)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    if (cull_face_enabled_)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}

NS_FT_END