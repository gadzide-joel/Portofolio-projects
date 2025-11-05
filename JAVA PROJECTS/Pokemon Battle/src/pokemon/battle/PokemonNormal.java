/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package pokemon.battle;


/**
 * Concrete class representing a Normal-type Pokémon.
 * Normal-type attacks have no specific damage multiplier against other types 
 * in this simplified implementation.
 */
public class PokemonNormal extends Pokemon {

    public PokemonNormal(String name, int hp, int atk) {
        super(name, hp, atk);
    }
    
    // --- Attack Implementations (No type advantage/disadvantage) ---
    
    @Override
    public void attack(PokemonNormal p) {
    // Check if both the attacker and the defender are alive
    if (!this.isDead() && !p.isDead()) {
        p.hp -= this.atk; // Base damage is simply the attacker's ATK
        if (p.hp < 0) p.hp = 0; // Ensure HP doesn't go below zero
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + this.atk + " damage!");
        } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonFire p) {
    if (!this.isDead() && !p.isDead()) {
        p.hp -= this.atk;
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + this.atk + " damage!");
        } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonWater p) {
    if (!this.isDead() && !p.isDead()) {
        p.hp -= this.atk;
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + this.atk + " damage!");
        } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonPlant p) {
    if (!this.isDead() && !p.isDead()) {
        p.hp -= this.atk;
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + this.atk + " damage!");
        } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}
}
