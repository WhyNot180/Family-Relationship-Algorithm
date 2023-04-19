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
    * Graphs would likely consume more memory as opposed to a general tree
    * Graph would still look similar to a tree, but with merging branches
    * Most likely best represented by a [multitree](https://en.wikipedia.org/wiki/Multitree), although this would not account for any marriages between blood relatives
    * Will likely choose to represent as a general tree for now, for simplicity's sake
* Could assign a value for each member based on generation, which could be used to find generational offset of a family member
* Could use number of hops and lowest common ancestor to find relative location
* Would probably be best navigated by a depth-first search, since the tree is wider than it is tall and only the lowest common ancestor need be found