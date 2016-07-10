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

#include <typeindex>

typedef bool(*ColFunc)(const Quantum2D::Collider2D*, const Quantum2D::Collider2D*);

namespace Quantum2D {
    namespace CollisionTest2D {
        static bool initialized = false;
        
        static ColFunc col_funcs[eNUMCOLTYPES][eNUMCOLTYPES];
        
        static bool colNONE(const Collider2D *a, const Collider2D *b) {
            return false;
        }
        
        static bool colAABB2(const Collider2D *a, const Collider2D *b) {
            return AABB2(static_cast<const AABBCollider2D*>(a),
                         static_cast<const AABBCollider2D*>(b));
        }

        static bool colCircle2(const Collider2D *a, const Collider2D *b) {
            return circle2(static_cast<const CircleCollider*>(a),
                           static_cast<const CircleCollider*>(b));
        }

        static bool colCircleAABB(const Collider2D *a, const Collider2D *b) {
            return circleAABB(static_cast<const CircleCollider*>(a),
                              static_cast<const AABBCollider2D*>(b));
        }

        static bool colAABBCircle(const Collider2D *a, const Collider2D *b) {
            return circleAABB(static_cast<const CircleCollider*>(b),
                              static_cast<const AABBCollider2D*>(a));
        }
        
        static bool colPoly2(const Collider2D *a, const Collider2D *b) {
            return poly2(static_cast<const PolyCollider*>(a),
                         static_cast<const PolyCollider*>(b));
        }
        
        // ea and eb must be in clockwise order!
        static bool edgeVertsOutisde(const Diamond::Vector2<tQ_pos> &ea,
                          const Diamond::Vector2<tQ_pos> &eb,
                          const PointList &verts) {
            using namespace Diamond;
            
            bool sep = true;
            
            for (Vector2<tQ_pos> vert : verts) {
                if (!Math::leftOf(vert, ea, eb)) {
                    sep = false;
                    break;
                }
            }
            
            return sep;
        }
        
        // edge points must be specified in clockwise order!
        static bool polyVertsOutside(const PointList &edgePoints,
                                     const PointList &verts) {
            
            for (int i = 1; i < edgePoints.size(); ++i) {
                if (edgeVertsOutisde(edgePoints[i-1],
                                     edgePoints[i],
                                     verts))
                    return true;
            }
            
            return edgeVertsOutisde(edgePoints.back(),
                                    edgePoints.front(),
                                    verts);
        }
    }
}

bool Quantum2D::CollisionTest2D::init() {
    if (!initialized) {
        // Initialize invalid collision functions
        col_funcs[eNONE][eNONE] = colNONE;
        for (int i = eNONE + 1; i < eNUMCOLTYPES; ++i) {
            col_funcs[eNONE][i] = colNONE;
            col_funcs[i][eNONE] = colNONE;
        }
        
        col_funcs[eAABB][eAABB] = colAABB2;
        col_funcs[eCIRCLE][eCIRCLE] = colCircle2;
        col_funcs[ePOLY][ePOLY] = colPoly2;
        
        col_funcs[eAABB][eCIRCLE] = colAABBCircle;
        col_funcs[eCIRCLE][eAABB] = colCircleAABB;
        
        // TODO: Initialize collision functions for all collider type pairs
        col_funcs[eAABB][ePOLY] = colNONE;
        col_funcs[ePOLY][eAABB] = colNONE;
        
        col_funcs[eCIRCLE][ePOLY] = colNONE;
        col_funcs[ePOLY][eCIRCLE] = colNONE;

        initialized = true;
    }
    return true;
}

bool Quantum2D::CollisionTest2D::collide(const Collider2D *a,
                                         const Collider2D *b) {
    return col_funcs[a->getType()][b->getType()](a, b);
}

bool Quantum2D::CollisionTest2D::AABB2(const AABBCollider2D *a,
                                       const AABBCollider2D *b) {
    return !(a->getMin().x - b->getMax().x > 0.0f ||
             a->getMin().y - b->getMax().y > 0.0f ||
             b->getMin().x - a->getMax().x > 0.0f ||
             b->getMin().y - a->getMax().y > 0.0f);
}

bool Quantum2D::CollisionTest2D::circle2(const CircleCollider *a,
                                         const CircleCollider *b) {
    tQ_pos rad_tot = a->getRadius() + b->getRadius();
    return a->getWorldPos().distanceSq(b->getWorldPos()) < rad_tot * rad_tot;
}

bool Quantum2D::CollisionTest2D::circleAABB(const CircleCollider *a,
                                            const AABBCollider2D *b) {
    tQ_pos distSq = 0, diff;

    if (a->getWorldPos().x < b->getMin().x) {
        diff = b->getMin().x - a->getWorldPos().x;
        distSq += diff * diff;
    }
    if (a->getWorldPos().x > b->getMax().x) {
        diff = a->getWorldPos().x - b->getMax().x;
        distSq += diff * diff;
    }

    if (a->getWorldPos().y < b->getMin().y) {
        diff = b->getMin().y - a->getWorldPos().y;
        distSq += diff * diff;
    }
    if (a->getWorldPos().y > b->getMax().y) {
        diff = a->getWorldPos().y - b->getMax().y;
        distSq += diff * diff;
    }

    return distSq < a->getRadiusSq();
}

bool Quantum2D::CollisionTest2D::poly2(const PolyCollider *a, const PolyCollider *b) {
    return !polyVertsOutside(a->worldPoints(), b->worldPoints()) ||
           !polyVertsOutside(b->worldPoints(), a->worldPoints());
}
