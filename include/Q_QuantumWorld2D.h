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

#ifndef Q_QUANTUM_WORLD_2D_H
#define Q_QUANTUM_WORLD_2D_H

#include <memory>
#include <vector>

#include "D_Transform2.h"

#include "Q_Collider2D.h"
#include "Q_RigidBody2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
	namespace QuantumWorld2D {
		
		extern std::vector<Diamond::Transform2<int, float> > transforms;
		extern std::vector<Rigidbody2D> bodies;
		extern std::vector<std::unique_ptr<Collider2D> > colliders;

		extern std::vector<tD_index> body_id_index_map;
		extern std::vector<tD_index> collider_id_index_map;
		
		extern std::vector<collider2_id> collider_id_stack;
		

		/**
		 Returns a reference to the transform with the given id.
		 Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
		 Only use this reference immediately after calling this function!
		 (ie, call this function again every time you want access)
		*/
		inline Diamond::Transform2<int, float> &getTransform(transform2_id transform) {
			return transforms[transform];
		}
		
		/**
		 Returns a reference to the rigidbody with the given id.
		 Note: the reference returned is only guaranteed to be valid until the next time a new rigidbody is created.
		 Only use this reference immediately after calling this function!
		 (ie, call this function again every time you want access)
		*/
		inline Rigidbody2D &getRigidbody(body2d_id body) {
			return bodies[body_id_index_map[body]];
		}
		
		/**
		 Returns a pointer to the collider with the given id.
		*/
		inline Collider2D *getCollider(collider2_id collider) {
			return colliders[collider_id_index_map[collider]].get();
		}
		
		
		/**
		 Creates a Transform2i object and returns its id.
		 The returned id can be used to access the transform with getTransform(id).
		*/
		transform2_id genTransform();
		
		/**
		 Frees the given index in transforms as available for a new Transform2i
		*/
		void freeTransform(transform2_id transform);
		
		
		/**
		 Creates a Rigidbody2D object attached to the given transform and returns its id.
		 The returned id can be used to access the rigidbody with getRigidbody(id).
		*/
		body2d_id genRigidbody(transform2_id transform);
		
		/**
		 Marks the given id as available for a new Rigidbody2D, and removes its currently associated rigidbody.
		*/
		void freeRigidbody(body2d_id body);
		
		
		/**
		 Creates a 2D collider object of the given type using the given constructor arguments.
		 The returned id can be used to access the collider with getCollider(id).
		*/
		template <class T, typename... Args>
		collider2_id genCollider(Args&&... args);
		
		/**
		 Marks the given id as available for a new Collider2D, and destroys its currently associated collider.
		*/
		void freeCollider(collider2_id collider);
		
		
		/**
		 Steps the physics simulation by the number of milliseconds given.
		*/
		void step(int16_t delta_ms);
	}
}


template <class T, typename... Args>
collider2_id Quantum2D::QuantumWorld2D::genCollider(Args&&... args) {
	collider2_id collider;
	if (!collider_id_stack.empty()) {
		collider = collider_id_stack.back();
		collider_id_stack.pop_back();
		collider_id_index_map[collider] = colliders.size();
	}
	else {
		collider = collider_id_index_map.size();
		collider_id_index_map.push_back(colliders.size());
	}
	colliders.push_back(std::unique_ptr<Collider2D>(new T(collider, std::forward<Args>(args)...)));
	return collider;
}


#endif // Q_QUANTUM_WORLD_2D_H
