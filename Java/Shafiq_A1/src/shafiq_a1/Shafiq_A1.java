//Mohamed Shafiq bin Roslan
//10193369
//6098253
//I swear that this is my work, please believe me

package shafiq_a1;

import java.util.Scanner;
public class Shafiq_A1 {
    
    public static void main(String[] args) {
        
        //declare each variable to be used
        int fourthquan;
        int fifthquan;
        int sixthquan;
        double fourthprice;
        double fifthprice;
        double sixthprice;
        int fourthsold;
        int fifthsold;
        int sixthsold;
        int fourthbal;
        int fifthbal;
        int sixthbal;
        int fourthorder;
        int fifthorder;
        int sixthorder;
        double fourthcost;
        double fifthcost;
        double sixthcost;
        double fourthgst;
        double fifthgst;
        double sixthgst;
        double subtotal;
        double subtotalgst;
        double total;
        
        
        //print information to be seen by user, gets input from user
        System.out.println("Welcome to M Shafiq B R Bookstore!");
        System.out.printf("%6s", "ABC's Book Information\n");
        
        Scanner input = new Scanner(System.in);
        System.out.print("\n4th Edition quantity and price: ");
        fourthquan = input.nextInt();
        fourthprice = input.nextDouble();
        input.nextLine();
        
        System.out.print("5th Edition quantity and price: ");
        fifthquan = input.nextInt();
        fifthprice = input.nextDouble();
        input.nextLine();
        
        System.out.print("6th Edition quantity and price: ");
        sixthquan = input.nextInt();
        sixthprice = input.nextDouble();
        input.nextLine();
        
        fourthsold = 0;
        fifthsold = 0;
        sixthsold = 0;
        
        fourthbal = fourthquan;
        fifthbal = fifthquan;
        sixthbal = sixthquan;
        
        //task 1
        
        //Displays information received by user
        System.out.println();
        System.out.println("#################################################\n");
        System.out.println("M Shafiq B R Bookstore Online Order\n");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "Item", "Quantity", "Unit($)", "Sold", "Balance");
        System.out.println("\n------------------------------------------------");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "4th Edition", fourthquan, (String.format("%.2f", fourthprice)), fourthsold, fourthbal);
        System.out.println("");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "5th Edition", fifthquan, (String.format("%.2f", fifthprice)), fifthsold, fifthbal);
        System.out.println("");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "4th Edition", sixthquan, (String.format("%.2f", sixthprice)), sixthsold, sixthbal);
        System.out.println("\n");
        System.out.println("################################################\n");
        
        //task 2
        
        //Receives order by user
        System.out.println("Please place your orders:\n");
        
        System.out.print("No. of 4th Edition: ");
        fourthorder = input.nextInt();
        input.nextLine();
        
        System.out.print("No. of 5th Edition: ");
        fifthorder = input.nextInt();
        input.nextLine();
        
        System.out.print("No. of 6th Edition: ");
        sixthorder = input.nextInt();
        input.nextLine();
        
        //Calculates total cost of each edition ordered by user
        fourthcost = fourthorder * fourthprice;
        fifthcost = fifthorder * fifthprice;
        sixthcost = sixthorder * sixthprice;
        
        //Calculates GST of each edition
        fourthgst = (Math.floor((fourthcost * 0.07) * 100) / 100);
        fifthgst = (Math.floor((fifthcost* 0.07) * 100) / 100);
        sixthgst = (Math.floor((sixthcost * 0.07) * 100) / 100);
        
        //Calculates the total of subtotal, GST and sum of both
        subtotal = fourthcost + fifthcost + sixthcost;
        subtotalgst = fourthgst + fifthgst + sixthgst;
        
        total = subtotal + subtotalgst;
        
        //Displays the information of the orders
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "Item", "Quantity", "Cost($)", "GST(7%)");
        System.out.println("\n------------------------------------------");
        System.out.printf("%-15s %-9s %-7s %-7s", "4th Edition", fourthorder, (String.format("%.2f", fourthcost)), (String.format("%.2f", fourthgst)));
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "5th Edition", fifthorder, (String.format("%.2f", fifthcost)), (String.format("%.2f", fifthgst)));
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "6th Edition", sixthorder, (String.format("%.2f", sixthcost)), (String.format("%.2f", sixthgst)));
        System.out.println("\n===========================================");
        System.out.printf("%-15s %-9s %-7s %-7s", "Subtotal Cost:", "****", (String.format("%.2f", subtotal)), (String.format("%.2f", subtotalgst)));
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "Total Cost:", "****", (String.format("%.2f", total)), "");
        System.out.println("\n");
        System.out.println("################################################\n");
        
        //task 3
        
        int temp;
        
        //Swaps the orders of the fourth and sixth editions
        temp = fourthorder;
        fourthorder = sixthorder;
        sixthorder = temp;
        
        //Calculates the cost of each edition
        fourthcost = fourthorder * fourthprice;
        fifthcost = fifthorder * fifthprice;
        sixthcost = sixthorder * sixthprice;
        
        //Calculates the GST of each edition order
        fourthgst = (Math.floor((fourthcost * 0.07) * 100) / 100);
        fifthgst = (Math.floor((fifthcost* 0.07) * 100) / 100);
        sixthgst = (Math.floor((sixthcost * 0.07) * 100) / 100);
        
        //Calculates the subtotal, total GST and sum of both
        subtotal = fourthcost + fifthcost + sixthcost;
        subtotalgst = fourthgst + fifthgst + sixthgst;
        
        total = subtotal + subtotalgst;
        
        //Displays the information
        System.out.printf("%-15s %-9s %-7s %-7s", "Item", "Quantity", "Cost($)", "GST(7%)");
        System.out.println("\n------------------------------------------");
        System.out.printf("%-15s %-9s %-7s %-7s", "4th Edition", fourthorder, (String.format("%.2f", fourthcost)), (String.format("%.2f", fourthgst)));
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "5th Edition", fifthorder, (String.format("%.2f", fifthcost)), (String.format("%.2f", fifthgst)));
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "6th Edition", sixthorder, (String.format("%.2f", sixthcost)), (String.format("%.2f", sixthgst)));
        System.out.println("\n===========================================");
        System.out.printf("%-15s %-9s %-7s %-7s", "Subtotal Cost:", "****", (String.format("%.2f", subtotal)), (String.format("%.2f", subtotalgst)));
        System.out.println();
        System.out.printf("%-15s %-9s %-7s %-7s", "Total Cost:", "****", (String.format("%.2f", total)), "");
        System.out.println("\n");
        System.out.println("################################################\n");
        
        //task 4
        
        //Updating the number of books sold and how many are left
        fourthsold += fourthorder;
        fifthsold += fifthorder;
        sixthsold += sixthorder;
        
        fourthbal -= fourthorder;
        fifthbal -= fifthorder;
        sixthbal -= sixthorder;
        
        //Displays the current information after the update
        System.out.println("Summary of Available Stock\n");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "Item", "Quantity", "Unit($)", "Sold", "Balance");
        System.out.println("\n------------------------------------------------");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "4th Edition", fourthquan, (String.format("%.2f", fourthprice)), fourthsold, fourthbal);
        System.out.println("");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "5th Edition", fifthquan, (String.format("%.2f", fifthprice)), fifthsold, fifthbal);
        System.out.println("");
        System.out.printf("%-13s %-9s %-7s %-7s %-10s", "4th Edition", sixthquan, (String.format("%.2f", sixthprice)), sixthsold, sixthbal);
        System.out.println("\n");
        System.out.println("################################################\n");
        
    }
    
}