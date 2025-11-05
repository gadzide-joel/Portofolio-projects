/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package pokemon.battle;

/**
 * Concrete class representing a Fire-type Pokémon.
 * Defines specific damage multipliers based on the target's type:
 * - 2x damage against Plant
 * - 0.5x damage against Fire and Water
 * - 1x damage against Normal
 */
public class PokemonFire extends Pokemon {

    public PokemonFire(String name, int hp, int atk) {
        super(name, hp, atk);
    }
    
    // --- Attack Implementations (Type effectiveness) ---
    
    @Override
    public void attack(PokemonNormal p) {
    // 1x damage (No type multiplier)
    if (!this.isDead() && !p.isDead()) {
        p.hp -= this.atk; // Use base ATK
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + this.atk + " damage!");
        } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonFire p) {
    // 0.5x damage (Not very effective)
    if (!this.isDead() && !p.isDead()) {
        // Corrected calculation for 0.5x damage: (int)(ATK * 0.5)
        int damage = (int)(this.atk * 0.5); 
        p.hp -= damage;
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + damage + " damage!");
    } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonWater p) {
    // 0.5x damage (Not very effective - Water resists Fire)
    if (!this.isDead() && !p.isDead()) {
        // Corrected calculation for 0.5x damage: (int)(ATK * 0.5)
        int damage = (int)(this.atk * 0.5); 
        p.hp -= damage;
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + damage + " damage!");
    } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonPlant p) {
    // 2.0x damage (Super effective - Fire is strong against Plant)
    if (!this.isDead() && !p.isDead()) {
        // Corrected calculation for 2.0x damage
        int damage = (int)(this.atk * 2.0); 
        p.hp -= damage;
        if (p.hp < 0) p.hp = 0;
        // NOTE: The original code printed 'this.atk' here instead of 'damage'. 
        // I have corrected it to print the actual calculated 'damage' for consistency.
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + damage + " damage!");
        } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

}