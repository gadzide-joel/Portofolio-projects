#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// --- BUILD and DISPLAY ---

/**
 * @brief Allows the user to dynamically build the linked list by entering 'n' numbers.
 * @param head Pointer to the head of the list (passed by reference).
 */
void buildList(struct Node** head) {
    int n, value;
    struct Node* newNode;
    struct Node* temp;

    printf("How many numbers do you want to add to the list? : \t");
    scanf("%d", &n);

    // If the list is not empty, we clear it first (optional cleanup)
    if (*head != NULL) {
        freeList(head);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &value);

        // Allocate memory for the new node
        newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Error: Memory allocation failed.\n");
            return;
        }
        newNode->value = value;
        newNode->next = NULL;

        if (*head == NULL) {
            // Case 1: List is empty, new node becomes the head
            *head = newNode;
        } else {
            // Case 2: Traverse to the end and append the new node
            temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}

/**
 * @brief Prints all elements of the list from head to tail.
 * @param head Pointer to the head of the list (passed by value).
 */
void displayList(struct Node* head) {
    struct Node* temp = head;

    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}

/**
 * @brief Calculates the total number of nodes in the list.
 * @param head Pointer to the head of the list.
 * @return The length of the list (integer count).
 */
int getListLength(struct Node* head) {
    int length = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    return length;
}

// --- INSERTION ---

/**
 * @brief Adds a new node at the beginning of the list.
 * @param head Pointer to the head (must be modified, so reference is needed).
 * @param value The integer value to be inserted.
 */
void insertAtHead(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newNode->value = value;
    newNode->next = *head; // New node points to the old head
    *head = newNode;       // Update the head pointer
    printf("SUCCESS: %d added at the head.\n", value);
}

/**
 * @brief Adds a new node at the end of the list.
 * @param head Pointer to the head (must be modified if the list is empty).
 * @param value The integer value to be inserted.
 */
void insertAtTail(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode; // List was empty
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("SUCCESS: %d added at the tail.\n", value);
}

/**
 * @brief Adds a new node at a specified position.
 * @param head Pointer to the head.
 * @param value The integer value to be inserted.
 * @param position The 1-based index where the node should be inserted.
 */
void insertAtPosition(struct Node** head, int value, int position) {
    if (position <= 0) {
        printf("FAILURE: Invalid position (%d).\n", position);
        return;
    }

    if (position == 1) {
        insertAtHead(head, value);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newNode->value = value;

    struct Node* previous = *head;

    // Traverse to the node *before* the insertion point (position - 1)
    for (int i = 1; i < position - 1 && previous != NULL; i++) {
        previous = previous->next;
    }

    if (previous == NULL) {
        printf("FAILURE: Position (%d) is out of bounds.\n", position);
        free(newNode);
        return;
    }

    // Link the new node
    newNode->next = previous->next;
    previous->next = newNode;
    printf("SUCCESS: %d added at position %d.\n", value, position);
}

/**
 * @brief Inserts a new node while maintaining the list's sorted order.
 * Assumes the list is already sorted (ascending).
 * @param head Pointer to the head.
 * @param value The integer value to be inserted.
 */
void insertInSortedOrder(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL || value < (*head)->value) {
        // Case 1: List is empty or value belongs at the head
        newNode->next = *head;
        *head = newNode;
    } else {
        // Case 2: Traverse to find the correct spot
        struct Node* current = *head;
        // Stop when the next node is NULL OR the next node's value is greater than the new value
        while (current->next != NULL && current->next->value < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    printf("SUCCESS: %d added in sorted order.\n", value);
}


// --- DELETION ---

/**
 * @brief Deletes the first node in the list.
 * @param head Pointer to the head.
 */
void deleteAtHead(struct Node** head) {
    if (*head == NULL) {
        printf("FAILURE: The list is empty. Cannot delete from head.\n");
        return;
    }

    struct Node* temp = *head;
    *head = (*head)->next; // Move head to the next node
    printf("SUCCESS: Deleted value %d from head.\n", temp->value);
    free(temp); // Free the memory of the old head
}

/**
 * @brief Deletes the last node in the list.
 * @param head Pointer to the head.
 */
void deleteAtTail(struct Node** head) {
    if (*head == NULL) {
        printf("FAILURE: The list is empty. Cannot delete from tail.\n");
        return;
    }

    if ((*head)->next == NULL) {
        // Only one node in the list
        printf("SUCCESS: Deleted value %d from tail.\n", (*head)->value);
        free(*head);
        *head = NULL;
        return;
    }

    struct Node* previous = *head;
    struct Node* last = (*head)->next;

    // Traverse until 'last' is the final node
    while (last->next != NULL) {
        previous = last;
        last = last->next;
    }

    previous->next = NULL; // Previous node becomes the new tail
    printf("SUCCESS: Deleted value %d from tail.\n", last->value);
    free(last);
}

/**
 * @brief Deletes a node at a specified position.
 * @param head Pointer to the head.
 * @param position The 1-based index of the node to delete.
 */
void deleteAtPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("FAILURE: The list is empty.\n");
        return;
    }

    if (position <= 0) {
        printf("FAILURE: Invalid position (%d).\n", position);
        return;
    }

    if (position == 1) {
        deleteAtHead(head);
        return;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;

    // Traverse to the node at the target position
    for (int i = 1; i < position && current != NULL; i++) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("FAILURE: Position (%d) is out of bounds.\n", position);
        return;
    }

    // Link the previous node to the next node (bypassing 'current')
    previous->next = current->next;
    printf("SUCCESS: Deleted value %d at position %d.\n", current->value, position);
    free(current);
}

// --- UTILITY and ADVANCED ---

/**
 * @brief Searches for a specific integer value in the list.
 * @param head Pointer to the head.
 * @param number The integer value to search for.
 * @return 1 if found, 0 otherwise.
 */
int searchNode(struct Node* head, int number) {
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->value == number) {
            return 1; // Found
        }
        temp = temp->next;
    }

    return 0; // Not found
}

/**
 * @brief Sorts the list values in ascending order using the Bubble Sort algorithm.
 * Note: Only the values are swapped, not the node pointers.
 * @param head Pointer to the head.
 */
void sortList(struct Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // List is empty or has only one element
    }

    struct Node* current = *head;
    struct Node* nextNode = NULL;
    int tempValue;

    // Outer loop traverses the list
    while (current != NULL) {
        nextNode = current->next;
        // Inner loop compares current with all subsequent nodes
        while (nextNode != NULL) {
            if (current->value > nextNode->value) {
                // Swap values
                tempValue = current->value;
                current->value = nextNode->value;
                nextNode->value = tempValue;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

/**
 * @brief Eliminates all duplicate values from the list.
 * Iterates through the list and removes nodes with the same value as the current node.
 * @param head Pointer to the head.
 */
void removeDuplicates(struct Node** head) {
    if (*head == NULL) {
        return; // Empty list
    }

    struct Node* current = *head;

    // Outer loop: selects the node to compare against (the 'current' node)
    while (current != NULL) {
        struct Node* temp = current;
        // Inner loop: checks all subsequent nodes for duplicates
        while (temp->next != NULL) {
            if (current->value == temp->next->value) {
                // Found a duplicate: bypass and free the node
                struct Node* duplicate = temp->next;
                temp->next = temp->next->next;
                free(duplicate);
                // Note: We don't advance 'temp' here because temp->next was replaced
            } else {
                temp = temp->next;
            }
        }
        current = current->next;
    }
}

/**
 * @brief Frees all dynamically allocated memory in the list to prevent memory leaks.
 * @param head Pointer to the head.
 */
void freeList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL; // Ensure the head pointer is set to NULL after freeing
    printf("\nINFO: All list memory freed.\n");
}
