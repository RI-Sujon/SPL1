#include<stdlib.h>
#include"library.h"

char fullTag[1000] ;
int count = 0 ;
char *emptyTagList1[] = {"<br>" , "<hr>" , "<img>" , "<input>" , "<link>" , "<meta>" , "<source>"} ;
int flagForEmptyTag1 = 0 ;

char* findAll(struct Node *current,char *tag){
    char str_Tag[100] ;
    int count_TagChar = 0 ,i;

    if(tag[0]=='['){
        for(i=1 ; i<strlen(tag)+1 && tag[i]!=']' ; i++){
            if(tag[i]==','||tag[i]=='\0'){

                str_Tag[count_TagChar] = '\0';
                 printf("test:  %s\n",str_Tag) ;

                findAll_byTag(current,str_Tag) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                continue ;
            }

            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;
        }
    }

    else if(tag[0]=='<'){
        for(i=0 ; i<strlen(tag) ; i++){
            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;

            if(tag[i]=='>'){

                str_Tag[count_TagChar] = '\0';
                printf("test:  %s\n",str_Tag) ;

                findAll_byTag(current,str_Tag) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }
        }

    }

    if(tag[i+1]==','){
        printf("matha\n") ;
        for(i=i+2;i<strlen(tag)+1 ; i++){
            if(tag[i]==','|| tag[i]=='\0'){
                str_Tag[count_TagChar] = '\0';
                printf("attr:%s\n",str_Tag);
                findAll_checkAttr(str_Tag) ;
            }

            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;
        }
    }

    fullTag[count-2] = '\0' ;
    return fullTag;
}

void findAll_checkAttr(char *attr){
    int i ,count_str=0;
    char str[100] ;
    for(i=0 ; i<count ; i++){

        if(fullTag[i]==' '){
            str[count_str]='\0' ;
            printf("checkAttr:%s\n",str) ;
            if(strcmp(str,attr)==0){
                printf("ok\n");
            }
            count_str=0 ;
            memset(str, 0, sizeof(str));
            continue ;

        }

        str[count_str]=fullTag[i] ;
        count_str++ ;

    }
}

void findAll_byTag(struct Node *current,char tag[100]){
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
        findAll_byTag_getFullTag(current) ;
        fullTag[count] = ',' ;
        count++ ;
        fullTag[count] = '\n' ;
        count++ ;
     }

    for(i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            findAll_byTag(current->children[i] ,tag ) ;
        }
    }
}

void findAll_byTag_getFullTag(struct Node *current){

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
            findAll_byTag_getFullTag(current->children[i]) ;
        }
    }

    if((current->tag)[0]=='<'){
        int i ;
        for(i=0 ; i < 7 ; i++){
            printf("%s\t%s\n",current->tag , emptyTagList1[i]) ;
            if(strcmp(current->tag , emptyTagList1[i])==0){
                flagForEmptyTag1 = 1 ;
                printf("matching:%s\t%s\n",current->tag , emptyTagList1[i]) ;
            }
        }

        if(flagForEmptyTag1!=1){
            fullTag[count] = '<' ;
            count++ ;
            fullTag[count] = '/' ;
            count++ ;
            int k ;
            for(k=1 ; k<strlen(current->tag) ; k++){
                fullTag[count] = (current->tag)[k] ;
                count++ ;
            }

            flagForEmptyTag1 = 0 ;
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
            //getTag(root,tagStr) ;
        }

        if(choice == 2){
            printf("Enter Tag Name : ") ;
            scanf( "%s" ,&tagStr );
            getTagAttributeOrString(root,tagStr,'!') ;
        }

        if(choice == 3){
            printf("Enter Tag Name : ") ;
            //scanf( "%s" ,&tagStr );
            getTagAttributeOrString(root,tagStr,'~') ;
        }

        if(choice == 4){
            printf("Enter Tag Name : ") ;
            //scanf( "%s" ,&tagStr );
            getTagParentsChildreansSublings(root , tagStr , 1) ;

        }

        if(choice == 5){
            printf("Enter Tag Name : ") ;
            //scanf( "%s" ,&tagStr );
            getTagParentsChildreansSublings(root , tagStr , 2) ;
        }

        if(choice == 6){
            printf("Enter Tag Name : ") ;
            //scanf( "%s" ,&tagStr );
            getTagParentsChildreansSublings(root , tagStr , 3) ;
        }

        if(choice == 7) break;
    }

}

