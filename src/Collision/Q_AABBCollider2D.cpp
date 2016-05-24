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

#include "Q_AABBCollider2D.h"

Quantum2D::AABBCollider2D::AABBCollider2D(const BodyList &bodylist, 
                                          body2d_id body,
                                          void *parent, 
                                          const std::function<void(void *other)> &onCollision, 
                                          const Diamond::Vector2<tQ_pos> &dims, 
                                          const Diamond::Vector2<tQ_pos> &origin) 
    : Collider2D(bodylist, eAABB, body, parent, onCollision), dims(dims), origin(origin) {}

void Quantum2D::AABBCollider2D::update(tQ_delta delta_ms) {
    // TODO: consider rotation!
    min = bodylist[body].getPosition() + origin;
    max = min + dims;
}
