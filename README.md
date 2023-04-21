# Family-Relationship-Algorithm
## Description

This project is an algorithm that will find the relationships between two family members in a family tree.

## Objectives
* Create an algorithm that will always get the correct relationship between two family members
* Have a time complexity of O(n log n) or faster
* Have a space complexity no larger than O(n<sup>2</sup>)
* Display a list of family members to choose from
* Display the relationship between two selected members

## Design Considerations
* Data could likely be represented as a general tree or a graph depending on whether both parents are included in the family tree (in this case they shall be in order to resolve possible edge cases)
    * Currently represented as a general tree with no limits on the number of child nodes
    * Graphs would likely consume more memory as opposed to a general tree
    * Graph would still look similar to a tree, but with merging branches
    * Most likely best represented by a [multitree](https://en.wikipedia.org/wiki/Multitree), although this would not account for any marriages between blood relatives

## How the algorithm works
The algorithm starts by iterating through the entirety of one of the chosen people's ancestors and marks each of the visited nodes as seen (including itself). Once it has reached the root node, the second node will begin to search for any marked nodes, the first one found being the lowest common ancestor. Once the lowest common ancestor is found, the hops each search took to reach said ancestor are subtracted from each other to find their depth, so that: 

    search_1_hops - search_2_hops = depth

We can then use the depth and hops to calculate the degree of consanguinity (without accounting for generational difference) between the two, such that:

    (search_1_hops + search_2_hops) - depth = partial_consanguinity

This results in a table of consanguinity that increments by 2:

| Resulting Number | Relationship |
| ---------------- | ------------ |
| 0                | Parent/self  |
| 2                | Sibling (including uncles and aunts) |
| 4                | 1st cousin   |
| 6                | 2nd cousin   |
| 8                | 3rd cousin   |
| 10               | 4th cousin   |
| ...              | ...          |

We can then use the depth to assign generation and get the full consanguinity, such as <span style="color:green">grand</span><span style="color:red">parent</span> or <span style="color:red">1st cousin </span><span style="color:green">once removed</span>.

This leads us to a time complexity of O(2n), which simply leads us with O(n) after dropping the constant, where n is equal to the height of the tree. The space complexity of this is O(n), where n is the total amount of nodes in the tree, due to both the data structure that the family tree is arranged in and the hop counters. However, there would also have to be a post processing clean-up if the "mark" would be stored in the data structure over the algorithm. If stored in the data structure rather than temporary variables, then the clean up would have a time complexity of O(n), where n equal to the number of nodes in the tree, since it would simply have to iterate through each node and reset it. Otherwise, it would simply add to the space complexity of the main algorithm, but would not change it from a linear complexity.

In summary:
* Time complexity: O(n), n = height
* Space complexity: O(n), n = total # of nodes
* Post Process (time): O(n), n = total # of nodes
* Post Process (space): O(1)

### Limitations
* Does not account for any added (or removed) family members
* Does not account for any interbreeding
* Does not account for multiple parents, so only one side of the family in the tree at a time