#include <bits/stdc++.h>
#include "src/IntventorySystem/InventoryPacker/InventoryPacker.h"
using namespace std;


class InventorySystem{
    public:
    bool optimizeLootSplit(int n, vector<int>& coins);
    int maximizeCarryValue(int capacity, vector<pair<int, int>>& items);
    long long countStringPossibilities(string s);

};
bool InventorySystem::optimizeLootSplit(int n, vector<int>& coins) {
    vector<bool>vec(n+1,false);
    vec[0]=true;
    for (int x :coins){
        for (int i=n;i>=x;i--){
            vec[i]= vec[i]||vec[i-x];
        }
    }
    return vec[n];

    }

int InventorySystem::maximizeCarryValue(int capacity, vector<pair<int, int>>& items) {
    InventoryPacker packer = InventoryPacker(capacity, items);
    return packer.maximizeCarryValue();
}


long long InventorySystem:: countStringPossibilities(string s) {
    int n = s.size();

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;  
    dp[1] = 1;  

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1]; 

        if ((s[i - 1] == 'u' && s[i - 2] == 'u') ||
            (s[i - 1] == 'n' && s[i - 2] == 'n')) {
            dp[i] = (dp[i] + dp[i - 2]) ;
        }
    }

    return dp[n];

private:
    

}


int main() {
    InventorySystem system;
    int size;
    // cin>>size;
    size=5;
    // int vec[size];
    vector<int>vec={5,1,11,5};

    // for(int i=0;i<size;i++)cin>>vec[i];
    int sum=0;
    for(int x :vec)sum+=x;
    if(sum%2==1)cout<<"No"<<endl;
    else if(system.optimizeLootSplit(sum/2,vec)){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    int output=system.countStringPossibilities("suuunn");
    cout<<output<<endl;

}
