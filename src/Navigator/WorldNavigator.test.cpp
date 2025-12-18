#include <gtest/gtest.h>
#include "WorldNavigator.cpp"

TEST(MinBribeCostTest, BasicAssertions) {
    WorldNavigator navigator;
    int n = 3;
    int m = 3;
    long long goldRate = 1;
    long long silverRate = 1;
    vector<vector<int>> roadData = {
        {0, 1, 10, 0},
        {1, 2, 5, 0},
        {0, 2, 20, 0}
    };

    long long result = navigator.minBribeCost(n, m, goldRate, silverRate, roadData);
    EXPECT_EQ(result, 15);
}

TEST(MinBribeCostTest, DisconnectedGraph) {
    WorldNavigator navigator;
    int n = 4;
    int m = 2;
    long long goldRate = 1;
    long long silverRate = 1;
    vector<vector<int>> roadData = {
        {0, 1, 10, 0},
        {2, 3, 5, 0}
    };

    long long result = navigator.minBribeCost(n, m, goldRate, silverRate, roadData);
    EXPECT_EQ(result, -1);
}

TEST(MinBribeCostTest, SingleNode) {
    WorldNavigator navigator;
    int n = 1;
    int m = 0;
    long long goldRate = 1;
    long long silverRate = 1;
    vector<vector<int>> roadData = {};

    long long result = navigator.minBribeCost(n, m, goldRate, silverRate, roadData);
    EXPECT_EQ(result, 0);
}