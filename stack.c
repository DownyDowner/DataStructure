#include <stdio.h>
#include <stdlib.h>

#define PUSH 1
#define POP 2
#define SHOW_STACK 3
#define EXIT 4

typedef struct element
{
    int number;
    struct element *next;
} ELEMENT;

typedef struct stack
{
    ELEMENT *head;
    ELEMENT *tail;
    int length;
} STACK;

void print_menu()
{
    printf("====================\n");
    printf("      STACK MENU     \n");
    printf("====================\n");
    printf("1. Push (Add an element)\n");
    printf("2. Pop (Remove an element)\n");
    printf("3. Display the stack\n");
    printf("4. Exit\n");
    printf("====================\n");
    printf("Choose an option: ");
}

void free_memory(STACK **stack)
{
    if (*stack != NULL)
    {

        ELEMENT *current = (*stack)->head;
        ELEMENT *temp = NULL;

        while (current != NULL)
        {
            temp = current->next;
            free(current);
            current = temp;
        }

        free(*stack);
        *stack = NULL;
    }
}

int main(void)
{
    STACK *stack = NULL;
    int is_running = 1;
    while (is_running)
    {
        print_menu();
        int option_chosen = -1;
        scanf("%d", &option_chosen);

        switch (option_chosen)
        {
        case PUSH:
            break;

        case POP:
            break;

        case SHOW_STACK:
            break;

        case EXIT:
            free_memory(&stack);
            if (stack == NULL)
            {
                printf("Stack successfully cleared and set to NULL.\n");
            }
            else
            {
                fprintf(stderr, "Error: Failed to clear the Stack.\n");
                return EXIT_FAILURE;
            }
            is_running = 0;
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
