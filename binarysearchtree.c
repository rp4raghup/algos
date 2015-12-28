/* BST problems*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct _node
{
    int val;
    struct _node *left;
    struct _node *right;
}Node;
Node *newNode(int val)
{
    Node *temp = malloc(sizeof(Node));
    if(temp != NULL)
    {
        temp->val = val;
        temp->left = NULL;
        temp->right = NULL;
    }
    return temp;
}
Node *insert(Node *root, int val)
{
    if (root == NULL)
        return newNode(val);
    else
    {
        if(root->val < val)
            root->right = insert(root->right, val);
        else
            root->left = insert(root->left, val);
    }
    return root;
}
void postorder(Node *root)
{
    if(root == NULL)
        return;
    else
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}
void inorder(Node *root)
{
    if(root == NULL)
        return;
    else
    {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}
void printPost(Node *root)
{
    printf("post-order : ");
    postorder(root);
    printf("\n");
}
void printIn(Node *root)
{
    printf("inorder : ");
    inorder(root);
    printf("\n");
}
int size(Node *root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + size(root->left) + size(root->right);
}
int max(int p, int q)
{
    return (p > q? p: q);
}
int maxDepth(Node *root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
int maxVal(Node *root) // always non - empty
{
    if (root == NULL)
    {
        return INT_MAX;
    }
    else if (root->right == NULL)
    {
        return root->val;
    }
    else
    {
        return maxVal(root->right);
    }
}
int minVal(Node *root) // always non - empty
{
    if (root == NULL)
    {
        return INT_MIN;
    }
    else if (root->left == NULL)
    {
        return root->val;
    }
    else
    {
        return minVal(root->left);
    }
}
int minValWhile(Node *root)
{
    while( root != NULL && root->left != NULL)
    {
        root = root->left;
    }

    if (root != NULL)
        return root->val;
    else
        return INT_MIN;
}
int hasPathSum(Node *root, int sum)
{
    if (root == NULL)
        return (sum == 0);
    else
    {
        int ans = 0;
        int subSum = sum - root->val;
        if(subSum == 0 && root->left == NULL && root->right == NULL)
            return 1;
        if(root->left)
            ans = ans || hasPathSum(root->left, subSum);
        if(root->right)
            ans = ans || hasPathSum(root->right, subSum);
    }
}
void printPathRecur(Node *root, int path[], int len)
{
    if (root == NULL)
        return;

    else
    {
        path[len++] = root->val;
        if (root->left == NULL && root->right == NULL)
        {
            int i;
            for (i = 0; i < len; i++)
                printf("%d ", path[i]);
            printf("\n");
        }
        printPathRecur(root->left, path, len);
        printPathRecur(root->right, path, len);
    }
}
void printPath(Node *root)
{
    int path[100], pathlen = 0;
    printPathRecur(root, path, pathlen);
}
void mirror(Node *root)
{
    if (root == NULL)
        return;
    else
    {
        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;
        mirror(root->left);
        mirror(root->right);
    }
}
void doubleTree(Node *root)
{
    if (root == NULL)
        return;
    else
    {
        Node *temp = malloc(sizeof(Node));
        temp->val = root->val;
        temp->left = root->left;
        temp->right = NULL;
        root->left = temp;
        doubleTree(root->left->left);
        doubleTree(root->right);
    }
}
int sameTree(Node *root1, Node *root2)
{
    if (root1 == NULL && root2 == NULL)
    {
        return 1;
    }
    else if (root1 != NULL && root2 != NULL)
    {
        if (root1->val != root2->val)
            return 0;
        else
            return sameTree(root1->left, root2->left) && sameTree(root1->right, root2->right);
    }
    else
    {
        return 0;
    }
}
int isBst1(Node *root)
{
    if (root == NULL)
        return 1;
    else
    {
        if((root->left != NULL && root->val < maxVal(root->left))|| (root->right != NULL && root->val > minVal(root->right)))
            return 0;
        else
            return isBst1(root->left) && isBst1(root->right);
    }
}
int isBstRec(Node *root, int min, int max)
{
    if (root == NULL)
        return 1;
    else
    {
        if(root->val < min || root->val > max)
            return 0;
        else
            return isBstRec(root->left, min, root->val) && isBstRec(root->right, root->val, max);
    }
}
int isBst2(Node *root)
{
    return isBstRec(root, INT_MIN, INT_MAX);
}
int isFullBT(Node *root)
{
    if (root == NULL)
        return 1;
    else
    {
        if(root->left == NULL && root->right == NULL)
            return 1;
        else if(root->left != NULL && root->right != NULL)
            return isFullBT(root->left) && isFullBT(root->right);
        else
            return 0;
    }
}
void printNodeAtGivenLevel(Node *root, int l, int even)
{
    if (root == NULL)
        return;
    else
    {
        if(l == 1)
            printf("%d ", root->val);
        else if (l > 1 && even == 1)
        {
            printNodeAtGivenLevel(root->left, l - 1, even);
            printNodeAtGivenLevel(root->right, l - 1, even);
        }
        else if (l > 1 && even == 0)
        {
            printNodeAtGivenLevel(root->right, l - 1, even);
            printNodeAtGivenLevel(root->left, l - 1, even);
        }
    }
}
void printLevelOrder(Node *root)
{
    int h = maxDepth(root);
    int i;
    printf("level order: ");
    for (i = 1; i <= h; i++)
        printNodeAtGivenLevel(root, i, i % 2);
    printf("\n");
}
int isSumTree(Node *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 1;
    else
    {
        int ld = 0, rd = 0;
        if (root->left != NULL)
            ld = root->left->val;
        if (root->right != NULL)
            rd = root->right->val;
        if ((root->val == ld + rd) && isSumTree(root->left) && isSumTree(root->right))
            return 1;
        else
            return 0;
    }
}
Node *delete(Node *root, int val)
{
    if (root == NULL)
        return NULL;
    if (val < root->val)
        root->left = delete(root->left, val);
    else if (val > root->val)
        root->right = delete(root->right, val);
    else
    {
        if(root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        int temp = minVal(root->right);
        root->val = temp;
        root->right = delete(root->right, temp);
    }
    return root;
}
int Ceil(Node *root, int val)
{
    if (root == NULL)
        return INT_MIN;
    if (root->val == val)
        return val;
    else if (root->val < val)
        Ceil(root->right, val);
    else
    {
        int c = Ceil(root->left, val);
        return c >= val ? c : root->val;
    }
}
int Floor(Node *root, int key)
{
    if (root == NULL)
        return INT_MAX;
    if (key == root->val)
        return root->val;
    else if (key < root->val)
        return Floor(root->left, key);
    else
    {
        int f = Floor(root->right, key);
        return f >= key ? root->val : f;
    }
}
int rank(Node *root, int key)
{
    if(root == NULL)
        return 0;
    if(key == root->val)
        return 1 + rank(root->left, key);
    else if (key > root->val)
        return 1 + rank(root->left, key) + rank(root->right, key);
    else
        return 0 + rank(root->left, key);
}
int search(Node *root, int val)
{
    if (root == NULL)
        return 0;
    if (val == root->val)
        return 1;
    else if (val < root->val)
        return search(root->left, val);
    else
        return search(root->right, val);
}
int rangeSearch(Node *root, int l, int h)
{
    if (root == NULL)
        return 0;
    if (root->val >= l && root->val <= h)
        return 1 + rangeSearch(root->left, l, h) + rangeSearch(root->right, l, h);
    else if (root->val >= h)
        return (root->val == h ? 1 : 0) + rangeSearch(root->left, l, h);
    else if (root->val <= l)
        return (root->val == l ? 1 : 0) + rangeSearch(root->right, l, h);
    else
        return 0;
}
void rangeSeaPrint(Node *root, int l, int h)
{
    if (root == NULL)
        return;
    rangeSeaPrint(root->left, l, h);
    if (root->val >= l && root->val <= h)
        printf("%d ", root->val);
    rangeSeaPrint(root->right, l, h);
}
void commonAncestor(Node *root, int l, int r)
{
    while(root)
    {
        if(root->val >= l && root->val <= r || root->val <= l && root->val >= r)
        {
            printf("ca: %d\n", root->val);
            return;
        }
        if(root->val > l)
            root = root->left;
        else
            root = root->right;
    }
    printf("no ca\n");
    return;
}
int main()
{
    Node *root = NULL, *root1 = NULL, *root3 = NULL;
    root = insert(root, 3);
    insert(root, 1);
    insert(root, 2);
    insert(root, 5);
    insert(root, 4);
    insert(root, 9);
    insert(root, 7);
    insert(root, 10);
    printIn(root);
    commonAncestor(root, 5, 7);
    delete(root, 3);
    printf("rank(8): %d\n", rank(root, 8));
    printf("Floor(8): %d\n", Floor(root, 8));
    printf("Ceil(8): %d\n", Ceil(root, 8));
    printf("search(8): %d, search(2): %d\n", search(root, 8), search(root, 2));
    printIn(root);
    printf("range count [2 - 8]: %d\n", rangeSearch(root, 2, 8));
    printf("range keys [2 - 8]: ");
    rangeSeaPrint(root, 2, 8);
    printf("\n");
    printPost(root);
    printLevelOrder(root);
    printf("size : %d\n", size(root));
    printf("maxDepth: %d\n", maxDepth(root));
    printf("minValue: %d, maxValue: %d\n", minVal(root), maxVal(root));
    printf("hasPathSum(24): %d, hasPathSum(7): %d\n", hasPathSum(root, 24), hasPathSum(root, 7));
    printf("path to leaves: \n");
    printPath(root);
    printf("mirror: ");
    mirror(root);
    printIn(root);
    printf("mirror: ");
    mirror(root);
    printIn(root);

    root1 = insert(root1, 3);
    insert(root1, 1);
    insert(root1, 2);
    insert(root1, 5);
    insert(root1, 8);
    insert(root1, 9);
    insert(root1, 7);
    insert(root1, 10);
    printf("first tree:");
    printIn(root);
    printf("second tree:");
    printIn(root1);
    printf("first and second same? %d\n", sameTree(root, root1));

    printf("double tree of root: ");
    doubleTree(root);
    printIn(root);

    printf("isBst1(root1): %d\n", isBst1(root1));
    printf("isBst2(root1): %d\n", isBst2(root1));

    root3 = insert(root3, 3);
    insert(root3, 2);
    insert(root3, 4);
    printf("isFullBT(root3): %d\n", isFullBT(root3));
    printf("isSumTree(root3): %d\n", isSumTree(root3));
    return 0;
}
