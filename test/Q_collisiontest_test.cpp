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

#include "Q_TestBody.h"
#include "Q_CollisionTest2D.h"
#include "gtest/gtest.h"

using namespace Diamond;
using namespace Quantum2D;

// TODO: test with non-zero centers/origins for colliders

template <typename F>
void testAABB2(F AABB2) {
    std::string name1("Harry");
    std::string name2("Hagrid");

    QTest::TestBody<AABBCollider2D> body1(name1, 0, Vector2<float>(10, 10), Vector2<float>(0, 0));
    QTest::TestBody<AABBCollider2D> body2(name2, 0, Vector2<float>(10, 10), Vector2<float>(0, 0));

    body1.checkInit(body1.name);
    body2.checkInit(body2.name);

    body1.body.setPosition(Vector2<int>(-10, 0));
    body2.body.setPosition(Vector2<int>(15, 0));

    body1.mCol->update(1, body1.body);
    body2.mCol->update(1, body2.body);

    EXPECT_FALSE(AABB2(body1.mCol, body2.mCol));
    EXPECT_FALSE(AABB2(body2.mCol, body1.mCol)); // switch order

    body1.body.setPosition(Vector2<int>(5, -2));
    body2.body.setPosition(Vector2<int>(7, 3));

    body1.mCol->update(1, body1.body);
    body2.mCol->update(1, body2.body);

    EXPECT_TRUE(AABB2(body1.mCol, body2.mCol));
    EXPECT_TRUE(AABB2(body2.mCol, body1.mCol));
}

template <typename F>
void testCircle2(F circle2) {
    std::string name1("Harry");
    std::string name2("Hagrid");

    QTest::TestBody<CircleCollider> body1(name1, 0, 3, Vector2<float>(0, 0));
    QTest::TestBody<CircleCollider> body2(name2, 0, 5, Vector2<float>(0, 0));

    body1.checkInit(body1.name);
    body2.checkInit(body2.name);

    body1.body.setPosition(Vector2<int>(-10, 0));
    body2.body.setPosition(Vector2<int>(15, 0));

    body1.mCol->update(1, body1.body);
    body2.mCol->update(1, body2.body);

    EXPECT_FALSE(circle2(body1.mCol, body2.mCol));
    EXPECT_FALSE(circle2(body2.mCol, body1.mCol)); // switch order

    body1.body.setPosition(Vector2<int>(5, -1));
    body2.body.setPosition(Vector2<int>(6, 3));

    body1.mCol->update(1, body1.body);
    body2.mCol->update(1, body2.body);

    EXPECT_TRUE(circle2(body1.mCol, body2.mCol));
    EXPECT_TRUE(circle2(body2.mCol, body1.mCol));
}

TEST(CollisionTestTest, Initializes) {
    ASSERT_TRUE(CollisionTest2D::init());
}

TEST(CollisionTestTest, FuncAABB2) {
    testAABB2(CollisionTest2D::AABB2);
}

TEST(CollisionTestTest, CollideAABB2) {
    testAABB2(CollisionTest2D::collide);
}

TEST(CollisionTestTest, FuncCircle2) {
    testCircle2(CollisionTest2D::circle2);
}

TEST(CollisionTestTest, CollideCircle2) {
    testCircle2(CollisionTest2D::collide);
}

TEST(CollisionTestTest, CircleAABB) {
    std::string name1("Harry");
    std::string name2("Hagrid");

    QTest::TestBody<CircleCollider> body1(name1, 0, 3, Vector2<float>(0, 0));
    QTest::TestBody<AABBCollider2D> body2(name2, 0, Vector2<float>(10, 10), Vector2<float>(0, 0));

    body1.checkInit(body1.name);
    body2.checkInit(body2.name);

    body1.body.setPosition(Vector2<int>(-10, 0));
    body2.body.setPosition(Vector2<int>(15, 0));

    body1.mCol->update(1, body1.body);
    body2.mCol->update(1, body2.body);

    EXPECT_FALSE(CollisionTest2D::circleAABB(body1.mCol, body2.mCol));
    EXPECT_FALSE(CollisionTest2D::collide(body1.mCol, body2.mCol));
    EXPECT_FALSE(CollisionTest2D::collide(body2.mCol, body1.mCol)); // switch order

    body1.body.setPosition(Vector2<int>(5, 1));
    body2.body.setPosition(Vector2<int>(6, 2));

    body1.mCol->update(1, body1.body);
    body2.mCol->update(1, body2.body);

    EXPECT_TRUE(CollisionTest2D::circleAABB(body1.mCol, body2.mCol));
    EXPECT_TRUE(CollisionTest2D::collide(body1.mCol, body2.mCol));
    EXPECT_TRUE(CollisionTest2D::collide(body2.mCol, body1.mCol));
}
