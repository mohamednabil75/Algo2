#include "../ArcadiaEngine.h"
#include <vector>
#include <algorithm>

using namespace std;

int ServerKernel::minIntervals(vector<char>& tasks, int n) {
    if (tasks.empty()) return 0;

    vector<int> freq(26, 0);
    for (char t : tasks) freq[t - 'A']++;

    // Sort frequencies in descending order
    sort(freq.begin(), freq.end(), greater<int>());

    int maxFreq = freq[0];

    // calculate idle slots needed for the most frequent task
    int idleSlot = (maxFreq - 1) * n;

    // Try to fill idle slots with the remaining tasks
    for (int i = 1; i < 26; ++i) {
        idleSlot -= min(freq[i], maxFreq - 1);
    }

    // If idleSlots becomes negative, it means we filled everything with tasks
    idleSlot = max(0, idleSlot);

    return tasks.size() + idleSlot;
}
