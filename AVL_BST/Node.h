//#pragma once
#ifndef NODE_H
#define NODE_H


class Node {
private:
    Node* left;
    Node* right;
    Node* parent;
    int key;
    int height;

public:
    Node();
    Node(int);
    virtual ~Node();

    Node* Getleft() {
        return left;
    }
    void Setleft(Node* val) {
        left = val;
    }
    Node* Getright() {
        return right;
    }
    void Setright(Node* val) {
        right = val;
    }
    Node* Getparent() {
        return parent;
    }
    void Setparent(Node* val) {
        parent = val;
    }
    int Getkey() {
        return key;
    }
    void Setkey(int val) {
        key = val;
    }
    int Getheight() {
        return height;
    }
    void Setheight(int val) {
        height = val;
    }

protected:
};

#endif // NODE_H