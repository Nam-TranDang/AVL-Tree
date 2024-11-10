#include "AVL.h"
#include <iostream>
#include "Node.h"
using namespace std;

AVL::AVL() {
    //ctor
    this->root = nullptr;
    height = 0;
    nNum = 1;
}

AVL::~AVL()
{
    //dtor
}

//GET HEIGHT of node to calculate balance 
int AVL::GetHeight(Node* p) {
    if (p == nullptr) {
        return 0;
    }
    else {
        return 1 + max(GetHeight(p->Getleft()), GetHeight(p->Getright()));
    }
}

//ROTATE
//reminder: if root = imbalance node -> set balance node to root (set parent of balance node = nullptr) -> if not, i'll get error
Node* AVL::LeftRotate(Node*& P) {

    Node* Q;
    Node* T;
    Q = P->Getright();
    T = Q->Getleft();
    P->Setright(Q->Getleft());
    Q->Setleft(P);
    P->Setparent(Q);

    if (T != nullptr)
        T->Setparent(P);

    if (P == root) {
        Setroot(Q);
        Q->Setparent(nullptr);
        return 0;
    }
    return Q;
}

Node* AVL::RightRotate(Node*& P) {
    Node* Q;
    Node* T;
    Q = P->Getleft();
    T = Q->Getright();
    P->Setleft(Q->Getright());
    Q->Setright(P);
    P->Setparent(Q);

    if (T != nullptr)
        T->Setparent(P);

    if (P == root) {
        Setroot(Q);
        Q->Setparent(nullptr);
        return 0;
    }
    return Q;

}

Node* AVL::LRRotate(Node*& P) {
    Node* Q;
    Node* T;
    Node* childOfT = nullptr;

    Q = P->Getleft();
    T = Q->Getright();

    //check child of T: if it null -> then don't execute 
    if (T->Getleft() != nullptr) {
        childOfT = T->Getleft();
        T->Setleft(nullptr);
    }
    else {
        childOfT = T->Getright();
        T->Setright(nullptr);
    }

    P->Setleft(nullptr);
    Q->Setright(nullptr);
    if (childOfT != nullptr) {
        if (childOfT->Getkey() < T->Getkey()) {
            Q->Setright(childOfT);
            childOfT->Setparent(Q);
        }
        else {
            P->Setleft(childOfT);
            childOfT->Setparent(P);
        }
    }

    T->Setleft(Q);
    T->Setright(P);

    P->Setparent(T);
    Q->Setparent(T);

    if (P == root) {    //case if it's a imbalance + root
        Setroot(T);
        T->Setparent(nullptr); //remove parent, because root dont have parent 

        return 0;
    }
    return T;

}

Node* AVL::RLRotate(Node*& P) {
    Node* Q;
    Node* T;
    Node* childOfT = nullptr;;

    Q = P->Getright();
    T = Q->Getleft();

    if (T->Getleft() != nullptr) {
        childOfT = T->Getleft();
    }
    else {
        childOfT = T->Getright();
    }

    P->Setright(nullptr);
    Q->Setleft(nullptr);

    if (childOfT != nullptr) {
        if (childOfT->Getkey() < T->Getkey()) {
            P->Setright(childOfT);
            childOfT->Setparent(P);
        }
        else {
            Q->Setleft(childOfT);
            childOfT->Setparent(Q);
        }
    }

    T->Setleft(P);
    T->Setright(Q);

    P->Setparent(T);
    Q->Setparent(T);

    if (P == root) {    //case if it's a imbalance + root
        Setroot(T);
        T->Setparent(nullptr); //remove parent, because root dont have parent 

        return 0;
    }
    return T; //return T -> to connect to parent of imbalance
}

//TRAVERSE
void AVL::NLR(Node* r) {
    if (r != nullptr) {
        cout << r->Getkey() << " ";
        NLR(r->Getleft());
        NLR(r->Getright());
    }
}

void AVL::LNR(Node* r) {
    if (r != nullptr) {
        LNR(r->Getleft());
        cout << r->Getkey() << " ";
        LNR(r->Getright());
    }
}

void AVL::LRN(Node* r) {
    if (r != nullptr)
    {
        LRN(r->Getleft());
        LRN(r->Getright());
        std::cout << r->Getkey() << " ";
    }
}

void AVL::TravelNLR() {
    NLR(this->root);
}

void AVL::TravelLNR() {
    LNR(this->root);
}

void AVL::TravelLRN() {
    LRN(this->root);
}

//TO BALANCE TREE after insert & delete
void AVL::balanceTreeFunction(Node* n) {
    /*
                   SOLVE ADDING IN AVL
       STEP 1: THE LASTEST IMBALANCE NODE (from the bottom most - if the tree has 2 imbalance node -> then balance th most bottom)
       STEP 2: GET PARENT OF IMBALANCE
       STEP 3: ROTATE BASE ON CASE
       STEP 4: CONNECT PARENT OF IMBALANCE -> NEW ROOT FROM ROTATION
    */

    Node* imbalanceNode = returnLastestImbalanceNode(root, n);

    if (imbalanceNode != nullptr) {

        Node* parentImbalance = imbalanceNode->Getparent();

        int balance = GetHeight(imbalanceNode->Getleft()) - GetHeight(imbalanceNode->Getright());

        Node* returnNode = nullptr;
        switch (balance) {
            //go to the left side
        case 2:
            // check the 2nd place of avl -> rotate only 3 node
            balance = GetHeight(imbalanceNode->Getleft()->Getleft()) - GetHeight(imbalanceNode->Getleft()->Getright());

            if (balance == 1) {
                returnNode = RightRotate(imbalanceNode);
                break;
            }
            if (balance == -1 || balance == 0) {
                returnNode = LRRotate(imbalanceNode);
                break;
            }

            // go the right side of root
        case -2:
            balance = GetHeight(imbalanceNode->Getright()->Getleft()) - GetHeight(imbalanceNode->Getright()->Getright());

            if (balance == -1) {
                returnNode = LeftRotate(imbalanceNode);
                break;
            }
            if (balance == 1 || balance == 0) {
                returnNode = RLRotate(imbalanceNode);
                break;
            }
        default:
            break;
        }

        //connect parent of imbalance node -> to the new avl tree "return node" - aka lastest rotated node.
        if (parentImbalance != nullptr) {
            if (parentImbalance->Getkey() > imbalanceNode->Getkey()) {
                parentImbalance->Setleft(returnNode);
            }
            else {
                parentImbalance->Setright(returnNode);
            }
            returnNode->Setparent(parentImbalance);
        }

    }
}

//Find the bottom most - imbalance node
Node* AVL::returnLastestImbalanceNode(Node* Root, Node* newNode) {
    //run from "new added" -> root 
    //new node added -> only imbalance from 1 side

    Node* updateImbalance = nullptr;
    Node* T = Root;
    int balance;


    //check only the branch, that contain newly added node which made tree imbalance 

    /* Explain: why newnode->getright

    - new added node will be add from the leaf -> if T (which run from root -> down to new added node) -> will stop check imbalance node
    - because new added node, both left and right null -> so it ok for T to traverse though "new added node" then stop

    WHY?
    because: delete node case
    //50  	20  	30 	10 	-5 	7 	15 	35 	57 	65 	55 	-1

    if you run this code LRN - post traverse
    ->  -5 7 -1 15 20 10 35 55 65 57 50 30

    if you delete 35 -> make tree imbalance (rewrite tree to know more)

    to balance -> must run from root -> parent of delete node (this case 50)

    if run to 50 -> then can not update "updateImbalance" node -> so we can not re-balance tree from this node
    -> here is the answer: -5 7 -1 15 20 10 50 65 57 55 30


    another case     //30 25 35 32 50 27 15 20 10 - delete 27

    */
    while (T != newNode->Getright()) {


        balance = GetHeight(T->Getleft()) - GetHeight(T->Getright()); // check balance between value {-1, 0, 1}

        if (newNode->Getkey() > T->Getkey()) {
            if (balance == 2) {
                updateImbalance = T; //if imbalance -> then update for this
                T = T->Getleft();
                continue;
            }
            if (balance == -2) {
                updateImbalance = T;

                T = T->Getright();
                continue;
            }

            if (balance == 0 || balance == 1 || balance == -1) {

                T = T->Getright();
                continue;
            }

        }

        //no need to care <= because -> add - STEP 1 return false when duplicate
        else if (newNode->Getkey() < T->Getkey()) {
            if (balance == 2) {
                updateImbalance = T;
                T = T->Getleft();
                continue;
            }
            if (balance == -2) {
                updateImbalance = T;
                T = T->Getright();
                continue;
            }

            if (balance == 0 || balance == 1 || balance == -1) {
                T = T->Getleft();
                continue;
            }
        }

        else { // case NewNode = T 
            if (balance == 2 || balance == -2) {
                updateImbalance = T;
            }
            if (T->Getright() != nullptr) {
                T = T->Getright();
            }
            else {
                T = T->Getleft();
            }
            continue;
        }
    }

    return updateImbalance;
}

bool AVL::InsertNode(Node* n) {

    //STEP 1: SET THE TREE 
    Node* p = this->root;
    Node* Temp = nullptr;

    if (root == nullptr) {
        this->root = n;
        return true;
    }

    while (p != nullptr) {
        Temp = p;

        if (p->Getkey() > n->Getkey()) {
            p = p->Getleft();
        }
        else {
            if (p->Getkey() < n->Getkey()) {
                p = p->Getright();
            }
            else {
                if (p->Getkey() == n->Getkey()) // case insert node duplicate 
                    return false;
            }
        }
    }
    if (Temp->Getkey() > n->Getkey()) {
        Temp->Setleft(n);
    }
    else {
        Temp->Setright(n);
    }
    n->Setparent(Temp); //each time add -> update parent 

    //STEP 2: BALANCE
    balanceTreeFunction(n);
}

bool AVL::deleteNode(int k) {
    Node* value = search_x(root, k); //value aka "the node you want to delete"
    Node* temp = nullptr;
    Node* parentOfMax = nullptr; //use for case node has 2 children

    //case: node don't exist in tree
    if (value == nullptr) { //case cannot find k -> parameter pass (root and k
        std::cout << "Value can not found, delete node cannot execute \n";
        return false;
    }

    Node* parent = value->Getparent(); //parent of delete value 

    //case 0: node is the leaf of tree
    if (value->Getleft() == nullptr && value->Getright() == nullptr) {
        if (parent->Getleft() == value) {
            parent->Setleft(nullptr);
        }
        else {
            parent->Setright(nullptr);
        }
        value->Setparent(nullptr);
        delete value;

        //after delete "value" -> rebalance form parent of node delete
        balanceTreeFunction(parent);
        return true;
    }

    //case 1: node has one child
    if (value->Getleft() == nullptr || value->Getright() == nullptr) {
        if (value->Getright() == nullptr) {

            temp = value->Getleft();

            if (value->Getkey() < parent->Getkey()) {
                parent->Setleft(nullptr);
                parent->Setleft(temp);

            }
            else {
                parent->Setright(nullptr);
                parent->Setright(temp);

            }

            temp->Setparent(parent);

            value->Setparent(nullptr);
            value->Setleft(nullptr);

            //if dont set the value aka "removed node" to null -> it'll compile error
        }
        else {

            //because it's null from the left - due to root has 1 child -> temp just get right
            temp = value->Getright();

            if (value->Getkey() < parent->Getkey()) {
                parent->Setleft(nullptr);
                parent->Setleft(temp);
            }
            else {
                parent->Setright(nullptr);
                parent->Setright(temp);
            }
            temp->Setparent(parent);

            value->Setparent(nullptr);
            value->Setright(nullptr);
        }

        delete value;
        balanceTreeFunction(parent);
        return true;
    }

    //case 2: node has 2 children 
    //Two method: find the greatest on the left side of tree child(do this one) + smallest on the right side

    // for sure 100% - if you find max 
    // -> 1. it don't have child 
    // -> 2. it has child but, child < max (because if child > max) -> then child must be max (complex case)

    // 1st: find subtitude node and parent of it
    temp = value->Getleft(); // find max from the value of left tree 
    Node* m = findMaxValue(temp);
    parentOfMax = m->Getparent(); //store parent of max value 
    Node* childOfMax = m->Getleft();

    // 2nd: set "removed node" to to substitude node 
    value->Setkey(m->Getkey()); //current value change

    if (m->Getkey() > parentOfMax->Getkey()) {
        parentOfMax->Setright(nullptr);
        parentOfMax->Setright(childOfMax);

    }
    else {
        parentOfMax->Setleft(nullptr);
        parentOfMax->Setleft(childOfMax);
    }
    if (childOfMax != nullptr) {
        childOfMax->Setparent(parentOfMax);
    }


    m->Setleft(nullptr);
    m->Setparent(nullptr);

    delete m;

    //balance from parent of delete node
    balanceTreeFunction(value);



    return true;
}

Node* AVL::findMaxValue(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->Getright() == nullptr) {
        return node;
    }
    else {
        return findMaxValue(node->Getright());
    }
}

Node* AVL::search_x(Node* node, int k) {
    /*Node* p = root;

    if (p == NULL) {
        return NULL;
    }
    else {
        if (p->Getkey() > k) {
            search_x(p->Getleft(), k);
        }
        else if (p->Getkey() < k) {
            search_x(p->Getright(), k);
        }
        else {
            return p;
        }
    }*/


    Node* update = root;

    while (update != nullptr) {

        if (update->Getkey() > k) {
            update = update->Getleft();
        }
        else {

            if (update->Getkey() == k) {
                return update; //return if equal
            }
            update = update->Getright();
        }
    }
    return update;
}

void AVL::deleteAll()
{
    Setroot(nullptr);
}


/* void AVL::InsertNodeRe(Node* p) {
    this->root = InsertNode(this->root, p);
}*/
Node* AVL::InsertNode(Node* r, Node* p) {
    if (r == nullptr) {
        r = p;
        return r;
    }
    if (r->Getkey() == p->Getkey())
        return nullptr;
    else if (r->Getkey() > p->Getkey()) {
        r->Setleft(InsertNode(r->Getleft(), p));
        return r->Getleft();
    }
    else {
        r->Setright(InsertNode(r->Getright(), p));
        return r->Getright();
    };
    //
 /*   r->Setheight ( 1 + max(r->Getleft()->Getheight(),r->Getright()->Getheight()));

    int valBalance = r->Getleft()->Getheight() - r->Getright()->Getheight();

    if(valBalance>1&&r->Getleft()->Getkey()>p->Getkey())
        this->RightRotate(r);*/

}

Node* AVL::find_parent(Node* node, int k)
{
    if (node->Getkey() == k) {
        return nullptr;
    }

    Node* parent = nullptr;
    Node* temp = root;


    while (temp != nullptr) {

        if (temp->Getkey() > k) {
            parent = temp;
            temp = temp->Getleft();
        }
        else {

            if (temp->Getkey() == k) {
                return parent; //return if equal
            }
            parent = temp;
            temp = temp->Getright();
        }
    }
    return parent;
}