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
#include "Q_CircleCollider.h"


TEST(CircleColTest, OnCollides) {
    std::string name1("Harry");
    std::string name2("Hagrid");

    QTest::TestBody<Quantum2D::CircleCollider> body1(name1, 0, 1);
    QTest::TestBody<Quantum2D::CircleCollider> body2(name2, 0, 1);

    body1.checkInit(body1.name);
    body2.checkInit(body2.name);

    body1.mCol->onCollide(body2.mCol);
    body2.mCol->onCollide(body1.mCol);

    ASSERT_NE(body1.other, nullptr);
    ASSERT_NE(body2.other, nullptr);

    EXPECT_EQ(body1.other->name, body2.name);
    EXPECT_EQ(body2.other->name, body1.name);
}

TEST(CircleColTest, Updates) {
    using namespace Diamond;
    tQ_pos radius = 3;
    Vector2<tQ_num> center(2, 2);

    QTest::TestBody<Quantum2D::CircleCollider> harry("Harry", 0, radius, center);
    
    harry.checkInit("Harry");

    ASSERT_EQ(harry.mCol->getRadius(), radius);
    ASSERT_EQ(harry.mCol->getCenter(), center);

    Vector2<tQ_num> curpos(5, 5);
    harry.trans.position = curpos;
    harry.mCol->update(1, harry.trans);
    EXPECT_EQ(harry.mCol->getWorldPos(), curpos + center);

    curpos.set(15, 15);
    harry.trans.position = curpos;
    harry.mCol->update(1, harry.trans);
    EXPECT_EQ(harry.mCol->getWorldPos(), curpos + center);
}
