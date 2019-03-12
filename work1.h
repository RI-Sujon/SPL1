#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct Node{
    char *tag ;
    struct Node *parent,*children[10] ;
};

struct Node *root , *current;

void createLinkList(){
    root = NULL ;
    current = NULL ;
}

struct Node* createNode(char *tag){

    struct Node *temp =  malloc(sizeof(struct Node));

    temp->tag = tag ;
    int i = 0 ;
    for(i=0 ; i<10 ; i++){
        temp->children[i] = NULL ;
    }

    temp->parent = NULL ;

    return temp ;
}

void inseartNode(struct Node *newNode , int flag){

    newNode->parent = current ;
    int i = 0 ;
    for(i=0 ; i<10 ; i++){
        if(current->children[i]==NULL)
        {
            current->children[i] = newNode ;
            if(flag==1) current = newNode ;
            break ;
        }
    }
}

void outputTreePreOrder(struct Node *parent)
{
    printf("%s\n",parent->tag) ;
    int i ;
    for(i=0 ; i<10 ; i++){

        if((parent->children[i])!=NULL)
        {
            outputTreePreOrder(parent->children[i]) ;
        }
    }
}

void operation(char *str){

        if(root==NULL){
            struct node *newNode = createNode(str) ;
            root = newNode ;
            current = newNode ;
            return ;
        }

        if(str[1]=='/'){
            if(current->parent == NULL){
                current = NULL ;
                return ;
            }
            current = current->parent   ;

            return ;
        }

        int flag ;

        if(str[0]=='<') flag = 1 ;
        struct node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;

        printf("%s\n" ,current->tag);
}
/*
int main(){
    createLinkList() ;
    int i = 0 ;
    while(1){
        char *str = (char*) malloc(10 + 1 ) ;
        i++;
        scanf("%s",str);

        operation(str) ;
        if(current==NULL) break ;
    }
    outputTreePreOrder(root) ;

    return 0 ;

}*/
