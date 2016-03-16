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

#ifndef Q_COLLIDER_2D_H
#define Q_COLLIDER_2D_H

#include <functional>
#include "Q_typedefs.h"

namespace Quantum2D {
    enum Coltype {
        eNONE, eAABB, eCIRCLE, ePOLY, eNUMCOLTYPES
    };

    class Collider2D {
    public:
        Collider2D(Coltype type, 
                   transform2_id transform, 
                   void *parent, 
                   std::function<void(void *other)> &onCollision) 
            : type(type), transform(transform), parent(parent), onCollision(onCollision) {};
        
        virtual ~Collider2D() {};

        Coltype getType() const { return type; }
        
        transform2_id getTransformID() const { return transform; }

        void *getParent() const { return parent; }

        void onCollide(Collider2D *other) { onCollision(other->getParent()); }

        void setColFunc(std::function<void(void *other)> &onCollision) { this->onCollision = onCollision; }
        
        virtual void update(tD_delta delta_ms) = 0;

    protected:
        Coltype type;
        transform2_id transform;
        void *parent;
        std::function<void(void *other)> onCollision;
    };
}

#endif // Q_COLLIDER_2D_H
