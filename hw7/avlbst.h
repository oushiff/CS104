#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{
    //super(key, value, parent);
}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/removing elements from the tree. You must implement
    // both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    //int getBalance(const std::pair<Key, Value>& keyValuePair);
    //rotate right function
    //rotate left function
    


};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/


template<typename Key, typename Value>
int AVLTree<Key, Value>::safeGetHeight(AVLNode<Key, Value> node) {
    if (node == NULL)
        return 0;
    return node.getHeight();
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::changeRoot(AVLNode<Key, Value> *formerRoot, AVLNode<Key, Value> *newRoot) {
    AVLNode<Key, Value>* parent = parent->getParent();
    if (formerRoot->getParent() != NULL)
        if (formerRoot->getRight() == formerRoot) {
            parent->setRight(newRoot);
        }
        else {
            parent->setLeft(newRoot);
        }
    }
    else {
        this->mRoot = newRoot;
    }
    formerRoot->setParent(newRoot);
    newRoot->setParent(parent);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateToLeft(AVLNode<Key, Value> *formerRoot) {
    AVLNode<Key, Value>* newRoot = formerRoo->.getRight();
    changeRoot(tree, formerRoot, newRoot);
    formerRoot->setRight(newRoot->getLeft());
    if (newRoot->getLeft()) 
        newRoot->getLeft()->setParent(formerRoot);
    newRoot->setLeft(formerRoot);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateToRight( AVLNode<Key, Value> *formerRoot) {
    AVLNode<Key, Value>* newRoot = formerRoot->getLeft();
    changeRoot(tree, formerRoot, newRoot);
    formerRoot->setLeft(newRoot->getRight());
    if (newRoot->getRight()) 
        newRoot->getRight()->setParent(formerRoot);
    newRoot->setRight(formerRoot);
}




/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    if (mRoot == NULL) {
        Key key = keyValuePair.first;
        Value value = keyValuePair.second;
        Node<Key, Value>* newNode = new Node<Key, Value>(key, value, NULL);
        mRoot = newNode;
        return;
    }

    Node<Key, Value>* parent = mRoot;
    Key key = keyValuePair.first;
    Value value = keyValuePair.second;

    Node<Key, Value>* newNode = NULL;
    while (true) {
        if (parent->getKey() == key)  {
            parent->setValue(value);
            break;
        }
        else if (parent->getKey() > key) {
            if (parent->getLeft())
                parent = parent->getLeft();
            else {
                newNode = new Node<Key, Value>(key, value, parent);
                parent->setLeft(newNode);
                break;
            }
        }
        else {
            if (parent->getRight())
                parent = parent->getRight();
            else {
                newNode = new Node<Key, Value>(key, value, parent);
                parent->setRight(newNode);
                break;
            }
        }
    }
      
    if (newNode == NULL || newNode->getParent()->getRight() == NULL || newNode->getParent()->getLeft() == NULL) 
        return;

    Node<Key, Value>* cur = NULL; 
    while (cur = newNode->getParent()) {
        cur->setHeight(cur->getHeight + 1);
        if (cur->getParent() == NULL)
            return;

        if (cur == cur->getParent()->getLeft()) {
            Node<Key, Value>* parent = cur->getParent();
            int rightBroHeight = safeGetHeight(parent->getRight());
            if (cur.getHeight - rightBroHeight == 2) {
                if (safeGetHeight(cur->getLeft()) < safeGetHeight(cur->getRight())) {
                    rotateToLeft(cur);
                    cur->setHeight(cur->getHeight() - 1);
                }
                rotateToRight(parent);
                parent->setHeight(parent->getHeight() - 2);
            }
        }
        else {
            Node<Key, Value>* parent = cur->getParent();
            int leftBroHeight = safeGetHeight(parent->getRight());
            if (leftBroHeight - cur.getHeight == -2) {
                if (safeGetHeight(cur->getLeft()) > safeGetHeight(cur->getRight())) {
                    rotateToRight(cur);
                    cur->setHeight(cur->getHeight() - 1);
                }
                rotateToLeft(parent);
                parent->setHeight(parent->getHeight() - 2);
            }
        }
    }

}

template<typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::findMinNode(AVLNode<Key, Value> *root) {
    Node<Key, Value>* minNode = root;
    while (minNode->getLeft() != NULL) 
        minNode = minNode->getLeft();
    return minNode;
}


/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
   // TODO
    Node<Key, Value>* deleted = internalFind(key);
    if (deleted == NULL)
        return;

    Node<Key, Value>* parent = deleted->getParent();
    if (parent == NULL) {
        // ....
    }
    if (parent->getLeft() == deleted) {
        if (deleted->getLeft() == NULL && deleted->getRight() == NULL) {
            parent->setLeft(NULL);
            //  de-alloc???
        }
        else if (deleted->getLeft() == NULL && deleted->getRight() != NULL) {
            parent->setLeft(deleted->getRight());
            deleted->getRight()->setParent(parent);
        }
        else if (deleted->getLeft() != NULL && deleted->getRight() == NULL) {
            parent->setLeft(deleted->getLeft());
            deleted->getLeft()->setParent(parent);
        }
        else {
            Node<Key, Value>* replace = findMinNode(deleted->getRight()); 
            if (replace->getParent() != deleted) {
                replace->getParent()->set
            }

        }

    }
    else {

    }
    

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/




#endif