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


bool Quantum2D::DynamicWorld2D::init(bool allLayersCollide) {
    if (allLayersCollide) {
        for (int i = 0; i < MAX_LAYERS; ++i) {
            layerMap[i].set(); // Turn on collision between all layers
        }
    }
    return CollisionTest2D::init();
}

void Quantum2D::DynamicWorld2D::step(tQ_delta delta) {
    // Move rigidbodies
    for (auto i = bodies.begin(); i != bodies.end(); ++i) {
        i->update(delta);
    }
    
    // Update colliders
    for (auto i = colliders.begin(); i != colliders.end(); ++i) {
        (*i)->update(delta);
    }
    
    
    // --Test collisions-- //
    
    
    // bool col = false; // DEBUG
    // Pairwise test collisions. TODO: broad phase
    
    pairs.clear();

    std::vector<std::unique_ptr<Collider2D> > &colliderVec = colliders.data();
    
    // Need to cast colliderVec.size() to int before subtracting 1
    // because size type might be unsigned, and subtracting 1 from
    // unsigned when size = 0 will cause mass chaos and destruction.
    for (int i = 0; i < (int64_t)colliderVec.size() - 1; ++i) {
        for (int j = i + 1; j < colliderVec.size(); ++j) {
            if (doLayersCollide(colliderVec[i]->getLayer(), colliderVec[j]->getLayer()) &&
                CollisionTest2D::collide(colliderVec[i].get(), colliderVec[j].get())) {
                // col = true; // DEBUG
                pairs.emplace_back(colliderVec[i].get(), colliderVec[j].get());
                // std::cout << "Collision!" << std::endl; // DEBUG
            }
        }
    }
    
    /*if (!col)
        std::cout << "No collision" << std::endl; // DEBUG*/
}


void Quantum2D::DynamicWorld2D::callbackCollisions() {
    for (ColliderPair pair : pairs) {
        pair.a->onCollide(pair.b);
        pair.b->onCollide(pair.a);
    }
}

