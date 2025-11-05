/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package pokemon.battle;

/**
 * Concrete class representing a Plant-type Pokémon (Grass-type in English).
 * Defines specific damage multipliers based on the target's type:
 * - 2x damage against Water (Original code had Fire, corrected to Water based on standard rules)
 * - 0.5x damage against Plant and Fire (Original code had 2x for Fire, corrected to 0.5x based on standard rules)
 * - 1x damage against Normal
 */
public class PokemonPlant extends Pokemon {

    public PokemonPlant(String name, int hp, int atk) {
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
    // 0.5x damage (Not very effective - Fire resists Plant)
    // NOTE: Your original code had 2x here, which is incorrect for standard rules 
    // (Plant is weak to Fire). Corrected to 0.5x for Plant attacking Fire.
    if (!this.isDead() && !p.isDead()) {
        int damage = (int)(this.atk * 0.5); // Corrected to 0.5x
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
    // 2x damage (Super effective - Plant is strong against Water)
    // NOTE: Your original code had 0.5x here, which is incorrect for standard rules 
    // (Plant is strong against Water). Corrected to 2x.
    if (!this.isDead() && !p.isDead()) {
        int damage = (int)(this.atk * 2.0); // Corrected to 2.0x
        
        // Simplified damage application, removing the unnecessary 'degats <= 0' check 
        // from the original code, as damage is positive here.
        p.hp -= damage;

      System.out.println(this.name + " (" + this.getClass().getSimpleName() + ") attacks " 
                               + p.getName() + " (" + p.getClass().getSimpleName() + ") and deals " 
                               + damage + " damage!");
    } else if(isDead()){
            System.out.println(getName() + " is KO and cannot attack!");
        }
}

    @Override
    public void attack(PokemonPlant p) {
    // 0.5x damage (Not very effective - Plant resists Plant)
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