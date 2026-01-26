#include <stdio.h>
#include <stdlib.h>

// Create new data structure called node:
// -> Add "node" to the typedef so we can use it within the definition.
typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./linked_list integer list\n");
        return 1;
    }

    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        // Convert argv to integers
        int number = atoi(argv[i]);

        // Create a temporary node n and allocate 'node' amount of memory to it
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Free memory thus far and abort
            return 1;
        }

        // n->number is a pointer from n to the number field
        n->number = number;
        // n->next is a pointer from n to the next field
        // Initialise it to the current position of list
        n->next = list;
        // Update list to the new latest position
        list = n;
    }

    // Print whole list
    // Initialise pointer (ptr) to current list address
    node *ptr = list;
    while (ptr != NULL)
    {
        // Print the number of the node ptr is pointing at
        printf("%i\n", ptr->number);
        // Update ptr to point at the next node in the list
        ptr = ptr->next;
    }

    // Free memory
    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    list = NULL;
}
