#include <stdio.h>
#include <stdlib.h>

struct node_struct
{
    struct knoten_struct *parent;
    int value;
    struct node_struct *left, *right;
};

typedef struct node_struct Node;

void traverse_preorder()
{

}

int main()
{
    puts("[Traverse trees with this program]");

    puts("Exiting..");

    return EXIT_SUCCESS;
}