#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h" // Include header file for structures and prototypes

int main() {
    struct Node* head = NULL;

    // Menu loop for user interaction
    int choice;
    do {
        printf("\n================ LINKED LIST MENU ================\n");
        printf("1. Build Linked List (and clear previous list)\n");
        printf("2. Display List\n");
        printf("3. Calculate List Length\n");
        printf("4. Add Number at Head\n");
        printf("5. Add Number at Tail\n");
        printf("6. Add Number at a Given Position\n");
        printf("7. Delete Number at Head\n");
        printf("8. Delete Number at Tail\n");
        printf("9. Delete Number at a Given Position\n");
        printf("10. Search for a Number\n");
        printf("11. Sort the List (Ascending)\n");
        printf("12. Add Number in Sorted Order\n");
        printf("13. Remove Duplicates\n");
        printf("0. Exit Program\n");
        printf("================================================\n");
        printf("Choice: ");

        // Input validation is generally recommended here in production code
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input
            while(getchar() != '\n'); // Clear the input buffer
            choice = -1; // Set to invalid choice
        }

        switch (choice) {
            case 1:
                buildList(&head);
                break;
            case 2:
                displayList(head);
                break;
            case 3:
                printf("List Length: %d\n", getListLength(head));
                break;
            case 4: {
                int value;
                printf("Enter value to add at head: ");
                scanf("%d", &value);
                insertAtHead(&head, value);
                break;
            }
            case 5: {
                int value;
                printf("Enter value to add at tail: ");
                scanf("%d", &value);
                insertAtTail(&head, value);
                break;
            }
            case 6: {
                int value, position;
                printf("Enter value to add: ");
                scanf("%d", &value);
                printf("Enter position to add at (1-based): ");
                scanf("%d", &position);
                insertAtPosition(&head, value, position);
                break;
            }
            case 7:
                deleteAtHead(&head);
                break;
            case 8:
                deleteAtTail(&head);
                break;
            case 9: {
                int position;
                printf("Enter position of the number to delete (1-based): ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;
            }
            case 10: {
                int number;
                printf("Enter number to search for: ");
                scanf("%d", &number);
                if (searchNode(head, number)) {
                    printf("Result: The number %d IS present in the list.\n", number);
                } else {
                    printf("Result: The number %d IS NOT present in the list.\n", number);
                }
                break;
            }
            case 11:
                sortList(&head);
                printf("SUCCESS: The list has been sorted.\n");
                break;
            case 12: {
                int value;
                printf("Enter value to insert in sorted order: ");
                scanf("%d", &value);
                insertInSortedOrder(&head, value);
                break;
            }
            case 13:
                removeDuplicates(&head);
                printf("SUCCESS: Duplicates have been removed.\n");
                break;
            case 0:
                printf("Program terminated.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Crucial step: Free dynamically allocated memory before exiting
    freeList(&head);

    return 0;
}
