#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Node *root = htmlPerser() ;

    char *sujon = find(root,"<h1>") ;
    printf("FullTag:%s\n",sujon) ;

    char *tag = getTagName(sujon) ;
    printf("tag Name:%s\n",tag) ;

    char *contents = getTagContents(sujon) ;
    printf("tag Contents:%s\n",contents) ;

    char *cont = getTagContents(contents) ;
    printf("tag Contents:%s\n",cont) ;



    /*char **tag = getAllTagName(sujon) ;

    int i ;
    for(i=0 ; i<sizeOfTagList(sujon) ;i++){
        printf("Tag:%s\n",tag[i]) ;
    }

    char **str = getAllTagString(sujon) ;

    for(i=0 ; i<sizeOfTagList(sujon) ;i++){
        printf("str:%s\n",str[i]) ;
    }*/

    return 0 ;
}

