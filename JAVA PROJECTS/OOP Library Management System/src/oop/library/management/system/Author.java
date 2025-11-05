/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package oop.library.management.system;

/**
 *
 * @author USER
 */
/**
 * Represents the author of a book.
 * This class primarily holds descriptive information about the author.
 */
public class Author {
    private String name;
    private String nationality;

    /**
     * Constructor to initialize an Author object.
     * @param name The name of the author.
     * @param nationality The nationality of the author.
     */
    public Author(String name, String nationality) {
        this.name = name;
        this.nationality = nationality;
    }

    // --- GETTERS ---
    
    public String getName() {
        return name;
    }

    /**
     * Provides a clean, readable string representation of the Author.
     * @return A string with the author's name and nationality.
     */
    @Override
    public String toString() {
        return name + " (" + nationality + ")";
    }
}