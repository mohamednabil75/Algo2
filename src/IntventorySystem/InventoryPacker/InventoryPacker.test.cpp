#include <gtest/gtest.h>
#include "InventoryPacker.h"

TEST(FirstSample, InventoryPacker)
{
    int capacity = 3;
    vector<pair<int, int>> items = { {1, 10}, {2, 15}, {3, 40} };
    InventoryPacker packer(capacity, items);
    EXPECT_EQ(packer.maximizeCarryValue(), 40);
}

TEST(SecondSample, InventoryPacker)
{
    int capacity = 5;
    vector<pair<int, int>> items = { {1, 10}, {2, 15}, {3, 40} };
    InventoryPacker packer(capacity, items);
    EXPECT_EQ(packer.maximizeCarryValue(), 55);
}

TEST(ThirdSample, InventoryPacker)
{
    int capacity = 10;
    vector<pair<int, int>> items = { {1, 10}, {2, 20}, {3, 30} };
    InventoryPacker packer(capacity, items);
    EXPECT_EQ(packer.maximizeCarryValue(), 60);
}