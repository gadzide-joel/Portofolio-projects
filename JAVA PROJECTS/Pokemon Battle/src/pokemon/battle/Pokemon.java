/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package pokemon.battle;

/**
 * The abstract base class for all Pokémon types.
 * It defines common attributes and abstract methods for combat.
 */
public abstract class Pokemon {

    // Protected members allow subclasses to access them directly
    protected String name; 
    protected int hp; // Health Points (Points de Vie)
    protected int atk; // Attack Power (Force d'Attaque)

    public Pokemon(String name, int hp, int atk) {
        this.name = name;
        this.hp = hp;
        this.atk = atk;
    }

    // --- Getters (Accessors) ---

    public String getName(){
        return name;
    }
    
    public int getHp() {
        return hp;
    }

    public int getAtk() {
        return atk;
    }
    
    // --- Utility Methods ---
    
    /**
     * Checks if the Pokémon is defeated (HP is 0).
     * @return true if HP is 0, false otherwise.
     */
    public boolean isDead(){
        // The Pokémon is considered dead if its HP is exactly 0
        return (hp == 0);       
    }
    
    /**
     * Displays the current status of the Pokémon to the console.
     */
    public void display(){
        
        System.out.println(" Pokémon Name: " + this.name  + ";" + " Health Points: " + this.hp + ";" + " Attack Power: " + this.atk +";" + " Type: " + this.getClass().getSimpleName() + ", " + "Is it KO? : " + this.isDead());
        System.out.println("  Life status of " + this.name + " : " + (isDead() ? "KO" : "Alive"));
        
    }
   
    // --- Abstract Attack Methods (Polymorphism via Method Overloading) ---
    // Subclasses MUST implement all these specific attack methods.
    public abstract void attack(PokemonNormal p);
    public abstract void attack(PokemonFire p);
    public abstract void attack(PokemonWater p);
    public abstract void attack(PokemonPlant p);
    

}
