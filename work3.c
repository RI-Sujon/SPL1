#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"work1.h"
#include"work2.h"

void getTagAttributeOrString(struct Node *current,char tagStr[100],char ch){

    if(current->tag == tagStr){
        char *str ;
        int i ;
        for(i=0 ; i<10 ; i++){
            if((current->children[i])!=NULL )
            {
                str = current->children[i]->tag ;
                if(str[0]==ch){
                    int i ;
                    for(i=0 ; i < strlen(str)-1 ; i++){
                        str[i] = str[i+1] ;
                    }
                    str[strlen(str)-1] = NULL ;
                    printf("%s\t\t" ,str);
                }
            }

            else return ;
        }
    }

    int i ;
    for(i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTagAttributeOrString(current->children[i] ,tagStr , ch) ;
        }
    }

}

void getTagParentsChildreansSublings(struct Node *current,char *tagStr,int flag){

    if(current->tag == tagStr){
        if(flag==1){
            if(current->parent!=NULL)
                printf("%s\n" ,current->parent->tag ) ;
            return ;
        }

        else if(flag==2){
            int i ;
            for(i=0 ; i<10 && current->children[i]!=NULL ; i++){
                char *str = current->children[i]->tag ;
                if(str[0]!='~' && str[0]!='!'){
                    printf("%s\t" ,str ) ;
                }
            }
        }

        else if(flag==3){
            int i ;
            for(i=0 ; i<10 && current->parent->children[i]!=NULL ;i++){
                char *str = current->parent->children[i]->tag ;
                if(str[0]!='~' && str[0]!='!'){
                    printf("%s\t" ,str ) ;
                }
            }
        }
    }
    int i ;
    for(i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTagParentsChildreansSublings(current->children[i] ,tagStr , flag) ;
        }
    }

}


void menu(){
    while(1){
        int choice ;
        printf("\nEnter Your Choice \n1.find tag\n2.get tag's attribute\n3.get tag's String\n4.get tag's parents\n5.get tag's childrens\n6.get tag's sublings\n7. exit \n " );
        scanf("%d" , choice) ;

        char *tagStr ;
        printf("Enter Tag Name : ") ;
        scanf( "%s" ,&tagStr );

        if(choice == 1) ;//findTag() ;
        if(choice == 2){
            getTagAttributeOrString(root,tagStr,'!') ;
        }

        if(choice == 3){
            getTagAttributeOrString(root,tagStr,'~') ;
        }

        if(choice == 4){
            getTagParentsChildreansSublings(root , tagStr , 1) ;
        }
        if(choice == 5){
            getTagParentsChildreansSublings(root , tagStr , 2) ;
        }
        if(choice == 6){
            getTagParentsChildreansSublings(root , tagStr , 3) ;
        }
        if(choice == 7) break;

    }

}

int main(){
    createLinkList() ;
    createTreeControl() ;
    //outputTreePreOrder(root) ;

   menu() ;

    return 0 ;

}

