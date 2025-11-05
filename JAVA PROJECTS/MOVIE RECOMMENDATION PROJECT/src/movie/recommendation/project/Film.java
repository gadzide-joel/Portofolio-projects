/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package movie.recommendation.project;

/**
 *
 * @author USER
 */
// Definition of a Film class to represent a movie
class Film {
    // Movie attributes
    private String title;
    private String director;
    private int year;
    private String genre;
    private double rating;

    // Movie constructor
    public Film(String title, String director, int year, String genre, double rating) {
        // Initialize movie attributes
        this.title = title;
        this.director = director;
        this.year = year;
        this.genre = genre;
        this.rating = rating;
    }

    // toString method to display movie information
    @Override
    public String toString() {
        // Return a string representing the movie
        return title + " - Directed by " + director + " (" + year + ") - Genre: " + genre + " - Rating: " + rating;
    }

    // Getters to access movie attributes
    public String getTitle() { return title; }
    public String getGenre() { return genre; }
    public String getDirector() { return director; }
    public int getYear() { return year; }
    public double getRating() { return rating; }
}