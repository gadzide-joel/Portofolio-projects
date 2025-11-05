/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package oop.library.management.system;

/**
 *
 * @author USER
 */
import java.util.LinkedList;
import java.util.Queue;

/**
 * Represents a book in the library catalog.
 * It manages the number of available copies and the queue for reservations.
 */
public class Book {
    private String title;
    private Author author;
    private String isbn;
    private int availableCopies; // Number of copies currently available for loan
    private Queue<String> reservationQueue; // Holds patron IDs for reservations (FIFO structure)

    /**
     * Constructor for the Book class.
     * @param title The title of the book.
     * @param author The Author object associated with the book.
     * @param isbn The International Standard Book Number.
     * @param availableCopies The initial number of copies in stock.
     */
    public Book(String title, Author author, String isbn, int availableCopies) {
        this.title = title;
        this.author = author;
        this.isbn = isbn;
        this.availableCopies = availableCopies;
        this.reservationQueue = new LinkedList<>(); // Initialize the reservation queue
    }

    // --- LOAN / RETURN LOGIC ---

    /**
     * Attempts to borrow one copy of the book.
     * @return true if a copy was successfully borrowed (stock > 0), false otherwise.
     */
    public boolean borrow() {
        if (availableCopies > 0) {
            availableCopies--;
            return true;
        }
        return false;
    }

    /**
     * Returns one copy of the book, increasing the available stock.
     */
    public void returnBook() {
        availableCopies++;
    }

    // --- RESERVATION LOGIC (NEW) ---
    
    /**
     * Adds a patron to the reservation queue.
     * @param patronId The unique identifier of the patron making the reservation.
     */
    public void reserve(String patronId) {
        if (!reservationQueue.contains(patronId)) {
            reservationQueue.offer(patronId); // Add to the end of the queue (FIFO)
            System.out.println("-> Reservation added for patron " + patronId + " for '" + title + "'.");
        } else {
            System.out.println("-> Patron " + patronId + " already has a reservation for this book.");
        }
    }

    /**
     * Processes the next reservation in the queue.
     * This is typically called after a copy of the book has been returned.
     * @return The ID of the next patron in line, or null if the queue is empty.
     */
    public String processNextReservation() {
        return reservationQueue.poll(); // Retrieves and removes the head of the queue
    }

    // --- GETTERS ---
    
    public String getTitle() {
        return title;
    }

    public int getAvailableCopies() {
        return availableCopies;
    }
    
    public int getReservationCount() {
        return reservationQueue.size();
    }
    
    /**
     * Provides a detailed string representation of the Book's current status.
     */
    @Override
    public String toString() {
        return "Title: " + title +
               " Author: " + author +
               " ISBN: " + isbn +
               " Available: " + availableCopies +
               " Reservations: " + reservationQueue.size();
    }
}
