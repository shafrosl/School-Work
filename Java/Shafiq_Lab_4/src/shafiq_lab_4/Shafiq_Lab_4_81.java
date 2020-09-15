//Mohamed Shafiq bin Roslan
//Full Time
//Group 3
//Class List no. 81
//10193369
//6098253
//I swear that this is my work, please believe me

package shafiq_lab_4;

import java.util.Scanner;
enum Types {Equilateral, Isosceles, Scalene, NoShape};

public class Shafiq_Lab_4_81 {

    public static void main(String[] args) {
        
        int firstInt, secInt, thirdInt;

        Scanner input = new Scanner(System.in);
        //getting input for the three integers.
        System.out.print("Enter three integers: ");
        firstInt = input.nextInt();
        secInt = input.nextInt();
        thirdInt = input.nextInt();
        System.out.println("");
        
        //running methods to test what kind of triangle it is and to print the triangles.
        Triangles.testTriangle(firstInt, secInt, thirdInt);
        Triangles.printTriangles(firstInt, secInt, thirdInt);
    }
}

class Triangles {
    public static Types triangleType;
    
    public static void testTriangle(int firstInt, int secInt, int thirdInt) {
        //testing whether it is a triangle by checking if it is smaller than 1, and if any two 
        //sides of the triangle is bigger than the third side.
        if (((firstInt < 1) || (secInt < 1) || (thirdInt < 1)) || (((firstInt + secInt) <= thirdInt) || ((firstInt + thirdInt) <= secInt) || ((secInt + thirdInt) <= firstInt))) {
            triangleType = Types.NoShape;
        }
        else {
            //testing for isosceles triangle by checking if there are two sides of the same length.
            if ((firstInt == secInt) || (firstInt == thirdInt) || (secInt == thirdInt)) {
                triangleType = Types.Isosceles;  
            }
            //testing for equilateral triangle by checking all three sides are the same length.
            if ((firstInt == secInt) && (secInt == thirdInt)) {
                triangleType = Types.Equilateral;
            }
            //testing for scalene triangle by checking all three sides are of different lengths.
            if ((firstInt != secInt) && (secInt != thirdInt)) {
                triangleType = Types.Scalene;
            }
        }
    }
    
    public static void printTriangles(int firstInt, int secInt, int thirdInt) {
        switch(triangleType) {
            //printing statements according to what kind of triangle it is. break is placed after NoShape 
            //because I do not want it to flow through to the end of the cases.
            case NoShape:
                System.out.println("(" + firstInt + ", " + secInt + ", " + thirdInt +") is not a triangle.");
                break;
            //I did not place a break after each of the other cases as they are placed logically in a way 
            //that an equilateral triangle is also both a triangle and an isosceles triangle, and an 
            //isosceles triangle is also a triangle.
            case Equilateral:
                System.out.println("(" + firstInt + ", " + secInt + ", " + thirdInt +") is an equilateral triangle.");    
            case Isosceles:
                System.out.println("(" + firstInt + ", " + secInt + ", " + thirdInt +") is an isosceles triangle.");
            case Scalene:
                System.out.println("(" + firstInt + ", " + secInt + ", " + thirdInt +") is a triangle.");
        }
    }
}
