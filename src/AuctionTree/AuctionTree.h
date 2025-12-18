#include <iostream>
#include "../ArcadiaEngine.h"

using namespace std;

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
