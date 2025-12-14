// ArcadiaEngine.cpp - STUDENT TEMPLATE
// TODO: Implement all the functions below according to the assignment requirements

#include "ArcadiaEngine.h"
#include <algorithm>
#include <queue>
#include <numeric>
#include<time.h>
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
    // void rehashInsertion(int playerId , string & name){
    //     int hash1 = h1(playerId) ;
    //     int hash2 = h2(playerId) ;
    //     int index = hash1 ;
    //     // cout << "After first call to h1 index = " << index << endl;
    //     for (int i = 0; i < capacity; i++) {
    //         int index = (hash1 + i * hash2) % capacity;
            
    //         if (!arr[index].occupied) {
    //             arr[index].key = playerId;
    //             arr[index].value = name;
    //             arr[index].occupied = true;
    //             occupiedCells++;
    //             return;
    //         }
    //     }

    // }
    // void rehashing(){
    //     hashcell* oldarr = arr ;
    //     int oldSz = capacity ;
    //     capacity*=2 ;
    //     arr = new hashcell[capacity] ;
    //     occupiedCells = 0 ;
    //     for(int i = 0 ; i < oldSz ;i++){
    //         if(oldarr[i].occupied){
    //         rehashInsertion(oldarr[i].key , oldarr[i].value) ;
    //         }
    //     }
    //     delete[] oldarr ;
    // }
public:
    ConcretePlayerTable() {
        arr = new hashcell[101] ;
        capacity = 101 ;
        occupiedCells = 0 ;
        // TODO: Initialize your hash table
    }
    void insert(int playerID, string name) override {
        // TODO: Implement double hashing insert
        // Remember to handle collisions using h1(key) + i * h2(key)
        //double checkRehash = static_cast<double>(occupiedCells)/capacity ;
        // cout << "occupied cells and capacity now " << endl; 
        // cout << occupiedCells << endl;
        // cout << capacity << endl;
        // if(checkRehash >= 0.7){
        //    // cout << "rehashing work " << endl;
        //     rehashing() ;
        // }
        if(occupiedCells == capacity){
            cout << "Table is full!" << endl;
            return ;
        }
        int hash1 = h1(playerID) ;
        int hash2 = h2(playerID) ;
        int index = hash1 ;
        // cout << "After first call to h1 index = " << index << endl;
        for (int i = 0; i < capacity; i++) { //double hashing 
            int index = (hash1 + i * hash2) % capacity;
            
            if (!arr[index].occupied) {
                arr[index].key = playerID;
                arr[index].value = name;
                arr[index].occupied = true;
                occupiedCells++;
               cout << "Player " << name << " inserted successfully :) at index " << index << endl;
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
    struct node {
        int id;
        int score;
        vector<node*> next;
        node(int id, int score, int level) : 
            id(id), score(score), next(level + 1, nullptr) {}
    };
    node* head ;
    const int max = 20 ;
    int currentMaxLevel ;
    int blocknum ;

protected:
    int getrandomlevel(){
        int level = 0 ;
        while(rand() % 2  == 0 && level < max ){
            level++ ;
        }
        return level ;
    }
    node* searchByScore(int score){
        node* curr = head ;
        for(int i = currentMaxLevel ; i >=0 ;i--){
            while(curr->next[i] !=nullptr && score > curr->next[i]->score){
                curr = curr->next[i] ;
            }
        }
        curr = curr->next[0] ;
        if(curr != nullptr && curr->score == score){
            return curr ;
        }
        return nullptr ;
    }
    node* searchById(int id){ // that linear search due to skip list not ordered by id 
        node *curr = head->next[0] ;
        while(curr !=nullptr && curr->id != id){
            curr = curr->next[0] ;
        }
        return curr ;

    }
public:
    ConcreteLeaderboard() {
        // TODO: Initialize your skip list
        currentMaxLevel = 0 ;
        head = new node(-1 , -1000 , max) ;
        blocknum = 0 ;
        srand(time(0)) ;
    }
    ~ConcreteLeaderboard() {
        node* curr = head->next[0];
        while (curr != nullptr) {
            node* temp = curr;
            curr = curr->next[0];
            delete temp;
        }
        delete head;
    }

    void addScore(int playerID, int score) override {
        // TODO: Implement skip list insertion
        // Remember to maintain descending order by score
        node*checkid = searchById(playerID);
        if(checkid != nullptr){
            cout << playerID << " already exists !" << endl;
            return ;
        }
        vector<node*> path(max+1 ,nullptr) ;
        node* curr = head ;
        node* checkDup = searchByScore(score) ;
        if(checkDup != nullptr && checkDup->id == playerID){
            cout << "Player already exist " << endl;
            return ;
        }
        for(int i = currentMaxLevel ; i >=0 ;i--){
            while(curr->next[i] != nullptr && (curr->next[i]->score > score || (curr->next[i]->score == score&& curr->next[i]->id < playerID ))){
                curr = curr->next[i] ;
            }
            path[i] = curr ;
        }
        curr = curr->next[0] ;
        int level = getrandomlevel() ;
        if(level > currentMaxLevel){
            for(int i = currentMaxLevel+1 ; i <= level ;i++){
                path[i] = head ;
            }
            this->currentMaxLevel = level ;
        }
        node* insertedBlock = new node(playerID,score ,level) ;
        for(int i = 0 ; i <= level ;i++){
            insertedBlock->next[i] = path[i]->next[i] ;
            path[i]->next[i] = insertedBlock ;
        }
        blocknum++ ;

    }

void removePlayer(int playerID) override {
    node* target = searchById(playerID);
    if (target == nullptr) {
        cout << "Player not found!" << endl;
        return;
    }
    int score = target->score;
    int id = target->id; 
    node* curr = head;
    int targetHeight = target->next.size() - 1; // to limit the search area according to the number of next pointer of target deleted node 
    vector<node*> path(targetHeight + 1, nullptr);
    for (int i = targetHeight; i >= 0; i--) {
        while (curr->next[i] != nullptr && 
               (curr->next[i]->score > score || 
                (curr->next[i]->score == score && curr->next[i]->id < id))) {
            curr = curr->next[i];
        }
        path[i] = curr;
    }
    for (int i = 0; i <= targetHeight; i++) {
        if (path[i]->next[i] == target) {
            path[i]->next[i] = target->next[i];
        }
    }
    while (currentMaxLevel > 0 && head->next[currentMaxLevel] == nullptr) { // that in case the deleted node is the heighest block we update currentmax level
        currentMaxLevel--;
    }
    
    delete target;
    blocknum--;
}
    void display(){
        for(int i = currentMaxLevel ; i >=0 ; i--){
            node *temp =head->next[i] ;
            while(temp!= nullptr){
                cout << "Level " << i << " " << temp->id << ":" << temp->score << "        " ;
                temp = temp->next[i] ;          
            }
            cout << endl;
        }
    }

    vector<int> getTopN(int n) override {
        // TODO: Return top N player IDs in descending score order
        vector<int> v ;
        node*temp = head->next[0] ;
        for(int i = 0 ; i < n ; i++){
            if(temp == nullptr){
                cout << "list not big enough !" << endl;
                return {} ;
            }
            v.push_back(temp->id) ;
            temp = temp->next[0] ;
        }
        return v ;

    }
};

// --- 3. AuctionTree (Red-Black Tree) ---
class ConcreteAuctionTree : public AuctionTree {
private:
    // TODO: Define your Red-Black Tree node structure
    // Hint: Each node needs: id, price, color, left, right, parent pointers
    struct treeNode{
    int id ;
    int price ;
    char color ;
    treeNode* left ;
    treeNode* right ;
    treeNode* parent ;
    treeNode(int id , int price){
        this->id = id ;
        this->price = price ;
        color = 'R' ;
        left = nullptr ;
        right = nullptr ;
        parent = nullptr ;
    }
    treeNode(){
        color = 'R' ;
        left = nullptr ;
        right = nullptr ;
        parent = nullptr ;
    }
};
    treeNode* root ; 
    int nodecount ;

 protected:
    void leftRotation(treeNode *x){
        treeNode *p = x->parent ;
        treeNode *c = x->right ;
        treeNode *cc = c->left ;
        c->left = x ;
        x->parent = c ;
        x->right = cc ;
        if(cc != nullptr){
            cc->parent = x ;
        }
        if(p == nullptr){
            root = c ;
        }
        else {
            if(x == p->right){
               p->right = c ;
            }
            else{
                p->left = c ;
            }
            c->parent = p ;
        }
    }
    void rightRotation(treeNode *x){
        treeNode *p = x->parent ;
        treeNode *c = x->left ;
        treeNode *cc = c->right ;
        c->right = x ;
        x->parent = c ;
        x->left = cc ;
        if(cc != nullptr){
            cc->parent = x ;
        }
        if(p == nullptr){
            root = c ;
        }
        else {
            if(x == p->left){
                p->left = c ;
            }
            else{
                p->right = c ;
            }
            c->parent = p ;
        }
    }
    void recolor(treeNode *node1 , treeNode *node2){
        if(node1->color == node2->color){
            char c = node1->color ;
            c = (c == 'R') ? c = 'B' : c = 'R' ;
            node1->color = c ;
            node2->color = c ;
            return ;
        }
        char c = node1->color ;
        node1->color = node2->color ;
        node2->color = c ;
    }
    treeNode* predecessor(treeNode *n){
        treeNode *target = nullptr ;
        treeNode *pretarget = n->left ;
        while(pretarget != nullptr){
            target = pretarget ;
            pretarget = pretarget->right ;
        }
        return target ;
    }
    treeNode* getNodeById(int id , treeNode* n){ // linear search 
        if(n == nullptr){
            return nullptr ;
        }
        if(n->id == id){
            return n ;
        }
        treeNode*l = getNodeById(id , n->left) ;
        if(l != nullptr){
            return l ;
        }
        treeNode *r = getNodeById(id , n->right) ;
        if(r != nullptr){
            return r ;
        }
        return nullptr ;
    }
    void inorder(treeNode*n){
        if(n == nullptr){
            return ;
        }
        inorder(n->left) ;
        cout << n->id << " " << n->price << " " << n->color << endl; 
        inorder(n->right) ;
    }
    treeNode* getSibling(treeNode *x){
        treeNode *sib = nullptr ;
        treeNode *p = x->parent ;
        if(p == nullptr){
            return nullptr ;
        }
        if(x = p->left){
            sib = p->right ;
        }
        else{
            sib = p->left ;
        }
        return sib ;
    }
    
    void fixDeletion(treeNode* x, treeNode* xparent) {
    while ((x == nullptr || x->color == 'B') && xparent != nullptr) {

        treeNode* sib;
        if (x == xparent->left)
            sib = xparent->right;
        else
            sib = xparent->left;

        if (sib != nullptr && sib->color == 'R') {
            sib->color = 'B';
            xparent->color = 'R';

            if (x == xparent->left){
                leftRotation(xparent);
            }
            else{
                rightRotation(xparent);
            }

            if (x == xparent->left)
                sib = xparent->right;
            else
                sib = xparent->left;
        }
        bool allblack =
            (sib == nullptr ||
             ((sib->left == nullptr || sib->left->color == 'B') &&
              (sib->right == nullptr || sib->right->color == 'B')));

        if (allblack) {
            if (sib != nullptr){
                 sib->color = 'R';
            }
            x = xparent;
            xparent = xparent->parent;
            continue;
        }

        if (x == xparent->left) {
            if (sib->right == nullptr || sib->right->color == 'B') {
                if (sib->left!=nullptr){
                 sib->left->color = 'B';
                }
                sib->color = 'R';
                rightRotation(sib);
                sib = xparent->right;
            }

            sib->color = xparent->color;
            xparent->color = 'B';
            if (sib->right != nullptr) {
                sib->right->color = 'B';
            }
            leftRotation(xparent);
        } 
        else {
            if (sib->left == nullptr || sib->left->color == 'B') {
                if (sib->right != nullptr){
                    sib->right->color = 'B';
                } 
                sib->color = 'R';
                leftRotation(sib);
                sib = xparent->left;
            }

            sib->color = xparent->color;
            xparent->color = 'B';
            if (sib->left != nullptr) {
                sib->left->color = 'B';
            }
            rightRotation(xparent);
        }
        break;
    }

    if (x != nullptr)
        x->color = 'B';
}




public:
    ConcreteAuctionTree() {
        // TODO: Initialize your Red-Black Tree
        root = nullptr ;
        nodecount = 0 ;
    }

    void insertItem(int itemID, int price) override {
        // TODO: Implement Red-Black Tree insertion
        // Remember to maintain RB-Tree properties with rotations and recoloring
        treeNode* check = getNodeById(itemID, root) ;
        if(check != nullptr && check->price == price){
            cout << "Item " << check->id << " : " << check->price <<" already exists !" << endl;
            return ;
        }
        treeNode *newnode = new treeNode(itemID , price) ;
        if(root == nullptr){
            newnode->color = 'B' ;
            root = newnode ;
        }
        else {
        treeNode *pre = nullptr ;
        treeNode *next = root ;
        while(next != nullptr){
            pre = next ;
            if(newnode->price > next->price){
                next = next->right ;
            }
            else {
                next = next->left ;
            }
        }
        if(newnode->price > pre->price){
            pre->right = newnode ;
        }
        else{
            pre->left = newnode ;
        }
        newnode->parent = pre ;
        treeNode *curr = newnode ;
        while(curr != root && curr->parent != nullptr &&curr->parent->color == 'R'){
            treeNode *uncle ;
            treeNode *parent = curr->parent ;
            treeNode *gp = parent->parent ;
            if(parent == gp->right){
                uncle = gp->left ;
            } 
            else{
                uncle = gp->right ;
            }
            if(uncle!= nullptr && uncle->color == 'R'){ // case 1 
                parent->color = 'B' ;
                uncle->color = 'B' ;
                gp->color = 'R' ;
                curr = gp ;
                continue;
            }
            else {
                if(parent == gp->right){
                    if(curr == parent->left){
                        rightRotation(parent) ;
                        curr = parent ;
                        parent = curr->parent ;
                    }
                    leftRotation(gp) ;
                    recolor(parent , gp) ;
                    break ;
                }
                else {
                    if(curr == parent->right){
                        leftRotation(parent) ;
                        curr = parent ;
                        parent = curr->parent ;
                    }
                    rightRotation(gp) ;
                    recolor(parent, gp) ;
                    break ;
                }
            }
    }
        }
        root->color = 'B' ;
        nodecount++ ;
    }
    void display(){
        if(root == nullptr){
            cout << "Tree is empty !" << endl; 
            return ;
        }
        inorder(root) ;
    }

void deleteItem(int itemID) override {
    if (root == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }
    treeNode* target = getNodeById(itemID, root);
    if (target == nullptr) {
        cout << "Item " << itemID << " doesn't exist!" << endl;
        return;
    }

    treeNode* y = target;      
    treeNode* x = nullptr;    
    treeNode* xparent = nullptr;
    char originalColor = y->color;

    if (target->left == nullptr && target->right == nullptr) {
        if (target == root) {
            root = nullptr;
        } else {
            xparent = target->parent; 
            if (target == target->parent->left) {
                target->parent->left = nullptr;
            } else {
                target->parent->right = nullptr;
            }
        }
        delete target;
        nodecount--;
        if (originalColor == 'B') {
            fixDeletion(nullptr, xparent);
        }
        return;
    }
    if (target->left == nullptr || target->right == nullptr) {
        x = (target->left != nullptr) ? target->left : target->right;
        xparent = target->parent;

        if (target == root) {
            root = x;
            if (x != nullptr) x->parent = nullptr;
        } else {
            if (target == target->parent->left) {
                target->parent->left = x;
            } else {
                target->parent->right = x;
            }
            if (x != nullptr) x->parent = target->parent;
        }

        delete target;
        nodecount--;
        
        if (originalColor == 'B') {
            if (x == nullptr) {
                fixDeletion(nullptr, xparent);
            } else {
                fixDeletion(x, xparent);
            }
        }
        return;
    }
    y = predecessor(target);
    originalColor = y->color;
    x = y->left;
    if (y->parent == target) {
        xparent = y;
        target->left = x;
        if (x != nullptr) {

            x->parent = target;
        }
    } 
    else {
        xparent = y->parent;
        y->parent->right = x; 
        if (x != nullptr) x->parent = y->parent;
    }
    target->id = y->id;
    target->price = y->price;
    delete y;
    nodecount--;
    if (originalColor == 'B') {
        fixDeletion(x, xparent);
    }
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
//     ConcretePlayerTable p ;
//     p.insert(11,"mosalah") ;
//     p.insert(17 , "seif") ;
//     p.insert(2 , "ezz") ;
//     p.insert(3 , "nour") ;
//     p.insert(18 , "anwar") ;
//     p.insert(7 , "vini") ;
//     p.insert(8 , "kroos") ;
//     p.insert(14 , "kama") ;
//     p.insert(5 , "jude") ;
//     p.insert(70 , "carvacal") ;
//    p.insert(22 , "abotrika") ;
//     p.insert(10 , "Mbappe") ;
//     cout << p.search(11) << endl;
//     cout << p.search(17) << endl ;
//     cout << p.search(2) << endl ;
//     cout << p.search(3) << endl ;
//     cout << p.search(18) << endl;
//     cout << p.search(7) << endl;
//     cout << p.search(8) << endl;
//     cout << p.search(14) << endl;
//     cout << p.search(5) << endl;
//     cout << p.search(300) << endl;
//     cout << p.search(70) << endl;
//     cout << p.search(22) << endl;
//     cout << p.search(10) << endl;


// ConcreteAuctionTree t ;
// t.insertItem(1,20) ;
// t.insertItem(2,30) ;
// t.insertItem(3,5) ;
// t.insertItem(7,10) ;
// t.insertItem(8,15) ;
// t.insertItem(18,40) ;
// t.insertItem(13,19) ;
// t.insertItem(9,3) ;
// t.insertItem(11,17) ;
// t.insertItem(16,8) ;
// t.insertItem(1,20) ;
// t.deleteItem(7) ;
// t.deleteItem(1) ;
// t.deleteItem(2) ;
// t.deleteItem(18) ;
// t.display() ;

// ConcreteLeaderboard b ;
// b.addScore(1,20) ;
// b.addScore(2,30) ;
// b.addScore(3,40) ;
// b.addScore(4,50) ;
// b.addScore(9,40) ;
// b.addScore(17,90) ;
// b.addScore(19,150) ;
// b.addScore(24,120) ;

// b.display() ;
// vector<int>v = b.getTopN(7) ;
// for(int i = 0 ; i < v.size() ;i++){
//     cout << i+1 << " " << v[i] << endl;
// }

// b.removePlayer(19) ;
// b.removePlayer(24) ;
// b.removePlayer(1) ;
// b.removePlayer(2) ;

// b.display() ;


    


    return 0 ;
}