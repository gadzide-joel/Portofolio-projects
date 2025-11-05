/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package store.project;

/**
 * Main class to test the inventory management system.
 */
public class Store {

    public static void main(String[] args) {
        
        // Create an Item instance (Article)
        Item item = new Item("A112","table",10,5,false); 
        
       item.display();
       
       // 1. Restock 2 units (10 + 2 = 12)
       item.restock(2); 
       item.display();
       
       // 2. De-stock 5 units (12 - 5 = 7). 7 > Safety Stock (5), so it's allowed.
       item.deStock(5); 
       item.display();
       
       // 3. De-stock 6 units (7 - 6 = 1). 1 < Safety Stock (5) and allowUnderStock is false. 
       // The setter should block this operation, keeping the quantity at 7.
       item.deStock(6); 
       item.display();
           
       }   
}
