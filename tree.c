#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ADD_ELEMENT 1
#define DISPLAY_PREORDER 2
#define DISPLAY_IN_ORDER 3
#define DISPLAY_POST_ORDER 4
#define EXIT 5

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} NODE;

void print_menu()
{
    printf("===================\n");
    printf("     TREE MENU     \n");
    printf("===================\n");
    printf("1. Add an element\n");
    printf("2. Display in preorder\n");
    printf("3. Display in in-order\n");
    printf("4. Display in post-order\n");
    printf("5. Exit\n");
    printf("====================\n");
    printf("Choose an option: ");
}

NODE *add_element(NODE *root, int number)
{
    if (root == NULL)
    {
        NODE *new_node = malloc(sizeof(NODE));
        assert(new_node != NULL);
        new_node->number = number;
        new_node->left = NULL;
        new_node->right = NULL;

        printf("Node with value %d successfully added as root.\n", number);

        return new_node;
    }
    if (number < root->number)
    {
        root->left = add_element(root->left, number);
        printf("Node with value %d inserted to the left of %d.\n", number, root->number);
    }
    else
    {
        root->right = add_element(root->right, number);
        printf("Node with value %d inserted to the right of %d.\n", number, root->number);
    }

    return root;
}

void display_preorder(NODE *root)
{
    printf("%d ", root->number);
    if (root->left != NULL)
        display_preorder(root->left);
    if (root->right != NULL)
        display_preorder(root->right);
}

void display_in_order(NODE *root)
{
    if (root->left != NULL)
        display_in_order(root->left);
    printf("%d ", root->number);
    if (root->right != NULL)
        display_in_order(root->right);
}

void display_post_order(NODE *root)
{
    if (root->left != NULL)
        display_post_order(root->left);
    if (root->right != NULL)
        display_post_order(root->right);
    printf("%d ", root->number);
}

void free_tree(NODE **root)
{
    if (*root != NULL)
    {
        free_tree(&((*root)->left));
        free_tree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

int main(void)
{
    NODE *root = NULL;
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
            root = add_element(root, number_to_add);
            break;

        case DISPLAY_PREORDER:
            if (root == NULL)
            {
                printf("The tree is empty.\n");
            }
            else
            {
                display_preorder(root);
                printf("\n");
            }
            break;

        case DISPLAY_IN_ORDER:
            if (root == NULL)
            {
                printf("The tree is empty.\n");
            }
            else
            {
                display_in_order(root);
                printf("\n");
            }
            break;

        case DISPLAY_POST_ORDER:
            if (root == NULL)
            {
                printf("The tree is empty.\n");
            }
            else
            {
                display_post_order(root);
                printf("\n");
            }
            break;

        case EXIT:
            free_tree(&root);
            if (root == NULL)
            {
                printf("Tree successfully cleared and set to NULL.\n");
            }
            else
            {
                fprintf(stderr, "Error: Failed to clear the tree.\n");
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
