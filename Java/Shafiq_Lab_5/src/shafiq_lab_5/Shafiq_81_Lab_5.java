//Mohamed Shafiq bin Roslan
//Full Time
//Group 3
//Class List no. 81
//10193369
//6098253
//I swear that this is my work, please believe me

package shafiq_lab_5;

import java.util.Random;
import java.util.Scanner;
import java.util.InputMismatchException;

public class Shafiq_81_Lab_5 {
    
    private static int cor = 0;
    
    //random number generator
    private static int randGen() {
        Random r = new Random();
        return r.nextInt(10);
        }
    
    //gets two new random integers
    static void getTwoInteger(myInteger a, myInteger b){
        a.setInt(randGen());
        b.setInt(randGen());
        }
    
    //random operator generator using numbers
    //as cases for which operator to use
    private static char randOp() {
        char operator = 0;
        Random o = new Random();
        int a = o.nextInt(3);
        
        switch (a) {
            case 0:
                operator = '-';
                return operator;
            case 1:
                operator = '+';
                return operator;
            case 2:
                operator = '*';
                return operator;
        }
        return operator;
    }
    
    //checks the input with the correct answer
    //and returns true/false depending if you are right
    private static boolean mathCheck(int a, int b, char c, int answer) {
        int d;
        boolean check = false;
        
        switch (c) {
            case '-':
                d = a - b;
                if (answer == d) {
                    cor++;
                    check = true;
                    return check;
                }
                else {
                    return check;
                }
                
            case '+':
                d = a + b;
                if (answer == d) {
                    cor++;
                    check = true;
                    return check;
                }
                else {
                    return check;
                }    
                
            case '*':
                d = a * b;
                if (answer == d) {
                    cor++;
                    check = true;
                    return check;
                }
                else {
                    return check;
                }    
        }
        return check;
    }
    
    //prints statement depending if you got it right or not
    public static void printAnswer(int a, int b, char c, int answer) {
        boolean check = mathCheck(a, b, c, answer);
        if (check == true) {
            System.out.println("Correct answer!");
            }
        else {
            System.out.println("Wrong answer!");
        }
    }
    
    //counts the number of correct answers
    //and prints it along with a message
    public static void totalCor() {
        if (cor < 5) {
            System.out.println("Your score: " + cor + "/5, do better next time!");
        }
        else {
            System.out.println("Your score: 5/5, well done!");
        }
    }
    
    public static void main(String[] args) {
        
        Scanner input = new Scanner(System.in);
        int i = 0;
        int x = 1;
        
        System.out.println("Welcome to CSIT 111 Arithmetic World");
        System.out.println("You will solve 5 difficult arithmetic questions\n");
        
        //i is counting the number of questions printed for the user
        //once it reaches 5 questions, it will break out of the loop
        //and stop printing more questions
        while (i < 5) {
            char c = randOp();
            int answer = 0;
            boolean validInput = false;
            myInteger a = new myInteger();
            myInteger b = new myInteger();
            getTwoInteger(a, b);
            System.out.print("Question " + x +": " + a.getInt() + " " + c + " " + b.getInt() + " = ");
            
            //this is to catch an input that is not an integer
            //when an non-integer input is entered,
            //it will ask for a proper input
            while (validInput == false) {
                try {
                    answer = input.nextInt();
                    validInput = true;
                }
                catch (InputMismatchException e) {
                    System.out.print("Please enter a valid integer: ");
                }
                input.nextLine();
            }
            
            //checks the input against the answer in the system
            //increases count of question number
            printAnswer(a.getInt(), b.getInt(), c, answer);
            System.out.println("");
            i++;
            x++;
        }
        
        //prints results
        totalCor();      
    }
}


class myInteger {
    private int n;
    
    //default constructor
    public myInteger() {

    }
    
    //other constructor
    public myInteger(int n) {
        this.n = n;
    } 
    
    //accessor
    public int getInt() {
        return n;
    }
    
    //mutator
    public void setInt(int n) {
        this.n = n;
    }
}
