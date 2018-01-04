/*
    Copyright 2015 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef Q_CIRCLE_COLLIDER_H
#define Q_CIRCLE_COLLIDER_H

#include "Q_Collider2D.h"
#include "duVector2.h"

namespace Quantum2D {
class CircleCollider : public Collider2D {
 public:
  CircleCollider(
      const BodyList &bodylist, body2d_id body, void *parent,
      const std::function<void(void *other)> &onCollision, tQ_pos radius,
      const Diamond::Vector2<tQ_pos> &center = Diamond::Vector2<tQ_pos>(0, 0),
      QLayer layer = 0);

  /**
   Get the radius of this circle in the parent rigidbody's local space.
  */
  tQ_pos getRadius() const { return radius; }

  /**
   Get the scaled radius of this circle in world space.
  */
  tQ_pos getWorldRadius() const { return world_radius; }

  /**
   Get the center position of this circle in the parent rigidbody's local space.
  */
  const Diamond::Vector2<tQ_pos> &getCenter() const { return center; }

  /**
   Get the current coordinates of this circle's center in world space.
  */
  const Diamond::Vector2<tQ_pos> &getWorldPos() const { return world_pos; }

  void setRadius(tQ_pos radius) { this->radius = radius; }

  void setCenter(const Diamond::Vector2<tQ_pos> &center) {
    this->center = center;
  }

  /**
   Update world coordinates, physics world calls this once per frame.
  */
  void update(tQ_delta delta) override;

 private:
  tQ_pos radius;
  tQ_pos world_radius;
  Diamond::Vector2<tQ_pos> center;
  Diamond::Vector2<tQ_pos> world_pos;
};
}  // namespace Quantum2D

#endif  // Q_CIRCLE_COLLIDER_H
