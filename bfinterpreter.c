/*

THINGS TO CONSIDER:
How do I find the right instructions with looping?
	How do I know if it's the first time through the loop or if I'm walking
	through saved memory?
How do I save the memory to the right location?


*/





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
const int MAX_SIZE = 1000;


int loop_level = -1;
char** loop_instructions[10][100];
char* save_instructions = NULL;
char* saved_instruction = NULL;
FILE *bf;
char bags[MAX_SIZE];

//void next()

char get_next_instruction()
{
	if (loop_level < 0)
	{
		return fgetc(bf);
	}
	else
	{
		return loop_instructions[loop_level];//NOT COMPLETE
	}
}

int excecute_instructions(char* pointer, char end_condition)
{
	char instruction = fgetc(bf);
	while(instruction != end_condition)
	{
		// printf("%c", instruction);
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
				loop_level += 1;
				save_instructions = *loop_instructions[loop_level][0]; //want this to be a pointer to a char
			}
		}
		else if(instruction == ENDLOOP)
		{
			if(loop_level < 0)
			{
				printf("ERROR: Parenthesis not lined up.");
				return 0;
			}
			if(*pointer == 0)
			{
				loop_level -= 1;
			}
			else			//repeat the loop
			{

			}

		}
		instruction = fgetc(bf);
		if (save_instructions != NULL)
		{
			*save_instructions = instruction;
			save_instructions += 1;
		}
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
	char* pointer = bags;
	return excecute_instructions(pointer, -1);
}