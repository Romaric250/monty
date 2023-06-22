#include "monty.h"

#define BUFFER_SIZE 1024

instruction_t instruction[] = {
    {"pint", pint},
    {"push", push},
    {"pall", pall},
    /* Other opcodes */
    {NULL, NULL}
};

/**
 * main - Entry point for the Monty Bytecode Interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char **argv)
{
    FILE *file;
    char buffer[BUFFER_SIZE];
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    instruction_t instruction;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        line_number++;

        if (parse_instruction(buffer, &instruction))
        {
            instruction.f(&stack, line_number);
        }

        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, instruction.opcode);
            free_stack(stack);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    free_stack(stack);
    fclose(file);
    exit(EXIT_SUCCESS);
}
