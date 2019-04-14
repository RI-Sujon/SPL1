#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Node *root = htmlPerser() ;
    char *sujon = find(root,"[<h1>,<font>]") ;
    printf("%s",sujon) ;
    return 0 ;
}

