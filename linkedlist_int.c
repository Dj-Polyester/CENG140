#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "linkedlist_int"

int main()
{
    LIST* list = createlist(); 

    append(list, 1);
    append(list, 5);
    append(list, 2);
    append(list, 12);
    append(list, 19);
    append(list, 19);
    append(list, 7);
    append(list, 19);
    append(list, 1);
    
    printlist(list);
    reverseprintlist(list);

    insert(list, 8,2);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    insert(list, 3,-1);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    insert(list, 3,16);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    nremove(list, -3);
    printf("NREMOVE:\n");
    printlist(list);
    reverseprintlist(list);

    nremove(list, 1);
    printf("NREMOVE:\n");
    printlist(list);
    reverseprintlist(list);

    removelast(list, 19);
    printf("REMOVELAST:\n");
    printlist(list);
    reverseprintlist(list);

    removelast(list, 19);
    printf("REMOVELAST:\n");
    printlist(list);
    reverseprintlist(list);

    removeall(list,3);
    printf("REMOVEALL:\n");
    printlist(list);
    reverseprintlist(list);

    invertarray(list);
    printf("INVERTARRAY:\n");
    printlist(list);
    reverseprintlist(list);

    printf("MIN: %d\n",min(list));
    printf("MAX: %d\n",max(list));
    printf("POP: %d\n",pop(list,-1));
    printlist(list);
    reverseprintlist(list);
    
    removelist(list);
    printf("REMOVELIST:\n");
    printlist(list);
    reverseprintlist(list);
    
    freelist(list);
    printf("FREELIST:\n");
    printlist(list);
    reverseprintlist(list);
    
    return 0;
}

LIST* createlist()
{

    NODE* liststart = (NODE*)malloc(sizeof(NODE));
    NODE* listend = (NODE*)malloc(sizeof(NODE));

    LIST* list = (LIST*)malloc(sizeof(LIST));

    liststart->next=listend;
    listend->next=NULL;
    listend->pre=liststart;
    liststart->pre=NULL;

    list->head=liststart;
    list->tail=listend;
    list->len=0;
    return list;
}

void printlist(LIST* list)
{
    if (list!=NULL)
    {
        NODE* current =list->head;
		int length=list->len;
        for(int i=0; i<length; i++)
        {
            current = current->next;
            printf("%d ", current->data);
        }
        printf("\n");
    }
}

void reverseprintlist(LIST* list)
{
    if (list!=NULL)
    {
        NODE* current =list->tail;
		int length=list->len;
        // list traversal
        for(int i=0; i<length; i++)
        {
            current = current->pre;
            printf("%d ", current->data);
        }
        printf("\n");
    }
}

void append(LIST* list, int data )
{
    if (list!=NULL)
    {
    	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	    newnode->data=data;

    	list->tail->pre->next=newnode;
	    newnode->pre=list->tail->pre;
    	newnode->next=list->tail;
	    list->tail->pre=newnode;

    	list->len++;
    }
}


void insert(LIST* list, int data,int index)
{
    if (list!=NULL)
    {
        int length=list->len;
        NODE* current;
        NODE* newnode = (NODE*)malloc(sizeof(NODE));
        newnode->data=data;

        //index negative
        if (index<0)
            index+=length+1;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            current = list->head;
            for(int i=0; i<=index; i++)
            {
                current=current->next;
            }
        }
        //close to tail
        else
        {
            current = list->tail;
            for(int i=0; i<length-index; i++)
            {
                current=current->pre;
            }
        }
        newnode->next=current;
        newnode->pre=current->pre;
        current->pre->next=newnode;
        current->pre=newnode;

        list->len++;
    }

}

void removefirst(LIST* list, int data)
{
    if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->head->next;
        for(int index=0; index<length; index++)
        {
            if (current->data==data)
            {
                current->pre->next=current->next;
                current->next->pre=current->pre;
                free(current);
                list->len--;
                break;
            }
            current = current->next;
        }
    }
}

void removelast(LIST* list, int data)
{
    if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->tail->pre;
        for(int index=0; index<length; index++)
        {
            if (current->data==data)
            {
                current->pre->next=current->next;
                current->next->pre=current->pre;
                free(current);
                list->len--;
                break;
            }
            current = current->pre;
        }
    }
}

void removeall(LIST* list, int data)
{
    if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->head->next;
        NODE* currentfree;
        for(int index=0; index<length; index++)
        {
            if (current->data==data)
            {

                current->pre->next=current->next;
                current->next->pre=current->pre;
                currentfree=current;
                current = current->pre;
                free(currentfree);

                list->len--;
            }
            current = current->next;
        }
    }
}

void nremove(LIST* list, int index)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current;
        int length=list->len;

        //index negative
        if (index<0)
            index+=length;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            current = list->head;

            for(int i=0; i<=index; i++)
                current=current->next;
        }
        //close to tail
        else
        {
            current = list->tail;

            for(int i=0; i<length-index; i++)
                current=current->pre;

        }
        current->pre->next=current->next;
        current->next->pre=current->pre;
        free(current);
        list->len--;
    }
}

void invertarray(LIST* list)
{
    if (list!=NULL)
    {
        NODE* currentnext=list->head->next;
        NODE* currentpre=list->tail->pre;
        for(int i=0;i<list->len/2;i++)
        {
            swap(&currentnext->data,&currentpre->data);
            currentnext=currentnext->next;
            currentpre=currentpre->pre;
        }
    }
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int min(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        int minimum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            int data=current->data;
            if(data<minimum) minimum=data;
        }
        return minimum;
    }
    return INT_MAX;
}

int max(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        int maximum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            int data=current->data;
            if(data>maximum) maximum=data;
        }
        return maximum;
    }
    return INT_MIN;
}

int pop(LIST* list,int index)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current;
        int length=list->len;

        //index negative
        if (index<0)
            index+=length;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            current = list->head;

            for(int i=0; i<=index; i++)
                current=current->next;
        }
        //close to tail
        else
        {
            current = list->tail;

            for(int i=0; i<length-index; i++)
                current=current->pre;

        }
        current->pre->next=current->next;
        current->next->pre=current->pre;
        int popdata=current->data;
        free(current);
        list->len--;
        return popdata;
    }
    return 0;
}

void removelist(LIST* list)
{
	if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->head->next;
        NODE* currentfree;
        for(int index=0; index<length; index++)
        {
            current->pre->next=current->next;
            current->next->pre=current->pre;
            currentfree=current;
            current = current->pre;
            free(currentfree);

            list->len--;
            
            current = current->next;
        }
    }
	
       
}

void freelist(LIST* list)
{
	if (list!=NULL)
		{
			free(list->head);
			free(list->tail);
			free(list);
		}
}
