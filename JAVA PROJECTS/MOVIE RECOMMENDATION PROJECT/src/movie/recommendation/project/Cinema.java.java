/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package movie.recommendation.project;

/**
 *
 * @author USER
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.stream.Collectors;

// Definition of a Cinema class to manage the movie library
class Cinema {
    // Attributes of the movie library
    private List<Film> films;
    private List<String> availableGenres;
    private Scanner scanner;
    private Random random;

    // Constructor of the movie library
    public Cinema() {
        // Initialization of library attributes
        films = new ArrayList<>();
        scanner = new Scanner(System.in);
        random = new Random();
        
        // Initialization of available genres
        availableGenres = new ArrayList<>(List.of(
            "Action", "Comedy", "Drama", "Science-Fiction", 
            "Horror", "Animation", "Thriller", "Romance", 
            "Documentary", "Fantasy"
        ));

        // Initialization of the movie library with default films
        initializeFilms();
    }

    // Method to add a movie to the library
    public void addMovie(Film film) {
        // Add the movie to the library
        films.add(film);
    }

    // Method to recommend movies
    public void recommendMovies() {
        // Check if the movie library is empty
        if (films.isEmpty()) {
            // Display a message if the library is empty
            System.out.println("No movies in the library to make recommendations.");
            return;
        }

        // Display the recommendation menu
        System.out.println("\n--- Movie Recommendation ---");
        System.out.println("1. Recommend by genre");
        System.out.println("2. Recommend a random movie");
        System.out.println("3. Recommend by director");
        System.out.println("4. Recommend by year");
        System.out.println("5. Recommend by rating");
        System.out.println("6. Add a movie");
        System.out.println("7. Preference");
        System.out.print("Choose an option (1-7): ");
        
        // Input of the user's chosen option
        String choice = scanner.nextLine();
        
        // Process the selected option
        switch (choice) {
            case "1":
                // Recommend movies by genre
                recommendByGenre();
                break;
            case "2":
                // Recommend a random movie
                recommendRandomMovie();
                break;
            case "3":
                // Recommend movies by director
                recommendByDirector();
                break;
            case "4":
                // Recommend movies by year
                recommendByYear();
                break;
            case "5":
                // Recommend movies by rating
                recommendByRating();
                break;
            case "6":
                // Add a movie
                addMovieManually();
                break;
            case "7":
                // Preference
                preference();
                break;
            default:
                // Display a message if the option is invalid
                System.out.println("Invalid option.");
        }
    }

    // Method to recommend movies by genre
    private void recommendByGenre() {
        // Suggest available genres
        String genre = suggestGenres();
        
        // Filter movies of the chosen genre
        List<Film> moviesOfGenre = films.stream()
            .filter(film -> film.getGenre().equalsIgnoreCase(genre))
            .collect(Collectors.toList());
        
        // Check if any movies were found
        if (moviesOfGenre.isEmpty()) {
            // Display a message if no movie was found
            System.out.println("No movie found in this genre.");
            return;
        }
        
        // Display recommendations
        System.out.println("\n--- Recommendations for the genre " + genre + " ---");
        
        // Select up to 3 movies or all if fewer than 3
        int numberOfRecommendations = Math.min(3, moviesOfGenre.size());
        
        // Display recommendations
        for (int i = 0; i < numberOfRecommendations; i++) {
            Film recommendedMovie = moviesOfGenre.get(random.nextInt(moviesOfGenre.size()));
            System.out.println("Recommendation " + (i + 1) + ": " + recommendedMovie);
            moviesOfGenre.remove(recommendedMovie); // avoid duplicates
        }
    }

    // Method to recommend a random movie
    private void recommendRandomMovie() {
        // Check if the movie library is empty
        if (films.isEmpty()) {
            // Display a message if the library is empty
            System.out.println("No movies in the library.");
            return;
        }
        
        // Select a random movie
        Film recommendedMovie = films.get(random.nextInt(films.size()));
        
        // Display the recommended movie
        System.out.println("\n--- Random Recommendation ---");
        System.out.println("Recommended movie: " + recommendedMovie);
        
        // Recommend movies from the same genre
        List<Film> sameGenreMovies = films.stream()
            .filter(film -> film.getGenre().equals(recommendedMovie.getGenre()) && 
                    !film.getTitle().equals(recommendedMovie.getTitle()))
            .limit(2)
            .collect(Collectors.toList());
        
        // Check if any movies were found
        if (!sameGenreMovies.isEmpty()) {
            // Display recommendations
            System.out.println("\nOther movies in the same genre:");
            sameGenreMovies.forEach(System.out::println);
        }
    }

    // Method to recommend movies by director
    private void recommendByDirector() {
        // Suggest available directors
        String director = suggestDirectors();
        
        // Filter movies by the chosen director
        List<Film> moviesByDirector = films.stream()
            .filter(film -> film.getDirector().equalsIgnoreCase(director))
            .collect(Collectors.toList());
        
        // Check if any movies were found
        if (moviesByDirector.isEmpty()) {
            // Display a message if no movie was found
            System.out.println("No movie found for this director.");
            return;
        }
        
        // Display recommendations
        System.out.println("\n--- Recommendations for the director " + director + " ---");
        
        // Select up to 3 movies or all if fewer than 3
        int numberOfRecommendations = Math.min(3, moviesByDirector.size());
        
        // Display recommendations
        for (int i = 0; i < numberOfRecommendations; i++) {
            Film recommendedMovie = moviesByDirector.get(random.nextInt(moviesByDirector.size()));
            System.out.println("Recommendation " + (i + 1) + ": " + recommendedMovie);
            moviesByDirector.remove(recommendedMovie); // avoid duplicates
        }
    }

    // Method to recommend movies by year
    private void recommendByYear() {
        // Suggest available years
        int year = suggestYears();
        
        // Filter movies from the chosen year
        List<Film> moviesFromYear = films.stream()
            .filter(film -> film.getYear() == year)
            .collect(Collectors.toList());
        
        // Check if any movies were found
        if (moviesFromYear.isEmpty()) {
            // Display a message if no movie was found
            System.out.println("No movie found for this year.");
            return;
        }
        
        // Display recommendations
        System.out.println("\n--- Recommendations for the year " + year + " ---");
        
        // Select up to 3 movies or all if fewer than 3
        int numberOfRecommendations = Math.min(3, moviesFromYear.size());
        
        // Display recommendations
        for (int i = 0; i < numberOfRecommendations; i++) {
            Film recommendedMovie = moviesFromYear.get(random.nextInt(moviesFromYear.size()));
            System.out.println("Recommendation " + (i + 1) + ": " + recommendedMovie);
            moviesFromYear.remove(recommendedMovie); // avoid duplicates
        }
    }

    // Method to recommend movies by rating
    private void recommendByRating() {
        // Define rating bounds
        double minRating = 0;
        double maxRating = 10;
        
        // Loop to input the rating
        while (true) {
            // Display prompt to enter the rating
            System.out.println("\n--- Recommendation by Rating ---");
            System.out.println("Enter a rating between " + minRating + " and " + maxRating + ": ");
            
            // Input the rating
            try {
                double rating = Double.parseDouble(scanner.nextLine());
                
                // Check if the rating is within range
                if (rating >= minRating && rating <= maxRating) {
                    // Filter movies with the chosen rating
                    List<Film> moviesWithRating = films.stream()
                        .filter(film -> film.getRating() == rating)
                        .collect(Collectors.toList());
                    
                    // Check if any movies were found
                    if (moviesWithRating.isEmpty()) {
                        // Display a message if no movie was found
                        System.out.println("No movie found for this rating.");
                        return;
                    }
                    
                    // Display recommendations
                    System.out.println("\n--- Recommendations for rating " + rating + " ---");
                    
                    // Select up to 3 movies or all if fewer than 3
                    int numberOfRecommendations = Math.min(3, moviesWithRating.size());
                    
                    // Display recommendations
                    for (int i = 0; i < numberOfRecommendations; i++) {
                        Film recommendedMovie = moviesWithRating.get(random.nextInt(moviesWithRating.size()));
                        System.out.println("Recommendation " + (i + 1) + ": " + recommendedMovie);
                        moviesWithRating.remove(recommendedMovie); // avoid duplicates
                    }
                    
                    // Exit the loop
                    return;
                } else {
                    // Display a message if the rating is out of range
                    System.out.println("Invalid rating. Please try again.");
                }
            } catch (NumberFormatException e) {
                // Display a message if the input is not a number
                System.out.println("Please enter a valid number.");
            }
        }
    }

    // Method to add a movie manually
    private void addMovieManually() {
        // Display prompt to enter movie details
        System.out.println("\n--- Add a Movie ---");
        
        // Input movie title
        System.out.print("Enter the movie title: ");
        String title = scanner.nextLine();
        
        // Input movie genre
        System.out.print("Enter the movie genre: ");
        String genre = scanner.nextLine();
        
        // Input movie director
        System.out.print("Enter the movie director: ");
        String director = scanner.nextLine();
        
        // Input movie release year
        System.out.print("Enter the movie release year: ");
        int year = Integer.parseInt(scanner.nextLine());
        
        // Input movie rating
        System.out.print("Enter the movie rating (between 0 and 10): ");
        double rating = Double.parseDouble(scanner.nextLine());
        
        // Add the movie to the library
        addMovie(new Film(title, director, year, genre, rating));
        
        // Display confirmation message
        System.out.println("Movie added successfully!");
    }

    // Method to suggest available genres
    public String suggestGenres() {
        // Display available genres
        System.out.println("\nPlease choose a genre from the following:");
        
        // Display numbered genres
        for (int i = 0; i < availableGenres.size(); i++) {
            System.out.println((i + 1) + ". " + availableGenres.get(i));
        }
        
        // Input selected option
        while (true) {
            try {
                System.out.print("Enter the number of the desired genre: ");
                int choice = Integer.parseInt(scanner.nextLine());
                
                // Check if the option is valid
                if (choice > 0 && choice <= availableGenres.size()) {
                    // Return the selected genre
                    return availableGenres.get(choice - 1);
                } else {
                    // Display a message if the option is invalid
                    System.out.println("Invalid choice. Please try again.");
                }
            } catch (NumberFormatException e) {
                // Display a message if the input is not a number
                System.out.println("Please enter a valid number.");
            }
        }
    }

    // Method to suggest available directors
    public String suggestDirectors() {
        // Display available directors
        System.out.println("\nPlease choose a director from the following:");
        
        // Display numbered directors
        List<String> directors = films.stream()
            .map(Film::getDirector)
            .distinct()
            .collect(Collectors.toList());
        
        for (int i = 0; i < directors.size(); i++) {
            System.out.println((i + 1) + ". " + directors.get(i));
        }
        
        // Input selected option
        while (true) {
            try {
                System.out.print("Enter the number of the desired director: ");
                int choice = Integer.parseInt(scanner.nextLine());
                
                // Check if the option is valid
                if (choice > 0 && choice <= directors.size()) {
                    // Return the selected director
                    return directors.get(choice - 1);
                } else {
                    // Display a message if the option is invalid
                    System.out.println("Invalid choice. Please try again.");
                }
            } catch (NumberFormatException e) {
                // Display a message if the input is not a number
                System.out.println("Please enter a valid number.");
            }
        }
    }

    // Method to suggest available years
    public int suggestYears() {
        // Display available years
        System.out.println("\nPlease choose a year from the following:");
        
        // Display numbered years
        List<Integer> years = films.stream()
            .map(Film::getYear)
            .distinct()
            .collect(Collectors.toList());
        
        for (int i = 0; i < years.size(); i++) {
            System.out.println((i + 1) + ". " + years.get(i));
        }
        
        // Input selected option
        while (true) {
            try {
                System.out.print("Enter the number of the desired year: ");
                int choice = Integer.parseInt(scanner.nextLine());
                
                // Check if the option is valid
                if (choice > 0 && choice <= years.size()) {
                    // Return the selected year
                    return years.get(choice - 1);
                } else {
                    // Display a message if the option is invalid
                    System.out.println("Invalid choice. Please try again.");
                }
            } catch (NumberFormatException e) {
                // Display a message if the input is not a number
                System.out.println("Please enter a valid number.");
            }
        }
    }

    // Method to display the list of all movies
    public void displayAllMovies() {
        // Check if the movie library is empty
        if (films.isEmpty()) {
            // Display a message if the library is empty
            System.out.println("No movies in the library.");
            return;
        }
        
        // Display the movie list
        System.out.println("\n--- Movie List ---");
        films.forEach(System.out::println);
    }

    // Method to handle preferences
    private void preference() {
        // Display prompt to enter preferences
        System.out.println("\n--- Preference ---");
        
        // Input movie title
        System.out.print("Enter the title of the movie you prefer: ");
        String title = scanner.nextLine();
        
        // Input movie genre
        System.out.print("Enter the genre of the movie you prefer: ");
        String genre = scanner.nextLine();
        
        // Input movie director
        System.out.print("Enter the director of the movie you prefer: ");
        String director = scanner.nextLine();
        
        // Input movie release year
        System.out.print("Enter the release year of the movie you prefer: ");
        int year = Integer.parseInt(scanner.nextLine());
        
        // Input movie rating
        System.out.print("Enter the rating of the movie you prefer (between 0 and 10): ");
        double rating = Double.parseDouble(scanner.nextLine());
        
        // Filter movies matching the preferences
        List<Film> matchingMovies = films.stream()
            .filter(film -> film.getTitle().equalsIgnoreCase(title) && 
                    film.getGenre().equalsIgnoreCase(genre) && 
                    film.getDirector().equalsIgnoreCase(director) && 
                    film.getYear() == year && 
                    film.getRating() == rating)
            .collect(Collectors.toList());
        
        // Check if any movies were found
        if (matchingMovies.isEmpty()) {
            // Display a message if no movie was found
            System.out.println("No movie found matching your preference.");
            return;
        }
        
        // Display matching movies
        System.out.println("\n--- Movies matching your preference ---");
        matchingMovies.forEach(System.out::println);
    }

    // Method to display the main menu
    public void mainMenu() {
        // Loop to display the main menu
        while (true) {
            // Display the main menu
            System.out.println("\n--- Cinema Manager ---");
            System.out.println("1. Display all movies");
            System.out.println("2. Recommend movies");
            System.out.println("3. Exit");
            
            // Input selected option
            System.out.print("Choose an option (1-3): ");
            String choice = scanner.nextLine();
            
            // Process the selected option
            switch (choice) {
                case "1":
                    // Display the movie list
                    displayAllMovies();
                    break;
                case "2":
                    // Recommend movies
                    recommendMovies();
                    break;
                case "3":
                    // Exit the program
                    System.out.println("Thank you for using the Cinema Manager. Goodbye!");
                    return;
                default:
                    // Display a message if the option is invalid
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    // Method to initialize the movie library
    private void initializeFilms() {
        // Add default movies to the library
        addMovie(new Film("Inception", "Christopher Nolan", 2010, "Science-Fiction", 8.5));
        addMovie(new Film("Interstellar", "Christopher Nolan", 2014, "Science-Fiction", 8.2));
        addMovie(new Film("Matrix", "Lana Wachowski", 1999, "Science-Fiction", 8.1));
        addMovie(new Film("The Lion King", "Roger Allers", 1994, "Animation", 7.8));
        addMovie(new Film("Ratatouille", "Brad Bird", 2007, "Animation", 8.0));
        addMovie(new Film("The Godfather", "Francis Ford Coppola", 1972, "Drama", 8.4));
        addMovie(new Film("Pulp Fiction", "Quentin Tarantino", 1994, "Drama", 8.9));
        addMovie(new Film("Avengers", "Joss Whedon", 2012, "Action", 7.9));
        addMovie(new Film("John Wick", "Chad Stahelski", 2014, "Action", 8.1));
    }
}