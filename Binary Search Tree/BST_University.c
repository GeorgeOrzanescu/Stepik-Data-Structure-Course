#include<stdio.h>
#include<malloc.h>
#include <stdbool.h>
#include <string.h>
typedef struct{
    int code;
    char *name;
    float price;
} product;

typedef struct{
    product data;
    struct node* left;
    struct node* right;
} node;

node* createNode(product p,node* left, node* right){
    node* new = (node*)malloc(sizeof(node));
    new->data.code = p.code;
    new->data.name = (char *)malloc(sizeof(char) * (strlen(p.name) + 1));
    strcpy(new->data.name, p.name);
    new->data.price = p.price;

    new->left = left;
    new->right = right;

    return new;
}


node* insertNode(node* root,product p){
    node *temp = root;
    if(root == NULL){ // BST IS EMPTY
        temp = createNode(p, NULL, NULL);
        return temp;
    }
    else{
        while(true){
            if(p.code < temp->data.code){ 
                if(temp->left != NULL){   // go left side and keep left until else
                    temp = temp->left;
                }
                else
                {
                    temp->left = createNode(p, NULL, NULL);  
                    return root;
                }
            }
            else{
                if(p.code > temp->data.code){
                    if(temp->right != NULL){ // go right side and keep left until else
                        temp = temp->right;
                    }
                    else{
                        temp->right = createNode(p, NULL, NULL);
                        return root;
                    }
                }
                else
                {
                    return root;
                }
            }
        }
            
    }
}

void preoderTravers(node* root){ // ROOT --> LEFT --> RIGHT
    if(root != NULL){
        printf("Code: %d Name: %s Price: %5.2f \n", root->data.code, root->data.name, root->data.price);
        preoderTravers(root->left);
        preoderTravers(root->right);
    }
}

void inorderTravers(node* root){ // LEFT --> ROOT --> RIGHT
    if(root != NULL){
        inorderTravers(root->left);
        printf("Code: %d Name: %s Price: %5.2f \n", root->data.code, root->data.name, root->data.price);
        inorderTravers(root->right);
    }
}

void dezalocation(node* root){
    if(root != NULL){
        dezalocation(root->left);
        dezalocation(root->right);
        free(root->data.name);
        free(root);
    }
}

node* search(node* root,int key){
    if(root != NULL)
    {  //  node searched is root
        if(key == root->data.code){
            return root;
        }
        else
        {
            if (key < root->data.code) { // if smaller than root go search left
                    search(root->left, key);
                }
            else { search(root->right, key); } // else search on right side
        }
    }
    else
        return NULL;
}

int main(){

    int n;
    node *root = NULL;
    char buffer[20];
    product p;

    FILE *f = fopen("BST.txt", "r");
    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &p.code);
        fscanf(f, "%s", buffer);
        p.name = (char *)malloc(sizeof(char *) * (strlen(buffer) + 1));
        strcpy(p.name, buffer);
        fscanf(f, "%f", &p.price);

        root = insertNode(root, p);
        free(p.name);
    }

    preoderTravers(root);
    // dezalocation(root);
    node *searched = search(root, 33);
    printf("Node: %s", searched->data.name);
    return 0;
}