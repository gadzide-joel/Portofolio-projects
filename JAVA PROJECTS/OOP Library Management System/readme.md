# Java Project: Library Management System
This project is an Object-Oriented Programming (OOP) application in Java that simulates the core operations of a library, including inventory management, borrowing, returning, and managing reservations.

# Core Architecture
The system is built on four distinct classes to manage data and functionality:

Author.java: A simple data class holding descriptive information (name, nationality) about a book's creator.

Book.java: The central entity representing a title. It manages its own stock count (availableCopies) and uses a Queue (reservationQueue) to handle patron reservations using the First-In, First-Out (FIFO) principle.

LibraryManager.java: The main operational class. It holds the complete collection of books in a List (catalog) and implements all high-level business logic.

Main.java: Initializes the authors and books, then simulates a sequence of transactions (borrowing, reserving, returning) to test the system flow.

# Key Functionalities
The system implements robust transaction logic:

Borrowing: Decreases the availableCopies. Fails if the stock is zero.

Reserving: Adds a patron ID to the reservation queue only if no copies are available and the patron hasn't already reserved the book.

Returning: Increases the availableCopies. If the stock was previously zero and the reservation queue is not empty, it automatically processes the next patron in line, notifying them that a copy is now available.

Reporting: The LibraryManager can generate a report displaying the overall inventory status, including which titles are out of stock and which have active reservations.