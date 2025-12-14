#include <vector>
#include <map>
using namespace std;

class InventoryPacker {
public:
    InventoryPacker(int capacity, const vector<pair<int, int>>& items) : capacity(capacity), items(items) {}

    int maximizeCarryValue();

private:
    int capacity;
    vector<pair<int, int>> items;
    map<pair<int, int>, int> memo;

    int maximizeCarryValueHelper(int index, int remainingCapacity);
};