#ifndef linkedlist_int
#define linkedlist_int

typedef struct node
{
    int data;
    struct node* next;
    struct node* pre;
} NODE;

typedef struct list
{
    int len;
    struct node* head;
    struct node* tail;
} LIST;

void insert(LIST* list, int data,int index);
void append(LIST* list, int data );
LIST* createlist();
void nremove(LIST* list, int index);
void printlist(LIST* list);
void reverseprintlist(LIST* list);
void removefirst(LIST* list, int data);
void removelast(LIST* list, int data);
void removeall(LIST* list, int data);
void swap(int *a,int *b);
void invertarray(LIST* list);
int pop(LIST* list,int index);
int max(LIST* list);
int min(LIST* list);
void removelist(LIST* list);
void freelist(LIST* list);

#endif
