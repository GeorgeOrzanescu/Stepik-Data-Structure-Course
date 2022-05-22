#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef struct {
    int code;
    char *name;
    float price;
} product;

typedef struct {
    product product;
    struct nodeAB *left, *right;
} nodeAB;

nodeAB* createNode(product p){
    nodeAB *newNode = (nodeAB *)malloc(sizeof(nodeAB));
    newNode->product.code = p.code;
    newNode->product.name = (char *)malloc((strlen(p.name) + 1) * sizeof(char));
    strcpy(newNode->product.name, p.name);
    newNode->product.price = p.price;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

nodeAB* insertNode(nodeAB* root,product p){
    if(root == NULL){
        return createNode(p);
    }
    // recursive
    if( root != NULL) { 
        if(p.code < root->product.code){
            root->left = insertNode(root->left, p);
        }
        else{
            root->right = insertNode(root->right, p);
        }   
        return root;
    }
}

nodeAB* searchProduct(nodeAB* root, int code){
    if(root == NULL){
        return NULL;
    }
    if(code == root->product.code){
        return root;
    }
    if (code < root->product.code)
    {
       searchProduct(root->left, code);
    }
    else{
        searchProduct(root->right, code);
    }
}

void preorderTravers(nodeAB* root){ // ROOT --> all left --> all right 
    if(root != NULL){ 
        printf("%d with name: %s and price %5.2f \n", 
            root->product.code, root->product.name, root->product.price);
        preorderTravers(root->left);
        preorderTravers(root->right);
    }
    /*
                    root
                    / \
                   /   \
                left   right
     */
}

void inorderTravers(nodeAB* root){ // all left --> root --> all right ASCENDING ORDER
    if(root != NULL) {
        inorderTravers(root->left);
        printf("%d with name: %s and price %5.2f \n",
               root->product.code, root->product.name, root->product.price);
        inorderTravers(root->right);
    }

        /*
                    root
                    / \
                   /   \
                left   right
     */
}

void main()
{
    nodeAB *root = NULL;

    FILE *f = fopen("products.txt", "r");
    char buffer[20];
    if (f)
    {
        int numProducts = 0;
        fscanf(f, "%d", &numProducts);
        for (int i = 0; i < numProducts; i++)
        {
            product p;
            fscanf(f, "%d", &p.code);
            fscanf(f, "%s", buffer);
            p.name = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
            strcpy(p.name, buffer);
            fscanf(f, "%f", &p.price);

            root = insertNode(root, p);
        }
    }

    preorderTravers(root);
    inorderTravers(root);

    nodeAB *findProduct = searchProduct(root, 12);
    printf("%d with name: %s and price %5.2f \n",
               findProduct->product.code, findProduct->product.name, findProduct->product.price);
}