#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Node *root = htmlPerser() ;
    char *sujon = findAll(root,"href=true") ;
    printf("%s",sujon) ;
    return 0 ;
}

