#ifndef linkedlist_char
#define linkedlist_char

typedef struct node
{
    char* data;
    struct node* next;
    struct node* pre;
} NODE;

typedef struct list
{
    int len;
    struct node* head;
    struct node* tail;
} LIST;

void insert(LIST* list, char* data,int index);
void append(LIST* list, char* data );
LIST* createlist();
void nremove(LIST* list, int index);
void printlist(LIST* list);
void reverseprintlist(LIST* list);
void removefirst(LIST* list, char* data);
void removelast(LIST* list, char* data);
void removeall(LIST* list, char* data);
void swap(char** a,char** b);
void invertarray(LIST* list);
char* pop(LIST* list,int index);
char* max(LIST* list);
char* min(LIST* list);
void freelist(LIST* list);
void removelist(LIST* list);

#endif
