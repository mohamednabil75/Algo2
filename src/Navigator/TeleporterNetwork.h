#include <vector>
#include <string>

struct GraphNode {
    int id;
    std::vector<std::pair<GraphNode*, int>> adjacents;
};

class TeleporterNetwork {

private:
    int n;
    std::vector<std::vector<int>> roads;
    std::vector<GraphNode> nodes;

    std::vector<int> dijkstra(int start);

public:
    TeleporterNetwork(int n, const std::vector<std::vector<int>>& roads) : n(n), roads(roads) {
        nodes.resize(n);

        for (int i = 0; i < n; ++i) {
            nodes[i] = GraphNode{i};
        }

        for (const auto& road : roads) {
            int from = road[0];
            int to = road[1];
            int distance = road[2];
            nodes[from].adjacents.emplace_back(&nodes[to], distance);
        }
    }
    
    int sumMinDistance();
    std::string sumMinDistanceBinary();
};
