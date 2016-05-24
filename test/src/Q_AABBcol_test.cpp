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
#include "Q_AABBCollider2D.h"


TEST(AABBColTest, OnCollides) {
    Quantum2D::BodyList blist;
    blist.emplace_back();
    blist.emplace_back();
    std::string name1("Harry");
    std::string name2("Hagrid");

    QTest::TestBody<Quantum2D::AABBCollider2D> body1(blist, name1, 0, Diamond::Vector2<float>(10, 10));
    QTest::TestBody<Quantum2D::AABBCollider2D> body2(blist, name2, 1, Diamond::Vector2<float>(10, 10));
    
    body1.checkInit(body1.name);
    body2.checkInit(body2.name);

    body1.mCol->onCollide(body2.mCol);
    body2.mCol->onCollide(body1.mCol);
    
    ASSERT_NE(body1.other, nullptr);
    ASSERT_NE(body2.other, nullptr);

    EXPECT_EQ(body1.other->name, body2.name);
    EXPECT_EQ(body2.other->name, body1.name);
}

TEST(AABBColTest, Updates) {
    using namespace Diamond;
    Quantum2D::BodyList blist;
    blist.emplace_back();
    Vector2<tQ_num> dims(10, 10);
    Vector2<tQ_num> origin(0, 0);

    QTest::TestBody<Quantum2D::AABBCollider2D> harry(blist, "Harry", 0, dims, origin);
    
    harry.checkInit("Harry");

    ASSERT_EQ(harry.mCol->getDims(), dims);
    ASSERT_EQ(harry.mCol->getOrigin(), origin);
    
    Vector2<tQ_num> curpos(5, 5);
    harry.getBody().setPosition(curpos);
    harry.mCol->update(1);
    EXPECT_EQ(harry.mCol->getMin(), curpos + origin);
    EXPECT_EQ(harry.mCol->getMax(), curpos + origin + dims);

    curpos.set(15, 15);
    harry.getBody().setPosition(curpos);
    harry.mCol->update(1);
    EXPECT_EQ(harry.mCol->getMin(), curpos + origin);
    EXPECT_EQ(harry.mCol->getMax(), curpos + origin + dims);
}
