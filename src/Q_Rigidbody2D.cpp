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

#include "Q_Rigidbody2D.h"

#include "Q_QuantumWorld2D.h"

Quantum2D::Rigidbody2D::Rigidbody2D(body2d_id body_id, transform2_id transform) : velocity(), body_id(body_id), transform(transform) {}


void Quantum2D::Rigidbody2D::update(int16_t delta_ms) {
	QuantumWorld2D::getTransform(transform).position.add(velocity * delta_ms);
}
