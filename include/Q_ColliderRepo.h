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

#ifndef Q_COLLIDER_REPO_H
#define Q_COLLIDER_REPO_H

#include <memory>
#include "D_swapvector.h"
#include "Q_Collider2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    typedef Diamond::swapvector<std::unique_ptr<Collider2D> > ColList;

    class ColliderRepo {
    public:
        /**
         Returns a pointer to the collider with the given id.
        */
        Collider2D *getCollider(collider2_id collider) { return colliders[collider].get(); }
        const Collider2D *getCollider(collider2_id collider) const { return colliders[collider].get(); }

        /**
         Creates a collider object of the given type using the given constructor arguments 
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
         Get a direct reference to the container of colliders.
        */
        ColList &getColliders() { return colliders; }
        const ColList &getColliders() const { return colliders; }

    private:
        ColList colliders;
    };
}

#endif // Q_COLLIDER_REPO_H
