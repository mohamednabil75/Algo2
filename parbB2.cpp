#include <bits/stdc++.h>
using namespace std;

bool LootSplit( int nums[], int size,int target) {
    int size2=(int)pow(2,size);
    int vec[size2+1]={0};
    vec[0]=0;
    cout<<vec[1]<<endl;
    for(int i=0;i<size;i++){
        int gap=pow(2,i);
        for(int j=gap;j<gap*2;j++){
            vec[j]+=nums[i]+vec[j-gap];
            // cout<<j<<"     "<<vec[j]<<endl;
        }
    }

    for (int i=0;i<size2;i++){
        if(vec[i]==target)return true;
        // cout<<vec[i]<<" ";
    }
    cout<<endl;
    return false;  
}



int main() {
    int size;
    // cin>>size;
    size=5;
    // int vec[size];
    int vec[size]={5,1,11,5,12};

    // for(int i=0;i<size;i++)cin>>vec[i];
    int sum=0;
    for(int x :vec)sum+=x;
    if(sum%2==1)cout<<"No"<<endl;
    else if(LootSplit(vec,size,sum/2)){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }

}
