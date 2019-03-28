#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"

void createTreeControl(struct Node *root,struct Node *current){

    FILE *ioFile ;
    if ((ioFile = fopen("ict4.html","r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }

    char str[100] ;
    char ch,flag='0' ;
    int s1 = 0 ;

        fscanf(ioFile,"%c",&ch) ; //read '<' from html page

        while(ch!='>'){           //read first tag from html page
            str[s1] = ch ;
            s1++ ;
            fscanf(ioFile,"%c",&ch) ;
        }

        str[s1] = ch ;
        str[s1+1] = '\0' ;
        //printf("tag1: %s\n",str) ;
        operation(root,current,str) ;

        char endstring[] ="<1html>" ;


        while(strcmp(endstring ,"</html>")){
            if(flag == '0'){
                fscanf(ioFile,"%c",&ch) ; // read a character...if character is '<' then it is symbol of starting a tag...else it it is symbol of starting a string element
                if(ch=='>'){
                    fscanf(ioFile,"%c",&ch) ;
                }
                if(ch=='\n' || ch ==' ' || ch == '\t') continue ;

            }
            else ch = flag ;

            int k ;
            for(k=strlen(str)-1 ; k >= 0 ; k--){
                    str[k] = '\0' ;
            }

            if(ch=='<'){
                fscanf(ioFile,"%[^>]s",&str) ;  //read a full tag

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
                fscanf(ioFile,"%[^<]s",&str) ; //read a full  string element
                char c = '~';
                int i ;
                for(i=strlen(str)+1 ; i > 1 ; i--){
                    str[i] = str[i-2] ;
                }
                str[1] = ch ;
                str[0] = c ;
                flag = '<' ;
                str[strlen(str)+1] = '\0';

            }

            char s[100] ;
            int flagForTag = 0 , flagForTag2 = 0;
            int i ,s2=0;
            for(i = 0 ; i<strlen(str)-1 && flag=='0' ; i++ ){ //find attribute from a tag

                s[s2]=str[i] ;
                s2++ ;
                s[s2]='\0' ;
                if(str[i]==' ' || str[i+1]=='>')
                {
                    if(flagForTag == 0){
                        if(s[s2-1]==' '){
                            s[s2-1] = '>'  ;
                        }
                        else {
                                s[s2] = '>' ;
                        }

                        flagForTag = 1 ;
                        for(k=0 ; k <7 ; k++){
                            endstring[k] = s[k] ;
                        }
                        //printf("tag3 : %s\t%s\n",s , endstring) ;
                        operation(root,current,s) ;
                        memset(s, 0, sizeof(s));
                        s2= 0 ;
                    }

                    else {
                            char c1 = '!';
                            int k ;
                            for(k=strlen(s) ; k > 0 ; k--){
                                str[k] = s[k-1] ;
                            }
                            str[0] = c1 ;

                            //printf("tag2 : %s\n",s) ;
                            operation(root,current,s) ;
                        memset(s, 0, sizeof(s));
                        s2 = 0 ;
                    }
                }
            }

            if(flag == '<'){
                //printf("tag1 :  %s\n",str) ;
                operation(root,current,str) ;
            }
    }
}




