//
//  BinaryTree.c
//  MediaService
//
//  Created by 梁甜 on 2022/9/5.
//

#include "OHBinaryTree.h"


void OHBinaryTreePreOrder(OHBinaryTree *tree, OHBinaryTreeNodeVisit visit) {
    if (tree) {
        visit(tree);
        OHBinaryTreePreOrder(tree->left, visit);
        OHBinaryTreePreOrder(tree->right, visit);
    }
}

void OHBinaryTreeInOrder(OHBinaryTree *tree, OHBinaryTreeNodeVisit visit) {
    if (tree) {
        OHBinaryTreeInOrder(tree->left, visit);
        visit(tree);
        OHBinaryTreeInOrder(tree->right, visit);
    }
}

void OHBinaryTreePostOrder(OHBinaryTree *tree, OHBinaryTreeNodeVisit visit) {
    if (tree) {
        OHBinaryTreePostOrder(tree->left, visit);
        OHBinaryTreePostOrder(tree->right, visit);
        visit(tree);
    }
}

void OHBinaryTreePostOrderWithoutRecur(OHBinaryTree *tree, OHBinaryTreeNodeVisit visit) {
    OHStack stack;
    OHStackInit(&stack);
    
    OHBinaryTreeNode *curr = tree;
    OHBinaryTreeNode *prev = nil;
    while (curr || !OHStackIsEmpty(&stack)) {
        if (curr) {
            OHStackPush(&stack, (id)curr);
            curr = curr->left;
        } else {
            curr = (OHBinaryTreeNode *)OHStackTop(&stack);
            if (curr->right && curr->right != prev) {
                curr = curr->right;
            } else {
                curr = (OHBinaryTreeNode *)OHStackPop(&stack);
                visit(curr);
                prev = curr;
                curr = nil;
            }
        }
    }
}

void OHBinaryTreeLevelOrder(OHBinaryTree *tree, OHBinaryTreeNodeVisit visit) {
    OHQueue queue;
    OHQueueInit(&queue);
    OHEnQueue(&queue, (id)tree);
    OHBinaryTreeNode *node = nil;
    while (!OHIsEmptyQueue(&queue)) {
        node = (OHBinaryTreeNode *)OHDeQueue(&queue);
        visit(node);
        if (node->left) OHEnQueue(&queue, (id)node->left);
        if (node->right) OHEnQueue(&queue, (id)node->right);
    }
}

void OHBinarySearchTreeInsert(OHBinaryTree *tree, OHBinaryTreeNodeCompare compare, id value) {
    if (tree) {
        OHBinaryTree node = {
            .left = nil,
            .right = nil,
            .value = value
        };
        
        OHBinaryTree *prev = nil;
        OHBinaryTreeNodeCompareResult result;
        while (tree) {
            result = compare(tree, &node);
            if (result == OHBinaryTreeNodeEqual) {
                break;
            }
            prev = tree;
            tree = result == OHBinaryTreeNodeGreat ? tree->left : tree->right;
        }
        
        if (result != OHBinaryTreeNodeEqual && prev) {
            OHBinaryTree *newNode = malloc(sizeof(OHBinaryTreeNode));
            memcpy(newNode, &node, sizeof(OHBinaryTreeNode));
            if (result == OHBinaryTreeNodeLess) prev->right = newNode;
            else prev->left = newNode;
        }
    }
}
