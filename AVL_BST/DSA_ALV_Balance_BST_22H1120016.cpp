#include "AVL.h"
#include<iostream>
using namespace std;

int main() {
    // TRAN DANG NAM - 22H1120016 - DATA STRUCTURE ALGORITH - SOPHOMORE 2023

    AVL* tree = new AVL();
    Node* n;
    n = new Node(50);
    tree->InsertNode(n);
    n = new Node(20);
    tree->InsertNode(n);
    n = new Node(30);
    tree->InsertNode(n);
    n = new Node(10);
    tree->InsertNode(n);
    n = new Node(-5);
    tree->InsertNode(n);
    n = new Node(7);
    tree->InsertNode(n);
    n = new Node(15);
    tree->InsertNode(n);
    n = new Node(35);
    tree->InsertNode(n);
    n = new Node(57);
    tree->InsertNode(n);
    n = new Node(65);
    tree->InsertNode(n);
    n = new Node(55);
    tree->InsertNode(n);
    n = new Node(-1);
    tree->InsertNode(n);

    tree->deleteNode(35);
    tree->deleteNode(55);
    tree->deleteNode(20);
    tree->deleteNode(15);
    tree->TravelLRN();

    tree->deleteAll();
}
