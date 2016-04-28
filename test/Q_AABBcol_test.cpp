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

/*
namespace QTest {
    class TestBody {
    public:
        TestBody(const std::string &name, 
                 const Diamond::Vector2<tQ_num> &dims = Diamond::Vector2<tQ_num>(1, 1), 
                 const Diamond::Vector2<tQ_num> &origin = Diamond::Vector2<tQ_num>(0, 0))
            : name(name), mCol(nullptr), other(nullptr) {
            std::function<void(void*)> callback = std::bind(&TestBody::onCollision, this, std::placeholders::_1);
            mCol = new Quantum2D::AABBCollider2D(0, this, callback, dims, origin);
        }

        ~TestBody() {
            delete mCol;
        }

        void onCollision(void *other) {
            this->other = static_cast<TestBody*>(other);
        }

        void checkInit() {
            ASSERT_NE(mCol, nullptr);
            ASSERT_EQ(other, nullptr);
        }

        std::string name;
        Diamond::Transform2<tQ_pos, tQ_rot> trans;
        Quantum2D::AABBCollider2D *mCol;
        TestBody *other;
    };   
}*/


TEST(AABBColTest, OnCollides) {
    std::string name1("Harry");
    std::string name2("Hagrid");

    QTest::TestBody<Quantum2D::AABBCollider2D> body1(name1, 0, Diamond::Vector2<float>(10, 10));
    QTest::TestBody<Quantum2D::AABBCollider2D> body2(name2, 0, Diamond::Vector2<float>(10, 10));
    
    body1.checkInit();
    body2.checkInit();
    ASSERT_EQ(body1.name, name1);
    ASSERT_EQ(body2.name, name2);

    body1.mCol->onCollide(body2.mCol);
    body2.mCol->onCollide(body1.mCol);
    
    ASSERT_NE(body1.other, nullptr);
    ASSERT_NE(body2.other, nullptr);

    EXPECT_EQ(body1.other->name, body2.name);
    EXPECT_EQ(body2.other->name, body1.name);
}

TEST(AABBColTest, Updates) {
    using namespace Diamond;
    Vector2<tQ_num> dims(10, 10);
    Vector2<tQ_num> origin(0, 0);

    QTest::TestBody<Quantum2D::AABBCollider2D> harry("Harry", 0, dims, origin);

    ASSERT_EQ(harry.name, "Harry");
    harry.checkInit();

    ASSERT_EQ(harry.mCol->getDims(), dims);
    ASSERT_EQ(harry.mCol->getOrigin(), origin);
    
    Vector2<tQ_num> curpos(5, 5);
    harry.trans.position = curpos;
    harry.mCol->update(0, harry.trans);
    EXPECT_EQ(harry.mCol->getMin(), curpos + origin);
    EXPECT_EQ(harry.mCol->getMax(), curpos + origin + dims);

    curpos.set(15, 15);
    harry.trans.position = curpos;
    harry.mCol->update(0, harry.trans);
    EXPECT_EQ(harry.mCol->getMin(), curpos + origin);
    EXPECT_EQ(harry.mCol->getMax(), curpos + origin + dims);
}
