/*

THINGS TO CONSIDER:
How do I find the right instructions with looping?
	How do I know if it's the first time through the loop or if I'm walking
	through saved memory?
How do I save the memory to the right location?


*/




#include "limits.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

const int TRUE = 1;
const int FALSE = 0;

const char NEXT = '>';
const char PREV = '<';
const char INC = '+';
const char DEC = '-';
const char PRINT = '*';
const char BEGLOOP = '(';
const char ENDLOOP = ')';
const int MAX_SIZE = 100000;


FILE *bf;
char bags[MAX_SIZE];


  
// A structure to represent a stack 
// C program for linked list implementation of stack 
  
// A structure to represent a stack 
struct StackNode 
{ 
    char* data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(char* char_pointer) 
{ 
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
    stackNode->data = char_pointer; 
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, char* data) 
{ 
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode; 
   // printf("pushed to stack\n"); 
} 
  
char* pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) 
        return NULL; 
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    char* popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
char* peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) 
        return NULL; 
    return root->data; 
} 




int excecute_instructions(char* file_as_string)
{
	char* instruction_pointer = file_as_string;
	struct StackNode* beg_loop_pointers = NULL;
	char instruction = *instruction_pointer;
	char* pointer = bags;
	while(instruction != 0)
	{
		if(instruction == INC)
		{
			*pointer = *pointer + 1;
		}
		if(instruction == DEC)
		{
			*pointer = *pointer - 1;
		}
		else if (instruction == NEXT)
		{
			if ((pointer - bags)/sizeof(char) < MAX_SIZE)
			{
				pointer += 1;
			}
			else
			{
				printf("ERROR: Tried to access memory beyond upper limit.");
				return 0;
			}
		}
		else if(instruction == PREV)
		{
			if (pointer > bags)
			{
				pointer -= 1;
			}
			else
			{
				printf("ERROR: Tried to access memory below lower limit.");
				return 0;
			}
		}
		else if(instruction == PRINT)
		{
			// printf("Printing something now: ");
			printf("%c", *pointer);
		}
		else if(instruction == BEGLOOP)
		{
			if(*pointer == 0)
			{
				int danglingParen = 1;
				char instruction_to_skip;
				while(danglingParen > 0)
				{
					instruction_to_skip = fgetc(bf);
					if (instruction_to_skip == '(')
					{
						danglingParen++;
					}
					else if (instruction_to_skip == ')')
					{
						danglingParen--;
					}
				}
			}
			else
			{
				push(&beg_loop_pointers, instruction_pointer); 
			}
		}
		else if(instruction == ENDLOOP)
		{
			if(isEmpty(beg_loop_pointers))
			{
				printf("ERROR: Parenthesis not lined up.");
				return 0;
			}
			if(*pointer == 0)
			{
				pop(&beg_loop_pointers);
			}
			else			//repeat the loop
			{
				instruction_pointer = peek(beg_loop_pointers);
			}

		}
		instruction_pointer = instruction_pointer + 1;
		instruction = *instruction_pointer;
	}
	printf("\n");
	return 1;
}

int main(void)
{
	bf = fopen("bftest2","r");
	if (bf == NULL)
	{
		printf("Failed to open bfcode.\n");
		return 0;
	}
	char* file_as_string;
	char single_char = fgetc(bf);
	while (single_char != -1)
	{
		strncat(file_as_string, &single_char, 1);
		single_char = fgetc(bf);
	}
	//printf("%s", file_as_string);

	return excecute_instructions(file_as_string);
}
