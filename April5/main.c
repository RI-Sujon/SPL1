#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Node *root = htmlPerser() ;
    menu(root) ;

    return 0 ;
}
