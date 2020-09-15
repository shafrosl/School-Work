//Mohamed Shafiq bin Roslan
//10193369
//6098253
//I swear that this is my work, please believe me

package shafiq_lab_2;

import java.util.Scanner;
public class Shafiq_Lab_2 {
    
    public static void main(String[] args) {
        //declaring all variables used
            double numb1;
            double numb2;
            double numb3;
            double numb4;
            double numb5;
            double largest;
            double smallest;
            double sum;
            double average;
        
        //reading the input to be stored as first number
        //and setting first number to be the largest and smallest number
        Scanner input = new Scanner(System.in);
        System.out.print("Enter first integer: ");
        numb1 = input.nextDouble();
        largest = numb1;
        smallest = numb1;
        
        //reading second number
        //comparing largest and smallest number with the second number
        System.out.print("Enter second integer: ");
        numb2 = input.nextDouble();
        largest = (Math.max(largest, numb2));
        smallest = (Math.min(smallest, numb2));
        
        //reading third number
        //comparing largest and smallest number with the third number
        System.out.print("Enter third integer: ");
        numb3 = input.nextDouble();
        largest = (Math.max(largest, numb3));
        smallest = (Math.min(smallest, numb3));
        
        //reading fourth number
        //comparing largest and smallest number with the fourth number
        System.out.print("Enter fourth integer: ");
        numb4 = input.nextDouble();
        largest = (Math.max(largest, numb4));
        smallest = (Math.min(smallest, numb4));
        
        //reading fifth number
        //comparing largest and smallest number with the fifth number
        System.out.print("Enter fifth integer: ");
        numb5 = input.nextDouble();
        largest = (Math.max(largest, numb5));
        smallest = (Math.min(smallest, numb5));
        
        //combining the sum of numbers
        //counting the average of the total numbers
        sum = numb1 + numb2 + numb3 + numb4 + numb5;
        average = sum/5;
        
        //printing the results
        System.out.println("");
        System.out.println("Analysis Results:");
        System.out.println("Largest number is: " + largest);
        System.out.println("Smallest number is: " + smallest);
        System.out.println("The total sum of numbers is: " + sum);
        System.out.println("The average is: " + average);
    }
    
}
