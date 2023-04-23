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

void nodeTraversal(relative *node, int traversalHops) {
    node->hops = traversalHops;
    node->isMarked = true;
    
    if (node->parent == NULL) return;
    else nodeTraversal(node->parent, traversalHops + 1);
}

int markSearch(relative *node, int *nodeHops, int searchHops) {
    if (node->isMarked) {
        *nodeHops = node->hops;
        return searchHops;
    } else return markSearch(node->parent, nodeHops, searchHops + 1);
}

void findGeneration(char *generation, int depth) {
    unsigned int genDiff = abs(depth);
    if (genDiff == 1) strcat(generation, "grand");
    else if (genDiff > 1) {
        char *greats = malloc((genDiff * 13) * sizeof(char));
        for (int i = 0; i < genDiff - 1; i++) strcat(greats, "great ");
        *generation = strcat(greats, "grand");
    } else {
        *generation = malloc(7 * sizeof(char));
    }
}

void findFullConsanguinity(int partial_consanguinity, int depth, char *return_relationship) {
    switch (partial_consanguinity) {
        case 0:
            if (depth == 0) *return_relationship = "self";
            else {
                char *generation;
                findGeneration(&generation, depth);
                if (depth < 0) *return_relationship = strcat(generation, "child");
                else if (depth > 0) *return_relationship = strcat(generation, "parent");
            }
            break;
        case 2: 
            if (depth == 0) *return_relationship = "sibling";
            else {
                char *generation;
                findGeneration(&generation, depth);
                if (depth < 0) *return_relationship = strcat(generation, "niece/nephew");
                else if (depth > 0) *return_relationship = strcat(generation, "uncle/aunt");
            }
            break;
        default:
            if (partial_consanguinity > 2 && partial_consanguinity % 2 == 0) {
                int cousin_number = partial_consanguinity - (partial_consanguinity/2 + 1);
            }
            break;
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

    int nodeHops;
    nodeTraversal(&first_member, 0);
    
    int searchHops = markSearch(&second_member, &nodeHops, 0);
    printf("nodeHops: %i \nsearchHops: %i", nodeHops, searchHops);

    int depth = nodeHops - searchHops;
    
    int partial_consanguinity = (nodeHops + searchHops) - depth;

    return 0;
}
