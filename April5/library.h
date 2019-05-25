struct Node
{
    char *tag ;
    struct Node *parent,*children[1000] ;
};

struct Node* htmlPerser() ;

char* findAll(struct Node *current,char *tag) ;
char* find(struct Node *current,char *tag);
char* findParent(struct Node *current,char *fullTagStr,char *tag);
char* findNextSublings(struct Node* current,char *fullTagStr);
char* findPreviousSublings(struct Node* current,char *fullTagStr);


char* getTagName(char tagStr[1000]);
char** getAllTagName(char tagStr[1000]);
char* getTagString(char tagStr[1000]);
char** getAllTagString(char tagStr[1000]);
char* getTagChildren(char tagStr[1000]);
char** getTagContents(char tagStr[1000]);
int sizeOfTagList(char tagStr[1000]);
int sizeOfTagContainsList(char tagStr[1000]) ;
