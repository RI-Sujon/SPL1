#include<stdlib.h>
#include "library.h"

char* getTagName(char tagStr[1000])
{
    int in ;
    char *stringResult = (char*) malloc(1000);
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
    char *stringResult=(char*) malloc(100 + 1 ) ;
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

char* getTagChildren(char tagStr[1000])
{
    int in ,countFlag=1;
    char *stringResult=(char*) malloc(1000 );
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
                //printf("Stringsssssss:%s\t%d\n",stringResult,countFlag) ;

                if(tagStr[in+1+jn]=='<' && countFlag==1 )
                {
                    //printf("Stringsssssss:%s\t%d\n",stringResult,countFlag) ;
                    int mn ;
                    for(mn=0 ; tagStr[in+1+jn+mn]!='>' ;mn++ )
                    {
                        stringResult[jn+mn] = tagStr[in+1+jn+mn] ;
                    }
                    stringResult[jn+mn] = tagStr[in+1+jn+mn] ;
                    stringResult[jn+mn+1] = '\0' ;
                    return stringResult ;
                }

                else if(tagStr[in+1+jn]=='<' && countFlag==2 && tagStr[in+1+jn-1]!='>' && tagStr[in+1+jn+1]!='/' )
                {
                    stringResult[jn] = '\0' ;
                    return stringResult ;
                }
                stringResult[jn] = tagStr[in+1+jn] ;
            }
        }
    }

}


char** getTagContents(char tagStr[1000])
{
    char** stringResult = malloc(100 * sizeof(char*));
    int i , kn=0 , flagForNextContents = 0 ,localflag = 0 ;
    for (i =0 ; i < 100; ++i)
    {
        stringResult[i] = malloc(1000 * sizeof(char));
    }

    int flagForStringChildren = 0 ;

    int pn ;
    for(pn = 0 ;kn < strlen(tagStr) ; pn++)
    {
        int in ,countFlag=1;
        for(in=0 ; kn<strlen(tagStr) ; in++)
        {
            kn++ ;
            localflag = 0 ;
            if(tagStr[kn]=='>' || flagForNextContents == 1)
            {
                int jn ;
                for(jn=0 ; kn<strlen(tagStr) ; jn++)
                {
                    kn++ ;
                    if(tagStr[kn]=='<' && tagStr[kn+1]=='/')
                    {
                        countFlag-- ;
                    }

                    else if(tagStr[kn]=='<')
                    {
                        countFlag++ ;
                    }

                    if(tagStr[kn]=='<' && countFlag==0 && tagStr[kn-1]!='>' && tagStr[kn+1]=='/' && flagForStringChildren==0 )
                    {
                        stringResult[pn][jn] = '\0' ;
                        kn = kn - 2  ;
                        flagForNextContents = 1 ;
                        flagForStringChildren = 1 ;
                        localflag = 1 ;
                        countFlag = 1 ;
                        //printf("StringsssssssNew:%s\n",stringResult[pn]) ;
                        break ;
                    }

                    else if(tagStr[kn]=='<' && countFlag==0 )
                    {
                        localflag = 1 ;
                        //printf("Stringsssssss:%s\n",stringResult[pn]) ;
                        break ;
                    }

                    else if(tagStr[kn]=='<' && countFlag==1 )
                    {
                        int mn ;
                        for(mn=0 ; tagStr[kn]!='>' ;mn++ )
                        {
                            stringResult[pn][jn+mn] = tagStr[kn] ;
                            kn++ ;
                        }
                        stringResult[pn][jn+mn] = tagStr[kn] ;
                        stringResult[pn][jn+mn+1] = '\0' ;
                        kn-- ;
                        flagForStringChildren = 0 ;
                        flagForNextContents = 1 ;
                        localflag = 1 ;
                        //printf("Stringsssssss:%s\n",stringResult[pn]) ;
                        break ;
                    }

                    else if(tagStr[kn]=='<' && countFlag==2 && tagStr[kn-1]!='>' && tagStr[kn+1]!='/' && flagForStringChildren==0 )
                    {
                        stringResult[pn][jn] = '\0' ;
                        kn = kn - 2  ;
                        flagForNextContents = 1 ;
                        flagForStringChildren = 1 ;
                        localflag = 1 ;
                        countFlag = 1 ;
                        //printf("StringsssssssNew:%s\n",stringResult[pn]) ;
                        break ;
                    }
                    stringResult[pn][jn] = tagStr[kn] ;
                }
            }
            if(localflag==1) break ;
        }
        if(localflag==2) break ;
    }

    return stringResult ;
}


int numberOfChildren(char tagStr[1000])
{
    int i , kn=0 , flagForNextContents = 0 ,localflag = 0 ;
    int count = 0 ;
    int flagForStringChildren = 0 ;
    int pn ;

    for(pn = 0 ;kn < strlen(tagStr) ; pn++)
    {
        int in ,countFlag=1;
        for(in=0 ; kn<strlen(tagStr) ; in++)
        {
            kn++ ;
            localflag = 0 ;
            if(tagStr[kn]=='>' || flagForNextContents == 1)
            {
                int jn ;
                for(jn=0 ; kn<strlen(tagStr) ; jn++)
                {
                    kn++ ;
                    if(tagStr[kn]=='<' && tagStr[kn+1]=='/')
                    {
                        countFlag-- ;
                    }

                    else if(tagStr[kn]=='<')
                    {
                        countFlag++ ;
                    }

                    if(tagStr[kn]=='<' && countFlag==0 && tagStr[kn-1]!='>' && tagStr[kn+1]=='/' && flagForStringChildren==0 )
                    {
                        count++ ;
                        kn = kn - 2  ;
                        flagForNextContents = 1 ;
                        flagForStringChildren = 1 ;
                        localflag = 1 ;
                        break ;
                    }

                    else if(tagStr[kn]=='<' && countFlag==0 )
                    {
                        localflag = 1 ;
                        break ;
                    }

                    else if(tagStr[kn]=='<' && countFlag==1 )
                    {
                        count++ ;
                        kn-- ;
                        flagForStringChildren = 0 ;
                        flagForNextContents = 1 ;
                        localflag = 1 ;
                        break ;
                    }

                    else if(tagStr[kn]=='<' && countFlag==2 && tagStr[kn-1]!='>' && tagStr[kn+1]!='/' && flagForStringChildren==0 )
                    {
                        count++ ;
                        kn = kn - 2  ;
                        flagForNextContents = 1 ;
                        flagForStringChildren = 1 ;
                        localflag = 1 ;
                        countFlag = 1 ;
                        break ;
                    }
                }
            }
            if(localflag==1) break ;
        }
        if(localflag==2) break ;
    }

    return count ;
}


int numberOfTag(char tagStr[1000]){
    int in ,count = 0 ;
    for(in=0 ; in<strlen(tagStr) ; in++)
    {
        if(tagStr[in]=='\n' && tagStr[in-1]==',' &&  tagStr[in-2]=='>' )
            count++ ;
    }
    count++ ;
    return count ;
}
