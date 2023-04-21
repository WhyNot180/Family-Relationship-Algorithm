#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node* parent;
    bool isMarked;
    int hops;
    char* name;
} relative;

//This is a nightmare
//TODO: create a parser to parse something else and autogenerate this
relative family_tree[] = 
    {{.name = "Elizabeth", .parent = NULL}, {.name = "Rosanne", .parent = &family_tree[0]}, {.name = "Ruthanne", .parent = &family_tree[0]}, 
    {.name = "Donnie", .parent = &family_tree[0]}, {.name = "Patricia", .parent = &family_tree[0]}, {.name = "Marj", .parent = &family_tree[0]},
    {.name = "Kim", .parent = &family_tree[5]}, {.name = "Monica", .parent = &family_tree[5]}, {.name = "Martin", .parent = &family_tree[5]},
    {.name = "Gabe", .parent = &family_tree[5]}, {.name = "John", .parent = &family_tree[5]}, {.name = "Ben", .parent = &family_tree[5]},
    {.name = "Jerome", .parent = &family_tree[5]}, {.name = "John G", .parent = &family_tree[6]}, {.name = "Jamie", .parent = &family_tree[6]},
    {.name = "Julia", .parent = &family_tree[6]}, {.name = "Veera", .parent = &family_tree[12]}, {.name = "Precila", .parent = &family_tree[12]},
    {.name = "Clarence", .parent = &family_tree[12]}, {.name = "Ellane", .parent = &family_tree[9]}, {.name = "Jake", .parent = &family_tree[9]},
    {.name = "Phil", .parent = &family_tree[7]}, {.name = "Alley", .parent = &family_tree[7]}, {.name = "Anna", .parent = &family_tree[7]},
    {.name = "Steven", .parent = &family_tree[7]}, {.name = "Mo", .parent = &family_tree[19]}, {.name = "Lincoln", .parent = &family_tree[21]},
    {.name = "Alex", .parent = &family_tree[26]}
};

int main(void) {

    printf("Family members: \n");
    for(int i = 0; i < sizeof(family_tree) / sizeof(family_tree[0]); i++) {
        printf("%i. %s \n", i + 1, family_tree[i].name);
    }

    return 0
}
