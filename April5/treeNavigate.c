#include<stdlib.h>
#include "library.h"

char* getTagName(char tagStr[1000])
{
    int in ;
    char stringResult[1000] ;
    int jn ;
    for(jn=0 ; jn<strlen(tagStr) ; jn++)
    {
        stringResult[jn] = tagStr[jn] ;
        if(tagStr[jn]=='>')
        {
            //printf("String:%c\n",tagStr[in+1+jn]) ;
            stringResult[jn+1] = '\0' ;
            return stringResult ;
        }

        else if(tagStr[jn]==' ')
        {
            stringResult[jn] = '>' ;
            //printf("String:%c\n",tagStr[in+1+jn]) ;
            stringResult[jn+1] = '\0' ;
            return stringResult ;
        }
    }
}

char** getAllTagName(char tagStr[1000])
{
    //char * sub_str = malloc(10 * sizeof(char*));
    char ** stringResult = malloc(100 * sizeof(char*));
    int i ;
    for (i =0 ; i < 100; ++i){
        stringResult[i] = malloc(1000 * sizeof(char));
    }

    //char stringResult[100][1000] ;
    int in , kn=0 ;
    for(in=0 ;  ; in++)
    {
        int jn ;
        for(jn=0 ; ; jn++)
        {
            kn++ ;
            if(tagStr[kn]=='\n') kn++ ;
            stringResult[in][jn] = tagStr[kn] ;

            if(tagStr[kn]=='>')
            {
                stringResult[in][jn+1] = '\0' ;
                for( ; ; kn++){
                    if(tagStr[kn]==','||tagStr[kn]==']')
                        break ;
                }
                break ;
            }

            else if(tagStr[kn]==' ')
            {
                stringResult[in][jn] = '>' ;
                stringResult[in][jn+1] = '\0' ;
                for( ; ; kn++){
                    if(tagStr[kn]==','||tagStr[kn]==']')
                        break ;
                }
                break ;
            }
        }
        //printf("String3:%c\n",tagStr[kn]) ;
        if(tagStr[kn]==']') break ;
    }

    return stringResult ;
}


char* getTagString(char tagStr[1000])
{
    int in ;
    char stringResult[1000] ;
    for(in=0 ; in<strlen(tagStr) ; in++)
    {
        if(tagStr[in]=='>')
        {
            int jn ;
            for(jn=0 ; in+1+jn<strlen(tagStr) ; jn++)
            {
                if(tagStr[in+1+jn]=='<')
                {
                    //printf("String:%c\n",tagStr[in+1+jn]) ;
                    stringResult[jn] = '\0' ;
                    return stringResult ;
                }
                stringResult[jn] = tagStr[in+1+jn] ;
            }
        }
    }
}

char** getAllTagString(char tagStr[1000])
{
    //char * sub_str = malloc(10 * sizeof(char*));
    char ** stringResult = malloc(100 * sizeof(char*));
    int i ;
    for (i =0 ; i < 100; ++i){
        stringResult[i] = malloc(1000 * sizeof(char));
    }

    //char stringResult[100][1000] ;
    int in , kn=0 ,localFlag = 0 ;
    for(in=0 ;  ; in++)
    {
        int jn ;
        localFlag = 0 ;
        for(jn=0 ; ; jn++)
        {
            kn++ ;
            if(tagStr[kn]=='>')
            {
                kn++ ;
                int mn ;
                for(mn=0 ;  ; mn++)
                {
                    if(tagStr[kn]=='<')
                    {
                        //printf("String:%c\n",tagStr[in+1+jn]) ;
                        stringResult[in][mn] = '\0' ;

                        for( ; ; kn++)
                        {
                            if(tagStr[kn]==','||tagStr[kn]==']')
                            break ;
                        }
                        localFlag = 1 ;
                        break ;

                    }
                    stringResult[in][mn] = tagStr[kn] ;
                    kn++ ;
                }
            }
            if(localFlag==1) break ;
        }
        //printf("String3:%c\n",tagStr[kn]) ;
        if(tagStr[kn]==']') break ;
    }

    return stringResult ;
}

char* getTagContents(char tagStr[1000])
{
    int in ,countFlag=1;
    char stringResult[1000] ;
    for(in=0 ; in<strlen(tagStr) ; in++)
    {
        if(tagStr[in]=='>')
        {
            int jn ;
            for(jn=0 ; in+1+jn<strlen(tagStr) ; jn++)
            {
                if(tagStr[in+1+jn]=='<' && tagStr[in+2+jn]=='/')
                {
                    countFlag-- ;
                }

                else if(tagStr[in+1+jn]=='<')
                {
                    countFlag++ ;
                }

                if(tagStr[in+1+jn]=='<' && countFlag==0 )
                {
                    //printf("Stringssssssssssssssssssss:%s\t%d\n",stringResult,countFlag) ;
                    stringResult[jn] = '\0' ;
                    return stringResult ;
                }
                stringResult[jn] = tagStr[in+1+jn] ;
            }
        }
    }

}

int sizeOfTagList(char tagStr[1000]){
    int in ,count = 0 ;
    for(in=0 ; in<strlen(tagStr) ; in++)
    {
        if(tagStr[in]=='\n' && tagStr[in-1]==',' &&  tagStr[in-2]=='>' )
            count++ ;
    }
    count++ ;
    return count ;
}
