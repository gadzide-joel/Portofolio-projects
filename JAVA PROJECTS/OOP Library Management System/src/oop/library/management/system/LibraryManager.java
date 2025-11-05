/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package oop.library.management.system;

/**
 *
 * @author USER
 */
import java.util.ArrayList;
import java.util.List;

/**
 * The central management class for the library system.
 * It holds the entire book catalog and implements all core functionalities.
 */
public class LibraryManager {
    private List<Book> catalog; // The main collection of all books

    /**
     * Constructor to initialize the LibraryManager with an empty catalog.
     */
    public LibraryManager() {
        this.catalog = new ArrayList<>();
    }

    // --- BASIC CATALOG MANAGEMENT ---

    /**
     * Adds a new Book object to the library's catalog.
     * @param book The Book object to add.
     */
    public void addBook(Book book) {
        catalog.add(book);
        System.out.println("Book added to catalog: " + book.getTitle());
    }

    /**
     * Searches for a book by its title (case-insensitive).
     * @param title The title to search for.
     * @return The Book object if found, or null otherwise.
     */
    public Book findBook(String title) {
        for (Book book : catalog) {
            if (book.getTitle().equalsIgnoreCase(title)) {
                return book;
            }
        }
        return null;
    }
    
    // --- LOAN AND RETURN LOGIC ---
    
    /**
     * Attempts to process a book loan (checkout).
     * @param title The title of the book to borrow.
     * @return true if the loan was successful, false if the book is not found or out of stock.
     */
    public boolean borrowBook(String title) {
        Book book = findBook(title);
        if (book != null) {
            if (book.borrow()) {
                System.out.println("SUCCESS: The book '" + title + "' has been borrowed.");
                return true;
            } else {
                System.out.println("FAILURE: All copies of '" + title + "' are currently checked out.");
            }
        } else {
            System.out.println("FAILURE: Book '" + title + "' not found in the catalog.");
        }
        return false;
    }

    /**
     * Processes a book return (check-in) and triggers reservation processing if applicable.
     * @param title The title of the book being returned.
     */
    public void returnBook(String title) {
        Book book = findBook(title);
        if (book != null) {
            book.returnBook();
            System.out.println("SUCCESS: The book '" + title + "' has been returned.");
            
            // NEW: Process the reservation queue after a return
            String nextPatron = book.processNextReservation();
            if (nextPatron != null) {
                System.out.println("ATTENTION: The book is reserved by patron " + nextPatron + ". Please notify them.");
            }
        } else {
            System.out.println("FAILURE: Book '" + title + "' not found.");
        }
    }
    
    // --- NEW: RESERVATION MANAGEMENT ---

    /**
     * Allows a patron to reserve a book if it's currently unavailable.
     * @param title The title of the book to reserve.
     * @param patronId The ID of the patron making the reservation.
     */
    public void reserveBook(String title, String patronId) {
        Book book = findBook(title);
        if (book != null) {
            if (book.getAvailableCopies() > 0) {
                System.out.println("INFO: The book is available. Reservation is not needed (or patron should borrow directly).");
            } else {
                book.reserve(patronId);
            }
        } else {
            System.out.println("FAILURE: Book '" + title + "' not found. Reservation impossible.");
        }
    }

    // --- NEW: INVENTORY STATUS REPORT ---

    /**
     * Generates and displays a comprehensive report of the library's inventory status.
     * (Functionality: State of the Inventory)
     */
    public void displayInventoryStatus() {
        int totalDistinctTitles = catalog.size();
        int totalAvailableCopies = 0;
        int outOfStockTitles = 0;
        int reservedTitles = 0;
        
        System.out.println("\n--- INVENTORY STATUS REPORT ---");
        
        for (Book book : catalog) {
            totalAvailableCopies += book.getAvailableCopies();
            
            if (book.getReservationCount() > 0) {
                System.out.println("️ Reserved Title: " + book.getTitle() + " (Waiting Patrons: " + book.getReservationCount() + ")");
                reservedTitles++;
            }
            if (book.getAvailableCopies() == 0) {
                outOfStockTitles++;
                System.out.println(" Out of Stock: " + book.getTitle());
            }
        }

        System.out.println("\n--- STOCK SUMMARY ---");
        System.out.println("Total Distinct Titles: " + totalDistinctTitles);
        System.out.println("Total Available Copies (Across all books): " + totalAvailableCopies);
        System.out.println("Number of Titles Currently Out of Stock: " + outOfStockTitles);
        System.out.println("Number of Titles with Active Reservations: " + reservedTitles);
        System.out.println("----------------------------------------");
    }
}
