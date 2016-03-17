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
#include "Q_QuantumWorld2D.h"

Quantum2D::CircleCollider::CircleCollider(transform2_id transform,
                                          void *parent,
                                          std::function<void(void *other)> &onCollision,
                                          tQ_pos radius,
                                          const Diamond::Vector2<tQ_pos> &center)
    : Collider2D(eCIRCLE, transform, parent, onCollision), 
      radius(radius), radiusSq(radius * radius), center(center) {}

void Quantum2D::CircleCollider::update(tQ_delta delta_ms) {
    world_pos = QuantumWorld2D::getTransform(getTransformID()).position + center;
}
