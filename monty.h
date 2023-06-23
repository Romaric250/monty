#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

#define STACK_MODE 0
#define QUEUE_MODE 1

/* Data structures */

/**
 * struct stack_s - Doubly linked list representation of a stack (or queue)
 * @n: Integer stored in the node
 * @prev: Pointer to the previous element of the stack (or queue)
 * @next: Pointer to the next element of the stack (or queue)
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - Opcode and its function
 * @opcode: The opcode
 * @f: The function associated with the opcode
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* Global variables */

extern int data_mode;

int parse_instruction(char *line, instruction_t *instruction);
void free_stack(stack_t *stack);


void add(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);

int _strcmp(char *s1, char *s2);
char *_strtok(char *str, const char *delim);
#endif /* MONTY_H */
