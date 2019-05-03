#include<stdlib.h>
#include"library.h"

char fullTag[1000000] ;
int fullTag_count = 0 ;
char *emptyTagList1[] = {"<br>" , "<hr>" , "<img>" , "<input>" , "<link>" , "<meta>" , "<source>"} ;
int flagForEmptyTag1 = 0 ;

int findTagFlag = 0,cssIdentifyFlag = -1 ,flagForFindParent = -1  ;

char* find_all(struct Node *current,char *tag);
char* find(struct Node *current,char *tag);
char* findParent(struct Node *current,char *fullTagStr,char *tag);
char* findNextSublings(struct Node* current,char *fullTagStr);
char* findNextSublings(struct Node* current,char *fullTagStr);

char* findAllTag(struct Node *current,char *tag);
void findAll_byAttrString(struct Node *current,char *AttrString,int flag);
void findAll_checkAttr(char *attr,int flag);
void findAll_byTag(struct Node *current,char tag[100]);
void findAll_byTagOrAttrString_getFullTag(struct Node *current);
void findAllTag_byString(struct Node *current,char stringTag[100],int flag);
void findParent_byBackTraverse(struct Node *current,char* parentTag) ;
char* findParent_byTag(struct Node* current,char *strTag,char *currentTagStr,char *tag,int spFlag,int sublingsFlag);
void findNextOrPreviousSublings_byBackAndForwardTraverse(struct Node* current ,char tag ,int spFlag , int sublingsFlag) ;
char* findNextOrPreviousSublings(struct Node* current,char *fullTagStr,int sublingsFlag) ;

char* find_all(struct Node *current,char *tag)
{
    char *sujon= findAllTag(current,tag) ;
    int i ;
    for(i=fullTag_count-2 ; i>0 ; i--)
    {
        fullTag[i] = fullTag[i-1] ;
    }

    fullTag[0] = '[' ;
    fullTag[fullTag_count-1] = ']' ;
    fullTag[fullTag_count] = '\0' ;

    return sujon ;
}

char* find(struct Node *current,char *tag)
{
    findTagFlag = 1 ;
    char *sujon= findAllTag(current,tag) ;

    return sujon ;
}

char* findParent(struct Node *current,char *fullTagStr,char *tag)
{

    findTagFlag = 0 ;
    char *strTag=(char*) malloc(100);
    char *currentTagStr=(char*) malloc(1000);
    int i ;

    for(i=0 ; i < strlen(fullTagStr) ; i++){
        currentTagStr[i] = fullTagStr[i] ;
    }
    currentTagStr[i] = '\0' ;

    for(i=0 ;  ;i++){
        if(fullTagStr[i]=='>'){
           strTag[i] = fullTagStr[i] ;
           strTag[i+1] = '\0' ;
           break ;
        }

        else if(fullTagStr[i]==' '){
            strTag[i] = '>' ;
            strTag[i+1] = '\0' ;
            break ;
        }

        strTag[i] = fullTagStr[i] ;
    }
    fullTag[0] = '\0' ;
    fullTag_count = 0 ;
    //printf("%s\n%s\n",strTag,currentTagStr) ;
    findParent_byTag(current,strTag,currentTagStr,tag,-5 , 0) ;

    return fullTag ;
}

char* findNextSublings(struct Node* current,char *fullTagStr)
{
    return findNextOrPreviousSublings(current,fullTagStr,1) ;
}

char* findPreviousSublings(struct Node* current,char *fullTagStr)
{
    return findNextOrPreviousSublings(current,fullTagStr,-1) ;
}


char* findAllTag(struct Node *current,char *tag)
{
    char str_Tag[100] ;
    int count_TagChar = 0 ,i;

    int pn ;
    char strTagForCheckingString[100] ;
    for(pn=0 ; pn<strlen(tag) ; pn++){
        if(tag[pn]=='='){
            if(strcmp(strTagForCheckingString,"string")==0){
                char strTagforString[100] ;
                int qn ;
                for(qn=0 ; qn+3+pn<strlen(tag) ; qn++){
                    strTagforString[qn] = tag[pn+2+qn] ;
                }
                strTagforString[qn] = '\0';

                char c = '~';
                int i ;
                for(i=strlen(strTagforString) ; i >= 1 ; i--){
                    strTagforString[i] = strTagforString[i-1] ;
                }
                strTagforString[0] = c ;
                strTagforString[strlen(strTagforString)+1] = '\0';
                //printf("matha2:%sEND\n",strTagforString) ;

                findAllTag_byString(current,strTagforString,1) ;

                fullTag[fullTag_count-2] = '\0' ;
                return fullTag;
            }
        }
        strTagForCheckingString[pn] = tag[pn] ;
    }

    if(strcmp(tag,"true")==0)
    {
        findAll_byTagOrAttrString_getFullTag(current) ;
        fullTag[fullTag_count] = ',' ;
        fullTag_count++ ;
        fullTag[fullTag_count] = '\n' ;
        fullTag_count++ ;
    }

    if(tag[0]=='[')                                       //find with a set of tag
    {
        for(i=1 ; i<strlen(tag)+1 && tag[i-1]!=']' ; i++){
            if(tag[i]==','||tag[i]==']')
            {
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

    else if(tag[0]=='<')                              //find with a single tag
    {
        for(i=0 ; i<strlen(tag) ; i++)
        {
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
        for(i=0 ; i<strlen(tag) && count_ForTrue<4 ; i++)
        {
            if(tag[i-1]=='=')
            {
                flagForTrueSign = 1 ;
            }

            if(flagForTrueSign==1)
            {
                trueStr[count_ForTrue] = tag[i] ;
                count_ForTrue++ ;
            }
        }
        trueStr[count_ForTrue] = '\0' ;
        //printf("%s\n",trueStr) ;

        for(i=0 ; i<strlen(tag)+1 && tag[i-1]!=','; i++)
        {
            if(strcmp(trueStr,"true")==0 && tag[i]=='=')
            {
                str_Tag[count_TagChar] = '\0';
                for( ; tag[i]!=','&& tag[i]!='\0' ; i++ )
                {
                    //printf("attr1:%s\n",str_Tag);
                }
                findAll_byAttrString(current,str_Tag,1) ;
                count_TagChar = 0 ;
                memset(str_Tag, 0, sizeof(str_Tag));
                break ;
            }

            else if(tag[i]==','||tag[i]=='\0')
            {
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

    if(tag[i+1]==','||tag[i]==',')                            //filter with attribute
    {
        if(tag[i]==',')
        {
            i=i-1;
        }

        int flagForCheckTrueBeforeComma = -1 ;
        char trueStr[5] ;

        for(i=i+2;i<strlen(tag)+1 ; i++)                        //true attribute
        {
            if(flagForCheckTrueBeforeComma==-1)
            {
                int flagForTrueSign = -1,count_ForTrue = 0 ,j=0;
                for(j=i ; j<strlen(tag)&&count_ForTrue<4 ; j++)
                {
                    if(tag[j-1]=='=')
                    {
                        flagForTrueSign = 1 ;
                    }

                    if(flagForTrueSign==1)
                    {
                        trueStr[count_ForTrue] = tag[j] ;
                        count_ForTrue++ ;
                    }
                }
                trueStr[count_ForTrue] = '\0' ;
                //printf("%s\n",trueStr) ;
                flagForCheckTrueBeforeComma = 1 ;
            }


            if(strcmp(trueStr,"true")==0 && tag[i]=='=')
            {
                str_Tag[count_TagChar] = '\0';
                for( ; tag[i]!=','&& tag[i]!='\0' ; i++ )
                {
                    //printf("attr1:%s\n",str_Tag);
                }
                //printf("attr1:%s\n",str_Tag);
                findAll_checkAttr(str_Tag,1) ;
                memset(str_Tag, 0, sizeof(str_Tag));
                count_TagChar = 0 ;
                flagForCheckTrueBeforeComma = -1 ;
                continue ;
            }

            else if(tag[i]==','|| tag[i]=='\0')                   //normal Attribute
            {
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

void findAll_byAttrString(struct Node *current,char *AttrString,int flag)
{
    int i , flagforEquality = 0 ;
    char *strr = current->tag ;
    if(flag==1){
        for(i=0 ; i<strlen(strr)&&strr[i]!='=' ; i++)
        {
            flagforEquality = 1 ;
            if(strr[i]!=AttrString[i])
            {
                flagforEquality = -1 ;
                break ;
            }
        }

        if(flagforEquality==1)
        {
            if(findTagFlag==1 || findTagFlag==0)
            {
                //printf("limit:%d\n",findTagFlag) ;
                findAll_byTagOrAttrString_getFullTag(current->parent) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagFlag==1){
                    findTagFlag = -1 ;
                    return ;
                }
            }
        }
    }

    else if(strcmp(strr,AttrString)==0 && flag!=1)
    {
        if(findTagFlag==1 || findTagFlag==0)
        {
                //printf("limit:%d\n",findTagFlag) ;
                findAll_byTagOrAttrString_getFullTag(current->parent) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagFlag==1){
                    findTagFlag = -1 ;
                    return ;
                }
            }
    }
    for(i=0 ; i<1000 ; i++)
    {
        if((current->children[i])!=NULL)
        {
            findAll_byAttrString(current->children[i] ,AttrString ,flag ) ;
        }
        else break ;
    }
}

void findAll_checkAttr(char *attr,int flag)
{
    int i,j ,count_str=0,start_fulltagForComma=0,flagForComma=-1,index_helpAttr=0,flagforEquality=-1;
    char str[100],helpAttr[fullTag_count];
    for(i=0 ; i<fullTag_count ; i++){
        if(fullTag[i]==' '||fullTag[i]=='>')
        {
            str[count_str]='\0' ;
            //printf("checkAttr:%s\n",str) ;
            //printf("ok\n");
            if(flag==1)
            {
                for(j=0 ; j<strlen(str)&&str[j]!='=' ; j++)
                {
                    flagforEquality = 1 ;
                    if(str[j]!=attr[j]) {
                        flagforEquality = -1 ;
                        break ;
                    }
                }

                if(flagforEquality==1)
                {
                    flagForComma = 1 ;
                }
            }

            else if(strcmp(str,attr)==0)
            {
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
        if(fullTag[i]==',')
        {
            if(flagForComma==1)
            {
                int j ;
                for(j=start_fulltagForComma ; j <= i ; j++)
                {
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

void findAll_byTag(struct Node *current,char tag[100])
{
    int i , flagforEquality = 0 ;
    char *strr = current->tag ;

    for(i=0 ; i<strlen(strr)&&strlen(strr)==strlen(tag) ; i++)
    {
            flagforEquality = 1 ;
            if(strr[i]!=tag[i])
            {
                flagforEquality = -1 ;
                break ;
            }
    }

    if(flagforEquality==1)
    {
        if(findTagFlag==1 || findTagFlag==0)
        {
                findAll_byTagOrAttrString_getFullTag(current) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagFlag==1)
                {
                    findTagFlag = -1 ;
                    return ;
                }
        }
     }

    for(i=0 ; i<1000 ; i++)
    {
        if((current->children[i])!=NULL)
        {
            findAll_byTag(current->children[i] ,tag ) ;
        }
        else break ;
    }
}

void findAll_byTagOrAttrString_getFullTag(struct Node *current)
{
    int j , flag = -1;

    if((current->tag)[0]=='!'){
        fullTag[fullTag_count-1] = ' ' ;
        for(j=1 ; j<strlen(current->tag) ;j++)
        {
            fullTag[fullTag_count] = (current->tag)[j] ;
            fullTag_count++ ;
        }
        fullTag[fullTag_count] = '>' ;
        fullTag_count++ ;
        flag = 0 ;
    }

    //cssIdentifyFlag = -1 ;

    for(j=0 ; j<strlen(current->tag) && flag!=0 ; j++)
    {
        if((current->tag)[0]=='~' && flag!=1)
        {
            flag = 1 ;
            continue ;
        }
        else if((current->tag)[0]=='^' && flag!=1)
        {
            flag = 1 ;
            if(cssIdentifyFlag==3)
            {
                fullTag[fullTag_count-1] = '}' ;
            }
            cssIdentifyFlag = 1 ;
            continue ;
        }
        else if((current->tag)[0]=='=' && flag!=1)
        {
            flag = 1 ;
            cssIdentifyFlag = 2 ;
            continue ;
        }
        else if((current->tag)[0]=='%' && flag!=1)
        {
            flag = 1 ;
            cssIdentifyFlag = 3 ;
            continue ;
        }

        fullTag[fullTag_count] = (current->tag)[j] ;
        fullTag_count++ ;
    }

    if(cssIdentifyFlag==1)
    {
        fullTag[fullTag_count] = '{' ;
        fullTag_count++ ;
    }
    else if(cssIdentifyFlag==2)
    {
        fullTag[fullTag_count] = ':' ;
        fullTag_count++ ;
    }
    else if(cssIdentifyFlag==3)
    {
        fullTag[fullTag_count] = ';' ;
        fullTag_count++ ;
    }
    //  printf("Get Tag:%s\n\n",current->tag) ;
    int i ;
    for(i=0 ; i<1000 ; i++)
    {
        if((current->children[i])!=NULL)
        {
            findAll_byTagOrAttrString_getFullTag(current->children[i]) ;
        }
        else break ;
    }

    if((current->tag)[0]=='<')
    {
        int i ;
        for(i=0 ; i < 7 ; i++)
        {
            //printf("%s\t%s\n",current->tag , emptyTagList1[i]) ;
            if(strcmp(current->tag , emptyTagList1[i])==0)
            {
                flagForEmptyTag1 = 1 ;
                //printf("matching:%s\t%s\n",current->tag , emptyTagList1[i]) ;
            }
        }

        if(flagForEmptyTag1!=1)
        {
            if(cssIdentifyFlag==3 && flag!=1)
            {
                fullTag[fullTag_count-1] = '}' ;
                cssIdentifyFlag=-1 ;
            }
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


void findAllTag_byString(struct Node *current,char stringTag[100],int flag)
{
    int i , flagforEquality = 0 ;
    char *strr = current->tag ;
    if(flag==1){
        for(i=0 ; i<strlen(strr)&&strr[i]!='=' ; i++)
        {
            flagforEquality = 1 ;
            if(strr[i]!=stringTag[i])
            {
                flagforEquality = -1 ;
                break ;
            }
        }

        if(flagforEquality==1)
        {
            if(findTagFlag==1 || findTagFlag==0)
            {
                //printf("limit:%d\n",findTagFlag) ;
                findAll_byTagOrAttrString_getFullTag(current->parent) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagFlag==1){
                    findTagFlag = -1 ;
                    return ;
                }
            }
        }
    }

    else if(strcmp(strr,stringTag)==0 && flag!=1)
    {
        if(findTagFlag==1 || findTagFlag==0)
        {
                //printf("limit:%d\n",findTagFlag) ;
                findAll_byTagOrAttrString_getFullTag(current->parent) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;

                if(findTagFlag==1){
                    findTagFlag = -1 ;
                    return ;
                }
            }
    }
    for(i=0 ; i<1000 ; i++)
    {
        if((current->children[i])!=NULL)
        {
            findAll_byAttrString(current->children[i] ,stringTag ,flag ) ;
        }
        else break ;
    }
}

void outputTreePreOrder(struct Node *parent)
{
    printf("%s\n",parent->tag) ;
    int i ;
    for(i=0 ; i<1000 ; i++)
    {

        if((parent->children[i])!=NULL)
        {
            outputTreePreOrder(parent->children[i]) ;
        }
        else break ;
    }
}


void findParent_byBackTraverse(struct Node *current,char* parentTag)
{
    if(flagForFindParent==1){
        return ;
    }

    int i , flagforEquality = 0 ;
    char *strr = current->tag ;

    for(i=0 ; i<strlen(strr)&&strlen(strr)==strlen(parentTag) ; i++)
    {
            flagforEquality = 1 ;
            if(strr[i]!=parentTag[i])
            {
                flagforEquality = -1 ;
                break ;
            }
    }

    if(flagforEquality==1)
    {
        if(findTagFlag==1 || findTagFlag==0)
        {
                findAll_byTagOrAttrString_getFullTag(current) ;
                fullTag[fullTag_count] = '\0' ;
                //printf("full:%s\n",fullTag) ;
                flagForFindParent = 1 ;
                return ;
        }
     }

    for(i=0 ; i<1000 ; i++)
    {
        if((current->children[i])!=NULL)
        {
            findParent_byBackTraverse(current->parent,parentTag ) ;
        }
        else break ;
    }
}

char* findParent_byTag(struct Node* current,char *strTag,char *currentTagStr,char *tag,int spFlag,int sublingsFlag)
{
    if(flagForFindParent==1){
        return fullTag ;
    }

    int i , flagforEquality = 0 ;
    char *strr = current->tag ;

    for(i=0 ; i<strlen(strr)&&strlen(strr)==strlen(strTag) ; i++)
    {
            flagforEquality = 1 ;
            if(strr[i]!=strTag[i])
            {
                flagforEquality = -1 ;
                break ;
            }
    }

    if(flagforEquality==1)
    {
        if(findTagFlag==1 || findTagFlag==0)
        {
                findAll_byTagOrAttrString_getFullTag(current) ;

                fullTag[fullTag_count] = '\0' ;
                flagforEquality = -1 ;
                for(i=0 ; i<strlen(fullTag)&&strlen(currentTagStr)==strlen(fullTag) ; i++)
                {
                        flagforEquality = 1 ;
                        if(currentTagStr[i]!=fullTag[i])
                        {
                            flagforEquality = -1 ;
                            break ;
                        }
                }

                if(flagforEquality==1 && spFlag<0)
                {
                    fullTag[0] = '\0' ;
                    fullTag_count = 0 ;

                    findParent_byBackTraverse(current->parent,tag) ;
                    return ;
                }

                if(flagforEquality==1 && spFlag>=0)
                {
                    fullTag[0] = '\0' ;
                    fullTag_count = 0 ;
                    findNextOrPreviousSublings_byBackAndForwardTraverse(current->parent,tag,spFlag,sublingsFlag) ;
                    flagForFindParent=1 ;
                    return fullTag ;
                }

                fullTag_count =  0 ;
        }
     }

    if(flagForFindParent==1){
        return fullTag;
    }

    for(i=0 ; i<1000 ; i++)
    {
        if((current->children[i])!=NULL)
        {
            if(spFlag<0){
                findParent_byTag(current->children[i] ,strTag,currentTagStr,tag,spFlag,sublingsFlag ) ;
            }

            else if(spFlag>=0) {
                spFlag = i ;
                findParent_byTag(current->children[i] ,strTag,currentTagStr,tag,spFlag,sublingsFlag) ;
            }
        }
        else break ;
    }
}

void findNextOrPreviousSublings_byBackAndForwardTraverse(struct Node* current ,char tag ,int spFlag , int sublingsFlag)
{
    int i ;
    if(sublingsFlag==1)
    {
        for(i=spFlag+1 ; i<1000 ; i++)
        {
            if((current->children[i])!=NULL)
            {
                findAll_byTagOrAttrString_getFullTag(current->children[i]) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;
            }
            else break ;
        }
    }

    else if(sublingsFlag==-1)
    {
        for(i=0 ; i<spFlag ; i++)
        {
            if((current->children[i])!=NULL)
            {
                findAll_byTagOrAttrString_getFullTag(current->children[i]) ;

                fullTag[fullTag_count] = ',' ;
                fullTag_count++ ;
                fullTag[fullTag_count] = '\n' ;
                fullTag_count++ ;
            }
            else break ;
        }
    }
}

char* findNextOrPreviousSublings(struct Node* current,char *fullTagStr,int sublingsFlag)
{
    findTagFlag = 0 ;
    char *strTag=(char*) malloc(100);
    char *currentTagStr=(char*) malloc(1000);
    char *fullSublingsTag = (char*) malloc(100000) ;

    int i ;
    for(i=0 ; i < strlen(fullTagStr) ; i++){
        currentTagStr[i] = fullTagStr[i] ;
    }
    currentTagStr[i] = '\0' ;

    for(i=0 ;  ;i++){
        if(fullTagStr[i]=='>'){
           strTag[i] = fullTagStr[i] ;
           strTag[i+1] = '\0' ;
           break ;
        }

        else if(fullTagStr[i]==' '){
            strTag[i] = '>' ;
            strTag[i+1] = '\0' ;
            break ;
        }
        strTag[i] = fullTagStr[i] ;
    }
    fullTag[0] = '\0' ;
    fullTag_count = 0 ;

    findParent_byTag(current,strTag,currentTagStr,"faltu",0,sublingsFlag) ;

    fullSublingsTag[0] = '[' ;
    for(i=1 ; i<fullTag_count ; i++)
    {
        fullSublingsTag[i] = fullTag[i-1] ;
    }
    fullSublingsTag[i-1] = ']' ;
    fullSublingsTag[i] = '\0' ;

    return fullSublingsTag ;
}
