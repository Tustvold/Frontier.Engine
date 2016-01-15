#pragma once
#include <Frontier.h>

class FTCamera;
class FTNode;
    
class FTBoundingShape {
public:
    FTBoundingShape() : node_(nullptr), dirty_(false) {

    }

   virtual ~FTBoundingShape() {
       
   }

   void onAddedToNode(FTNode* node) {
       FTAssert(node_ == nullptr, "Bounding Shape already added to node");
       node_ = node;
    }

   // Update internal state
   virtual void visit() {
       dirty_ = false;
   }

    virtual bool containsMousePosition(const glm::vec2& mouse_pos);

    // Return true if this bounding shape contains the provided position in local coordinates
   virtual bool containsLocalPosition(const glm::vec3& position) {
       return false;
   }

   virtual bool visibleInCamera(FTCamera* camera) {
       return true;
   }

   virtual glm::vec3 getLayoutSize() const {
       return glm::vec3();
   }

   // Compute the offset in local coordinates for a given anchor point
   virtual glm::vec3 computeLocalOffset(const glm::vec3& anchor_point) {
       return glm::vec3();
   }

   bool getDirty() const {
       return dirty_;
   }

   void computeWorldAABFromLocalAAB(const glm::vec3& local_origin ,const glm::vec3& local_size, glm::vec3& world_aab_center, glm::vec3& world_aab_half_extents) const;


protected:
    FTNode* node_;
    bool dirty_;
};