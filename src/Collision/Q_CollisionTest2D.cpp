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

void Quantum2D::CollisionTest2D::init() {
    // TODO: initialize a 2D array of function pointers to collision test functions addressed by collider types
}

bool Quantum2D::CollisionTest2D::collide(Collider2D *a, Collider2D *b) {
    return false;
}

bool Quantum2D::CollisionTest2D::AABB2(Quantum2D::AABBCollider2D *a, Quantum2D::AABBCollider2D *b) {
	return !(a->getMin().x - b->getMax().x > 0.0f || a->getMin().y - b->getMax().y > 0.0f
			|| b->getMin().x - a->getMax().x > 0.0f || b->getMin().y - a->getMax().y > 0.0f);
}
