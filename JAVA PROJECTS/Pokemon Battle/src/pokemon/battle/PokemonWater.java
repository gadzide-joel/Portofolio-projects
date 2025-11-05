/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package pokemon.battle;

/**
 * Concrete class representing a Water-type Pokémon.
 * Defines specific damage multipliers based on the target's type:
 * - 2x damage against Fire
 * - 0.5x damage against Water and Plant
 * - 1x damage against Normal
 */
public class PokemonWater extends Pokemon {

    public PokemonWater(String name, int hp, int atk) {
        super(name, hp, atk);
    }

    // --- Attack Implementations (Type effectiveness) ---

    @Override
    public void attack(PokemonNormal p) {
        // 1x damage (No type multiplier)
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
    public void attack(PokemonFire p) {
    // 2x damage (Super effective - Water is strong against Fire)
    if (!this.isDead() && !p.isDead()) {
        int damage = (int)(this.atk * 2); 
        p.hp -= damage;
        if (p.hp < 0) p.hp = 0;
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + damage + " damage!");
        
        // These lines were in your original code and are kept here for reference, 
        // but they are generally verbose for a simple battle log.
        // System.out.println("Full class name of attacker: " + this.getClass().getName());
        // System.out.println("Full class name of attacked class: " + p.getClass().getName());
        
    } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
    
}

    @Override
    public void attack(PokemonWater p) {
    // 0.5x damage (Not very effective - Water resists Water)
    if (!this.isDead() && !p.isDead()) {
        int damage = (int)(this.atk * 0.5);
        
        // Original logic checked for damage <= 0, but since ATK is int > 0, 
        // (int)(ATK * 0.5) will only be 0 if ATK is 0 or 1, which is unlikely 
        // for an active attacker. Simplifying the check.
        if (damage <= 0) { 
            // Ensures minimum 1 damage if ATK > 0, but sticking to original logic:
            if (this.atk > 0 && damage == 0) damage = 1; // Optional: ensure minimum 1 damage
            p.hp = Math.max(0, p.hp - damage); // Use Math.max for conciseness
        } else {
            p.hp -= damage;
        }
        if (p.hp < 0) p.hp = 0; // Final check
        
        System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + damage + " damage!");
    } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonPlant p) {
    // 0.5x damage (Not very effective - Plant resists Water)
    if (!this.isDead() && !p.isDead()) {
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

}