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

long long WorldNavigator::minBribeCost(int n, int m, long long goldRate, long long silverRate, vector<vector<int>>& roadData) 
{
    vector<vector<pair<int, long long>>> adj(n);
    for (auto road : roadData)
    {
        int u = road[0];
        int v = road[1];
        long long goldCost = road[2];
        long long silverCost = road[3];
        long long totalCost = goldCost * goldRate + silverCost * silverRate;
        adj[u].push_back({v, totalCost});
        adj[v].push_back({u, totalCost});
    }

    vector<bool> inMST(n, false);
    vector<long long> minEdge(n, LLONG_MAX);
    minEdge[0] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
   
    pq.push({0, 0});
    long long MSTcost = 0;

    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();

        if (cost > minEdge[u])
            continue;
        if (inMST[u])
            continue;

        inMST[u] = true;
        MSTcost += cost;

        for (auto [v, edgeCost] : adj[u])
        {
            if (!inMST[v] && edgeCost < minEdge[v])
            {
                minEdge[v] = edgeCost;
                pq.push({edgeCost, v});
            }
        }
    }

    for (auto visited : inMST)
        if (!visited)
            return -1;

    return MSTcost;
}

string WorldNavigator::sumMinDistancesBinary(int n, vector<vector<int>>& roads) {
    TeleporterNetwork network(n, roads);
    return network.sumMinDistanceBinary();
}
