#pragma once
#ifndef AVL_H
#define AVL_H
#include "Node.h"

class AVL {
private:
    Node* root;
    int nNum; // Node number of tree
    int height; //height of tree

public:
    AVL();
    virtual ~AVL();
    Node* Getroot() {
        return root;
    }
    void Setroot(Node* val) {
        root = val;
    }

    //GET HEIGHT TO CHECK IMBALANCE NODE 
    int GetHeight(Node*);

    //void LeftRotate(Node*&);
    Node* LeftRotate(Node*&);
    Node* RightRotate(Node*&);
    Node* LRRotate(Node*&);
    Node* RLRotate(Node*&);

    //TRAVERSE 
    void TravelNLR();
    void TravelLNR();
    void TravelLRN();
    void NLR(Node*);
    void LNR(Node*);
    void LRN(Node*);

    //BALANCE AVL TREE FUNCTION
    void balanceTreeFunction(Node*);

    // function travel top-down to find the "bottom most" imbalance node  
    Node* returnLastestImbalanceNode(Node* Root, Node* newNode);

    //INSERT 
    bool InsertNode(Node*);

    //DELETE 
    Node* findMaxValue(Node* node);
    bool deleteNode(int k);
    Node* search_x(Node* node, int k);
    void deleteAll();

    Node* InsertNode(Node*, Node*);
    //void InsertNodeRe(Node*);         
    //void deleteNode(Node*);
    Node* find_parent(Node* node, int k); //recursion may cause error -> search parent
};

#endif // AVL_TREE_H

