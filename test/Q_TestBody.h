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

#ifndef Q_TEST_BODY_H
#define Q_TEST_BODY_H

#include <functional>
#include "Q_Collider2D.h"
#include "gtest/gtest.h"

namespace QTest {
    template <class COL>
    class TestBody {
    public:
        template <typename... Args>
        TestBody(const std::string &name, int rbody, Args&&... args)
            : name(name), mCol(nullptr), other(nullptr) {
            std::function<void(void*)> callback = std::bind(&TestBody::onCollision, this, std::placeholders::_1);
            mCol = new COL(rbody, this, callback, std::forward<Args>(args)...);
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
        COL *mCol;
        TestBody *other;
    };
}

#endif // Q_TEST_BODY_H
