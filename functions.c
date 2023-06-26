#include "monty.h"

/**
 * free_stack - Frees all nodes in a stack.
 * @stack: Pointer to the top of the stack.
 */
void free_stack(stack_t *stack)
{
    stack_t *current;

    while (stack != NULL)
    {
        current = stack;
        stack = stack->next;
        free(current);
    }
}

/**
 * add_node - Creates a new node and adds it to the top of the stack.
 * @stack: Pointer to the top of the stack.
 * @n: Value to be added to the new node.
 *
 * Return: Pointer to the new node, or NULL on failure.
 */
stack_t *add_node(stack_t **stack, int n)
{
    stack_t *new_node;

    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
        return (NULL);

    new_node->n = n;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
        (*stack)->prev = new_node;

    *stack = new_node;

    return (new_node);
}


void nop(stack_t **stack, unsigned int line_number)
{
    (void) stack;
    (void) line_number;
}
void add(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n += (*stack)->n;
    pop(stack, line_number);
}

/**
 * push - Pushes an element to the stack.
 * @stack: Pointer to the top of the stack.
 * @line_number: Line number in the Monty byte code file.
 */
void push(stack_t **stack, unsigned int line_number)
{
        char *arg = strtok(NULL, " \n\t");
        int n;

        if (arg == NULL || !isdigit(*arg))
        {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
        }

        n = atoi(arg);

        if (!add_node(stack, n))
        {
                fprintf(stderr, "Error: malloc failed\n");
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
}

/**
 * pall - Prints all the values on the stack.
 * @stack: Pointer to the top of the stack.
 * @line_number: Line number in the Monty byte code file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
        stack_t *current = *stack;

        (void)line_number;

        while (current != NULL)
        {
                printf("%d\n", current->n);
                current = current->next;
        }
}


void swap(stack_t **stack, unsigned int line_number)
{
	int delete;
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    delete = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = delete;
}

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *empty;
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    empty = *stack;
    *stack = (*stack)->next;
    free(empty);
}


void mul(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n *= (*stack)->n;
    pop(stack, line_number);
}

void div_m(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n /= (*stack)->n;
    pop(stack, line_number);
}

void sub(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n -= (*stack)->n;
    pop(stack, line_number);
}


void mod(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n %= (*stack)->n;
    pop(stack, line_number);
}

void pchar(stack_t **stack, unsigned int line_number)
{
    int value;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = (*stack)->n;
    if (value < 0 || value > 127)
    {
        fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }

    putchar(value);
    putchar('\n');
}

void rotl(stack_t **stack, unsigned int line_number)
{
   stack_t *top_node;
   stack_t *second_node;
   stack_t *bottom_node;
   (void) line_number;

    if (*stack == NULL || (*stack)->next == NULL)
        return;

    top_node = *stack;
    second_node = top_node->next;
    bottom_node = top_node;
    while (bottom_node->next != NULL)
        bottom_node = bottom_node->next;

    bottom_node->next = top_node;
    top_node->prev = bottom_node;
    top_node->next = NULL;
    second_node->prev = NULL;
    *stack = second_node;
}
void rotr(stack_t **stack, unsigned int line_number)
{
    stack_t *last_node;
   stack_t *second_last_node;
    (void) line_number;

    if (*stack == NULL || (*stack)->next == NULL)
        return;

    last_node = *stack;
    while (last_node->next != NULL)
        last_node = last_node->next;

    second_last_node = last_node->prev;
    second_last_node->next = NULL;
    last_node->prev = NULL;
    last_node->next = *stack;
    (*stack)->prev = last_node;
    *stack = last_node;
}

void pstr(stack_t **stack, unsigned int line_number)
{
    int value;
    stack_t *current;

    (void) line_number;

    if (*stack == NULL)
    {
        putchar('\n');
        return;
    }

    current = *stack;
    while (current != NULL && current->n != 0 && current->n >= 0 && current->n <= 127)
    {
        value = current->n;
        putchar(value);
        current = current->next;
    }
    putchar('\n');
}

void stack(stack_t **stack, unsigned int line_number)
{
    (void) line_number;
    (void) stack;
    /* Do nothing, since stack is the default behavior */
}

void queue(stack_t **stack, unsigned int line_number)
{
    stack_t *current;
   stack_t *last;
    (void) line_number;

    if (*stack == NULL || (*stack)->next == NULL)
        return;

    current = *stack;
    last = current;
    while (last->next != NULL)
        last = last->next;

    current->prev = last;
    last->next = current;
    while (current->next != last)
    {
        current->next->prev = current;
        current = current->next;
    }
    current->next = NULL;
    *stack = last;
}


/**
 * parse_instruction - Parses an instruction in a line of Monty bytecode.
 * @line: Line of Monty bytecode.
 * @instruction: Pointer to an instruction_t struct to fill.
 *
 * Return: 1 if the instruction is valid, 0 otherwise.
 */
int parse_instruction(char *line, instruction_t *instruction)
{
        char *opcode = strtok(line, " \n\t");

        if (opcode == NULL || *opcode == '\0')
        {
		
                return (0);
        }

        instruction->opcode = opcode;

        if (strcmp(opcode, "push") == 0)
        {
                instruction->f = push;
        }
        else if (strcmp(opcode, "pall") == 0)
        {
                instruction->f = pall;
        }
	else if (strcmp(opcode, "pint") == 0)
        {
                instruction->f = pint;
        }
	else if (strcmp(opcode, "pop") == 0)
        {
                instruction->f = pop;
        }
	else if (strcmp(opcode, "mul") == 0)
        {
                instruction->f = mul;
        }
	else if (strcmp(opcode, "swap") == 0)
        {
                instruction->f = swap;
        }
	else if (strcmp(opcode, "rotr") == 0)
        {
                instruction->f = rotr;
        }
	else if (strcmp(opcode, "queue") == 0)
        {
                instruction->f = queue;
        }
	else if (strcmp(opcode, "stack") == 0)
        {
                instruction->f = stack;
        }

	else if (strcmp(opcode, "rotl") == 0)
        {
                instruction->f = rotl;
        }
	else if (strcmp(opcode, "pstr") == 0)
        {
                instruction->f = pstr;
        }

	else if (strcmp(opcode, "pchar") == 0)
        {
                instruction->f = pchar;
        }
	else if (strcmp(opcode, "mod") == 0)
        {
                instruction->f = mod;
        }
	else if (strcmp(opcode, "add") == 0)
	{
		instruction->f = add;
	}
	else if (strcmp(opcode, "sub") == 0)
        {
                instruction->f = sub;
        }
	else if (strcmp(opcode, "div_m") == 0)
        {
                instruction->f = div_m;
        }

	else if (strcmp(opcode, "nop") == 0)
	{
	instruction->f = nop;	
	}
        else
        {
                return (0);
        }

        return (1);
}


/**
 * pint - Prints the value at the top of the stack, followed by a new line.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: Line number of the opcode.
 */
 void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}
