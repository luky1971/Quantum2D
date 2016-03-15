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

#include "Q_CollisionTest2D.h"

#include <typeindex>

typedef bool(*ColFunc)(Quantum2D::Collider2D*, Quantum2D::Collider2D*);

namespace Quantum2D {
    namespace CollisionTest2D {
        static ColFunc col_funcs[eNUMCOLTYPES][eNUMCOLTYPES];
        
        static bool colNONE(Collider2D *a, Collider2D *b) {
            return false;
        }
        
        static bool colAABB2(Collider2D *a, Collider2D *b) {
            return AABB2(static_cast<AABBCollider2D*>(a), static_cast<AABBCollider2D*>(b));
        }
    }
}

bool Quantum2D::CollisionTest2D::init() {
    // TODO: initialize a 2D array of function pointers to collision test functions addressed by collider types
    col_funcs[eNONE][eNONE] = colNONE;
    for (int i = eNONE + 1; i < eNUMCOLTYPES; ++i) {
        col_funcs[eNONE][i] = colNONE;
        col_funcs[i][eNONE] = colNONE;
    }
    
    col_funcs[eAABB][eAABB] = colAABB2;
    
    return true;
}

bool Quantum2D::CollisionTest2D::collide(Collider2D *a, Collider2D *b) {
    return col_funcs[a->getType()][b->getType()](a, b);
}

bool Quantum2D::CollisionTest2D::AABB2(Quantum2D::AABBCollider2D *a, Quantum2D::AABBCollider2D *b) {
    return !(a->getMin().x - b->getMax().x > 0.0f || a->getMin().y - b->getMax().y > 0.0f
            || b->getMin().x - a->getMax().x > 0.0f || b->getMin().y - a->getMax().y > 0.0f);
}
