#include<stdlib.h>
#include"library.h"

char fullTag[1000000] ;
int fullTag_count = 0 ;
char *emptyTagList1[] = {"<br>" , "<hr>" , "<img>" , "<input>" , "<link>" , "<meta>" , "<source>"} ;
int flagForEmptyTag1 = 0 ;

int findTagLimit = 0 ;

char* findAllTag(struct Node *current,char *tag){
    char str_Tag[100] ;
    int count_TagChar = 0 ,i;

    if(strcmp(tag,"true")==0){
        findAll_byTagOrAttrString_getFullTag(current) ;
        fullTag[fullTag_count] = ',' ;
        fullTag_count++ ;
        fullTag[fullTag_count] = '\n' ;
        fullTag_count++ ;
    }

    if(tag[0]=='['){                                        //find with a set of tag
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

    else if(tag[0]=='<'){                                   //find with a single tag
        for(i=0 ; i<strlen(tag) ; i++){
            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;

            if(tag[i]=='>'){
                str_Tag[count_TagChar] = '\0';
                //printf("test1:  %s\n",str_Tag) ;
                findAll_byTag(current,str_Tag) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }
        }
    }

    else{                                                   //find with attribute
        str_Tag[count_TagChar] = '!';
        count_TagChar++ ;
        char trueStr[5] ;
        int flagForTrueSign = -1,count_ForTrue = 0 ;
        for(i=0 ; i<strlen(tag) && count_ForTrue<4 ; i++){
            if(tag[i-1]=='='){
                flagForTrueSign = 1 ;
            }

            if(flagForTrueSign==1){
                trueStr[count_ForTrue] = tag[i] ;
                count_ForTrue++ ;
            }
        }
        trueStr[count_ForTrue] = '\0' ;
        //printf("%s\n",trueStr) ;

        for(i=0 ; i<strlen(tag)+1 && tag[i-1]!=','; i++){
            if(strcmp(trueStr,"true")==0 && tag[i]=='='){
                str_Tag[count_TagChar] = '\0';
                for( ; tag[i]!=','&& tag[i]!='\0' ; i++ ){
                    //printf("attr1:%s\n",str_Tag);
                }
                findAll_byAttrString(current,str_Tag,1) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }

            else if(tag[i]==','||tag[i]=='\0'){
                str_Tag[count_TagChar] = '\0';
                //printf("test 1:  %s\n",str_Tag) ;
                findAll_byAttrString(current,str_Tag,-1) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }

            str_Tag[count_TagChar] = tag[i];
            count_TagChar++ ;
        }
    }

    if(tag[i+1]==','||tag[i]==','){                         //filter with attribute
        if(tag[i]==','){
            i=i-1;
        }

        int flagForCheckTrueBeforeComma = -1 ;
        char trueStr[5] ;

        for(i=i+2;i<strlen(tag)+1 ; i++){                  //true attribute
            if(flagForCheckTrueBeforeComma==-1){
                int flagForTrueSign = -1,count_ForTrue = 0 ,j=0;
                for(j=i ; j<strlen(tag)&&count_ForTrue<4 ; j++){
                    if(tag[j-1]=='='){
                        flagForTrueSign = 1 ;
                    }

                    if(flagForTrueSign==1){
                        trueStr[count_ForTrue] = tag[j] ;
                        count_ForTrue++ ;
                    }
                }
                trueStr[count_ForTrue] = '\0' ;
                //printf("%s\n",trueStr) ;
                flagForCheckTrueBeforeComma = 1 ;
            }


            if(strcmp(trueStr,"true")==0 && tag[i]=='='){
                str_Tag[count_TagChar] = '\0';
                for( ; tag[i]!=','&& tag[i]!='\0' ; i++ ){
                    //printf("attr1:%s\n",str_Tag);
                }
                //printf("attr1:%s\n",str_Tag);
                findAll_checkAttr(str_Tag,1) ;
                memset(str_Tag, 0, sizeof(str_Tag));
                count_TagChar = 0 ;
                flagForCheckTrueBeforeComma = -1 ;
                continue ;
            }

            else if(tag[i]==','|| tag[i]=='\0'){            //normal Attribute
                str_Tag[count_TagChar] = '\0';
                //printf("attr2:%s\n",str_Tag);
                findAll_checkAttr(str_Tag,-1) ;
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

void findAll_byAttrString(struct Node *current,char *AttrString,int flag){

    int i , flagforEquality = 0 ;
    char *strr = current->tag ;
    if(flag==1){
        for(i=0 ; i<strlen(strr)&&strr[i]!='=' ; i++){
            flagforEquality = 1 ;
            if(strr[i]!=AttrString[i]) {
                flagforEquality = -1 ;
                break ;
            }
        }

        if(flagforEquality==1){
            if(findTagLimit==1 || findTagLimit==0){
                //printf("limit:%d\n",findTagLimit) ;
                findAll_byTagOrAttrString_getFullTag(current->parent) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagLimit==1){
                    findTagLimit = -1 ;
                    return ;
                }
            }
        }
    }

    else if(strcmp(strr,AttrString)==0 && flag!=1){
        if(findTagLimit==1 || findTagLimit==0){
                //printf("limit:%d\n",findTagLimit) ;
                findAll_byTagOrAttrString_getFullTag(current->parent) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagLimit==1){
                    findTagLimit = -1 ;
                    return ;
                }
            }
     }

    for(i=0 ; i<1000 ; i++){
        if((current->children[i])!=NULL)
        {
            findAll_byAttrString(current->children[i] ,AttrString ,flag ) ;
        }
        else break ;
    }
}

void findAll_checkAttr(char *attr,int flag){
    int i,j ,count_str=0,start_fulltagForComma=0,flagForComma=-1,index_helpAttr=0,flagforEquality=-1;
    char str[100],helpAttr[fullTag_count];
    for(i=0 ; i<fullTag_count ; i++){
        if(fullTag[i]==' '||fullTag[i]=='>'){
            str[count_str]='\0' ;
            //printf("checkAttr:%s\n",str) ;
            //printf("ok\n");
            if(flag==1){
                for(j=0 ; j<strlen(str)&&str[j]!='=' ; j++){
                    flagforEquality = 1 ;
                    if(str[j]!=attr[j]) {
                        flagforEquality = -1 ;
                        break ;
                    }
                }

                if(flagforEquality==1){
                    flagForComma = 1 ;
                }
            }

            else if(strcmp(str,attr)==0){
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
                for(j=start_fulltagForComma ; j <= i ; j++){
                    helpAttr[index_helpAttr] = fullTag[j] ;
                    index_helpAttr++ ;
                }
                helpAttr[index_helpAttr] = '\0' ;

                flagForComma = -1 ;
                start_fulltagForComma = i+1 ;
            }

            else {
                //fullTag_count = fullTag_count - i+1 ;
                start_fulltagForComma = i+1 ;
            }
        }
    }
    memset(fullTag, 0, sizeof(fullTag));
    strcpy(fullTag,helpAttr) ;
    fullTag_count = strlen(helpAttr)+1 ;
    //printf("flltag5:%s\n",fullTag) ;
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

        if(findTagLimit==1 || findTagLimit==0) {
                findAll_byTagOrAttrString_getFullTag(current) ;
                //printf("limit:%d\n",findTagLimit) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagLimit==1){
                    findTagLimit = -1 ;
                    return ;
                }
        }
     }

    for(i=0 ; i<1000 ; i++){
        if((current->children[i])!=NULL)
        {
            findAll_byTag(current->children[i] ,tag ) ;
        }
        else break ;
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
    //  printf("Get Tag:%s\n\n",current->tag) ;
    int i ;
    for(i=0 ; i<1000 ; i++){
        if((current->children[i])!=NULL)
        {
            findAll_byTagOrAttrString_getFullTag(current->children[i]) ;
        }
        else break ;
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
    for(i=0 ; i<1000 ; i++){

        if((parent->children[i])!=NULL)
        {
            outputTreePreOrder(parent->children[i]) ;
        }
        else break ;
    }
}


char* findAll(struct Node *current,char *tag){
    char *sujon= findAllTag(current,tag) ;
    int i ;
    for(i=fullTag_count-2 ; i>0 ; i--){
        fullTag[i] = fullTag[i-1] ;
    }

    fullTag[0] = '[' ;
    fullTag[fullTag_count-1] = ']' ;
    fullTag[fullTag_count] = '\0' ;

    return sujon ;
}

char* find(struct Node *current,char *tag){
    findTagLimit = 1 ;
    char *sujon= findAllTag(current,tag) ;

    return sujon ;
}
