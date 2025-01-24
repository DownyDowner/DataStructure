#include <stdio.h>
#include <stdlib.h>

#define ADD_ELEMENT 1
#define REMOVE_ELEMENT 2
#define SHOW_LIST 3
#define EXIT 4

typedef struct element
{
    int number;
    struct element *next;
} ELEMENT;

void printMenu()
{
    printf("==========================\n");
    printf("     LINKED LIST MENU     \n");
    printf("==========================\n");
    printf("1. Add an element\n");
    printf("2. Remove an element\n");
    printf("3. Show the list\n");
    printf("4. Exit\n");
    printf("==========================\n");
    printf("Choose an option: ");
}

void add_element(ELEMENT **current, int number)
{
    if (*current == NULL)
    {
        *current = malloc(sizeof(ELEMENT));
        if (*current == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        (*current)->number = number;
        (*current)->next = NULL;
    }
    else
    {
        ELEMENT *temp = *current;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(ELEMENT));
        if (temp->next == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        temp->next->number = number;
        temp->next->next = NULL;
    }
    printf("%d has been added to the list.\n", number);
}

void free_memory(ELEMENT **current)
{
    ELEMENT *temp = NULL;
    while (*current != NULL)
    {
        temp = (*current)->next;
        free(*current);
        *current = temp;
    }
    *current = NULL;
}

void show_list(ELEMENT *current)
{
    if (current == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    printf("List elements:\n");
    while (current != NULL)
    {
        printf("%d -> ", current->number);
        current = current->next;
    }
    printf("NULL\n");
}

int main(void)
{
    ELEMENT *head = NULL;
    int isRunning = 1;
    while (isRunning)
    {
        printMenu();
        int option_chosen = -1;
        scanf("%d", &option_chosen);
        switch (option_chosen)
        {
        case ADD_ELEMENT:
            int number_to_add = -1;
            printf("Enter a value: ");
            scanf("%d", &number_to_add);
            add_element(&head, number_to_add);
            break;

        case REMOVE_ELEMENT:
            printf("Option REMOVE_ELEMENT not implemented yet.\n");
            break;

        case SHOW_LIST:
            show_list(head);
            break;

        case EXIT:
            free_memory(&head);
            if (head == NULL)
            {
                printf("List successfully cleared and head is set to NULL.\n");
            }
            else
            {
                fprintf(stderr, "Error: Failed to clear the list.\n");
                return EXIT_FAILURE;
            }
            isRunning = 0;
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
