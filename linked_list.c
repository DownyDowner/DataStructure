#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ADD_ELEMENT 1
#define REMOVE_ELEMENT 2
#define SHOW_LIST 3
#define EXIT 4

typedef struct element
{
    int number;
    struct element *next;
} ELEMENT;

void print_menu()
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

void add_element(ELEMENT **head, int number)
{
    if (*head == NULL)
    {
        *head = malloc(sizeof(ELEMENT));
        assert(*head != NULL);
        (*head)->number = number;
        (*head)->next = NULL;
    }
    else
    {
        ELEMENT *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = malloc(sizeof(ELEMENT));
        assert(current->next != NULL);
        current->next->number = number;
        current->next->next = NULL;
    }
    printf("%d has been added to the list.\n", number);
}

void free_memory(ELEMENT **head)
{
    ELEMENT *current = *head;
    ELEMENT *temp = NULL;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    *head = NULL;
}

void show_list(ELEMENT *head)
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
    }
    else
    {
        ELEMENT *current = head;
        printf("List elements:\n");
        while (current != NULL)
        {
            printf("%d -> ", current->number);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void remove_element(ELEMENT **head, int number)
{
    if (*head == NULL)
    {
        printf("The list is empty.\n");
    }
    else
    {
        int is_found = 0;
        ELEMENT *current = *head;
        ELEMENT *previous = NULL;
        while (current != NULL && !is_found)
        {
            if (current->number == number)
            {
                is_found = 1;
                if (previous == NULL)
                {
                    *head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                free(current);
                current = NULL;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }

        if (is_found)
        {
            printf("Element %d removed successfully.\n", number);
        }
        else
        {
            printf("Element %d not found in the list.\n", number);
        }
    }
}

int main(void)
{
    ELEMENT *head = NULL;
    int is_running = 1;

    while (is_running)
    {
        print_menu();
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
            int number_to_remove = -1;
            printf("Enter a value: ");
            scanf("%d", &number_to_remove);
            remove_element(&head, number_to_remove);
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
            is_running = 0;
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
