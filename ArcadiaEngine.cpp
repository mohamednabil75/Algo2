// ArcadiaEngine.cpp - STUDENT TEMPLATE
// TODO: Implement all the functions below according to the assignment requirements

#include "ArcadiaEngine.h"
#include <algorithm>
#include <queue>
#include <numeric>
#include <climits>
#include <cmath>
#include <cstdlib>
#include<cstring>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>

using namespace std;

// =========================================================
// PART A: DATA STRUCTURES (Concrete Implementations)
// =========================================================

// --- 1. PlayerTable (Double Hashing) ---
struct hashcell{
int key ;
string value ;
bool occupied ;
hashcell(){
    key = -1 ;
    occupied = false ;
}
};
class ConcretePlayerTable : public PlayerTable {
private:
    hashcell* arr ;
    int capacity ;
    int occupiedCells ;
protected:
    int h1(int key) { // multiplication hash function
        const double A = 0.6180339887; // this value of A i searched for it's the optimal value of A
        double product = (double)key * A;
        double fractional = product - int(product); 
        return (int)(capacity * fractional);
    }
    int h2(int key){ // midsquare function 
        long long keysquare = key*key ;
        string k = to_string(keysquare) ;
        int digitsTaken = to_string(capacity-1).length() ;
        while(k.length() < digitsTaken*2){
            k = "0" + k ;
        }
        int keySquareSz = k.length() ;
        int st = (keySquareSz - digitsTaken)/2 ;
        string finalKey = "" ;
        int last = st+digitsTaken ;
        do{
            finalKey+= k[st] ;
            st++ ;
        }while(st < last);
        
        int final = stoi(finalKey)%capacity ;
        if(final == 0){
            return 1 ;
        }
        return final ;
    }
    void rehashInsertion(int playerId , string & name){
        int hash1 = h1(playerId) ;
        int hash2 = h2(playerId) ;
        int index = hash1 ;
        // cout << "After first call to h1 index = " << index << endl;
        for (int i = 0; i < capacity; i++) {
            int index = (hash1 + i * hash2) % capacity;
            
            if (!arr[index].occupied) {
                arr[index].key = playerId;
                arr[index].value = name;
                arr[index].occupied = true;
                occupiedCells++;
                return;
            }
        }

    }
    void rehashing(){
        hashcell* oldarr = arr ;
        int oldSz = capacity ;
        capacity*=2 ;
        arr = new hashcell[capacity] ;
        occupiedCells = 0 ;
        for(int i = 0 ; i < oldSz ;i++){
            if(oldarr[i].occupied){
            rehashInsertion(oldarr[i].key , oldarr[i].value) ;
            }
        }
        delete[] oldarr ;
    }
public:
    ConcretePlayerTable() {
        arr = new hashcell[10] ;
        capacity = 10 ;
        occupiedCells = 0 ;
        // TODO: Initialize your hash table
    }
    void insert(int playerID, string name) override {
        // TODO: Implement double hashing insert
        // Remember to handle collisions using h1(key) + i * h2(key)
        double chechRehash = static_cast<double>(occupiedCells)/capacity ;
        // cout << "occupied cells and capacity now " << endl; 
        // cout << occupiedCells << endl;
        // cout << capacity << endl;
        if(chechRehash >= 0.7){
            cout << "rehashing work " << endl;
            rehashing() ;
        }
        int hash1 = h1(playerID) ;
        int hash2 = h2(playerID) ;
        int index = hash1 ;
        // cout << "After first call to h1 index = " << index << endl;
        for (int i = 0; i < capacity; i++) {
            int index = (hash1 + i * hash2) % capacity;
            
            if (!arr[index].occupied) {
                arr[index].key = playerID;
                arr[index].value = name;
                arr[index].occupied = true;
                occupiedCells++;
               // cout << "Player " << name << " inserted successfully :) at index " << index << endl;
                return;
            }
        }

    }
    string search(int playerID) override {
        // TODO: Implement double hashing search
        // Return "" if player not found
        int hash1 = h1(playerID) ;
        int hash2 = h2(playerID) ;
        int index = hash1 ;
        int i = 0 ;
        while(i < capacity){
            if(arr[index].occupied && arr[index].key == playerID){
                return arr[index].value ; ;
            }
            if(!arr[index].occupied){
                return "" ;
            }
            i++ ;
            index = (hash1+i*hash2)%capacity ;
        }
        return "";
    }
};

// --- 2. Leaderboard (Skip List) ---

class ConcreteLeaderboard : public Leaderboard {
private:
    // TODO: Define your skip list node structure and necessary variables
    // Hint: You'll need nodes with multiple forward pointers

public:
    ConcreteLeaderboard() {
        // TODO: Initialize your skip list
    }

    void addScore(int playerID, int score) override {
        // TODO: Implement skip list insertion
        // Remember to maintain descending order by score
    }

    void removePlayer(int playerID) override {
        // TODO: Implement skip list deletion
    }

    vector<int> getTopN(int n) override {
        // TODO: Return top N player IDs in descending score order
        return {};
    }
};

// --- 3. AuctionTree (Red-Black Tree) ---

class ConcreteAuctionTree : public AuctionTree {
private:
    // TODO: Define your Red-Black Tree node structure
    // Hint: Each node needs: id, price, color, left, right, parent pointers

public:
    ConcreteAuctionTree() {
        // TODO: Initialize your Red-Black Tree
    }

    void insertItem(int itemID, int price) override {
        // TODO: Implement Red-Black Tree insertion
        // Remember to maintain RB-Tree properties with rotations and recoloring
    }

    void deleteItem(int itemID) override {
        // TODO: Implement Red-Black Tree deletion
        // This is complex - handle all cases carefully
    }
};

// =========================================================
// PART B: INVENTORY SYSTEM (Dynamic Programming)
// =========================================================

int InventorySystem::optimizeLootSplit(int n, vector<int>& coins) {
    // TODO: Implement partition problem using DP
    // Goal: Minimize |sum(subset1) - sum(subset2)|
    // Hint: Use subset sum DP to find closest sum to total/2
    return 0;
}

int InventorySystem::maximizeCarryValue(int capacity, vector<pair<int, int>>& items) {
    // TODO: Implement 0/1 Knapsack using DP
    // items = {weight, value} pairs
    // Return maximum value achievable within capacity
    return 0;
}

long long InventorySystem::countStringPossibilities(string s) {
    // TODO: Implement string decoding DP
    // Rules: "uu" can be decoded as "w" or "uu"
    //        "nn" can be decoded as "m" or "nn"
    // Count total possible decodings
    return 0;
}

// =========================================================
// PART C: WORLD NAVIGATOR (Graphs)
// =========================================================

bool WorldNavigator::pathExists(int n, vector<vector<int>>& edges, int source, int dest) {
    // TODO: Implement path existence check using BFS or DFS
    // edges are bidirectional
    return false;
}

long long WorldNavigator::minBribeCost(int n, int m, long long goldRate, long long silverRate,
                                       vector<vector<int>>& roadData) {
    // TODO: Implement Minimum Spanning Tree (Kruskal's or Prim's)
    // roadData[i] = {u, v, goldCost, silverCost}
    // Total cost = goldCost * goldRate + silverCost * silverRate
    // Return -1 if graph cannot be fully connected
    return -1;
}

string WorldNavigator::sumMinDistancesBinary(int n, vector<vector<int>>& roads) {
    // TODO: Implement All-Pairs Shortest Path (Floyd-Warshall)
    // Sum all shortest distances between unique pairs (i < j)
    // Return the sum as a binary string
    // Hint: Handle large numbers carefully
    return "0";
}

// =========================================================
// PART D: SERVER KERNEL (Greedy)
// =========================================================

int ServerKernel::minIntervals(vector<char>& tasks, int n) {
    // TODO: Implement task scheduler with cooling time
    // Same task must wait 'n' intervals before running again
    // Return minimum total intervals needed (including idle time)
    // Hint: Use greedy approach with frequency counting
    return 0;
}

// =========================================================
// FACTORY FUNCTIONS (Required for Testing)
// =========================================================

extern "C" {
    PlayerTable* createPlayerTable() { 
        return new ConcretePlayerTable(); 
    }

    Leaderboard* createLeaderboard() { 
        return new ConcreteLeaderboard(); 
    }

    AuctionTree* createAuctionTree() { 
        return new ConcreteAuctionTree(); 
    }
}


int main()
{
    ConcretePlayerTable p ;
    p.insert(1 , "seif") ;
    p.insert(2 , "ezz") ;
    p.insert(3 , "nour") ;
    p.insert(8 , "anwar") ;
    p.insert(7 , "vini") ;
    p.insert(11 , "rodrigo") ;
    p.insert(14 , "kama") ;
    p.insert(5 , "jude") ;
    p.insert(70 , "carvacal") ;
   p.insert(22 , "abotrika") ;
    p.insert(10 , "Mbappe") ;
    cout << p.search(1) << endl ;
    cout << p.search(2) << endl ;
    cout << p.search(3) << endl ;
    cout << p.search(8) << endl;
    cout << p.search(7) << endl;
    cout << p.search(11) << endl;
    cout << p.search(14) << endl;
    cout << p.search(5) << endl;
    cout << p.search(300) << endl;
    cout << p.search(70) << endl;
    cout << p.search(22) << endl;
    cout << p.search(10) << endl;

    


    return 0 ;
}