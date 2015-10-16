#include "FTCamera2D.h"
#include <Rendering/Scene/FTNode.h>

void FTCamera2D::preDraw() {
    FTCamera::preDraw();
    if (projection_matrix_dirty_) {
        projection_matrix_ = glm::ortho<float>(0, (float)draw_rect_abs_.width_, 0, (float)draw_rect_abs_.height_, near_clipping_plane_, far_clipping_plane_);
    }

    if (view_matrix_dirty_ || projection_matrix_dirty_) {
        view_matrix_dirty_ = false;
        projection_matrix_dirty_ = false;
        view_projection_matrix_ = projection_matrix_.getData() * view_matrix_.getData();
        view_projection_matrix_inv_dirty_ = true;
    }
}

bool FTCamera2D::testNodeVisible(const FTNode* node) const {
    auto& center = node->getAABCenter();
    auto& half_extents = node->getAABHalfExtents();

    return center.x - half_extents.x <= draw_rect_abs_.x_ + draw_rect_abs_.width_ && center.x + half_extents.x >= draw_rect_abs_.x_ && center.y - half_extents.y <= draw_rect_abs_.y_ + draw_rect_abs_.height_ && center.y + half_extents.y >= draw_rect_abs_.y_;
}
