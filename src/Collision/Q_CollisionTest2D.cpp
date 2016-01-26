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

bool Quantum2D::CollisionTest2D::AABB2(Quantum2D::AABBCollider2D *a, Quantum2D::AABBCollider2D *b) {
	return !(a->min.x - b->max.x > 0.0f || a->min.y - b->max.y > 0.0f
			|| b->min.x - a->max.x > 0.0f || b->min.y - a->max.y > 0.0f);
}
