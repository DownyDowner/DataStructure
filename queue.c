#include <stdio.h>
#include <stdlib.h>

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
