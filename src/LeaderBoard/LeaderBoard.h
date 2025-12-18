#include <iostream>
#include <vector>
#include "../ArcadiaEngine.h"

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