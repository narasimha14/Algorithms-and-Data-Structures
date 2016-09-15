/*
  This is a solution to the LeetCode Challenge https://leetcode.com/problems/kth-smallest-element-in-a-bst/
  @author: Narasimha Murthy
  Basic idea is to do an inorder traversal and keep track of the number of elements traversed and stop the inorder traversal once the count reaches 'k'
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void inorder(TreeNode* root, int& count, int k, bool& set, int& out){
        if(set){
            return;
        }
        if(root == NULL)
            return;
        
        if(root->left){
            inorder(root->left, count, k, set, out);
        }
        ++count;
        if(count == k){
            out = root->val;
            set = true;
        }
        if(root->right){
            inorder(root->right, count, k, set, out);
        }
    }
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        int out = 0;
        bool set = false;
        inorder(root, count, k, set, out);
        return out;
    }
};
