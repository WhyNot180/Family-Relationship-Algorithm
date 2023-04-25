#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Makes sure it's proper null and not just 0
#define nullptr ((void*)0)

typedef struct node {
    struct node* parent;
    bool isMarked;
    int hops;
    char* name;
} relative;

//This is a nightmare
//TODO: create a parser to parse something else and autogenerate this
relative family_tree[] = 
    {{.name = "Elizabeth", .parent = nullptr}, {.name = "Rosanne", .parent = &family_tree[0]}, {.name = "Ruthanne", .parent = &family_tree[0]}, 
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

void selectMembers(relative **node_1, relative **node_2, size_t family_size) {
    while (true) {
        char input[5];
        
        printf("Please select a person: ");
        char *error = fgets(input, sizeof(input), stdin);
        
        int value;
        
        if ((*error != 1 && is_int(input))) {
            sscanf(input, "%d", &value);
            if (value < family_size && value > 0) {
                printf("Selected: %s \n", family_tree[value - 1].name);
                *node_1 = &family_tree[value - 1]; // Needs to be a double pointer so we do not copy and properly traverse the tree
                break;
            } else {
                printf("Error: Out of bounds \n");
            }
        } else {
            printf("Error: Invalid Input \n");
        }
    }
    
    // Same as above, should be consolidated into one thing so we conform to DRY
    while (true) {
        char input[5];
        
        printf("Please select another person: ");
        char *error = fgets(input, sizeof(input), stdin);
        
        int value;
        
        
        if ((*error != 1 && is_int(input))) {
            sscanf(input, "%d", &value);
            if (value < family_size && value > 0) {
                printf("Selected: %s\n", family_tree[value - 1].name);
                *node_2 = &family_tree[value - 1];
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
    
    if (node->parent != nullptr) nodeTraversal(node->parent, traversalHops + 1);
}

int markSearch(relative *node, int *nodeHops, int searchHops) {
    if (node->isMarked) {
        *nodeHops = node->hops;
        return searchHops;
    } else return markSearch(node->parent, nodeHops, searchHops + 1);
}

void nodeCleanup(relative *node) {
    node->isMarked = false;
    
    if (node->parent != nullptr) nodeCleanup(node->parent);
}

void findGeneration(char **generation, int depth) {
    unsigned int genDiff = abs(depth);
    if (genDiff == 1) {
        *generation = malloc((5 + 1) * sizeof(char));
    } else if (genDiff > 1) {
        char *greats = malloc((genDiff * 10 + 1) * sizeof(char));
        *generation = malloc((genDiff * 10 + 1) * sizeof(char));
        for (int i = 0; i < genDiff - 2; i++) strcat(greats, "great ");
        strcpy(*generation, strcat(greats, "grand"));
        free(greats);
    } 
}

char *get_ordinal (char **ordinals, int value)
{
    value %= 100;  // Normalize values between 0-100

    if (3 < value && value < 21)
        return ordinals[3];

    switch (value % 10) {
        case 1 :    return ordinals[0];
                    break;
        case 2 :    return ordinals[1];
                    break;
        case 3 :    return ordinals[2];
                    break;
        default:    return ordinals[3];
                    break;
    }
}

void findFullConsanguinity(int partial_consanguinity, int depth, char **return_relationship) {
    switch (partial_consanguinity) {
        case 0:
            if (depth == 0) *return_relationship = "self";
            else {
                char *generation;
                findGeneration(&generation, depth);
                if (depth < 0) strcpy(*return_relationship, strcat(generation, "child"));
                else if (depth > 0) strcpy(*return_relationship, strcat(generation, "parent"));
                free(generation);
            }
            break;
        case 2: 
            if (depth == 0) *return_relationship = "sibling";
            else {
                char *generation;
                findGeneration(&generation, depth);
                if (depth < 0) strcpy(*return_relationship, strcat(generation, "niece/nephew"));
                else if (depth > 0) strcpy(*return_relationship, strcat(generation, "uncle/aunt"));
                free(generation);
            }
            break;
        default:
            if (partial_consanguinity > 2 && partial_consanguinity % 2 == 0) {
                int cousin_number = partial_consanguinity - (partial_consanguinity/2 + 1);
                int times_removed = abs(depth);
                char *ordinals[] = { "st", "nd", "rd", "th" };
                if (times_removed == 0) sprintf(*return_relationship, "%i%s cousin", cousin_number, get_ordinal(ordinals, cousin_number));
                else sprintf(*return_relationship, "%i%s cousin, %ix removed", cousin_number, get_ordinal(ordinals, cousin_number), times_removed);
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

    relative *first_member;
    relative *second_member;
    
    selectMembers(&first_member, &second_member, family_size + 1);
    
    int nodeHops;
    nodeTraversal(second_member, 0);
    
    int searchHops = markSearch(first_member, &nodeHops, 0);

    int depth = nodeHops - searchHops;
    
    int partial_consanguinity = (nodeHops + searchHops) - abs(depth);
    
    char *return_relationship = malloc(29 * sizeof(char));
    
    findFullConsanguinity(partial_consanguinity, depth, &return_relationship);
    
    nodeCleanup(second_member);
    
    printf("%s is the %s of %s", first_member->name, return_relationship, second_member->name);

    return 0;
}