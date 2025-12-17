#include <gtest/gtest.h>
#include "TeleporterNetwork.h"

TEST(FirstSample, TeleporterNetwork) 
{
    int n = 3;
    std::vector<std::vector<int>> roads = {
        {0, 1, 1},
        {1, 2, 2}
    };

    TeleporterNetwork network(n, roads);
    int result = network.sumMinDistance();
    int expected = 6;
    EXPECT_EQ(result, expected);
}

TEST(SecondSample, TeleporterNetwork) 
{
    int n = 2;
    std::vector<std::vector<int>> roads = {
        {0, 1, 4}
    };

    TeleporterNetwork network(n, roads);
    int result = network.sumMinDistance();
    int expected = 4;
    EXPECT_EQ(result, expected);
}

TEST(ThirdSample, TeleporterNetwork) 
{
    int n = 3;
    std::vector<std::vector<int>> roads = {
        {0, 1, 2},
        {0, 2, 8}
    };

    TeleporterNetwork network(n, roads);
    int result = network.sumMinDistance();
    int expected = 10;
    EXPECT_EQ(result, expected);
}