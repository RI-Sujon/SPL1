#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Node *root = htmlPerser() ;;
    char *sujon = findAll(root,"<font>,face=Calibri") ;
    printf("%s ghjgj\n",sujon) ;
    return 0 ;
}

