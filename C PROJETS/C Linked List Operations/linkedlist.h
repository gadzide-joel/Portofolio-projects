#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// 1. Structure Definition
// Represents a single node (element) in the linked list.
struct Node {
    int value;
    struct Node* next; // Pointer to the next node in the sequence
};

// 2. Function Prototypes (Declarations)

// --- BUILD and DISPLAY ---
void buildList(struct Node** head);
void displayList(struct Node* head);
int getListLength(struct Node* head);

// --- INSERTION ---
void insertAtHead(struct Node** head, int value);
void insertAtTail(struct Node** head, int value);
void insertAtPosition(struct Node** head, int value, int position);
void insertInSortedOrder(struct Node** head, int value); // Inserts into a sorted list

// --- DELETION ---
void deleteAtHead(struct Node** head);
void deleteAtTail(struct Node** head);
void deleteAtPosition(struct Node** head, int position);

// --- UTILITY and ADVANCED ---
int searchNode(struct Node* head, int number);
void sortList(struct Node** head);
void removeDuplicates(struct Node** head);
void freeList(struct Node** head); // Utility to free all allocated memory

#endif // LINKEDLIST_H
