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

bool is_int(char const* s) {
    int n;
    int i;
    return sscanf(s, "%d %n", &i, &n) == 1 && !s[n];
}

void selectMembers(relative *node_1, relative *node_2, size_t family_size) {
    while (true) {
        char input[5];
        
        printf("Please select a person: ");
        int error = fgets(&input, 5, stdin);
        
        int value;
        
        if ((error != EOF && is_int(input))) {
            sscanf(input, "%d", &value);
            if (value < family_size && value > 0) {
                printf("Selected: %s \n", family_tree[value - 1].name);
                *node_1 = family_tree[value - 1];
                break;
            } else {
                printf("Error: Out of bounds \n");
            }
        } else {
            printf("Error: Invalid Input \n");
        }
    }
    
    while (true) {
        char input[5];
        
        printf("Please select another person: ");
        int error = fgets(&input, 5, stdin);
        
        int value;
        
        if ((error != EOF && is_int(input))) {
            sscanf(input, "%d", &value);
            if (value < family_size && value > 0) {
                printf("Selected: %s", family_tree[value - 1].name);
                *node_2 = family_tree[value - 1];
                break;
            } else {
                printf("Error: Out of bounds \n");
            }
        } else {
            printf("Error: Invalid Input \n");
        }
    }
}

int main(void) {

    size_t family_size = sizeof(family_tree) / sizeof(family_tree[0]);

    printf("Family members: \n");
    for(int i = 0; i < family_size; i++) {
        printf("%i. %s \n", i + 1, family_tree[i].name);
    }

    relative first_member;
    relative second_member;
    
    selectMembers(&first_member, &second_member, family_size + 1);

    return 0;
}
