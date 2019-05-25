#include <stdio.h>

int main()
{
    struct Node *root = htmlPerser() ;
    int i ;

    char *findStr = find(root,"<p>") ;
    printf("find:\n%s\n\n",findStr) ;

    char *findAllStr = findAll(root,"<p>") ;
    printf("findAll:\n%s\n\n",findAllStr) ;

    char *findPrnt = findParent(root,findStr,"<body>");
    printf("findParent:\n%s\n\n",findPrnt) ;

    char *findPrSub = findPreviousSublings(root,findStr);
    printf("findPreviousSublings:\n%s\n\n",findPrSub) ;

    char *findNxtSub = findNextSublings(root,findStr);
    printf("findNextSublings:\n%s\n\n",findNxtSub) ;

    char *tag = getTagName(findStr) ;
    printf("getTagName:\n%s\n\n",tag) ;


    char **tagAll = getAllTagName(findAllStr) ;

    printf("getAllTagName:\n") ;
    for(i=0 ; i<sizeOfTagList(findAllStr) ;i++){
       printf("%s\t",tagAll[i]) ;
    }

    char *tagStr = getTagString(findStr) ;
    printf("\n\ngetTagString:\n%s\n\n",tagStr) ;


    char **tagAllStr = getAllTagString(findAllStr) ;
    printf("getAllTagString:%s\n",findAllStr) ;
    for(i=0 ; i<sizeOfTagList(findAllStr) ;i++){
       printf("%s\t",tagAllStr[i]) ;
    }

    char *tagChildren = getTagChildren(findStr) ;
    printf("\n\ngetTagChildren:%s\n",tagChildren) ;

    char **tagContents = getTagContents(findStr) ;
    printf("getTagContents:\n") ;
    for(i=0 ; i<sizeOfTagContainsList(findAllStr) ;i++){
        printf("%s\n",tagContents[i]) ;
    }

    return 0 ;
}

