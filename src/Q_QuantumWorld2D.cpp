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
		static std::vector<unsigned long> trans_index_stack = std::vector<unsigned long>();
		
		static std::vector<unsigned long> body_id_index_map = std::vector<unsigned long>();
		static std::vector<unsigned long> body_id_stack = std::vector<unsigned long>();
	}
}

std::vector<Diamond::Transform2i> Quantum2D::QuantumWorld2D::transforms(0);
std::vector<Quantum2D::Rigidbody2D> Quantum2D::QuantumWorld2D::bodies(0);

Quantum2D::Rigidbody2D *Quantum2D::QuantumWorld2D::getRigidbody(unsigned long body_id) {
	return &bodies[body_id_index_map[body_id]];
}

unsigned long Quantum2D::QuantumWorld2D::genTransform() {
	if (trans_index_stack.size() != 0) {
		unsigned long index = trans_index_stack.back();
		trans_index_stack.pop_back();
		transforms[index].reset();
		return index;
	}
	else {
		transforms.push_back(Diamond::Transform2i());
		return transforms.size() - 1;
	}
}

void Quantum2D::QuantumWorld2D::freeTransform(unsigned long index) {
	trans_index_stack.push_back(index);
}

unsigned long Quantum2D::QuantumWorld2D::genRigidbody(unsigned long transform_index) {
	unsigned long body_id;
	if (body_id_stack.size() != 0) {
		body_id = body_id_stack.back();
		body_id_stack.pop_back();
		body_id_index_map[body_id] = bodies.size();
	}
	else {
		body_id = body_id_index_map.size();
		body_id_index_map.push_back(bodies.size());
	}
	bodies.push_back(Rigidbody2D(body_id, transform_index));
	return body_id;
}

void Quantum2D::QuantumWorld2D::freeRigidbody(unsigned long body_id) {
	unsigned long index = body_id_index_map[body_id];
	if (index < bodies.size() - 1) { // If in middle of vector, replace it with last element in vector
		bodies[index] = bodies.back();
		body_id_index_map[bodies[index].body_id] = index;
	}
	bodies.pop_back();
	body_id_stack.push_back(body_id);
}


void Quantum2D::QuantumWorld2D::step(int delta_ms) {
	for (std::vector<Rigidbody2D>::iterator i = bodies.begin(); i != bodies.end(); i++) {
		i->update(delta_ms);
	}
}
