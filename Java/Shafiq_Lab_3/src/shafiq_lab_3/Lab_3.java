//Mohamed Shafiq bin Roslan
//Full Time
//Group 3
//10193369
//6098253
//I swear that this is my work, please believe me

package shafiq_lab_3;

import java.util.Scanner;
class Lab_3 {
    
    public static void main (String[] args) {
        
        String station, petrol;
        double litres, price;
        int discount;
        
        Scanner input = new Scanner(System.in);
        
        System.out.print("Enter name of petrol station: ");
        station = input.nextLine();
        
        System.out.print("Enter type of petrol: ");
        petrol = input.nextLine();
        
        System.out.print("Enter quantity in litres: ");
        litres = input.nextDouble();
        input.nextLine();

        System.out.print("Enter price of petrol: ");
        price = input.nextDouble();
        input.nextLine();
        
        System.out.print("Enter total discount: ");
        discount = input.nextInt();
        input.nextLine();
        
        Petrol_Purchase p = new Petrol_Purchase (station, petrol, price, litres, discount);
        p.printInfo();
    }
}

class Petrol_Purchase {
    
    //instance variables
    private String station, petrol;
    private double price, litres;
    private int discount;
    
    //constructors
    public Petrol_Purchase(String station, String petrol, double litres,double price, int discount) {
            this.station = station;
            this.petrol = petrol;
            this.litres = litres;
            this.price = price;
            this.discount = discount;
    }
            
    
    private void setInfo(String station, String petrol, double litres, double price, int discount) {
        station = station;
        petrol = petrol;
        litres = litres;
        price = price;
        discount = discount;
    }
    
    //accessor methods
    public String getStation () {
        return station;
    }
    
    public String getPetrol () {
        return petrol;
    }
    
    public double getLitres () {
        return litres;
    }
    
    public double getPrice () {
        return price;
    }
    
    public int getDiscount () {
        return discount;
    }
    
    //calculates the total cost of petrol
    public double getCost (double litres, double price) {
        double petrol_cost = litres * price;
        return petrol_cost;
    }
    
    //calculates the discount
    public double getDiscount (int discount, double petrol_cost) {
        double total_disc = petrol_cost * discount/100;
        return total_disc;
    }
    
    //calculates the price after discount
    public double getPayment (double petrol_cost, double total_disc) {
        double final_price = (petrol_cost - total_disc);
        return final_price;
    }
    
    //prints the summary of purchase
    public void printInfo () {
        
        double petrol_cost = getCost(litres, price);
        double total_disc = getDiscount(discount, petrol_cost);
        double final_price = getPayment(petrol_cost, total_disc);
        
        System.out.println();
        System.out.println("Summary of Your Purchase");
        System.out.println("Petrol Station: " + station);
        System.out.println("Petrol Type: " + petrol);
        System.out.println("Total litres: " + (String.format("%.2f", litres)));
        System.out.println("Actual cost: " + (String.format("%.2f", petrol_cost)));
        System.out.println("Discount (" + discount + "%): " + (String.format("%.2f", total_disc)));
        System.out.println("Amount to pay: " + (String.format("%.2f", final_price)));
    }
    
}
