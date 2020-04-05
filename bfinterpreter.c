#include "limits.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

const char NEXT = '>';
const char PREV = '<';
const char INC = '+';
const char DEC = '-';
const char PRINT = '*';
const char BEGLOOP = '(';
const char ENDLOOP = ')';
const int MAX_SIZE = 100000;

  
// A structure to represent a stack 
// C program for linked list implementation of stack 
  
// A structure to represent a stack 
struct StackNode 
{ 
    int data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(int num) 
{ 
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
    stackNode->data = num; 
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, int data) 
{ 
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode; 
   // printf("pushed to stack\n"); 
} 
  
int pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) 
        return INT_MIN; 
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    int popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
int peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) 
        return INT_MIN; 
    return root->data; 
} 


int main(int argc, char** argv)
{
	char* filepath = argv[1];
	FILE *file;
	file = fopen(filepath,"r");
	if (file == NULL)
	{
		printf("Failed to open %s.\n", filepath);
		return 0;
	}
	struct StackNode* beg_loop_pointers = NULL;
	//printf("\n\nInstruction1: %d\n\n", (int) instruction);
	char bags[MAX_SIZE];
	char instruction = fgetc(file);
	char* pointer = bags;
	while(instruction != -1)
	{
		//printf("%c", instruction);
		if(instruction == INC)
			*pointer = *pointer + 1;
		else if(instruction == DEC)
			*pointer = *pointer - 1;
		else if (instruction == NEXT) {
			if ((pointer - bags)/sizeof(char) < MAX_SIZE)
				pointer += 1;
			else {
				printf("ERROR: Tried to access memory beyond upper limit.");
				return 0;
			}
		}
		else if(instruction == PREV) {
			if (pointer > bags)
				pointer -= 1;
			else {
				printf("ERROR: Tried to access memory below lower limit.");
				return 0;
			}
		}
		else if(instruction == PRINT)
			printf("%c", *pointer);
		else if(instruction == BEGLOOP) {
			if(*pointer == 0)
			{
				int danglingParen = 1;
				char instruction_to_skip;
				while(danglingParen > 0)
				{
					instruction_to_skip = fgetc(file);
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
				push(&beg_loop_pointers, ftell(file) + 1); 
			}
		}
		else if(instruction == ENDLOOP) {
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
				fseek(file, peek(beg_loop_pointers) - 1, SEEK_SET);
			}
		}
		instruction = fgetc(file);
	}
	printf("\nFinished\n");
	return 1;
}