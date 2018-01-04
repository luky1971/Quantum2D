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

#include "Q_CircleCollider.h"
#include "duMath.h"

Quantum2D::CircleCollider::CircleCollider(
    const BodyList &bodylist, body2d_id body, void *parent,
    const std::function<void(void *other)> &onCollision, tQ_pos radius,
    const Diamond::Vector2<tQ_pos> &center, QLayer layer)
    : Collider2D(bodylist, eCIRCLE, body, parent, onCollision, layer),
      radius(radius),
      center(center) {}

void Quantum2D::CircleCollider::update(tQ_delta delta) {
  using namespace Diamond;

  const Rigidbody2D &rbody = bodylist[body];
  // choosing to scale with x is arbitrary
  world_radius = rbody.scale().x * radius;
  world_pos = rbody.position() +
              center.mul(Math::transMat(Qrot2rad(rbody.rotation()),
                                        rbody.scale().x, rbody.scale().y)
                             .m);
}
