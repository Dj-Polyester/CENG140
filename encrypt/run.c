//
// Created by yusufc on 23.04.2019.
//

#include <stdio.h>
#include "exam_3_0.h"
#include <string.h>
#include <stdlib.h>


void printchars(char* str)
{
	int i=0;
	
	while(str[i])
	{
		if(str[i]!=' ' || str[i]!='.' ) printf("%c",str[i]);
		++i;
	}
	printf("\n");
}

int main() {

	char **messages;
	char** encrypted_messages;
	int n_messages=3,grouping=4,a=3; 
	char *salt;
	void* shift=&a;
	
	salt=calloc(5,sizeof(char));
	strcpy(salt,"ceng");
	messages=malloc(sizeof(char*)*n_messages);
	
	messages[0]=calloc(13,sizeof(char));
	strcpy(messages[0],"I have a pen");
	messages[1]=calloc(16,sizeof(char));
	strcpy(messages[1],"I have an apple");
	messages[2]=calloc(14,sizeof(char));
	strcpy(messages[2],"Uhh apple pen");
	
	/*printchars(plain_text);*/
	printchars(messages[0]);
	printchars(messages[1]);
	printchars(messages[2]);
	
	encrypted_messages=mycipher_encrypt(messages, n_messages, grouping, salt, polyalphabetic_encrypt, shift);

	printchars(encrypted_messages[0]);
	printchars(encrypted_messages[1]);
	printchars(encrypted_messages[2]);
	
	free(messages[0]);
	free(messages[1]);
	free(messages[2]);
	free(messages);
	
	free(encrypted_messages[0]);
	free(encrypted_messages[1]);
	free(encrypted_messages[2]);
	free(encrypted_messages);
	
	return 0;
}

char **mycipher_encrypt(char **messages, int n_messages, int grouping, char *salt, char *(*cipher_method)(char *, void *),  void* shift)
{
	char** encrypted_messages;
	int i;
	
	encrypted_messages=combine_strings(messages, n_messages, grouping, salt);
	
	if(cipher_method==caesar_encrypt)
	{
		for(i=0;i<n_messages;++i)
		{
			encrypted_messages[i]=caesar_encrypt(encrypted_messages[i], shift);
		}
	}
	
	
	if(cipher_method==polyalphabetic_encrypt)
	{
		for(i=0;i<n_messages;++i)
		{
			encrypted_messages[i]=polyalphabetic_encrypt(encrypted_messages[i], salt);
		}
	}
	
	return encrypted_messages;
}             

char **combine_strings(char **messages, int n_messages, int grouping, char *salt)
{
	int i,j,k=0,len_max=0,length,padding_max;
	char** encrypted_messages,**encrypted_messages2;
	
	for(i=0;i<n_messages;++i)
	{
		if(!messages[i]) return NULL;
		length=get_string_length(messages[i]);
		if(len_max<length) len_max=length;
	}
	padding_max=n_messages*grouping*(len_max/(n_messages*grouping)+1);
	
	/*form encrypted_messages*/
	encrypted_messages=(char**)malloc(n_messages*sizeof(char*));
	for(i=0;i<n_messages;++i)
	{
		encrypted_messages[i]=calloc(padding_max+1,sizeof(char));
		length=get_string_length(messages[i]);
		for(j=0;j<length;j++)
		{
			encrypted_messages[i][j]=messages[i][j];
		}
		k=0;
		while(j<padding_max)
		{
			encrypted_messages[i][j]=salt[k%4];
			++j;
			++k;
		}
		
	}
	
	/*form encrypted_messages2*/
	encrypted_messages2=(char**)malloc(n_messages*sizeof(char*));
	j=0;
	for(i=0;i<n_messages;++i)
	{
		encrypted_messages2[i]=calloc(padding_max+1,sizeof(char));
		for(k=0;k<padding_max;++k)
		{
			encrypted_messages2[i][k]=encrypted_messages[j][k];
			if(k%grouping==grouping-1) ++j;
			if(j==n_messages) j-=n_messages;
		}
		++j;
	}
	
	/*free 	encrypted_messages*/
	free(encrypted_messages[0]);
	free(encrypted_messages[1]);
	free(encrypted_messages[2]);
	free(encrypted_messages);
	
	return encrypted_messages2;
}

char *caesar_encrypt(char *message_to_encrypt, void *shift)
{
	int length=get_string_length(message_to_encrypt),i;
	char* encrypted_message;
	
	if(!message_to_encrypt) return NULL;
	
	if(!(encrypted_message=calloc(length+1,sizeof(char)))) return NULL;
	
	for(i=0;i<length;++i)
	{
		if(message_to_encrypt[i]==' ' || message_to_encrypt[i]=='.') 
		{
			
			encrypted_message[i]=message_to_encrypt[i];
			continue;
		}
		
		if(message_to_encrypt[i]< 91 && message_to_encrypt[i]>64)
		{
			encrypted_message[i]=64+((message_to_encrypt[i]%64+*((int*)shift))%26);
		}
		
		else if (message_to_encrypt[i]< 123 && message_to_encrypt[i]> 96)
		{
			encrypted_message[i]=96+((message_to_encrypt[i]%96+*((int*)shift))%26);
		}
		
	}
	
	return encrypted_message;

}

char *polyalphabetic_encrypt(char *message_to_encrypt, void *key_string)
{
	
	int length=get_string_length(key_string),addvalue,i,k;
	char* encrypted_message,*key_string2;
	
	if(!message_to_encrypt) return NULL;
	
	if(!(key_string2=calloc(length+1,sizeof(char)))) 
	{
		printf("not allocated");
		return NULL;
	}
	
	for(i=0;i<length;++i)
	{
		key_string2[i]=*((char*)key_string+i);
	}
	//key_string2[length]='\0';/*unnecessary,since given string already contains null*/
	
	
	length=get_string_length(message_to_encrypt);
	if(!(encrypted_message=calloc(length+1,sizeof(char)))) 
	{
		printf("not allocated");
		return NULL;
	}
	
	for(i=0,k=0;i<length;++i)
	{
		
		if(message_to_encrypt[i]==' ' || message_to_encrypt[i]=='.') 
		{
			
			encrypted_message[i]=message_to_encrypt[i];
			continue;
		}
		
		if(message_to_encrypt[i]< 91 && message_to_encrypt[i]>64) addvalue=64;
		else if (message_to_encrypt[i]< 123 && message_to_encrypt[i]> 96) addvalue=96;
		
		encrypted_message[i]=addvalue+((letter_to_shift(message_to_encrypt[i])+letter_to_shift(key_string2[k%4]))%26);
		++k;
	}
	//encrypted_message[length]='\0';/*unnecessary,since given string already contains null*/
	if(!key_string2) free(key_string2);
	return encrypted_message;
}











