#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist_char"

int main()
{
    LIST* list = createlist();

    append(list, "arab");
    append(list, "ben");
    append(list, "BEN!!!");
    append(list, "arabayı");
    append(list, "çaldı");
    append(list, "BEN!!!");
    append(list, "BEN!!!");
    append(list, "arab");
    append(list, "çaldı");
    append(list, "BEN!!!");
    append(list, "dedim");
    append(list, "AMERİKANO!!!");
    append(list, "ben");
    append(list, "BEN!!!");
    append(list, "?");
    append(list, "BEN!!!");

    printlist(list);
    reverseprintlist(list);

    insert(list, "AMERİKANO!!!",2);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    insert(list, "LIFE IS A TORTURE TO OUR SOULS",-1);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    insert(list, "I WANNA DIE",16);
    printf("INSERT:\n");
    printlist(list);
    reverseprintlist(list);

    nremove(list, -2);
    printf("NREMOVE:\n");
    printlist(list);
    reverseprintlist(list);

    nremove(list, 3);
    printf("NREMOVE:\n");
    printlist(list);
    reverseprintlist(list);

    removefirst(list, "AMERİKANO!!!");
    printf("REMOVEFIRST:\n");
    printlist(list);
    reverseprintlist(list);

    removelast(list, "ben");
    printf("REMOVELAST:\n");
    printlist(list);
    reverseprintlist(list);

    removeall(list,"BEN!!!");
    printf("REMOVEALL:\n");
    printlist(list);
    reverseprintlist(list);

    invertarray(list);
    printf("INVERTARRAY:\n");
    printlist(list);
    reverseprintlist(list);

    printf("MIN: %s\n",min(list));
    printf("MAX: %s\n",max(list));
    printf("POP: %s\n",pop(list,-1));
    printlist(list);
    reverseprintlist(list);
    
    removelist(list);
    printf("REMOVELIST:\n");
    printlist(list);
    reverseprintlist(list);
    
    printf("%d\n",list->len);
    
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
    listend->data=NULL;
    listend->pre=liststart;
    liststart->pre=NULL;
    liststart->data=NULL;

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
            printf("%s ", current->data);
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
        for(int i=0; i<-length; i++)
        {
            current = current->pre;
            printf("%s ", current->data);
        }
        printf("\n");
    }
}

void append(LIST* list, char* data )
{
    if (list!=NULL)
    {
    	NODE* newnode = (NODE*)malloc(sizeof(NODE));
    	newnode->data=(char*)malloc((strlen(data)+1)*sizeof(char));
    	strcpy(newnode->data,data);
		
		printf("%s\n",newnode->data);
		
	    list->tail->pre->next=newnode;
    	newnode->pre=list->tail->pre;
	    newnode->next=list->tail;
    	list->tail->pre=newnode;

    	list->len++;
   	}
}


void insert(LIST* list, char* data,int index)
{
    if (list!=NULL)
    {
        int length=list->len;
        NODE* current;
        NODE* newnode = (NODE*)malloc(sizeof(NODE));
        newnode->data=(char*)malloc((strlen(data)+1)*sizeof(char));
        strcpy(newnode->data,data);

		printf("%s\n",newnode->data);

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
     	free(current->data);
     	free(current);
        list->len--;
    }
}

void removefirst(LIST* list, char* data)
{
    if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->head->next;
        for(int index=0; index<length; index++)
        {
            if (strcmp(current->data,data)==0)
            {
                current->pre->next=current->next;
                current->next->pre=current->pre;
                free(current->data);
                free(current);
                list->len--;
                break;
            }
            current = current->next;
        }
    }
}

void removelast(LIST* list, char* data)
{
    if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->tail->pre;
        for(int index=0; index<length; index++)
        {
            if (strcmp(current->data,data)==0)
            {
                current->pre->next=current->next;
                current->next->pre=current->pre;
                free(current->data);
                free(current);
                list->len--;
                break;
            }
            current = current->pre;
        }
    }
}

void removeall(LIST* list, char* data)
{
    if (list!=NULL && list->len!=0)
    {
        int length=list->len;
        NODE* current=list->head->next;
        NODE* currentfree;
        for(int index=0; index<length; index++)
        {
            if (strcmp(current->data,data)==0)
            {

                current->pre->next=current->next;
                current->next->pre=current->pre;
                currentfree=current;
                current = current->pre;
                free(currentfree->data);
                free(currentfree);

                list->len--;
            }
            current = current->next;
        }
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

void swap(char** a,char** b)
{
    char* temp=*a;
    *a=*b;
    *b=temp;
}

char* min(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        char* minimum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            char* data=current->data;
            if(strcmp(data,minimum)<0) minimum=data;
        }
        return minimum;
    }
    return NULL;
}

char* max(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        char* maximum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            char* data=current->data;
            if(strcmp(data,maximum)>0) maximum=data;
        }
        return maximum;
    }
    return NULL;
}

char* pop(LIST* list,int index)
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
        char* popdata=current->data;
        free(current);
        list->len--;
        return popdata;
    }
    return NULL;
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
            free(currentfree->data);
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
			list->head->next=NULL;
			list->tail->pre=NULL;
			free(list->head);
			free(list->tail);
			free(list);
		}
}
