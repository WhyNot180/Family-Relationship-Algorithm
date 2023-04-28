# Family-Relationship-Algorithm
## Description
---
This project is an algorithm that will find the relationships between two family members in a family tree.

## Objectives
---

* Create an algorithm that will always get the correct relationship between two family members
* Have a time complexity of O(n log n) or faster
* Have a space complexity no larger than O(n<sup>2</sup>)
* Display a list of family members to choose from
* Display the relationship between two selected members

## How the algorithm works
---

The algorithm starts by iterating through the entirety of one of the chosen people's ancestors and marks each of the visited nodes as seen (including itself). Once it has reached the root node, the second node will begin to search for any marked nodes, the first one found being the lowest common ancestor. Once the lowest common ancestor is found, the hops each search took to reach said ancestor are subtracted from each other to find their depth, so that: 

    search_1_hops - search_2_hops = depth

We can then use the depth and hops to calculate the degree of consanguinity (without accounting for generational difference) between the two, such that:

    (search_1_hops + search_2_hops) - |depth| = partial_consanguinity

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

### Complexity
---

The time complexity of this algorithm is O(h), where h is the height of the tree, since the nodes are traversed bottom up. The space complexity of the algorithm is O(1), since the data the algorithm stores for its use remains constant. There is a post process which would have a time complexity of O(h). This is for resetting the nodes that were marked.

In summary:
* Time complexity: O(h), h = height
* Space complexity: O(1)
* Post Process (time): O(h), h = height
* Post Process (space) O(1)

### Limitations
---

* Does not account for any removed family members
* Does not account for any inbreeding
* Does not account for multiple parents, so only one side of the family searched at a time
* Will get stuck in a tree with an infinite height

## Future Improvements
---

### Family Forest

There is a way to search for relationships across multiple family trees, however, it can take quite a lot of memory.

When I say multiple family trees, I mean the family trees of every single node in every single tree.

For example, take a look at this family tree:

![family shrub](images/Family%20Shrub.png)

If someone wanted to figure out what the relationship between Ethan and Raymond were, with the current algorithm, it would have to traverse through each and every part of the family tree. However, if we were to assign a sort of inherited ID, it would be able to traverse through the correct path towards a common ancestor.