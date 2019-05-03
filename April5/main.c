#include <stdio.h>

int main()
{
    struct Node *root = htmlPerser() ;

    char *sujon = find(root,"<p>") ;
    printf("FullTag:%s\n",sujon) ;

    char *str = findPreviousSublings(root,sujon) ;
    printf("tag Name:%s\n",str) ;

    /*char *tag = getTagName(sujon) ;
    printf("tag Name:%s\n",tag) ;

    char *children = getTagChildren(sujon) ;
    printf("%s tag Contents:%s\n",tag,children) ;

    char **contents = getTagContents(sujon) ;
    int i ;
    for(i=0 ; i<sizeOfTagContainsList(sujon) ;i++){
        printf("Contents:%s\n",contents[i]) ;
    }

    char **tagList = getAllTagName(sujon) ;


    for(i=0 ; i<sizeOfTagList(sujon) ;i++){
        printf("Tag:%s\n",tagList[i]) ;
    }

    char **str = getAllTagString(sujon) ;

    for(i=0 ; i<sizeOfTagList(sujon) ;i++){
        printf("str:%s\n",str[i]) ;
    }*/

    return 0 ;
}

