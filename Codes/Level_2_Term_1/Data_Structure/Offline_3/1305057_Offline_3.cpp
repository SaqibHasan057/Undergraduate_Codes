#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0)return 0;
    int l,r;
    l=getSize(node->left);
    r=getSize(node->right);
    return l+r+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode *temp;
    int depth=0;
    temp=root;
    while(temp->item!=node->item)
    {
        if(node->item<temp->item)temp=temp->left;
        else temp=temp->right;
        depth++;
    }
    if(temp==0)return -1;
    else return depth;
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode *temp;
    int depth=0;
    temp=root;
    while(temp->item!=item)
    {
        if(item<temp->item)temp=temp->left;
        else temp=temp->right;
        depth++;
    }
    if(temp==0)return -1;
    else return depth;
}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    struct treeNode *temp=0,*prev=0;
    temp = node;
    if(temp==0)return FALSE_VALUE;
    int direction = 0; //1 means from derived from left,2 means derived from right
    while(temp!=0)
    {
        if(item<temp->item)
        {
            prev=temp;
            temp=temp->left;
            direction=1;
        }
        else if(item>temp->item)
        {
            prev=temp;
            temp=temp->right;
            direction=2;
        }
        else
        {
            if(temp->right==0 && temp->left==0)
            {
                if(direction==0)
                {
                    free(temp);
                    root=0;
                    return TRUE_VALUE;
                }
                else if(direction==1)
                {
                    prev->left=0;
                    free(temp);
                    return TRUE_VALUE;
                }
                else if(direction==2)
                {
                    prev->right=0;
                    free(temp);
                    return TRUE_VALUE;
                }

            }
            else if(temp->right!=0 && temp->left==0)
            {
                if(direction==0)
                {
                    temp=temp->right;
                    free(node);
                    root=temp;
                    return TRUE_VALUE;
                }
                else if(direction==1)
                {
                    prev->left=temp->right;
                    free(temp);
                    return TRUE_VALUE;
                }
                else if(direction==2)
                {
                    prev->right=temp->right;
                    free(temp);
                    return TRUE_VALUE;
                }
            }
            else if(temp->right==0 && temp->left!=0)
            {
                if(direction==0)
                {
                    temp=temp->left;
                    free(node);
                    root=temp;
                    return TRUE_VALUE;
                }
                else if(direction==1)
                {
                    prev->left=temp->left;
                    free(temp);
                    return TRUE_VALUE;
                }
                else if(direction==2)
                {
                    prev->right=temp->left;
                    free(temp);
                    return TRUE_VALUE;
                }
            }
            else
            {
                struct treeNode *rightSubtreeMin,*head;
                head = temp;
                rightSubtreeMin=temp->right;
                while(rightSubtreeMin->left!=0)
                {
                    head=rightSubtreeMin;
                    rightSubtreeMin=rightSubtreeMin->left;
                }
                temp->item=rightSubtreeMin->item;
                if(head!= temp)head->left=rightSubtreeMin->right;
                else head->right=rightSubtreeMin->right;
                free(rightSubtreeMin);
                return TRUE_VALUE;
            }

        }
    }
    return FALSE_VALUE;
}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    while(temp->left!=0)temp=temp->left;
    return temp->item;
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    while(temp->right!=0)temp=temp->right;
    return temp->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    if(node==0)return 0;
    int l,r;
    l=rangeSearch(node->left,leftBound,rightBound);
    r=rangeSearch(node->right,leftBound,rightBound);
    if(node->item>=leftBound && node->item<=rightBound)return l+r+1;
    else return l+r;
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}

int findLCA(struct treeNode *node, int item1,int item2)
{
    struct treeNode *temp;
    temp=node;
    if(item1<temp->item && item2>temp->item)return temp->item;
    while(!(item1<temp->item && item2>temp->item)){
        if(item1<temp->item && item2<temp->item)temp=temp->left;
        else if(item1>temp->item && item2>temp->item) temp=temp->right;
    }
    return temp->item;
}



int main(void)
{
    initializeTree();
    /*insertItem(root, 50);
    insertItem(root, 25);
    insertItem(root, 100);
    insertItem(root, 10);
    insertItem(root, 27);
    insertItem(root, 95);
    insertItem(root, 105);
    insertItem(root, 6);
    insertItem(root, 11);
    insertItem(root, 26);
    insertItem(root, 30);
    insertItem(root, 85);
    insertItem(root, 97);
    insertItem(root, 104);
    insertItem(root, 120);*/

    /*insertItem(root, 20);
    insertItem(root, 5);
    insertItem(root, 3);
    insertItem(root, 7);
    insertItem(root, 100);
    insertItem(root, 90);
    insertItem(root, 200);
    insertItem(root, 60);
    insertItem(root, 95);
    insertItem(root, 150);
    insertItem(root, 230);
    insertItem(root, 210);
    insertItem(root, 250);*/

    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7.Get size 8.Calculate depth.\n");
        printf("9.Calculate node depth 10.Get minimum item 11.Get maximum item\n");
        printf("12.Range Search 13.Delete item from BST 14.Quit\n");
        printf("15.Find the LCA of two given item inputs\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            int size = getSize(root);
            printf("%d\n",size);
        }
        else if(ch==8)
        {
            int item;
            printf("Enter item:");
            scanf("%d",&item);
            int depth = calcDepth(item);
            printf("%d\n",depth);

        }
        else if(ch==9)
        {
            int item;
            printf("Enter node item:");
            scanf("%d",&item);
            int depth = calcNodeDepth(searchItem(root,item));
            printf("%d\n",depth);

        }
        else if(ch==10)
        {
            int getMin = getMinItem();
            printf("The minimum item in the tree is: %d\n",getMin);
        }
        else if(ch==11)
        {
            int getMax = getMaxItem();
            printf("%d\n",getMax);
        }
        else if(ch==12)
        {
            int lowbound,highbound;
            printf("Enter lowbound and highbound:");
            scanf("%d %d",&lowbound,&highbound);
            int range = rangeSearch(root,lowbound,highbound);
            printf("The number of items in the range: %d\n",range);
        }
        else if(ch==13)
        {
            int item;
            printf("Enter item to be deleted:");
            scanf("%d",&item);
            int ret = deleteItem(root,item);
            if(ret)printf("The %d has been successfully deleted.\n",item);
            else printf("The delete function has failed!\n");
        }
        else if(ch==14)
        {
            break;
        }
        else if(ch==15)
        {
            int item1,item2;
            printf("Enter item1:");
            scanf("%d",&item1);
            printf("Enter item2:");
            scanf("%d",&item2);
            int answer = findLCA(root,item1,item2);
            printf("The LCA is %d.\n",answer);
        }

    }

}
