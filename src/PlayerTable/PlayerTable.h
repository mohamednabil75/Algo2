#include "../ArcadiaEngine.h"
#include <string>
#include <stdexcept>

using namespace std;

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
    int h1(int key) { 
        int h = key%capacity;
        return h;
    }

    int h2(int key){ 
        int h = 51-(key%51) ;
        if(key == 0){
            return 1 ;
        }
        return h;
    }
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
        if(occupiedCells == capacity){
            throw overflow_error("table is full!");
        }
        int hash1 = h1(playerID) ;
        int hash2 = h2(playerID) ;
        for (int i = 0; i < capacity; i++) { //double hashing 
            int index = (hash1 + i * hash2) % capacity;
            
            if (!arr[index].occupied) {
                arr[index].key = playerID;
                arr[index].value = name;
                arr[index].occupied = true;
                occupiedCells++;
               //cout << "Player " << name << " inserted successfully :) at index " << index << endl;
                return;
            }
            if(arr[index].key == playerID){
                arr[index].value = name ;
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