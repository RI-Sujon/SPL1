struct Node{
    char *tag ;
    struct Node *parent,*children[10] ;
};

struct Node* htmlPerser() ;

char* findAll(struct Node *current,char *tag) ;

