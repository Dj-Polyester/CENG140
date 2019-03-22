#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "linkedlist_cha.h"

int main()
{
    LIST* list = createlist(); 

    append(list, 'q');
    append(list, 'r');
    append(list, 'p');
    append(list, 's');
    append(list, 's');
    append(list, 'r');
    append(list, 'r');
    append(list, 'U');
    append(list, 'G');
    append(list, 'u');
    append(list, 'R');
    append(list, 'r');    
    printlist(list);
    reverseprintlist(list);

    insert(list, 'a',2);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    insert(list, 'z',-1);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    insert(list, 'X',16);
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

    removelast(list, 'U');
    printf("REMOVELAST:\n");
    printlist(list);
    reverseprintlist(list);

    removelast(list, 'q');
    printf("REMOVELAST:\n");
    printlist(list);
    reverseprintlist(list);

    removeall(list,'r');
    printf("REMOVEALL:\n");
    printlist(list);
    reverseprintlist(list);

    invertarray(list);
    printf("INVERTARRAY:\n");
    printlist(list);
    reverseprintlist(list);

    printf("MIN: %c\n",min(list));
    printf("MAX: %c\n",max(list));
    printf("POP: %c\n",pop(list,-1));
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
            printf("%c ", current->data);
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
            printf("%c ", current->data);
        }
        printf("\n");
    }
}

void append(LIST* list, char data )
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


void insert(LIST* list, char data,int index)
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

void removefirst(LIST* list, char data)
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

void removelast(LIST* list, char data)
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

void removeall(LIST* list, char data)
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

void swap(char *a,char *b)
{
    char temp=*a;
    *a=*b;
    *b=temp;
}

char min(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        char minimum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            char data=current->data;
            if(data<minimum) minimum=data;
        }
        return minimum;
    }
    return '\0';
}

char max(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        char maximum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            char data=current->data;
            if(data>maximum) maximum=data;
        }
        return maximum;
    }
    return '\0';
}

char pop(LIST* list,int index)
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
        char popdata=current->data;
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
