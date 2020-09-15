//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 26
//10193369 / 6098253
//I swear that this is my work, please believe me

import java.util.ArrayList;
import java.util.Random;

//main class
class Shafiq_26_A2 {
    //generates a random integer between a range
    private static int getInt() {
        Random rand = new Random();
        int integer = rand.nextInt(9) + 1;
        
        return integer;
    }
    
    //creates a 2D shape, and randomizes
    //the length of the shape
    private static TwoD getTwoD() {
        Random rand = new Random();
        int type = rand.nextInt(3);
        TwoD TwoD;
   
        if (type == 0) {
            TwoD = new Circle(getInt());
        }
        else if (type == 1) {
            TwoD = new Rectangle(getInt(), getInt());
        }
        else {
            TwoD = new Triangle(getInt(), getInt(), getInt());
        }
        return TwoD;
    }
    
    //creates a 3D shape, and randomizes
    //the length of the shape
    private static ThreeD getThreeD() {
        Random rand = new Random();
        int type = rand.nextInt(3);
        ThreeD ThreeD;
        
        if (type == 0) {
            ThreeD = new Sphere(getInt());
        }
        else if (type == 1) {
            ThreeD = new Cube(getInt());
        }
        else {
            ThreeD = new Tetrahedron(getInt());
        }
        return ThreeD;
    }
    
    //displays the list
    private static void displayList(ArrayList<Shape> alist) {
        int count = 1;
        
        //prints the list according to its shape
        for (Shape i : alist) {
            if (i instanceof Circle) {
                Circle c = (Circle) (i);
                System.out.printf("Shape[%d] = %s\n", count, c.toString());
                System.out.println("-------------------------");
                count++;
            }
            else if (i instanceof Rectangle) {
                Rectangle r = (Rectangle) (i);
                System.out.printf("Shape[%d] = %s\n", count, r.toString());
                System.out.println("-------------------------");
                count++;
            }
            else if (i instanceof Triangle) {
                Triangle t = (Triangle) (i);
                System.out.printf("Shape[%d] = %s\n", count, t.toString());
                System.out.println("-------------------------");
                count++;
            }
            else {
                System.out.printf("Shape[%d] = %s\n", count, i.toString());
                System.out.println("-------------------------");
                count++;
            }
        }
    }
    
    public static void main(String[] args) {
        ArrayList<Shape> alist = new ArrayList<Shape>();
        Random rand = new Random();
        Shafiq_26_A2 s = new Shafiq_26_A2();     
        int count = 10;
        
        //generates a random number to choose
        //whether to create a 2D or a 3D shape
        while (count > 0) {
            int type = rand.nextInt(2);
            if (type == 0) { 
                alist.add(s.getTwoD());
                count--;
            }
            else if (type == 1) {
                alist.add(s.getThreeD());
                count--;
            }
        }
        s.displayList(alist);
    }
}

interface Shape {
    public double area();
    public double getArea();
    public double PI = Math.PI;
}

abstract class TwoD implements Shape {
    protected int a, b, c;
    
    //default constructor
    public TwoD() {
    }
    
    //constructor for single argument 2D shape
    public TwoD(int a) {
        this.a = a;
    }

    //constructor for double argument 2D shape    
    public TwoD(int a, int b) {
        this.a = a;
        this.b = b;
    }

    //constructor for triple argument 2D shape    
    public TwoD(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }
    
    //copy constructor
    public TwoD(TwoD td) {
        this(td.a, td.b, td.c);
    }
    
    //accessor and mutator methods
    public int getA() {
        return a;
    }
    
    public int getB() {
        return b;
    }
    
    public int getC() {
        return c;
    }

    public void setTD(int a) {
        this.a = a;
    }
    
    public void setTD(int a, int b) {
        this.a = a;
        this.b = b;
    }    
    
    public void setTD(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }
    
    //returns a string
    public String toString() {
        return String.format("");
    } 
}

abstract class ThreeD implements Shape {
    protected int a;
    
    //default constructor
    public ThreeD() {
    }
    
    //other constructor
    public ThreeD(int a) {
        this.a = a;
    }
    
    //copy constructor
    public ThreeD(ThreeD td) {
        this(td.a);
    }
    
    //accessors and mutators
    public int getA() {
        return a;
    }
    
    public void setTD(int a) {
        this.a = a;
    }
    
    protected double volume() {
        double volume = 0.0;
        return volume;
    }
    
    public double getVolume() {
        return volume();
    }
    
    //returns a string
    public String toString() {
        return String.format("");
    }
}

class Circle extends TwoD {
    //default constructor
    public Circle() {
    }    
    
    //other constructor
    public Circle(int radius) {
        super(radius);
    }
    
    //accessor and mutator methods
    @Override
    public int getA() {
        return a;
    }

    @Override
    public void setTD(int a) {
        this.a = a;
    }
    
    
    //method to calculate area
    @Override
    public double area() {
        return PI * (Math.pow(a, 2));
    }
    
    //method to call area
    @Override
    public double getArea() {
        return area();
    }
    
    //returns the string
    @Override
    public String toString() {
        return String.format("Circle (2D (%d)) ==> Area = %.3f\nI am a Circle", a, getArea());
    }
    
}

class Rectangle extends TwoD {
    //default constructor
    public Rectangle() {
    }
    
    //other constructor
    public Rectangle(int length, int width) {
        super(length, width);
    }
    
    //accessor and mutator methods
    @Override
    public int getA() {
        return a;
    }
    
    @Override
    public int getB() {
        return b;
    }
    
    @Override
    public void setTD(int a, int b) {
        this.a = a;
        this.b = b;
    }
    
    
    //calculates the area of the rectangle
    @Override
    public double area() {
        return a * b;
    }

    //calls the area method
    @Override
    public double getArea() {
        return area();
    }
    
    //returns a string
    @Override
    public String toString() {
        return String.format("Rectangle (2D (%d, %d)) ==> Area = %.3f\nI am a Rectangle", a, b, getArea());
    }
    
}

class Triangle extends TwoD {
    //default constructor
    public Triangle() {
    }
    
    //other constructor
    public Triangle(int a, int b, int c) {
        super(a, b, c);
    }
    
    //accessor and mutator methods
    @Override
    public int getA() {
        return a;
    }
    
    @Override
    public int getB() {
        return b;
    }
    
    @Override
    public int getC() {
        return c;
    }
    
    @Override
    public void setTD(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }
    
    //calculates area
    @Override
    public double area() {
        double semip = (a + b + c) / 2.0;
        double ar =(semip * (semip - a) * (semip - b) * (semip - c));
        double area = Math.sqrt(ar);
        return area;
    }
    
    //calls the area method
    @Override
    public double getArea() {
        return area();
    }
    
    //returns string
    @Override
    public String toString() {
        //checks whether it is a valid triangle
        //if it is not, it will print the first statement
        if (((a + b) <= c) || ((a + c) <= b) || ((b + c) <= a)) {
           return String.format("Triangle (2D (%d, %d, %d)\nI am not a Triangle", a, b, c); 
        }
        else {
            return String.format("Triangle (2D (%d, %d, %d)) ==> Area = %.3f\nI am a Triangle", a, b, c, getArea());
        }
    }    
}

class Sphere extends ThreeD {
    //default constructor
    public Sphere() {
    }
    
    //other constructor
    public Sphere(int a) {
        super(a);
    }
    
    //accessor and mutator methods
    @Override
    public int getA() {
        return a;
    }
    
    @Override
    public void setTD(int a) {
        this.a = a;
    }
    
    //calculates area
    @Override
    public double area() {
        return 4.0 * PI * (Math.pow(a, 2.0));
    }
    
    //calls the area method
    @Override
    public double getArea() {
        return area();
    }
    
    //calculates volume
    @Override
    protected double volume() {
        return (4.0/3.0) * (PI * (Math.pow(a, 3.0)));
    }
    
    //calls the volume method
    @Override
    public double getVolume() {
        return volume();
    }
    
    //prints the string
    @Override
    public String toString() {
        return String.format("Sphere (2D (%d)) ==> Surface Area = %.3f, Volume = %.3f\nI am a Sphere", a, getArea(), getVolume());
    }
}

class Cube extends ThreeD {
    //default constructor
    public Cube() {
    }
    
    //other constructor
    public Cube(int a) {
        super(a);
    }
    
    //accessor and mutator methods
    @Override
    public int getA() {
        return a;
    }
    
    @Override
    public void setTD(int a) {
        this.a = a;
    }
    
    //calculates area
    @Override
    public double area() {
        return 6.0 * (Math.pow(a, 2.0));
    }
    
    //calls the area method
    @Override
    public double getArea() {
        return area();
    }
    
    //calculates volume
    @Override
    protected double volume() {
        return (Math.pow(a, 3.0));
    }
    
    //calls volume method
    @Override
    public double getVolume() {
        return volume();
    }
    
    //returns the string
    @Override
    public String toString() {
        return String.format("Cube (2D (%d)) ==> Surface Area = %.3f, Volume = %.3f\nI am a Cube", a, getArea(), getVolume());
    }
}

class Tetrahedron extends ThreeD {
    //default constructor
    public Tetrahedron() {
    }
    
    //other constructor
    public Tetrahedron(int a) {
        super(a);
    }
    
    //accessor and mutator methods
    @Override
    public int getA() {
        return a;
    }
    
    @Override
    public void setTD(int a) {
        this.a = a;
    }
    
    //calculates area
    @Override
    public double area() {
        return (Math.sqrt(3.0)) * ((Math.pow(a, 2.0)));
    }
    
    //calls the area method
    @Override
    public double getArea() {
        return area();
    }
    
    //calculates volume
    @Override
    protected double volume() {
        return (Math.pow(a, 3.0)) / (6.0 * (Math.sqrt(2.0)));
    }
    
    //calls the volume method
    @Override
    public double getVolume() {
        return volume();
    }
    
    //returns string
    @Override
    public String toString() {
        return String.format("Tetrahedron (2D (%d)) ==> Surface Area = %.3f, Volume = %.3f\nI am a Tetrahedron", a, getArea(), getVolume());
    }
}