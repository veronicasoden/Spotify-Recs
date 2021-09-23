#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "song.h"
#include "BST.h"
#include "Survey.h"
#include "Node.h"
#include "BST.h"

using namespace std;

//constructor
BST::BST() {
    this->root = nullptr;
    this->size = 0;
}

//return true if insertion successful, calls on recursive helper function
bool BST::insert(song *Song) {
    //check duration is unique if not inc till is
    Node* temp = searchRecursion(root, Song);
    while(temp != nullptr) {
        if(temp->Song.songName == (Song->songName)) {
            //song is repeated in data and has already been inserted
            return true;
        }
        else {
            Song->duration = Song->duration + 1;
            temp = searchRecursion(root, Song);
        }
    }
    size++;
    return insertRecusrion(root, Song);
}

// Return true if insertion successful
bool BST::insertRecusrion(Node* temp, song* Song) {
    //three main insert cases
    //first case check if root has yet to be made, i.e., first insertion
    if(root == nullptr) {
        root = new Node(*Song);
        return true;
    }
    //use song duration to sort
    else if(Song->duration > temp->Song.duration) {
        if (temp->right == nullptr) {
            temp->right = new Node(*Song);
            return true;
        }
        else {
            //use recursion to insert new node
            return insertRecusrion(temp->right, Song);
        }
    }
        //id number is less than node
    else if(Song->duration < temp->Song.duration) {
        if (temp->left == nullptr) {
            temp->left = new Node(*Song);
            return true;
        }
        else {
            //use recursion to insert new node
            return insertRecusrion(temp->left, Song);
        }
    }
    else {
        return false;
    }
}

// method to find height of given node
int BST::height(Node* temp) {
    if (temp == nullptr) {
        return 0;
    }
    return 1 + max(height(temp->left), height(temp->right));
}

// Return vector of songs of inorder traversal (by duration)
vector<song> BST::traverseInOrder(Node* temp){
    vector<song> toQL;
    vector<song> toQR;
    if(temp != nullptr) {
        toQL = traverseInOrder(temp->left);
        toQL.push_back(temp->Song);
        toQR = traverseInOrder(temp->right);
        toQL.insert(toQL.end(), toQR.begin(), toQR.end());
    }
    return toQL;
}

// Return vector of songs of postorder traversal (by duration)
vector<song> BST::traversePostOrder(Node* temp){
    vector<song> toQ;
    vector<song> toQL;
    vector<song> toQR;
    if(temp != nullptr) {
        toQL = traversePostOrder(temp->left);
        if(toQL.size()) {
            toQ.insert(toQ.end(), toQL.begin(), toQL.end());
        }
        toQR = traversePostOrder(temp->right);
        if(toQR.size()) {
            toQ.insert(toQ.end(), toQR.begin(), toQR.end());
        }
        toQ.push_back(temp->Song);
    }
    return toQ;
}

//use recursion to search through tree to see if contains duplicate
Node* BST::searchRecursion(Node* temp, song* Song) {
    if(temp == nullptr || temp->Song.duration == Song->duration) {
        return temp;
    }
    else if(Song->duration < temp->Song.duration) {
        return searchRecursion(temp->left, Song);
    }
    else {
        return searchRecursion(temp->right, Song);
    }
}
