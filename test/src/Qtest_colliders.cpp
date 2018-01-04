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
#include "Q_PolyCollider.h"
#include "gtest/gtest.h"

using namespace Diamond;
using namespace Quantum2D;

void colFunc(void *ptr) {
  //
}

// TEST(LayerTest, MaxLayers) {
//     EXPECT_EQ(Quantum2D::MAX_LAYERS, 256);
// }

TEST(LayerTest, LayerSet) {
  DynamicWorld2D world;
  ASSERT_TRUE(world.init(false));

  world.setLayersCollide(0, 0, 1);
  EXPECT_TRUE(world.doLayersCollide(0, 0));

  world.setLayersCollide(0, 0, 0);
  EXPECT_FALSE(world.doLayersCollide(0, 0));

  world.setLayersCollide(4, 6, 1);
  EXPECT_TRUE(world.doLayersCollide(4, 6));
  EXPECT_TRUE(world.doLayersCollide(6, 4));

  world.setLayersCollide(4, 6, 0);
  EXPECT_FALSE(world.doLayersCollide(4, 6));
  EXPECT_FALSE(world.doLayersCollide(6, 4));
}

TEST(PolyColliderTest, PersistsCWPoints) {
  DynamicWorld2D world;
  ASSERT_TRUE(world.init());

  PointList2D points;

  // Clockwise order
  points.emplace_back(9, 10);
  points.emplace_back(7, 8);
  points.emplace_back(5, 6);
  points.emplace_back(4, 7);
  points.emplace_back(6, 12);

  collider2_id colID = world.genCollider<PolyCollider>(
      world.genRigidbody(), nullptr, colFunc, points);

  PolyCollider *collider = (PolyCollider *)world.getCollider(colID);

  EXPECT_FLOAT_EQ(collider->points()[0].x, 9);
  EXPECT_FLOAT_EQ(collider->points()[0].y, 10);

  EXPECT_FLOAT_EQ(collider->points()[1].x, 7);
  EXPECT_FLOAT_EQ(collider->points()[1].y, 8);

  EXPECT_FLOAT_EQ(collider->points()[2].x, 5);
  EXPECT_FLOAT_EQ(collider->points()[2].y, 6);

  EXPECT_FLOAT_EQ(collider->points()[3].x, 4);
  EXPECT_FLOAT_EQ(collider->points()[3].y, 7);

  EXPECT_FLOAT_EQ(collider->points()[4].x, 6);
  EXPECT_FLOAT_EQ(collider->points()[4].y, 12);
}

TEST(PolyColliderTest, PersistsThreeCWPoints) {
  DynamicWorld2D world;
  ASSERT_TRUE(world.init());

  PointList2D points;

  // Clockwise order
  points.emplace_back(25, 50);
  points.emplace_back(50, 0);
  points.emplace_back(0, 0);

  collider2_id colID = world.genCollider<PolyCollider>(
      world.genRigidbody(), nullptr, colFunc, points);

  PolyCollider *collider = (PolyCollider *)world.getCollider(colID);

  EXPECT_FLOAT_EQ(collider->points()[0].x, 25);
  EXPECT_FLOAT_EQ(collider->points()[0].y, 50);

  EXPECT_FLOAT_EQ(collider->points()[1].x, 50);
  EXPECT_FLOAT_EQ(collider->points()[1].y, 0);

  EXPECT_FLOAT_EQ(collider->points()[2].x, 0);
  EXPECT_FLOAT_EQ(collider->points()[2].y, 0);
}

TEST(PolyColliderTest, PersistsCCWPoints) {
  DynamicWorld2D world;
  ASSERT_TRUE(world.init());

  PointList2D points;

  // Counterclockwise order
  points.emplace_back(6, 4);
  points.emplace_back(8, 5);
  points.emplace_back(9, 7);
  points.emplace_back(4, 12);
  points.emplace_back(2, 7);

  collider2_id colID = world.genCollider<PolyCollider>(
      world.genRigidbody(), nullptr, colFunc, points);

  PolyCollider *collider = (PolyCollider *)world.getCollider(colID);

  // Points should be reversed into clockwise order
  EXPECT_FLOAT_EQ(collider->points()[0].x, 2);
  EXPECT_FLOAT_EQ(collider->points()[0].y, 7);

  EXPECT_FLOAT_EQ(collider->points()[1].x, 4);
  EXPECT_FLOAT_EQ(collider->points()[1].y, 12);

  EXPECT_FLOAT_EQ(collider->points()[2].x, 9);
  EXPECT_FLOAT_EQ(collider->points()[2].y, 7);

  EXPECT_FLOAT_EQ(collider->points()[3].x, 8);
  EXPECT_FLOAT_EQ(collider->points()[3].y, 5);

  EXPECT_FLOAT_EQ(collider->points()[4].x, 6);
  EXPECT_FLOAT_EQ(collider->points()[4].y, 4);
}
