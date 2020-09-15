//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 133
//10193369 / 6098253
//I swear that this is my work, please believe me

import java.util.InputMismatchException;
import java.util.Scanner;

class InvalidHrException extends Exception {
    private String message;
    
    //default constructor
    public InvalidHrException() {
        
    }
    
    //other constructor
    public InvalidHrException(String str) {
        this.message = str;
    }
    
    //accessor method
    public String getMessage() {
        return message;
    }
    
    //mutator method
    public String toString() {
        return getMessage();
    }
}

class InvalidMinException extends Exception {
    private String message;
    
    //default constructor
    public InvalidMinException() {
        
    }
    
    //other constructor
    public InvalidMinException(String str) {
        this.message = str;
    }
    
    //accessor method
    public String getMessage() {
        return message;
    }
    
    //mutator method
    public String toString() {
        return getMessage();
    }
}

class InvalidSecException extends Exception {
    private String message;
    
    //default constructor
    public InvalidSecException() {

    }
    
    //other constructor
    public InvalidSecException(String str) {
        this.message = str;
    }
    
    //accessor method
    public String getMessage() {
        return message;
    }
    
    //mutator method
    public String toString() {
        return getMessage();
    }
}

class Shafiq_133_Lab_4 {
    private static Scanner console = new Scanner(System.in);

    public static void main(String[] args) {
        int h = 0, m = 0, s = 0;
        String d = null;
        boolean correct = false;
        
        //for all hours, minutes and seconds input
        //an InputMismatchException is added to check
        //whether the input is a valid integer
        //on top of the user-defined exceptions
        while (!correct) {
            try {
                h = getHours();
                correct = true;
            }           
            catch (InvalidHrException e) {
                System.out.println(e.toString());
                correct = false;
            }
            catch (InputMismatchException e) {
                System.out.println("Enter a valid integer");
                console.nextLine();
            }
        }    
        
        correct = false;
        
        while (!correct) {
            try {
                m = getMinutes();
                correct = true;
            }
            catch (InvalidMinException e) {
                System.out.println(e.toString());
                correct = false;
            }
            catch (InputMismatchException e) {
                System.out.println("Enter a valid integer");
                console.nextLine();
            }
        }    
        
        correct = false;
        
        while (!correct) {
            try {
                s = getSeconds();
                correct = true;
            }
            catch (InvalidSecException e) {
                System.out.println(e.toString());
                correct = false;
            }
            catch (InputMismatchException e) {
                System.out.println("Enter a valid integer");
                console.nextLine();
            }
        }
        
        correct = false;
        
        //AM and PM are also checked to ensure that only AM or PM is entered
        while (!correct) {
            System.out.print("Enter AM or PM: ");
            d = console.next();
            
            //acts as a buffer for any input after the first space
            console.nextLine();
        
            if ((d.toLowerCase().equals("am")) || (d.toLowerCase().equals("pm"))) {
                correct = true;
            }
            else {
                correct = false;
            }
        }
        System.out.println();
        
        //prints the 24-hr clock
        print24(h, m, s, d);
    }
    
    //for all hours, minutes and seconds
    //the input is received through these methods
    //and a check is also made through the user-defined exceptions
    public static int getHours() throws InvalidHrException {
        System.out.print("Enter hours: ");
        int hours = console.nextInt();
        
        //acts as a buffer for any input after the first space
        console.nextLine();
        
        //hour is to be entered from 1 - 12
        //to ensure there is no 00pm
        if ((hours < 1) || (hours > 12)) {
            throw new InvalidHrException("The value of hours must be from 1 - 12");
        }
        
        return hours;
    }
    
    public static int getMinutes() throws InvalidMinException {
        System.out.print("Enter minutes: ");
        int mins = console.nextInt();
        
        //acts as a buffer for any input after the first space
        console.nextLine();
        
        //minutes to be entered from 0 - 59
        //to ensure that the hours stay true
        //to what user wants the hours to be
        //eg. 14:00:00 will not turn into 15:00:00 if 60 is entered
        if ((mins < 0) || (mins > 59)) {
            throw new InvalidMinException("The value of minutes must be from 0 - 59");
        }
        
        return mins;
    }
    
    public static int getSeconds() throws InvalidSecException {
        System.out.print("Enter seconds: ");
        int secs = console.nextInt();
        
        //acts as a buffer for any input after the first space
        console.nextLine();
        
        //seconds to be entered from 0 - 59
        //to ensure that the minutes stay true
        //to what the user wants the minutes to be
        //eg. 13:26:00 will not turn into 13:27:00 if 60 is entered
        if ((secs < 0) || (secs > 59)) {
            throw new InvalidSecException("The value of minutes must be from 0 - 59");
        }
        
        return secs;
    }
    
    //method to convert given time to 24hrs
    public static void print24(int hr, int min, int sec, String str) {
        //adds 12 to the hours if PM is entered and it is not 12
        if ((str.toLowerCase().equals("pm")) && (hr != 12)) {
            hr = hr + 12;
        }
        
        //subtracts 12 from 12 is AM is entered
        else if ((str.toLowerCase().equals("am")) && (hr == 12)) {
            hr = hr - 12;
        }
        
        System.out.printf("24 hour clock time: %02d:%02d:%02d\n", hr, min, sec);
    }
}