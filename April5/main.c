#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main()
{
    struct Node *root = htmlPerser() ;
    char *sujon = findAll(root,"[<font>,<br>,<img>]") ;
    printf("%s\n",sujon) ;
    return 0 ;
}

