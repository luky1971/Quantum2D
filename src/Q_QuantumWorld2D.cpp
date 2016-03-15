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

#include "Q_QuantumWorld2D.h"
#include "Q_CollisionTest2D.h"

Diamond::sparsevector<Diamond::Transform2<tD_pos, tD_rot> > Quantum2D::QuantumWorld2D::transforms
    = Diamond::sparsevector<Diamond::Transform2<tD_pos, tD_rot> >();

Diamond::swapvector<Quantum2D::Rigidbody2D> Quantum2D::QuantumWorld2D::bodies
    = Diamond::swapvector<Quantum2D::Rigidbody2D>();

Diamond::swapvector<std::unique_ptr<Quantum2D::Collider2D> > Quantum2D::QuantumWorld2D::colliders
    = Diamond::swapvector<std::unique_ptr<Quantum2D::Collider2D> >();


bool Quantum2D::QuantumWorld2D::init() {
    return CollisionTest2D::init();
}

void Quantum2D::QuantumWorld2D::step(tD_delta delta_ms) {
    // Move rigidbodies
    for (Rigidbody2D body: bodies) {
        body.update(delta_ms);
    }

    // Test collisions
    // TODO: broad phase testing
    for (auto i = colliders.begin(); i != colliders.end(); ++i) {
        i->get()->update(delta_ms);
    }

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
                std::cout << "Collision!" << std::endl;
            }
        }
        
    }
}
