/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };

 題目要求找出最長的路徑，也就是任意兩點AB，A走到B的邊數，找最大的
 首先直覺可以用暴力法
 但是for迴圈明顯到了底層4、5時 要怎麼變化迴圈指標讓他能去走到3?
 故可以用遞迴 放棄迴圈指標


分割問題、想終止條件:
1.最長的路徑會通過 root
    則起點在左邊，終點在右邊
也就是說會變成問說 我找左邊的樹，其樹根到樹葉最長的路 +上 右邊的樹，其樹根到樹葉最長的路
因此就是找樹的深度 (跟題目的路徑不同，不需要跨子樹)

maxDepth()
實作方法:一個樹的高度會是左或右子樹的高度+1
因此主要靠這個1 去計算高度
遞迴遍歷到沒有子樹時才終止，回傳0


2. 最長的路徑沒有通過ROOT
    則不是都在左邊
    就是都在右邊
也就是說會變成問說 MAX(找左邊的樹最長的路徑, 找右邊的樹最長的路徑)
因此在遞迴上直接用原函式就好了
 */

int maxDepth(struct TreeNode* root)
{
    if (root == NULL) return 0; //當沒有樹時返回0

    int leftMax = maxDepth(root->left); //找左子樹的深度
    int rightMax = maxDepth(root->right); //找右子樹的深度

    //找到後回傳比較深的那棵樹，+1是因為對於最初的樹來說，左子樹、右子樹都還要一個邊才能到達最初的樹

    if (leftMax > rightMax) {
        return leftMax + 1;
    }
    return rightMax + 1;
}

int diameterOfBinaryTree(struct TreeNode* root) {
    if (root == NULL) { return 0; }

    //1.最長的路徑會通過root 因此是左子樹+右子樹，為何不用+1? 因為函式內已經+了
    int middle = maxDepth(root->left) + maxDepth(root->right);
    //2.最長的路徑沒有通過root
    int left = diameterOfBinaryTree(root->left);
    int right = diameterOfBinaryTree(root->right);

    int max = middle;
    if (left > max) {
        max = left;
    }
    if (right > max)
    {
        max = right;
    }
    return max;
}