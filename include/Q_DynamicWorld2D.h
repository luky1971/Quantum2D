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

#ifndef Q_DYNAMIC_WORLD_2D_H
#define Q_DYNAMIC_WORLD_2D_H

#include <memory>
#include "D_Transform2.h"
#include "D_sparsevector.h"
#include "D_swapvector.h"
#include "Q_Collider2D.h"
#include "Q_Rigidbody2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    class DynamicWorld2D {
    public:
        /**
         Initializes the simulation world.
         Returns true if initialization was successful, otherwise false.
        */
        bool init();


        /**
         Returns a reference to the transform with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
         Only use this reference immediately after calling this function!
        */
        Diamond::Transform2<tQ_pos, tQ_rot> &getTransform(transform2_id transform) { return transforms[transform]; }

        /**
         Creates a transform object and returns its id.
         The returned id can be used to access the transform with getTransform(id).
        */
        transform2_id genTransform() { return transforms.emplace_back(); }

        /**
         Frees the given transform's memory.
        */
        void freeTransform(transform2_id transform) { transforms.erase(transform); }


        /**
         Returns a reference to the rigidbody with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new rigidbody is created.
         Only use this reference immediately after calling this function!
        */
        Rigidbody2D &getRigidbody(body2d_id body) { return bodies[body]; }

        /**
         Creates a rigidbody object attached to the given transform and returns its id.
         The returned id can be used to access the rigidbody with getRigidbody(id).
        */
        body2d_id genRigidbody(transform2_id transform) { return bodies.emplace_back(transform); }

        /**
         Frees the given rigidbody's memory.
        */
        void freeRigidbody(body2d_id body) { bodies.erase(body); }


        /**
         Returns a pointer to the collider with the given id.
        */
        Collider2D *getCollider(collider2_id collider) { return colliders[collider].get(); }

        /**
         Creates a 2D collider object of the given type using the given constructor arguments 
         and adds it to the collision detection system.
         The returned id can be used to access the collider with getCollider(id).
        */
        template <class T, typename... Args>
        collider2_id genCollider(Args&&... args) {
            return colliders.emplace_back(new T(std::forward<Args>(args)...));
        }

        /**
         Adds a collider to the collision detection system.
         The owner of the given pointer should now be QuantumWorld2D!
         The returned id can be used to access the collider with getCollider(id).
        */
        collider2_id addCollider(Collider2D *col) { return colliders.emplace_back(col); }

        /**
         Frees the given collider's memory.
        */
        void freeCollider(collider2_id collider) { colliders.erase(collider); }


        /**
        Steps the physics simulation by the number of milliseconds given.
        */
        void step(tQ_delta delta_ms);

    private:
        Diamond::sparsevector<Diamond::Transform2<tQ_pos, tQ_rot> > transforms;
        Diamond::swapvector<Rigidbody2D> bodies;
        Diamond::swapvector<std::unique_ptr<Collider2D> > colliders;
    };
}

#endif // Q_DYNAMIC_WORLD_2D_H
