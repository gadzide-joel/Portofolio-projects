/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package store.project;

/**
 * Represents an item or product in the store's inventory.
 */
public class Item {

    private String reference;
    private String label;
    private int availableQuantity;
    private int safetyStock;
    private boolean allowUnderStock;

    public Item(String reference, String label, int availableQuantity, int safetyStock, boolean allowUnderStock) {
        this.reference = reference;
        this.label = label;
        this.availableQuantity = availableQuantity;
        this.allowUnderStock = allowUnderStock;
        this.safetyStock = safetyStock;
    }

    // --- Getters and Setters ---

    public int getAvailableQuantity() {
        return availableQuantity;
    }

    /**
     * Sets the available quantity, preventing the stock from falling below 
     * the safety stock level unless under-stocking is explicitly allowed.
     */
    public void setAvailableQuantity(int availableQuantity) {
        // If the new quantity is greater than or equal to the safety stock OR 
        // if under-stocking is allowed, update the quantity.
        if (availableQuantity >= this.safetyStock || this.allowUnderStock == true ) {
            this.availableQuantity = availableQuantity;
        }else{
            System.out.println("The quantity cannot be lower than the safety stock level.");
        }
    }

    public int getSafetyStock() {
        return safetyStock;
    }

    /**
     * Sets the safety stock level. The current quantity must be greater than 
     * the new safety stock level, unless under-stocking is allowed.
     */
    public void setSafetyStock(int safetyStock) {
        // If the current quantity is greater than or equal to the new safety stock OR 
        // if under-stocking is allowed, update the safety stock.
        if (this.availableQuantity >= safetyStock || this.allowUnderStock == true ) {
            this.safetyStock = safetyStock;
        }else{
            System.out.println("The safety stock cannot be set higher than the current quantity unless under-stocking is permitted.");
        }
    }

    public String getReference() {
        return reference;
    }

    public void setReference(String reference) {
        this.reference = reference;
    }

    public boolean isAllowUnderStock() {
        return allowUnderStock;
    }

    public void setAllowUnderStock(boolean allowUnderStock) {
        this.allowUnderStock = allowUnderStock;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }
    
    // --- Inventory Management Methods ---
    
    /**
     * Adds the specified quantity to the available stock (restock).
     */
    public void restock(int quantity) {
        int newQuantity = this.availableQuantity + quantity;
        this.setAvailableQuantity(newQuantity);
    }
    
    /**
     * Removes the specified quantity from the available stock (de-stock/ship).
     */
    public void deStock(int quantity){
       int newQuantity = this.availableQuantity - quantity;
       this.setAvailableQuantity(newQuantity);  
       
    }
    
    /**
     * Prints the current item details.
     */
    public void display(){
        System.out.println("Available quantity: "+this.availableQuantity
                         + ", Safety stock: " +this.safetyStock
                         + " Label: " +this.label
                         + " Reference: "+ this.reference );
    }

}