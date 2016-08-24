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

#ifndef Q_RIGIDBODY_2D_H
#define Q_RIGIDBODY_2D_H

#include "duVector2.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    template <typename Scalar>
    class LRigidbody2D {
    public:
        LRigidbody2D(Scalar &posX, Scalar &posY, Scalar &rot)
            : positionX(posX),
              positionY(posY),
              rotation(rot) {}
        
        void integrate(tQ_delta delta) {
            positionX += velocityX * delta;
            positionY += velocityY * delta;
            rotation  += angVelocity * delta;
        }
        
        Scalar &positionX, &positionY;
        Scalar &rotation;
        
        Scalar velocityX, velocityY;
        Scalar angVelocity;
    };
}

#endif // Q_RIGIDBODY_2D_H
