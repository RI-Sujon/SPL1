#include"library.h"
#include<stdlib.h>

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

char fullTag[1000] ;
int count = 0 ;

void getTagInfo(struct Node *current){

    int j , flag = -1;

    if((current->tag)[0]=='!'){
        fullTag[count-1] = ' ' ;
        for(j=1 ; j<strlen(current->tag) ;j++){
            fullTag[count] = (current->tag)[j] ;
            count++ ;
        }
        fullTag[count] = '>' ;
        count++ ;
        flag = 0 ;
    }

    for(j=0 ; j<strlen(current->tag) && flag!=0 ; j++){

        if((current->tag)[0]=='~' && flag!=1){
            flag = 1 ;
            continue ;
        }
        fullTag[count] = (current->tag)[j] ;
        count++ ;
    }

    int i ;
    for(i=0 ; i<10 ; i++){
        if((current->children[i])!=NULL)
        {
            getTagInfo(current->children[i]) ;
        }
    }

    if((current->tag)[0]=='<'){
        fullTag[count] = '<' ;
        count++ ;
        fullTag[count] = '/' ;
        count++ ;
        int k ;
        for(k=1 ; k<strlen(current->tag) ; k++){
            fullTag[count] = (current->tag)[k] ;
            count++ ;
        }
     }
}

void getTag(struct Node *current,char tag[100]){
    int i , flagforEquality = 0 ;
    char *strr = current->tag ;

    for(i=0 ; i<strlen(strr)&&strlen(strr)==strlen(tag) ; i++){

            flagforEquality = 1 ;
            if(strr[i]!=tag[i]) {
                    flagforEquality = -1 ;
                break ;
            }
    }

     if(flagforEquality==1){
        getTagInfo(current) ;
        printf("fullTag: %s\n",fullTag) ;
        memset(fullTag, 0, sizeof(fullTag));
        count = 0 ;
     }

    for(i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTag(current->children[i] ,tag ) ;
        }
    }
}

void getTagAttributeOrString(struct Node *current,char tagStr[100],char ch){

    int i , flagforEquality = 0 ;
    char *strr = current->tag ;

    for(i=0 ; i<strlen(strr)&&strlen(strr)==strlen(tagStr) ; i++){

            flagforEquality = 1 ;
            if(strr[i]!=tagStr[i]) {
                flagforEquality = -1 ;
                break ;
            }
    }

    if(flagforEquality==1){

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
                    str[strlen(str)-1] = '\0' ;
                    printf("string or attribute is: %s\t\t" ,str);
                }
            }

            else return ;
        }
    }

    //int i ;
    for(i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTagAttributeOrString(current->children[i] ,tagStr , ch) ;
        }
    }

}

void getTagParentsChildreansSublings(struct Node *current,char *tagStr,int flag){


    int i , flagforEquality = 0 ;
    char *str = current->tag ;

    for(i=0 ; i<strlen(str)&&strlen(str)==strlen(tagStr) ; i++){
            flagforEquality = 1 ;
            if(str[i]!=tagStr[i]) {
                    flagforEquality = -1 ;
                break ;
            }
    }

    if(flagforEquality==1){
        if(flag==1){
            if(current->parent!=NULL)
                printf("Parent is %s\n" ,current->parent->tag ) ;
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

    for(i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTagParentsChildreansSublings(current->children[i] ,tagStr , flag) ;

        }
    }
}

void menu(struct Node *root){
    while(1){
        int choice ;

        printf("\nEnter Your Choice \n1.find tag\n2.get tag's attribute\n3.get tag's String\n4.get tag's parents\n5.get tag's childrens\n6.get tag's sublings\n7. exit \n " );
        scanf("%d" , &choice) ;

        char tagStr[100] ;

        if(choice == 1) {
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTag(root,tagStr) ;
        }

        if(choice == 2){
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTagAttributeOrString(root,tagStr,'!') ;
        }

        if(choice == 3){
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTagAttributeOrString(root,tagStr,'~') ;
        }

        if(choice == 4){
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTagParentsChildreansSublings(root , tagStr , 1) ;

        }

        if(choice == 5){
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTagParentsChildreansSublings(root , tagStr , 2) ;
        }

        if(choice == 6){
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTagParentsChildreansSublings(root , tagStr , 3) ;
        }

        if(choice == 7) break;
    }

}


