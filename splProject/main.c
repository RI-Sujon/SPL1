#include <stdio.h>
#include <stdlib.h>
#include "library.h"

struct Node *root , *current;

void createLinkList(){
    root = NULL ;
    current = NULL ;
}

int main(){
    createLinkList(root,current) ;
    createTreeControl(root,current) ;
    outputTreePreOrder(root) ;

    //menu() ;

    return 0 ;

}
