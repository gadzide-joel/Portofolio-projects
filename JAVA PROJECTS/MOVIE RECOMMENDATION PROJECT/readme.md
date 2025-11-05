# Java Project: Interactive Movie Recommendation System
This project is an Object-Oriented Programming (OOP) application in Java that simulates a cinema or streaming platform manager. It allows users to browse a catalog of films and receive personalized movie recommendations based on specific criteria.

# Core Architecture
The system is driven by a two-class design:

Film.java: This class is the primary data entity. It holds essential movie attributes such as title, director, year, genre, and a numeric rating.

Cinema.java: This is the central manager. It maintains the film catalog in an internal List and contains all the operational logic.

# Key Functionalities
The Cinema class manages an interactive console menu and implements the following features:

Catalog Initialization: A default list of movies, covering various genres (e.g., Science-Fiction, Drama, Animation), is loaded upon startup.

Full Browsing: Allows the user to display the entire film catalog with all details.

Recommendation Engine: The core feature. It prompts the user to enter a desired genre and a minimum rating. The system then efficiently filters the catalog to present only the films that meet the user's criteria.

User Interface: The application runs via a simple loop, allowing the user to easily navigate between browsing the catalog, requesting recommendations, or exiting the program.