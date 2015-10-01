/*
 *  avlTree.h
 *  avlTree
 *
 *  Created by Seth Menghi on 11/10/14.
 *  Copyright (c) 2014 menghi. All rights reserved.
 *
 */


// AVL TREE Makes sure each branch is the same length
// Rank = how many elements are to its left

#include <iostream>

//----------------------------------------------//
//                                              //
//                Node Class Def                //
//                                              //
//----------------------------------------------//

struct Node
{
    Node();
    Node(int);
    Node(int, Node*);
    
    Node* left;
    Node* right;
    Node* parent;
    int data;
    int height;
    int size;
};



//----------------------------------------------//
//                                              //
//                 AVL Class Def                //
//                                              //
//----------------------------------------------//



class AVL
{
    
    public:
        AVL(); //constructor
        ~AVL(); //destructor
    
        int elementAtRank(int r);   // return the element at rank r, error if out of bounds

        void replaceAtRank(int r, int e); // replace element at rank r by e, error if out of bounds
        void insertAtRank(int r, int e);  // insert e at rank r;  elements at rank r or above
                                          // are pushed up by 1 in rank, error if out of bounds
    
        Node* index(int);
        Node* index(int i, Node*);
    
        void balanceTree(Node*);
    
        void right_rotation(Node*);
        void left_rotation(Node*);
    
        int Height(Node* current);
        int Size(Node* current);
    
        void removeAtRank(int r);   // delete element at rank r; elements at rank r or above
                                    // are pushed down by 1 in rank, error if out of bounds

        void printAll();  // print elements by rank.
    
    
    private:
        Node* head;
        int count;
};