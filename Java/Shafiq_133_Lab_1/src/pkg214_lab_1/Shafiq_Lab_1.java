//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 26
//10193369 / 6098253
//I swear that this is my work, please believe me

package pkg214_lab_1;

import java.util.*; 

public class Shafiq_Lab_1 {

public static void main(String[] args) {
    
    ArrayList<String> facts = new ArrayList<String>();
    ArrayList<String> wishes = new ArrayList<String>();

    information me = new information();
    
    //this is where the information is stored or changed if needed to
    me.Name("Mohamed Shafiq Bin Roslan");
    me.Nation("Singaporean");
    me.Birthdate("20/03/1994");
    
    //add facts
    facts.add("love soccer");
    facts.add("love watching TV");
    facts.add("love dark colours");
    facts.add("studied music for my diploma");
    facts.add("am working as a barista");
    facts.add("think the world could use with lesser people");
    facts.add("like Marvel over DC");
    facts.add("play the bass guitar");
    facts.add("am 173cm tall");
    facts.add("like to keep my hair long");
    facts.add("like movies by Wes Anderson");
    facts.add("hate running");
    facts.add("cannot swim");
    facts.add("like watching people cook");
    facts.add("ride a motorcycle");
    facts.add("am a smoker");
    me.Facts(facts);
    
    //add wishes
    wishes.add("graduate with a distinction");
    wishes.add("live overseas");
    wishes.add("watch Radiohead in concert");
    wishes.add("retire without any financial issues");
    wishes.add("be really good at something");
    wishes.add("leave a dent in the world");
    me.Wish(wishes);
    
    //prints the information
    me.printInfo();
    }
}

class information {
    String name, nation, DOB;
    ArrayList<String> facts = new ArrayList<String>();
    ArrayList<String> wishes = new ArrayList<String>();

    //constructors
    public void Name(String name) {
        this.name = name;
    }
    public void Nation(String nation) {
        this.nation = nation;
    }

    public void Birthdate(String DOB) {
        this.DOB = DOB;
    }
    
    public void Facts(ArrayList<String> facts) {
        this.facts = facts;
    }

    public void Wish(ArrayList<String> wishes) {
        this.wishes = wishes;
    }

    //prints the information
    public void printInfo() {
        Scanner input = new Scanner(System.in);

        System.out.println("My Information");
        System.out.println("______________________________________________");
        System.out.printf("\nName: %32s\n", name);
        System.out.printf("Nationality: %11s\n", nation);
        System.out.printf("DOB: %18s\n", DOB);
        
        //prints items in the list with a format
        int i = 1;
        System.out.println("\nI wish to...");
        for (String wish : wishes) {
            System.out.print("\t..." + wish);
            if (i < wishes.size()) {
                System.out.println(",");
                i++;
            }
            else {
                System.out.println(".");
                i++;
            }
        }
        
        //prints a random fact about myself
        String check = "";
        System.out.print("\nPress enter for a random fact about me or enter 'q' to quit\t");
        while (!"q".equals(check)) {
            check = input.nextLine();
            //prints a fact if check == ""
            if ("".equals(check)) {
                System.out.print("\nI " + facts.get((int)(Math.random()*facts.size())) + ".\t");
                System.out.print("\nWant to know more about me? (Press enter or enter 'q')\t");
            }
            //exits the program if check == "q"
            else if ("q".equals(check)) {
                System.out.println("\nBye, see you! Hope you will give me a distinction!");
            }
            //check if anything other than the instructed keys are entered
            //and if so, it prints an error message
            else {
                System.out.print("\nOoops! Wrong button! Press enter for a fact or enter 'q' to quit\t");
            }
        }
    }
}