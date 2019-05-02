#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "library.h"

struct Node *root , *current;

char *emptyTagList[] = {"<br>" , "<hr>" , "<img>" , "<input>" , "<link>" , "<meta>" , "<source>"} ;
int flagForEmptyTag = 0 ;

void createLinkList()
{
    root = NULL ;
    current = NULL ;
}

struct Node* createNode(char *tag)
{
    struct Node *temp =  malloc(sizeof(struct Node));
    temp->tag = tag ;
    int i = 0 ;
    for(i=0 ; i<1000 ; i++){
        temp->children[i] = NULL ;
    }
    temp->parent = NULL ;
    return temp ;
}

void inseartNode(struct Node *newNode , int flag)
{
    newNode->parent = current ;
    int i = 0 ;
    for(i=0 ; i<1000 ; i++){
        if(current->children[i]==NULL)
        {
            current->children[i] = newNode ;
            if(flag==1) current = newNode ;
            break ;
        }
    }
}

void operation(char *str)
{
    //printf("String:%s\n",str) ;
    if(flagForEmptyTag == 1 &&  str[0] == '<'|| flagForEmptyTag == 1 && str[0] == '~')
    {
        flagForEmptyTag = 0 ;
        current = current->parent ;
    }
    if(root==NULL)
    {
        struct node *newNode = createNode(str) ;
        root = newNode ;
        current = newNode ;
        return ;
    }

    if(str[1]=='/')
    {
        if(current->parent == NULL){
            current = NULL ;
            return ;
        }
        current = current->parent   ;

        return ;
    }

    int flag = 0 ;
    if(str[0]=='<') flag = 1 ;

    int i ;
    for(i=0 ; i < 7 ; i++)
    {
        if(strcmp(str , emptyTagList[i])==0)
        {
            flagForEmptyTag = 1 ;
        }
    }
    //printf("Pre Current:\t\t%s\n" ,current->tag);
    struct node *newNode = createNode(str) ;
    inseartNode(newNode,flag) ;
    //printf("Post Current:\t\t%s\n" ,current->tag);
}

void cssOperation(char *str ,int cssFlagForSelectParent)
{
    //printf("String:%s\n",str) ;
    //printf("Pre Current3:\t\t%s\n" ,current->tag);
    int flag ;
    if(cssFlagForSelectParent==1)
    {
        flag = 1 ;
        struct node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;
    }

    else if(cssFlagForSelectParent==2)
    {
        flag = 1 ;
        struct node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;
    }

    else if(cssFlagForSelectParent==3)
    {
        flag = 0 ;
        struct node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;
        current = current->parent   ;
    }

    else if(cssFlagForSelectParent==4)
    {
        flag = 0 ;
        struct node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;
        current = current->parent   ;
        current = current->parent   ;
    }
    //printf("Post Current4:\t\t%s\n" ,current->tag);

    return 0 ;
}

void createTreeControl()
{
    FILE *ioFile ;
    if ((ioFile = fopen("ict4.html","r")) == NULL)
    {
       printf("Error! opening file");
       exit(1);
    }

    char str[20000] ;
    char ch,flag='0' ;
    int s1 = 0 ,flagForHtmlAttr = -1,cnt ,cssFlag=0 ;

    fscanf(ioFile,"%c",&ch) ;                       //read '<' from html page

    while(ch!='>')
    {

        while(ch!='>'&&ch!=' ')                 //read first tag from html page
        {
            str[s1] = ch ;
            s1++ ;
            fscanf(ioFile,"%c",&ch) ;

        }

        if(flagForHtmlAttr==-1)
        {
            str[s1] = '>' ;
            str[s1+1] = '\0' ;
        }
        else str[s1] = '\0' ;

        char *hstr = (char*) malloc(100 + 1 ) ;

        for(cnt = 0 ; cnt < strlen(str) ; cnt++ )
        {
            hstr[cnt] = str[cnt] ;
        }
        hstr[cnt] = '\0' ;
        operation(hstr) ;

        if(ch==' ')
        {
            flagForHtmlAttr = 1 ;
            fscanf(ioFile,"%c",&ch) ;
            s1 = 0 ;
            memset(str, 0, sizeof(str));
            str[s1]='!' ;
            s1++ ;
        }
     }

        char endstring[] ="<1html>" ;

        while(strcmp(endstring ,"</html>"))
        {
            if(flag == '0')
            {
                fscanf(ioFile,"%c",&ch) ; // read a character...if character is '<' then it is symbol of starting a tag...else it it is symbol of starting a string element
                if(ch=='>')
                {
                    fscanf(ioFile,"%c",&ch) ;
                }
                if(ch=='\n' || ch ==' ' || ch == '\t') continue ;
            }
            else ch = flag ;

            int k ;
            for(k=strlen(str)-1 ; k >= 0 ; k--)
            {
                    str[k] = '\0' ;
            }

            if(ch=='<')
            {
                fscanf(ioFile,"%[^>]s",&str) ;          //read a full tag

                int i , j ,checkDoubleSignflag = 0 ;

                if(str[0]==ch)checkDoubleSignflag = 1 ;
                for(i=strlen(str) ; i > 0  && checkDoubleSignflag == 0; i--){
                    str[i] = str[i-1] ;
                }
                str[0] = ch ;
                str[strlen(str)] = '>' ;
                str[strlen(str)+1] = '\0' ;

                flag = '0' ;
            }

            else{
                fscanf(ioFile,"%[^<]s",&str) ;          //read a full  string element
                char c = '~';
                int i ;
                for(i=strlen(str)+1 ; i > 1 ; i--){
                    str[i] = str[i-2] ;
                }
                str[1] = ch ;
                str[0] = c ;
                flag = '<' ;
                str[strlen(str)+1] = '\0';
                //printf("%s\n",str) ;
            }

            char s[100] ;
            int flagForTag = 0 , flagForTag2 = 0;
            int i ,s2=0;
            for(i = 0 ; i<strlen(str)-1 && flag=='0' ; i++ )    //find attribute and tag from a tag
            {
                s[s2]=str[i] ;
                s2++ ;
                s[s2]='\0' ;
                if(str[i]==' ' || str[i+1]=='>')
                {
                    if(flagForTag == 0)
                    {
                        if(s[s2-1]==' ')
                        {
                            s[s2-1] = '>'  ;
                            s[s2] = '\0' ;
                        }
                        else {
                            s[s2] = '>' ;
                            s[s2+1] = '\0' ;
                        }

                        flagForTag = 1 ;
                        for(k=0 ; k <7 ; k++)
                        {
                            endstring[k] = s[k] ;
                        }

                        char *hstr = (char*) malloc(100 + 1 ) ;

                        for(cnt = 0 ; cnt < strlen(s) ; cnt++ )
                        {
                            hstr[cnt] = s[cnt] ;
                        }
                        hstr[cnt] = '\0' ;
                        operation(hstr) ;
                        if(strcmp(hstr,"<style>")==0)
                        {
                            //printf("%s\n",hstr) ;
                            cssFlag = 1 ;
                        }

                        else if(strcmp(hstr,"</style>")==0)
                        {
                            //printf("%s\n",hstr) ;
                            cssFlag = 0 ;
                        }
                        memset(s, 0, sizeof(s));
                        s2= 0 ;
                    }

                    else {
                        char c1 = '!';
                        int k ;
                        for(k=strlen(s) ; k > 0 ; k--)
                        {
                            s[k] = s[k-1] ;
                        }
                        s[0] = c1 ;

                        char *hstr = (char*) malloc(100 + 1 ) ;

                        for(cnt = 0 ; cnt < strlen(s) ; cnt++ )
                        {
                            hstr[cnt] = s[cnt] ;
                        }

                        if(hstr[cnt-1] == ' ')
                        {
                            hstr[cnt-1] = '\0' ;
                        }
                        else hstr[cnt] = '\0' ;

                        operation(hstr) ;

                        memset(s, 0, sizeof(s));
                        s2 = 0 ;
                    }
                }
            }

            if(flag == '<')
            {
                if(cssFlag==0){
                    char *hstr = (char*) malloc(100 + 1 ) ;
                    for(cnt = 0 ; cnt < strlen(str) ; cnt++ )
                    {
                        hstr[cnt] = str[cnt] ;
                    }
                    hstr[cnt] = '\0' ;
                    //printf("%s\n",hstr) ;
                    operation(hstr) ;
                }

                else if(cssFlag==1)
                {
                    char *cssStr = (char*) malloc(100 + 1 ) ;
                    int in = 0 ;

                    for(cnt = 1 ; cnt < strlen(str)  ; cnt++,in++ )
                    {
                        if(str[cnt]=='{')
                        {
                            char *hstr = (char*) malloc(100 + 1 ) ;
                            int jn ;
                            hstr[0] = '^' ;
                            for(jn = 0 ; jn<in ; jn++)
                            {
                                hstr[jn+1] = cssStr[jn] ;

                            }
                            hstr[jn+1] = '\0' ;

                            //printf("%s\n",hstr) ;
                            cssOperation(hstr , 1) ;

                            in = -1 ;
                            memset(cssStr, 0, sizeof(cssStr));
                            //memset(hstr, 0, sizeof(hstr));

                            continue ;
                        }

                        else if(str[cnt]==':')
                        {
                            char *hstr = (char*) malloc(100 + 1 ) ;
                            int jn ;
                            hstr[0] = '=' ;
                            for(jn = 0 ; jn<in ; jn++)
                            {
                                hstr[jn+1] = cssStr[jn] ;

                            }
                            hstr[jn+1] = '\0' ;

                            //printf("%s\n",hstr) ;
                            cssOperation(hstr,2) ;
                            in = -1 ;
                            memset(cssStr, 0, sizeof(cssStr));
                            //memset(hstr, 0, sizeof(hstr));
                            continue ;
                        }

                        else if(str[cnt]==';')
                        {
                            char *hstr = (char*) malloc(100 + 1 ) ;
                            int jn ;
                            hstr[0] = '%' ;
                            for(jn = 0 ; jn<in ; jn++)
                            {
                                hstr[jn+1] = cssStr[jn] ;

                            }
                            hstr[jn+1] = '\0' ;
                            //printf("%s\n",hstr) ;
                            cssOperation(hstr,3) ;
                            in = -1 ;
                            memset(cssStr, 0, sizeof(cssStr));
                            //memset(hstr, 0, sizeof(hstr));
                            continue ;
                        }

                        else if(str[cnt]=='}')
                        {
                            char *hstr = (char*) malloc(100 + 1 ) ;
                            int jn ;
                            hstr[0] = '%' ;
                            for(jn = 0 ; jn<in ; jn++)
                            {
                                hstr[jn+1] = cssStr[jn] ;
                            }
                            hstr[jn+1] = '\0' ;
                            //printf("%s\n",hstr) ;
                            cssOperation(hstr,4) ;
                            in = -1 ;
                            memset(cssStr, 0, sizeof(cssStr));
                            //memset(hstr, 0, sizeof(hstr));
                            continue ;
                        }
                        cssStr[in] = str[cnt] ;
                    }
                }
            }
    }
}

struct Node* htmlPerser()
{
    //getHtmlPage() ;
    createLinkList() ;
    createTreeControl() ;
    //outputTreePreOrder(root) ;
    return root ;
}
