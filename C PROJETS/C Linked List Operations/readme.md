\# C Project: Singly Linked List Operations
This project implements the basic and advanced functionalities of a Singly Linked List data structure using the C programming language.

The main application (main.c) features an interactive menu that allows the user to dynamically test all list operations.

# Core Features

The source code is divided into three files (main.c, linkedlist.h, linkedlist.c) for clear organization. The implementation defines and carries out the following operations on list nodes (struct Node):

Build and Cleanup: Create the list (buildList), display its contents (displayList), get its length, and correctly free all allocated memory (freeList).

Modification (Insertion): Add new elements at the head, at the tail, at a specified position, or insert a value while maintaining a sorted order.

Modification (Deletion): Remove elements from the head, the tail, or a specific position.

Advanced Utilities: Search for a specific element, sort the list (by swapping values), and remove all duplicate values.

All functions include checks for boundary conditions (e.g., empty list, invalid position) and print success/failure messages.

