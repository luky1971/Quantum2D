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
#include "Q_QuantumWorld2D.h"

Quantum2D::AABBCollider2D::AABBCollider2D(body2d_id body, 
                                          void *parent, 
                                          std::function<void(void*)> &onCollision, 
                                          Diamond::Vector2<tD_pos> &origin, 
                                          Diamond::Vector2<tD_pos> &dims) 
    : Collider2D(eAABB, body, parent, onCollision), origin(origin), dims(dims) {}

void Quantum2D::AABBCollider2D::update(tD_delta delta_ms) {
    // TODO: consider rotation!
    min = QuantumWorld2D::getTransform(QuantumWorld2D::getRigidbody(body).getTransformID()).position + origin;
    max = min + dims;
}
