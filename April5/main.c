#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Node *root = htmlPerser() ;
    char *sujon = findAll(root,"<font>,color=Red") ;
    printf("%s",sujon) ;
    return 0 ;
}

