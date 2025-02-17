#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ADD_ELEMENT 1
#define REMOVE_ELEMENT 2
#define DISPLAY_PREORDER 3
#define DISPLAY_IN_ORDER 4
#define DISPLAY_POST_ORDER 5
#define EXIT 6

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
    printf("2. Remove an element\n");
    printf("3. Display in preorder\n");
    printf("4. Display in in-order\n");
    printf("5. Display in post-order\n");
    printf("6. Exit\n");
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

void remove_element(NODE **node, int number)
{
    if (*node == NULL)
        return;

    if (number < (*node)->number)
    {
        remove_element(&((*node)->left), number);
    }
    else if (number > (*node)->number)
    {
        remove_element(&((*node)->right), number);
    }
    else
    {
        // Node with only one child or no child
        if ((*node)->left == NULL)
        {
            NODE *temp = *node;
            *node = (*node)->right;
            free(temp);
        }
        else if ((*node)->right == NULL)
        {
            NODE *temp = *node;
            *node = (*node)->left;
            free(temp);
        }
        else
        {
            // Node with two children
            NODE *temp = (*node)->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            (*node)->number = temp->number;
            remove_element(&((*node)->right), temp->number);
        }
    }
}

int get_tree_size(NODE *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + get_tree_size(root->left) + get_tree_size(root->right);
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

int is_tree_empty(NODE *root)
{
    if (root == NULL)
    {
        printf("The tree is empty.\n");
        return 1;
    }
    return 0;
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

        case REMOVE_ELEMENT:
            if (!is_tree_empty(root))
            {
                int number_to_remove = -1;
                printf("Enter a value: ");
                scanf("%d", &number_to_remove);
                remove_element(&root, number_to_remove);
            }
            break;

        case DISPLAY_PREORDER:
            if (!is_tree_empty(root))
            {
                printf("Tree size: %d\n", get_tree_size(root));
                display_preorder(root);
                printf("\n");
            }
            break;

        case DISPLAY_IN_ORDER:
            if (!is_tree_empty(root))
            {
                printf("Tree size: %d\n", get_tree_size(root));
                display_in_order(root);
                printf("\n");
            }
            break;

        case DISPLAY_POST_ORDER:
            if (!is_tree_empty(root))
            {
                printf("Tree size: %d\n", get_tree_size(root));
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
