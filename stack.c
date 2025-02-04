#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

void push(STACK **stack, int number)
{
    if (*stack == NULL)
    {
        *stack = malloc(sizeof(STACK));
        assert(*stack != NULL);
        (*stack)->head = NULL;
        (*stack)->tail = NULL;
        (*stack)->length = 0;
    }

    ELEMENT *new_element = malloc(sizeof(ELEMENT));
    assert(new_element != NULL);
    new_element->number = number;
    new_element->next = (*stack)->head;
    (*stack)->head = new_element;

    if ((*stack)->tail == NULL)
    {
        (*stack)->tail = new_element;
    }

    (*stack)->length++;
    printf("%d pushed to stack.\n", number);
}

void pop(STACK **stack)
{
    if (*stack != NULL && (*stack)->head != NULL)
    {
        ELEMENT *element_to_delete = (*stack)->head;
        printf("Element removed: %d\n", element_to_delete->number);

        (*stack)->head = element_to_delete->next;
        free(element_to_delete);
        (*stack)->length--;

        if ((*stack)->length == 0)
        {
            (*stack)->tail = NULL;
            free(*stack);
            *stack = NULL;
        }
    }
    else
    {
        printf("Stack is empty. Cannot pop.\n");
    }
}

void show_stack(STACK *stack)
{
    if (stack == NULL || stack->head == NULL)
    {
        printf("The stack is empty.\n");
    }
    else
    {
        printf("The stack has %d element(s).\n", stack->length);
        ELEMENT *current = stack->head;
        while (current != NULL)
        {
            printf("%d -> ", current->number);
            current = current->next;
        }
        printf("NULL\n");
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
            int number_to_add = -1;
            printf("Enter a value: ");
            scanf("%d", &number_to_add);
            push(&stack, number_to_add);
            break;

        case POP:
            pop(&stack);
            break;

        case SHOW_STACK:
            show_stack(stack);
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
