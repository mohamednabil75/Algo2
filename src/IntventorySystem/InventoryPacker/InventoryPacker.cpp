#include "InventoryPacker.h"

int InventoryPacker::maximizeCarryValueHelper(int index, int remainingCapacity) {
    if (index >= items.size() || remainingCapacity <= 0) {
        return 0;
    }

    pair<int, int> key = {index, remainingCapacity};
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    int weight = items[index].first;
    int value = items[index].second;

    int maxValue = maximizeCarryValueHelper(index + 1, remainingCapacity);

    if (weight <= remainingCapacity) {
        maxValue = max(maxValue, value + maximizeCarryValueHelper(index + 1, remainingCapacity - weight));
    }

    memo[key] = maxValue;
    return maxValue;
}

int InventoryPacker::maximizeCarryValue() {
    memo.clear();
    return maximizeCarryValueHelper(0, capacity);
}