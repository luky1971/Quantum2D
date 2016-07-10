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

#include "Q_PolyCollider.h"

Quantum2D::PolyCollider::PolyCollider(const BodyList &bodylist,
                                      body2d_id body,
                                      void *parent,
                                      const std::function<void(void *other)> &onCollision,
                                      const PointList &points)
    : Quantum2D::Collider2D(bodylist, ePOLY, body, parent, onCollision),
      m_points(points), m_worldPoints(points.size()) {}

void Quantum2D::PolyCollider::update(tQ_delta delta) {
    using namespace Diamond;
    
    // Because user can add more points at any time
    m_worldPoints.resize(m_points.size());
    
    const Rigidbody2D &rbody = bodylist[body];
    auto transMat = Math::transMat(Qrot2rad(rbody.rotation()), 1.0f, 1.0f);
    
    for (int i = 0; i < m_worldPoints.size(); ++i) {
        m_worldPoints[i] = rbody.position() + m_points[i].mul(transMat.m);
    }
}
