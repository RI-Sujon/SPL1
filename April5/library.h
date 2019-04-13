struct Node{
    char *tag ;
    struct Node *parent,*children[1000] ;
};

struct Node* htmlPerser() ;

char* findAll(struct Node *current,char *tag) ;
