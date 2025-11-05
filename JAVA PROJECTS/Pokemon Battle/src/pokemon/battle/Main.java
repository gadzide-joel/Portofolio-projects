/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package pokemon.battle;

/**
 * Main class to test the Pokémon battle system.
 */
public class Main {
    public static void main(String[] args) {
        // Create Pokémon instances (using English/standard names for clarity)
        PokemonNormal pikachu = new PokemonNormal("Pikachu", 100, 20); // Normal
        PokemonFire charmander = new PokemonFire("Charmander", 60, 25); // Fire
        PokemonWater squirtle = new PokemonWater("Squirtle", 90, 22); // Water
        PokemonPlant bulbasaur = new PokemonPlant("Bulbasaur", 85, 18); // Plant

        System.out.println("\n***Initial Pokémon Status***:");
        pikachu.display();
        charmander.display();
        squirtle.display();
        bulbasaur.display();

        System.out.println("\n***Start of Battles***:");
        
        // 1. Pikachu (Normal, 20 ATK) attacks Charmander (Fire, 60 HP) -> Normal vs Fire = 1x damage (20)
        pikachu.attack(charmander); 
        // Charmander HP: 60 - 20 = 40
        
        // 2. Bulbasaur (Plant, 18 ATK) attacks Squirtle (Water, 90 HP) -> Plant vs Water = 2x damage (18*2=36)
        // NOTE: This was corrected from the 0.5x in your original Plant code.
        bulbasaur.attack(squirtle); 
        // Squirtle HP: 90 - 36 = 54
        
        // 3. Squirtle (Water, 22 ATK) attacks Charmander (Fire, 40 HP) -> Water vs Fire = 2x damage (22*2=44)
        squirtle.attack(charmander); 
        // Charmander HP: 40 - 44 = -4 -> 0 (KO)
        
        // 4. Pikachu (Normal, 20 ATK) attacks Charmander (Fire, 0 HP) -> Should be blocked by isDead() check
        pikachu.attack(charmander); 
        
        
        System.out.println("\n***End of Battles and Final Pokémon Status***:");
        pikachu.display();
        charmander.display();
        squirtle.display();
        bulbasaur.display();
        
        System.out.println("\n***Test to verify if the Pokémon is KO***");
        System.out.println("**Start of a second battle**");
        
        // 5. Charmander (Fire, 0 HP) attacks Bulbasaur (Plant, 85 HP) -> Should be blocked because Charmander is KO
        charmander.attack(bulbasaur);
        
        System.out.println("**Displaying info of the KO Pokémon**");
        charmander.display();
    }
}