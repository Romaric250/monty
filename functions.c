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

        if (opcode == NULL || *opcode == '#')
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
