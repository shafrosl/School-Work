//Mohamed Shafiq bin Roslan
//Full Time
//Group 3
//Class List no. 81
//10193369
//6098253
//I swear that this is my work, please believe me

package Main_A3;

import java.util.Random;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.InputMismatchException;

public class Shafiq_81_A3 {
    static Scanner input = new Scanner (System.in);
    static String [] Countries;
    static double [] average;
    
    //returns index position of highest average
    static int getHighA() {
        int j = 0;
        double highestAve = average [0];
        
        for (int i = 1; i < average.length; i++) {
            if (highestAve < average [i]) {
                highestAve = average [i];
                j = i;
            }
        }
        return j;
    }
    
    //returns index position of second highest average
    static int getHighB() {
        int j = 0;
        double highestAve = average [j];
        
        //to make sure the highest average is not chosen as a starter
        if (getHighA() == 0) {
            highestAve = average [j += 1];
        }
        
        //each element is checked up until the highest average
        //this is to ensure that the highest average is not chosen again
        for (int i = j + 1; i < getHighA(); i++) {
            if (highestAve < average [i]) {
                highestAve = average [i];
                j = i;
            }
        }
        
        //highest average is skipped and elements are compared
        //to other elements until the end of the array
        for (int i = (getHighA() + 1); i < average.length; i++) {
            if (highestAve < average [i]) {
                highestAve = average [i];
                j = i;
            }
        }
        return j;
    }    
    
    //returns the index position of third highest average
    static int getHighC() {
        int j = 0;
        double highestAve = average [j];
        int skip1;
        int skip2;
        
        //skips all the steps below if there are only 3 participants
        //and returns the index immediately
        if (MissWorld.size == 3) {
            if ((getHighA() == 1 && getHighB() == 0) || (getHighA() == 0 && getHighB() == 1)) {
                return 2;
            }
            if ((getHighA() == 2 && getHighB() == 0) || (getHighA() == 0 && getHighB() == 2)) {
                return 1;
            }
            if ((getHighA() == 1 && getHighB() == 2) || (getHighA() == 2 && getHighB() == 1)) {
                return 0;
            }
        }
        
        //to ensure that the two highest averages are not picked again
        if (getHighA() == 0 || getHighB() == 0) {
            highestAve = average [j += 1];
        }
        if ((getHighA() == 1 && getHighB() == 0) || (getHighA() == 0 && getHighB() == 1)){
            highestAve = average [j += 2];
        }
        
        //to find which index comes first
        //to be used in the next statement
        if (getHighA() < getHighB()) {
            skip1 = getHighA();
            skip2 = getHighB();
        }
        else {
            skip1 = getHighB();
            skip2 = getHighA();
        }
        
        //the two highest averages are skipped 
        //to ensure they are not picked again
        for (int i = j + 1; i < skip1; i++) {
            if (highestAve < average [i]) {
                highestAve = average [i];
                j = i;
            }
        }
        
        for (int i = (skip1 + 1); i < skip2; i++) {
            if (highestAve < average [i]) {
                highestAve = average [i];
                j = i;
            }
        }
        
        for (int i = (skip2 + 1); i < average.length; i++) {
            if (highestAve < average [i]) {
                highestAve = average [i];
                j = i;
            }
        }
        return j;
    }  
    
    //gets index of the highest average and returns the country
    static String getChampion(ArrayList <String> cList) {
    
        //Nest stage, transfer from ArrayList to array of String
	String [] listArray = new String [cList.size()];
	MissWorld.listToArray(cList, listArray);  

        return listArray[getHighA()];
    }
      
    //gets index of second highest average and returns the country
    static String getRunnerUp(ArrayList <String> cList) {
        
        //Nest stage, transfer from ArrayList to array of String
	String [] listArray = new String [cList.size()];
	MissWorld.listToArray(cList, listArray); 
        
        return listArray[getHighB()];
    }
    
    //gets the index of the third highest average and returns the country
    static String getSecUp(ArrayList <String> cList) {
        //Nest stage, transfer from ArrayList to array of String
	String [] listArray = new String [cList.size()];
	MissWorld.listToArray(cList, listArray); 
        
        return listArray[getHighC()];
    }    
    
    public static void main(String[] args) {
        boolean validInput = false;
        
        //creates a list to input the countries joining the competition
        ArrayList <String> cList = new ArrayList <String>();
        
        //gets input for how many participants there are in the competition
        System.out.println("Welcome to the Miss World Pageant!");
        System.out.print("Please enter how many countries that are participating: ");
        
        //catches an input that is not an integer
        //and asks for a proper input
        while (validInput == false) {
            try {
                MissWorld.size = input.nextInt();
                validInput = true;
            }
            catch (InputMismatchException e) {
                    System.out.print("Please enter a valid integer: ");
            }
            input.nextLine();
        }
        
        System.out.println("");
        
        //adds the country to the list
        for (int i = 0; i < MissWorld.size; i++) {
            cList.add(MissWorld.getCountry());
        }
			
	//to create an arrayList of models
	ArrayList <MissWorld> modelList = new ArrayList <MissWorld>();
			
	for (String m : cList)
            modelList.add (new MissWorld(m));
        
        //prints the table
        System.out.println("");
	System.out.printf("%-18s", "Countries");
        
        for (int i = 0; i <8; i++)
            System.out.printf("%1s%-7d", "J", (i + 1));
			
        System.out.printf("%-7s%n", "Average");
        
        //fills up the table with information
        for (MissWorld m : modelList)
            m.printInfo ();
        
        System.out.println("\nThe result is:");
        
        if (MissWorld.size == 1) {
            System.out.printf("%-1s%-1s%-2s%n", "Winner: ", "Miss ", getChampion(cList));
        }
        
        if (MissWorld.size == 2) {
            System.out.printf("%-11s%-1s%-2s%n", "Winner: ", "Miss ", getChampion(cList));
            System.out.printf("%-11s%-1s%-2s%n", "Runner-Up: ", "Miss ", getRunnerUp(cList));
        }
        
        if (MissWorld.size >= 3) {
            System.out.printf("%-18s%-1s%-2s%n", "Winner: ", "Miss ", getChampion(cList));
            System.out.printf("%-18s%-1s%-2s%n", "Runner-Up: ", "Miss ", getRunnerUp(cList));
            System.out.printf("%-18s%-1s%-2s%n", "Second Runner-Up: ", "Miss ", getSecUp(cList));
        }
    }
}

class MissWorld {
    static Scanner input = new Scanner (System.in);
    private String country;
    private double[] score;
    static int size;
    static int j = 0;
    
    //constructor
    public MissWorld(String country) {
        this.country = country;
        score = new double [8];
        Shafiq_81_A3.average = new double [size];
        
        getScore();
    } 
    
    //random number generator
    private static double randGen() {
        Random r = new Random();
        double randDouble = r.nextDouble() * 10;
        return randDouble;
    }
    
    //gets input for the countries participating
    public static String getCountry() {
        String country;
        
        System.out.print("Please enter the country where model is from: ");
        country = new String(input.nextLine());
        
        return country;
    }
    
    //fills the score with random doubles from 0 to 10
    private void getScore() {
        for (int i = 0; i < score.length; i++) {
            score [i] = randGen();
	}
    }    
    
    //searches for the lowest score
    private int getLowest() {
	double lowestMark = score [0];
        for (int i = 0; i < score.length; i++) {
            if (lowestMark > score [i]) {
                lowestMark = score [i];
            }
        }	
        return (int)lowestMark;
    }
   
    //searches for the highest score
    private int getHighest() {
	double highestMark = score [0];
        for (int i = 0; i < score.length; i++) {
            if (highestMark < score [i]) {
                highestMark = score [i];
            }
        }	
	return (int)highestMark;
    }
    
    //computes for the average score
    public double getAverage() {
        double total = score [0];
        
        for (int i = 1; i < score.length; i++) {
            total += score [i];
        }
        total = total - (getHighest() + getLowest());
        double aver = total/6;
        
        //adds the average score into the array to be used later
        Shafiq_81_A3.average [j] = aver;
        j++;
        
        return aver;
    }
    
    //prints the information
    public void printInfo() {
        System.out.printf ("%-13s", country);
        
        for (int i = 0; i < 8; i++) {
            System.out.printf ("%8.1f", score [i]);
        }
        
        System.out.printf ("%9.2f", getAverage());
        System.out.println("");
    }
    
    //used to convert list to array
    public static void listToArray (ArrayList <String> cList, String [] listArray) {
	int i = 0;
	for (String s : cList) {
            listArray [i] = s;
            ++i;
	}
    }
}