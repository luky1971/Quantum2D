/*
    Copyright 2016 Ahnaf Siddiqui

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

#include "Q_DynamicWorld2D.h"
#include "Q_CollisionTest2D.h"

bool Quantum2D::DynamicWorld2D::init() {
    return CollisionTest2D::init();
}

void Quantum2D::DynamicWorld2D::step(tQ_delta delta_ms) {
    // Move rigidbodies
    for (auto i = bodies.getBodies().begin(); i != bodies.getBodies().end(); ++i) {
        (*i).setPosition((*i).getPosition() + ((*i).getVelocity() * delta_ms));
    }

    // --Test collisions-- //

    // Update colliders
    for (auto i = colliders.getColliders.begin(); i != colliders.end(); ++i) {
        (*i)->update(delta_ms, getRigidbody((*i)->getBodyID()));
    }

    bool col = false; // DEBUG
    // Pairwise test collisions. TODO: broad phase
    for (int i = 0; i < colliders.size() - 1; ++i) {
        // for (int i = 0; i < colliders.size(); ++i) {
        /*
        // DEBUG
        std::cout << colliders[i]->getBodyID() << ", ";
        AABBCollider2D *col = static_cast<AABBCollider2D*>(colliders[i].get());
        std::cout << col->getOrigin() << "; " << col->getDims() << "; " << col->getMin() << "; " << col->getMax() << std::endl;
        */

        for (int j = i + 1; j < colliders.size(); ++j) {
            if (CollisionTest2D::collide(colliders[i].get(), colliders[j].get())) {
                col = true; // DEBUG
                colliders[i]->onCollide(colliders[j].get());
                colliders[j]->onCollide(colliders[i].get());
                // std::cout << "Collision!" << std::endl; // DEBUG
            }
        }
    }
    if (!col)
        std::cout << "No collision" << std::endl; // DEBUG
}
