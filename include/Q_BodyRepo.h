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

#ifndef Q_BODY_REPO_H
#define Q_BODY_REPO_H

#include <memory>
#include "D_swapvector.h"
#include "Q_Rigidbody2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    typedef Diamond::swapvector<Rigidbody2D> BodyList;

    class BodyRepo {
    public:
        /**
         Returns a reference to the rigidbody with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new rigidbody is created.
         Only use this reference immediately after calling this function!
        */
        Rigidbody2D &getRigidbody(body2d_id body) { return bodies[body]; }
        const Rigidbody2D &getRigidbody(body2d_id body) const { return bodies[body]; }

        /**
         Creates a rigidbody object and returns its id.
         The returned id can be used to access the rigidbody with getRigidbody(id).
        */
        body2d_id genRigidbody() { return bodies.emplace_back(); }

        /**
         Frees the given rigidbody's memory.
        */
        void freeRigidbody(body2d_id body) { bodies.erase(body); }

        /**
         Get a direct reference to the container of rigidbodies.
        */
        BodyList &getBodies() { return bodies; }
        const BodyList &getBodies() const { return bodies; }

    private:
        BodyList bodies;
    };
}

#endif // Q_BODY_REPO_H
