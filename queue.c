#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ENQUEUE 1
#define DEQUEUE 2
#define SHOW_QUEUE 3
#define EXIT 4

typedef struct element
{
    int number;
    struct element *next;
} ELEMENT;

typedef struct queue
{
    ELEMENT *head;
    ELEMENT *tail;
    int length;
} QUEUE;

void print_menu()
{
    printf("====================\n");
    printf("      QUEUE MENU     \n");
    printf("====================\n");
    printf("1. Enqueue (Add an element)\n");
    printf("2. Dequeue (Remove an element)\n");
    printf("3. Display the queue\n");
    printf("4. Exit\n");
    printf("====================\n");
    printf("Choose an option: ");
}

void enqueue(QUEUE **queue, int number)
{
    ELEMENT *element = malloc(sizeof(ELEMENT));
    assert(element != NULL);
    element->next = NULL;
    element->number = number;
    if (*queue == NULL)
    {
        *queue = malloc(sizeof(QUEUE));
        assert(*queue != NULL);
        (*queue)->head = element;
        (*queue)->tail = element;
        (*queue)->length = 1;
    }
    else
    {
        (*queue)->tail->next = element;
        (*queue)->tail = element;
        (*queue)->length++;
    }
}

void dequeue(QUEUE **queue)
{
    if (queue != NULL && (*queue) != NULL && (*queue)->head != NULL)
    {
        ELEMENT *element_to_delete = (*queue)->head;
        printf("Element removed: %d\n", element_to_delete->number);
        (*queue)->head = element_to_delete->next;
        free(element_to_delete);
        (*queue)->length--;

        if ((*queue)->length == 0)
        {
            (*queue)->tail = NULL;
        }
    }
    else
    {
        printf("Queue is empty. Cannot dequeue.\n");
    }
}

void show_queue(QUEUE *queue)
{
    if (queue == NULL)
    {
        printf("The queue is empty.\n");
    }
    else
    {
        printf("The queue has %d element(s).\n", queue->length);
        ELEMENT *current = queue->head;
        while (current != NULL)
        {
            printf("%d -> ", current->number);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void free_memory(QUEUE **queue)
{
    if (*queue != NULL)
    {

        ELEMENT *current = (*queue)->head;
        ELEMENT *temp = NULL;

        while (current != NULL)
        {
            temp = current->next;
            free(current);
            current = temp;
        }

        free(*queue);
        *queue = NULL;
    }
}

int main(void)
{
    QUEUE *queue = NULL;
    int is_running = 1;
    while (is_running)
    {
        print_menu();
        int option_chosen = -1;
        scanf("%d", &option_chosen);

        switch (option_chosen)
        {
        case ENQUEUE:
            int number_to_add = -1;
            printf("Enter a value: ");
            scanf("%d", &number_to_add);
            enqueue(&queue, number_to_add);
            break;

        case DEQUEUE:
            dequeue(&queue);
            break;

        case SHOW_QUEUE:
            show_queue(queue);
            break;

        case EXIT:
            free_memory(&queue);
            if (queue == NULL)
            {
                printf("Queue successfully cleared and set to NULL.\n");
            }
            else
            {
                fprintf(stderr, "Error: Failed to clear the queue.\n");
                return EXIT_FAILURE;
            }
            is_running = 0;
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }
}