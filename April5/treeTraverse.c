#include<stdlib.h>
#include"library.h"

char fullTag[10000] ;
int fullTag_count = 0 ;
char *emptyTagList1[] = {"<br>" , "<hr>" , "<img>" , "<input>" , "<link>" , "<meta>" , "<source>"} ;
int flagForEmptyTag1 = 0 ;

char* findAll(struct Node *current,char *tag){
    char str_Tag[100] ;
    int count_TagChar = 0 ,i;

    if(strcmp(tag,"true")==0){
        findAll_byTagOrAttrString_getFullTag(current) ;
        fullTag[fullTag_count] = ',' ;
        fullTag_count++ ;
        fullTag[fullTag_count] = '\n' ;
        fullTag_count++ ;
    }

    if(tag[0]=='['){
        for(i=1 ; i<strlen(tag)+1 && tag[i-1]!=']' ; i++){
            if(tag[i]==','||tag[i]==']'){

                str_Tag[count_TagChar] = '\0';
                 //printf("test 1:  %s\n",str_Tag) ;

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
                printf("test1:  %s\n",str_Tag) ;
                findAll_byTag(current,str_Tag) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }
        }
    }

    else{
        str_Tag[count_TagChar] = '!';
        count_TagChar++ ;
        for(i=0 ; i<strlen(tag)+1 && tag[i-1]!=','; i++){
            if(tag[i]==','||tag[i]=='\0'){
                str_Tag[count_TagChar] = '\0';
                //printf("test 1:  %s\n",str_Tag) ;
                findAll_byAttrString(current,str_Tag) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }

            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;
        }
    }

    if(tag[i+1]==','||tag[i]==','){
        if(tag[i]==','){
            i=i-1;
        }

        for(i=i+2;i<strlen(tag)+1 ; i++){
            if(tag[i]==','|| tag[i]=='\0'){
                str_Tag[count_TagChar] = '\0';
                printf("attr:%s\n",str_Tag);
                findAll_checkAttr(str_Tag) ;
                memset(str_Tag, 0, sizeof(str_Tag));
                count_TagChar = 0 ;
                continue ;
            }

            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;
        }
    }

    fullTag[fullTag_count-2] = '\0' ;
    return fullTag;
}

void findAll_byAttrString(struct Node *current,char *AttrString){
    int i , flagforEquality = 0 ;
    char *strr = current->tag ;

    if(strcmp(strr,AttrString)==0){
        findAll_byTagOrAttrString_getFullTag(current->parent) ;
        fullTag[fullTag_count] = ',' ;
        fullTag_count++ ;
        fullTag[fullTag_count] = '\n' ;
        fullTag_count++ ;
     }

    for(i=0 ; i<10 ; i++){
        if((current->children[i])!=NULL)
        {
            findAll_byAttrString(current->children[i] ,AttrString ) ;
        }
    }
}

void findAll_checkAttr(char *attr){
    int i ,count_str=0,start_fulltagForComma=0,flagForComma=-1,index_helpAttr=0;
    char str[100],helpAttr[fullTag_count];
    for(i=0 ; i<fullTag_count ; i++){
        if(fullTag[i]==' '||fullTag[i]=='>'){
            str[count_str]='\0' ;
            //printf("checkAttr:%s\n",str) ;
            if(strcmp(str,attr)==0){
                //printf("ok\n");
                flagForComma = 1 ;
            }

            count_str=0 ;
            memset(str, 0, sizeof(str));
            continue ;
        }

        str[count_str]=fullTag[i] ;
        count_str++ ;
        //printf("ddd:%s\n",helpAttr) ;
        if(fullTag[i]==','){
            if(flagForComma==1){
                int j ;
                for(j=start_fulltagForComma ; j < i ; j++){
                    helpAttr[index_helpAttr] = fullTag[j] ;
                    index_helpAttr++ ;
                }
                helpAttr[index_helpAttr] = '\0' ;

                flagForComma = -1 ;
                start_fulltagForComma = i ;
            }

            else {
                start_fulltagForComma = i+1 ;
            }
        }
    }
    memset(fullTag, 0, sizeof(fullTag));
    strcpy(fullTag,helpAttr) ;
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

        findAll_byTagOrAttrString_getFullTag(current) ;
        fullTag[fullTag_count] = ',' ;
        fullTag_count++ ;
        fullTag[fullTag_count] = '\n' ;
        fullTag_count++ ;
     }

    for(i=0 ; i<10 ; i++){
        if((current->children[i])!=NULL)
        {
            findAll_byTag(current->children[i] ,tag ) ;
        }
    }
}

void findAll_byTagOrAttrString_getFullTag(struct Node *current){
    int j , flag = -1;

    if((current->tag)[0]=='!'){
        fullTag[fullTag_count-1] = ' ' ;
        for(j=1 ; j<strlen(current->tag) ;j++){
            fullTag[fullTag_count] = (current->tag)[j] ;
            fullTag_count++ ;
        }
        fullTag[fullTag_count] = '>' ;
        fullTag_count++ ;
        flag = 0 ;
    }

    for(j=0 ; j<strlen(current->tag) && flag!=0 ; j++){

        if((current->tag)[0]=='~' && flag!=1){
            flag = 1 ;
            continue ;
        }
        fullTag[fullTag_count] = (current->tag)[j] ;
        fullTag_count++ ;
    }

    int i ;
    for(i=0 ; i<10 ; i++){
        if((current->children[i])!=NULL)
        {
            findAll_byTagOrAttrString_getFullTag(current->children[i]) ;
        }
    }

    if((current->tag)[0]=='<'){
        int i ;
        for(i=0 ; i < 7 ; i++){
            //printf("%s\t%s\n",current->tag , emptyTagList1[i]) ;
            if(strcmp(current->tag , emptyTagList1[i])==0){
                flagForEmptyTag1 = 1 ;
                //printf("matching:%s\t%s\n",current->tag , emptyTagList1[i]) ;
            }
        }

        if(flagForEmptyTag1!=1){
            fullTag[fullTag_count] = '<' ;
            fullTag_count++ ;
            fullTag[fullTag_count] = '/' ;
            fullTag_count++ ;
            int k ;
            for(k=1 ; k<strlen(current->tag) ; k++){
                fullTag[fullTag_count] = (current->tag)[k] ;
                fullTag_count++ ;
            }
        }
        flagForEmptyTag1 = 0 ;
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
