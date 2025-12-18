#include "../ArcadiaEngine.h"
#include "Navigator/TeleporterNetwork.h"
#include <queue>

bool WorldNavigator::pathExists(int n, vector<vector<int>>& edges, int source, int dest) {
    vector<vector<int>> arr2D(n, vector<int>(n, 0));

    for (auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        arr2D[u][v] = 1;
        arr2D[v][u] = 1;
    }

    vector<bool> visited(n, false);
    visited[source] = true;
    queue<int> que;
    que.push(source);

    while (!que.empty())
    {
        int current = que.front();
        que.pop();
        if (current == dest)
            return true;

        for (auto i = 0; i < n; i++)
        {
            if (arr2D[current][i])
            {
                if (!visited[i])
                {
                    que.push(i);
                    visited[i] = true;
                }
            }
        }
    }
    return false;
}

long long WorldNavigator::minBribeCost(int n, int m, long long goldRate, long long silverRate,
                                       vector<vector<int>>& roadData) {
    vector<vector<pair<int, long long>>> adj(n);
    for (auto road : roadData)
    {
        int u = road[0];
        int v = road[1];
        int goldCost = road[2];
        int silverCost = road[3];
        int totalCost = goldCost * goldRate + silverCost * silverRate;
        adj[u].push_back({v, totalCost});
        adj[v].push_back({u, totalCost});
    }
    vector<bool> inMST(n, false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, 0});
    long long MSTcost = 0;
    int connected = 0;

    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();
        if (inMST[u])
            continue;
        inMST[u] = true;
        MSTcost += cost;
        connected++;
        for (auto [v, edgeCost] : adj[u])
        {
            if (!inMST[v])
            {
                pq.push({edgeCost, v});
            }
        }
    }
    if (connected == n - 1)
        return MSTcost;

    return -1;
}

string WorldNavigator::sumMinDistancesBinary(int n, vector<vector<int>>& roads) {
    TeleporterNetwork network(n, roads);
    return network.sumMinDistanceBinary();
}
