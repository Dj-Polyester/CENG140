#include <stdio.h>



typedef struct node
{
    int data;
    int len;
    struct node* next;
} NODE;


void insert(NODE* list, int data,int index);
void append(NODE* list, int data );
NODE* createlist();
void nremove(NODE* list, int index);
void printlist(NODE* list);
void removedata(NODE* list, int data);

int main()
{
    NODE* list = createlist(); // bos bir liste yaratildi

    append(list, 5);
    append(list, 2);
    append(list, 12);

    insert(list, 3,1);
    printlist(list);

    nremove(list, 2);
    printlist(list);

    nremove(list, 1);
    printlist(list);

    //buraya kadar düzgün gidiyor
    //[5,12]

    removedata(list, 1);//passing argument 1 of “remove” from incompatible pointer type
    printlist(list);

    removedata(list, 12);
    printlist(list);

    getch();
}

NODE* createlist()
{


        NODE* liststart = (NODE*)malloc(sizeof(NODE));
        NODE* listend = (NODE*)malloc(sizeof(NODE));

        liststart->len=0;
        liststart->next=listend;
        listend->next=NULL;

        return liststart;


}

void printlist(NODE* list)
{
    if (list!=NULL)
    {
        NODE* current =list->next;

        // list traversal
        for(int i=0; i<list->len; i++)
        {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void append(NODE* list, int data )
{
    // yeni eleman listenin sonuna eklenir

    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    NODE* currentpre =list;
    NODE* currentnext =list->next;
    newnode->data=data;

    for(int i=0; i<list->len; i++)
    {
        currentpre = currentpre->next;
        currentnext = currentnext->next;
    }
    currentpre->next=newnode;
    newnode->next=currentnext;
    list->len++;
}


void insert(NODE* list, int data,int index)
{
    if (list!=NULL)
    {
        NODE* newnode = (NODE*)malloc(sizeof(NODE));

        {
            NODE* currentpre=list;
            NODE* currentnext=list->next;
            newnode->data=data;

            if (index<0)
                index=index+list->len;

            if(list->len-1 < index)
                index=list->len;

            //printf("cP before: %d\n",currentpre->data);
            //printf("cN before: %d\n",currentnext->data);
            for(int i=0; i<index; i++)
            {
                currentpre = currentpre->next;
                currentnext = currentnext->next;
            }
            //printf("cP after: %d\n",currentpre->data);
            //printf("cN after: %d",currentnext->data);
            currentpre->next=newnode;
            newnode->next=currentnext;
        }
        list->len++;
    }

}

void removedata(NODE* list, int data)
{
    if (list!=NULL)
    {
        NODE* finder=list->next;
        for(int i=0; i<list->len; i++)
        {
            if (finder->data==data)
            {
                nremove(list, i);
                break;
            }
            finder = finder->next;
        }
    }
}

void nremove(NODE* list, int index)
{
    if (list!=NULL)
    {
        NODE* currentpre=list;
        NODE* currentnext=list->next;

        if (index<0)
            index=index+list->len;

        if(list->len-1 < index)
            index=list->len;

        for(int i=0; i<index; i++)
        {
            currentpre = currentpre->next;
            currentnext = currentnext->next;
        }
        if (list->len>0)
        {
            //!!!
            currentpre->next=currentnext->next;
            free(currentnext);
            list->len--;
        }
    }
}

