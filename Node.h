//
// Created by Veronica  Soden  on 4/17/21.
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "song.h"

#ifndef PROJ3_NODE_H
#define PROJ3_NODE_H
class Node{
public:
    song Song;
    Node* left;
    Node* right;
    Node() : left(nullptr), right(nullptr) {}
    Node(song Song) : left(nullptr), right(nullptr), Song(Song) {}
    Node(Node* tempa, Node* tempb, song Song) : left(tempa), right(tempb), Song(Song) {}
};
#endif //PROJ3_NODE_H
