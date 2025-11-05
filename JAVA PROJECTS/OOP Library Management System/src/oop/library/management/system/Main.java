/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package oop.library.management.system;

/**
 *
 * @author USER
 */
/**
 * Main class to demonstrate the functionalities of the Library Management System.
 * Simulates book addition, borrowing, reservation, return, and inventory checks.
 */
public class Main {
    public static void main(String[] args) {
        
        // 1. Initialization
        Author balzac = new Author("Honoré de Balzac", "French");
        LibraryManager manager = new LibraryManager();
        
        // Create Books (Title, Author, ISBN, Available Copies)
        Book book1 = new Book("Le Père Goriot", balzac, "978-2070366914", 1); // 1 copy
        Book book2 = new Book("La Comédie humaine", balzac, "978-2070381610", 0); // 0 copies (Out of stock initially)
        
        manager.addBook(book1);
        manager.addBook(book2);

        System.out.println("\n================ STARTING LIBRARY OPERATIONS ==================");

        // 2. Test Borrowing
        System.out.println("\n--- Borrowing Phase ---");
        manager.borrowBook("Le Père Goriot"); // Stock passes to 0 (all copies checked out)
        manager.borrowBook("Le Père Goriot"); // Failure (Stock = 0)
        
        // 3. Test Reservation
        System.out.println("\n--- Reservation Phase ---");
        manager.reserveBook("Le Père Goriot", "PATRON-001"); // Reservation added
        manager.reserveBook("Le Père Goriot", "PATRON-002"); // Reservation added
        manager.reserveBook("Le Père Goriot", "PATRON-001"); // Failure: Already reserved

        // 4. Test Inventory Status Report (Includes out-of-stock and reserved titles)
        manager.displayInventoryStatus();
        
        // 5. Test Return (Triggers reservation processing)
        System.out.println("\n--- Return Phase ---");
        manager.returnBook("Le Père Goriot"); // Stock passes to 1, notifies PATRON-001
        
        // 6. Final Inventory Check
        manager.displayInventoryStatus();
    }
}
