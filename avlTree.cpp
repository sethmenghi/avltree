/*
 *  avlTree.cpp
 *  avlTree
 *
 *  Created by Seth Menghi on 11/10/14.
 *  Copyright (c) 2014 menghi. All rights reserved.
 *
 */

#include "avlTree.h"


//----------------------------------------------//
//                                              //
//                Node Class Imp                //
//                                              //
//----------------------------------------------//


//---------------------------------------//
// Default Constructor, defaults to NULL //
//---------------------------------------//
Node::Node()
{
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
    int data = 0;
    int height = 1; //default height to one.
    int size = 1;
}


//----------------------------------------------//
// Overloaded Constructor w/ element            //
//----------------------------------------------//
Node::Node(int e)
{
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
    
    int data = e;
    int height = 1; // write height to h
    int size = 1;
}


//-------------------------------------------------//
// Overloaded Constructor w/ parent Node + element //
//-------------------------------------------------//
Node::Node(int e, Node* dad)
{
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = dad;
    
    int data = e;
    int height = 1;
    int size = 1;
}


//----------------------------------------------//
//                                              //
//                 AVL Class Imp                //
//                                              //
//----------------------------------------------//


//--------------//
// Constructor  //
//--------------//
AVL::AVL()
{
    Node * head = NULL;
    int count = 0;
}


//---------------------------------------------------------//
// Destructor, need to delete each Node - unallocate memory//
//---------------------------------------------------------//
AVL::~AVL()
{
    Node * current = NULL;
    if (head != NULL)
    {
        for (int i = count - 1; i >= 0; i--)
        {
            current = index(i);
            delete current;
        }
    }
}


//---------------------------------------------------------//
// Indexes AVL Tree at int i                               //
//---------------------------------------------------------//
Node* AVL::index(int i)
{
    Size(head);
    
    if (count >= i)
    {
        std::cout << "ERROR - Rank: " << i << " out of bounds"
                  << std::endl;
    }
    
    Node* current = head;
    int size_left_tree = 0;
    
    //get size of the left tree
    if (current->left == NULL)
    {
        size_left_tree = 0;
    }
    else
    {
        size_left_tree = (current->left)->size;
    }
    
    //check which side of the tree continue
    if (i == 0)
    {
        return current;
    }
    //index is on left side
    else if (size_left_tree >= i)
    {
        return index(size_left_tree, current->left);
    }
    //index is on the right side
    else
    {
        return index(current->size - size_left_tree - 1, current->right);
    }
    
    return current;
}

Node* AVL::index(int i, Node* current)
{
    
    int size_left_tree = 0;

    if (current->left == NULL)
    {
        size_left_tree = 0;
    }
    else
    {
        size_left_tree = (current->left)->size;
    }
    
    //check which side of the tree continue
    if (i == 0)
    {
        return current;
    }
    //index is on left side
    else if (size_left_tree >= i)
    {
        return index(size_left_tree, current->left);
    }
    //index is on the right side
    else
    {
        //new tree index = total size - size of left tree - 1
        int new_index = current->size - size_left_tree - 1;
        return index(new_index, current->right);
    }
    
    return current;
}


//---------------------//
// Inserts e at rank r //
//---------------------//
void AVL::insertAtRank(int r, int e)
{
    Node* current = NULL;
    
    if (count == 0 && r == 0)
    {
        head = new Node(e);
        return;
    }
    else if (count == 0 && r > 0)
    {
        std::cout << "ERROR: AVL tree empty, insert at rank 0" << std::endl;
    }
    else
    {
        //get place of new Node, need to push all other nodes up one rank
        Node * temp = NULL;
        current = index(r, head);
        temp = new Node(e);
        temp->left = current;
        temp->parent = current->parent;
        
        if (current == current->parent->left)
        {
            current->parent->left = temp;
        }
        else //if (current == current->parent->right)
        {
            current->parent->right = temp;
        }
        
        current->parent = temp;
        //if on left insert there
        //if on right insert then make new->left = current
        
        balanceTree(temp);
    }
    count++;
}


//----------------------------------------------//
// Checks Heights of all the Nodes in the tree  //
//----------------------------------------------//
int AVL::Height(Node* current)
{
    //if there is no Node returns 0
    if (current == NULL)
    {
        return 0;
    }
    
    int rightHeight = Height(current->right); //height of right subtree
    int leftHeight = Height(current->left); //height of left subtree

    if (rightHeight > leftHeight)
    {
        //if there are more Nodes in righttree, take right height
        current->height = rightHeight + 1;
        return rightHeight + 1;
    }
    else
    {
        //if there are more Nodes in lefttree, take left height
        current->height = leftHeight + 1;
        return leftHeight + 1;
    }
}


//-----------------------//
// Gets Size of Subtrees //
//-----------------------//
int AVL::Size(Node* current)
{
    if (current == NULL)
    {
        return 0;
    }
    
    int rightSize = Size(current->right);
    int leftSize = Size(current->left);
    
    current->size = leftSize + rightSize + 1;
    return leftSize + rightSize + 1;
}

//--------------------------------------------//
// Rotates Node to the right for tree balance //
//--------------------------------------------//
void AVL::right_rotation(Node* current)
{
    Node* swapNode = NULL;
    swapNode = current->right;
    current->right = swapNode->left;
    swapNode->left = current;
}


//-------------------------------------------//
// Rotates Node to the left for tree balance //
//-------------------------------------------//
void AVL::left_rotation(Node* current)
{
    Node* swapNode = NULL;
    swapNode = current->left;
    current->left = swapNode->right;
    swapNode->right = current;
}


//--------------//
// Balance tree //
//--------------//
void AVL::balanceTree(Node* current)
{
    
    Height(current); //initalize all the heights of Nodes below
    int balanceOfCurrent = current->left->height - current->right->height;
    if (balanceOfCurrent > 1 || balanceOfCurrent < -1)
    {
        if (balanceOfCurrent < -1)
        {
            
            int balanceOfLeftSubTree = current->left->left->height - current->left->right->height;
            if (balanceOfLeftSubTree < 0) //if balance of left subtree is -1
            {
                left_rotation(current);
            }
            right_rotation(current);
        }
        else
        {
            int balanceOfRightSubTree = current->right->left->height - current->right->right->height;
            if (balanceOfRightSubTree > 0)
            {
                right_rotation(current);
            }
            left_rotation(current);
        }
    }
}



//----------------------------------------//
// Replaces data at rank r with element e //
//----------------------------------------//
void AVL::replaceAtRank(int rank, int e)
{
    Node * current = index(rank);
    current->data = e;
}


//---------------------------//
// Returns element at rank r //
//---------------------------//
int AVL::elementAtRank(int r)
{
    Node* current = index(r);
    
    return current->data;
}


//---------------------------//
// Removes element at rank r //
//---------------------------//
void AVL::removeAtRank(int r)
{
    if (head == NULL)
    {
        count = 0;
        return;
    }
    
    Node * current = index(r);
    Node * temp = current->parent;
    Node * rightNode = NULL;
    
    if (current->left != NULL && current->right != NULL)
    {

        temp->left = current->left;
        if (rightNode != NULL)
        {
            rightNode = current->right;
            insertAtRank(count - 1, rightNode->data);
            delete rightNode; // sent to back
            delete current;
        }
    }
    else if (current->left != NULL)
    {
        if (temp->left == current)
        {
            temp->left = current->left;
            delete current;
        }
        else
        {
            temp->right = current->left;
            delete current;
        }
    }
    else if (current->right != NULL)
    {
        if (temp->left == current)
        {
            temp->left = current->right;
            delete current;
        }
        else
        {
            temp->right = current->right;
            delete current;
        }
    }
    else //current has no children
    {
        
        if (temp->left == current)
        {
            temp->left = NULL;
            delete current;
        }
        else
        {
            temp->right = NULL;
            delete current;
        }
        
        balanceTree(temp);

    }
    current = index(r);
    balanceTree(current);
    count--;
}


//----------------------------------------------//
// Prints all elements in entire tree
//----------------------------------------------//
void AVL::printAll()
{
    for (int i = count - 1; i >= 0; i--)
    {
        std::cout << "Index: " << i << " Data: " << index(i)->data << std::endl;
    }
}


