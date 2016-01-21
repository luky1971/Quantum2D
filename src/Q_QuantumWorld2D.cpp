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

namespace Quantum2D {
	namespace QuantumWorld2D {
		static std::vector<transform2_id> trans_id_stack = std::vector<transform2_id>();
		static std::vector<body2d_id> body_id_stack = std::vector<body2d_id>();
	}
}

std::vector<Diamond::Transform2<int, float> > Quantum2D::QuantumWorld2D::transforms = std::vector<Diamond::Transform2<int, float> >();
std::vector<Quantum2D::Rigidbody2D> Quantum2D::QuantumWorld2D::bodies = std::vector<Quantum2D::Rigidbody2D>();
std::vector<tD_index> Quantum2D::QuantumWorld2D::body_id_index_map = std::vector<tD_index>();


transform2_id Quantum2D::QuantumWorld2D::genTransform() {
	if (trans_id_stack.size() != 0) {
		transform2_id index = trans_id_stack.back();
		trans_id_stack.pop_back();
		transforms[index].reset();
		return index;
	}
	else {
		transforms.push_back(Diamond::Transform2<int, float>());
		return transforms.size() - 1;
	}
}

void Quantum2D::QuantumWorld2D::freeTransform(transform2_id index) {
	trans_id_stack.push_back(index);
}

body2d_id Quantum2D::QuantumWorld2D::genRigidbody(transform2_id transform) {
	body2d_id body;
	if (body_id_stack.size() != 0) {
		body = body_id_stack.back();
		body_id_stack.pop_back();
		body_id_index_map[body] = bodies.size();
	}
	else {
		body = body_id_index_map.size();
		body_id_index_map.push_back(bodies.size());
	}
	bodies.push_back(Rigidbody2D(body, transform));
	return body;
}

void Quantum2D::QuantumWorld2D::freeRigidbody(body2d_id body) {
	tD_index index = body_id_index_map[body];
	if (index < bodies.size() - 1) { // If in middle of vector, replace it with last element in vector
		bodies[index] = bodies.back();
		body_id_index_map[bodies[index].body_id] = index;
	}
	bodies.pop_back();
	body_id_stack.push_back(body);
}


void Quantum2D::QuantumWorld2D::step(int16_t delta_ms) {
	for (Rigidbody2D body: bodies) {
		body.update(delta_ms);
	}
}
