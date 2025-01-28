#include <stdio.h>
#include <stdlib.h>

#define ENQUEUE 1
#define DEQUEUE 2
#define SHOW_LIST 3
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

void printMenu()
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
