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

#include "Q_DynamicWorld2D.h"
#include "Q_AABBCollider2D.h"
#include "Q_CircleCollider.h"
#include "gtest/gtest.h"

// TODO: test velocity, collisions, etc. from DynamicWorld2D interface
using namespace Diamond;
using namespace Quantum2D;

TEST(DynamicWorldTest, Initializes) {
    DynamicWorld2D world;
    ASSERT_TRUE(world.init());
}

class SimulationTest : public ::testing::Test {
protected:
    SimulationTest() {
        world.init();

        for (int i = 0; i < SIZE; ++i) {
            bodies[i] = world.genRigidbody();
            world.getRigidbody(bodies[i]).setVelocity(Vector2<int>(i, i));
        }
    }

    static const int SIZE = 10;
    DynamicWorld2D world;
    body2d_id bodies[SIZE];
};

TEST_F(SimulationTest, PersistBodies) {
    for (int i = 0; i < SIZE; ++i) {
        if (i % 2 == 1) {
            world.freeRigidbody(bodies[i]);
        }
        else {
            EXPECT_EQ((Vector2<int>)(world.getRigidbody(bodies[i]).getVelocity()), Vector2<int>(i, i));
        }
    }
}

TEST_F(SimulationTest, PersistColliders) {
    collider2_id colliders[SIZE];
    std::function<void(void*)> func = [](void *other) {};

    for (int i = 0; i < SIZE; ++i) {
        if (i % 2 == 1) {
            colliders[i] = world.genCollider<AABBCollider2D>(bodies[i], nullptr, func, Vector2<int>(i, i));
        }
        else {
            colliders[i] = world.genCollider<CircleCollider>(bodies[i], nullptr, func, i);
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        if (i % 3 == 0) {
            world.freeCollider(colliders[i]);
        }
        else if (i % 2 == 1) {
            EXPECT_EQ((Vector2<int>)(((AABBCollider2D*)(world.getCollider(colliders[i])))->getDims()),
                Vector2<int>(i, i));
        }
        else {
            EXPECT_EQ(((CircleCollider*)world.getCollider(colliders[i]))->getRadius(), i);
        }
    }
}
