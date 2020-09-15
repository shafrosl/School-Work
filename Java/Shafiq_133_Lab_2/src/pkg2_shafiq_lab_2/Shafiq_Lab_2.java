//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 26
//10193369 / 6098253
//I swear that this is my work, please believe me

package pkg2_shafiq_lab_2;

import java.util.Random;
import java.util.Scanner;

public class Shafiq_Lab_2 {
    
    static Random rand = new Random();
    
    //random number generator
    private static int getInt() {
        int n = rand.nextInt(200) - 100;
        return n;
    }
    
    //creates and stores two coordinates, p1 and p2
    private static void getTwoPoints(Point p1, Point p2) {
        int x = getInt();
        int y = getInt();
        p1.set(x, y);
        
        x = getInt();
        y = getInt();
        p2.set(x, y);
    }
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        //asks for input for how many sets of coordinates
        System.out.print("Enter how many sets of coordinates you want to print: ");
        int sets = input.nextInt();
        input.nextLine();
        
        int count = 1;
        
        //prints the number of coordinates that was asked for
        while (count < (sets + 1)) {
            Point p1 = new Point();
            Point p2 = new Point();
            Line l = new Line(p1, p2);
        
            getTwoPoints(p1, p2);
            
            System.out.println("\nSet " + count);
            System.out.println(p1.toString());
            System.out.println(p2.toString());
            System.out.println(l.toString());
            
            if (count < sets) {
                System.out.println("\n------------------------------------------------------------");  
            }
            else {
                System.out.println();
            }
            
            count++;
        }
    }
    
}

class Point {
    
    private int x, y;
    
    //default constructor
    public Point() {
        
    }
    
    //other constructor
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    //copy constructor
    public Point(Point p) {
        this.x = p.x;
        this.y = p.y;
    }
    
    private double DistanceX(Point p) {
        double distanceX = getX();
        
        return distanceX;
    }
    
    private double DistanceY(Point p) {
        double distanceY = getY();
        
        return distanceY;
    }
    
    //accessor methods
    public double getDistance(Point p) {
        DistanceX(p);
        DistanceY(p);
        
        double distance = Math.sqrt(((this.x - p.x)*(this.x - p.x)) + ((this.y - p.y)*(this.y - p.y)));
        
        return distance;
        
    }
    
    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    
    //mutator method
    public void set(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    //method to print the information of the coordinates
    public String toString() {
        return String.format("Point (%d, %d)", getX(), getY());
    }
}

class Line {
    
    private Point p1, p2;
    
    //default constructor
    public Line() {
        
    }
    
    //other constructor
    public Line(Point p1, Point p2) {
        this.p1 = p1;
        this.p2 = p2;
    }
    
    //copy constructor
    public Line(Line aline) {
        this.p1 = aline.p1; 
        this.p2 = aline.p2;
    }
    
    //accessor methods
    public double getDistance() {
        return p1.getDistance(p2);
    }
    
    public Point getP1() {
        return p1;
    }
    
    public Point getP2() {
        return p2;
    }
    
    //mutator methods
    public void set(Point p1, Point p2) {
        this.p1 = p1;
        this.p2 = p2;
    }
    
    //method to print the distance between the coordinates
    public String toString() {
        return String.format("Line (%s, (%s, distance = %.4f)", getP1(), getP2(), getDistance());
    }
}