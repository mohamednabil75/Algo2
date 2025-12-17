#include "TeleporterNetwork.h"
#include <queue>

std::vector<int> TeleporterNetwork::dijkstra(int start) {
    std::vector<int> distances(n, INT_MAX);
    distances[start] = 0;

    using PII = std::pair<int, int>; // (distance, node_id)
    std::priority_queue<PII, std::vector<PII>, std::greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [dist, node] = pq.top();
        pq.pop();

        if (dist > distances[node]) continue;

        for (const auto& [neighbor, weight] : nodes[node].adjacents) {
            int v = neighbor->id;
            int newDist = dist + weight;
            if (newDist < distances[v]) {
                distances[v] = newDist;
                pq.emplace(newDist, v);
            }
        }
    }

    return distances;
}

int TeleporterNetwork::sumMinDistance() {
    int totalDistance = 0;

    for (int i = 0; i < n; ++i) {
        std::vector<int> distances = dijkstra(i);
        for (int j = 0; j < n; ++j) {
            if (distances[j] != INT_MAX) {
                totalDistance += distances[j];
            }
        }
    }

    return totalDistance;
}

std::string TeleporterNetwork::sumMinDistanceBinary() {
    int totalDistance = sumMinDistance();

    if (totalDistance == 0) return "0";
    std::string binary;
    while (totalDistance > 0) {
        binary = (totalDistance % 2 == 0 ? "0" : "1") + binary;
        totalDistance /= 2;
    }

    return binary;
}