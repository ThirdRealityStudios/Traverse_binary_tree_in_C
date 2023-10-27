#include <stdio.h>
#include <stdlib.h>

struct knoten_struct
{
    struct knoten_struct *vaterknoten;
    int wert;
    struct knoten_struct *links, *rechts;
};

typedef knoten_struct Knoten;

void traverse_preorder()
{

}

int main()
{


    return EXIT_SUCCESS;
}