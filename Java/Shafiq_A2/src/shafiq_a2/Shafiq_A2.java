//Mohamed Shafiq bin Roslan
//Full Time
//Group 3
//10193369
//6098253
//I swear that this is my work, please believe me

package shafiq_a2;

import java.util.Scanner;
import java.io.File;
import java.io.IOException;

enum Gender {Male, Female};

class Shafiq_A2 {
    
public static void main(String[] args) throws IOException {

    //reads file and prints the information    
    Scanner input = new Scanner(new File("/Users/user/Desktop/patient.txt"));    
    String fName, lName;
    double height, weight;
    Gender g;
    int count = 0;

    count++;
    System.out.println("Patient " + count);
    fName = input.nextLine();
    lName = input.nextLine();
   
    int day = input.nextInt();
    String month = input.next();
    int year = input.nextInt();
    Date dob = new Date(day, month, year);
    
    height = input.nextDouble();
    
    g = Gender.valueOf(input.next());

    weight = input.nextDouble();
    
    Health_Profile p1 = new Health_Profile(fName, lName, dob, g, height, weight);
    p1.printProfile();
    
    System.out.println("\n---------------------------\n");
    input.nextLine();

    count++;
    System.out.println("Patient " + count);
    fName = input.nextLine();
    lName = input.nextLine();
        
    day = input.nextInt();
    month = input.next();
    year = input.nextInt();
    dob = new Date(day, month, year);
    
    height = input.nextDouble();
    
    g = Gender.valueOf(input.next());

    weight = input.nextDouble();
    
    Health_Profile p2 = new Health_Profile(fName, lName, dob, g, height, weight);
    p2.printProfile();
    }
}

class Date {
    private int day;
    private String month;
    private int year;
    
    //constructor
    public Date(int day, String month, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }
    
    //accessor methods
    public int getDay() {
        return day;
    }
    
    public String getMonth() {
        return month;
    }
    
    public int getYear() {
        return year;
    }
    
    public String getDateString() {
        String dateString = (getDay() + " " + getMonth() + ", " + getYear());
        return dateString;
    }

}

class Health_Profile {
    private String fName;
    private String lName;
    private Date dob;
    private double height;
    private double weight;
    private Gender g;
        
    Health_Profile(String fName, String lName, Date dob, Gender g, double height, double weight) {
        setInfo(fName, lName, dob, g, height, weight);
    }
    //accessor methods    
    public String getFName() {
        return fName;
    }
    
    public String getLName() {
        return lName;
    }

    public Date getDOB() {
        return dob;
    }
    
    public Gender getGender() {
        return g;
    }
    
    public double getHeight() {
        return height;
    }
    
    public double getWeight() {
        return weight;
    }
    
    //computes BMI
    private double computeBMI(double weight, double height) {
        double BMI = weight / (height*height);
        return BMI;
    }
    
    public void setInfo (String fName, String lName, Date dob, Gender g, double height, double weight) {
        this.fName = fName;
        this.lName = lName;
        this.dob = dob;
        this.g = g;
        this.height = height;
        this.weight = weight;
    }
    
    //prints profile
    public void printProfile () {
        double BMI = computeBMI(weight, height);
        System.out.println("Name: " + fName + " " + lName);
        System.out.println("Date of Birth: " + dob.getDateString());
        System.out.println("Gender: " + g);
        System.out.println("Height: " + (String.format("%.2f", height)));
        System.out.println("Weight: " + (String.format("%.1f",weight)));
        System.out.println("BMI: " + (String.format("%.2f",BMI)));
    }

}
