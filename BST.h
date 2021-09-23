//
// Created by Veronica  Soden  on 4/17/21.
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "song.h"
#include "Node.h"

#ifndef PROJ3_BST_H
#define PROJ3_BST_H


class BST {
public:
    BST(void);
    Node* root;
    int size;

    bool insert(song*);
    bool insertRecusrion(Node*, song*);
    Node* searchRecursion(Node*, song*);
    vector<song> traverseInOrder(Node*);
    vector<song> traversePostOrder(Node*);
    int height(Node*);
};


#endif //PROJ3_BST_H
