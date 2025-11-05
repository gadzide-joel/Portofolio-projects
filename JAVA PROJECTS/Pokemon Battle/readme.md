# Pokémon Battle System (Java OOP Summary)
This project simulates a simplified Pokémon combat system in Java, focused on demonstrating key Object-Oriented Programming (OOP) concepts, primarily Inheritance and Polymorphism.

# Core Architecture
The system uses a class hierarchy to manage the combat mechanics:

Pokemon.java: This is the abstract base class (Parent). It defines common attributes like name, hp, and atk. It uses abstract methods to ensure all subclasses implement their own battle logic.

Pokemon[Type].java: These are the concrete subclasses (Fire, Water, Plant, Normal). They inherit from Pokemon and override the attack methods. This is where the core logic of type effectiveness is implemented.

Main.java: The main runner class. It initializes various Pokémon instances and orchestrates a series of test battles to showcase how the different type attacks interact.

# Battle Mechanics: Type Effectiveness
The core feature is the implementation of type-based damage multipliers (Polymorphism):

When a Pokémon attacks, the system calls the specialized attack() method for that specific type.

Super Effective (2.0x): The attack deals double damage against certain types (e.g., Fire attacks Plant).

Not Very Effective (0.5x): The attack deals half damage against certain types (e.g., Fire attacks Water or Fire).

Neutral (1.0x): Normal-type attacks always deal neutral damage.

The system also includes checks (isDead()) to prevent a Pokémon from attacking if its HP is zero.