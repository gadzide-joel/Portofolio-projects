# Java Project: Inventory Management System
This project is a small-scale Object-Oriented Programming (OOP) implementation in Java for managing product stock and enforcing inventory safety rules.

# Key Features
Item.java: The core class representing a product with properties like available quantity and safety stock level.

Safety Enforcement: The system strictly prevents the stock from falling below the safetyStock level during a withdrawal (deStock) unless the allowUnderStock flag is explicitly set to true. This logic is handled within the setter methods to ensure stock integrity.

Operations: Includes methods for adding stock (restock) and withdrawing stock (deStock), with automatic enforcement of the safety policy.

Store.java: Contains the main() method to test the inventory logic and demonstrate how stock controls block invalid operations.