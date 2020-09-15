//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 26
//10193369 / 6098253
//I swear that this is my work, please believe me

package shafiq_a1;

import java.util.ArrayList;
import java.util.Random;

public class Shafiq_A1 {
    private final int MAXC = 13;
    private final int MAXD = 52;
    private final String LINE = "\n-------------------------------------------------------------------------------\n";
    
    //creates a deck of cards by combining both enums
    //and stores them in a list
    private void deckOfCards(ArrayList<playingCard> values) {
        for (SuitEnum s : SuitEnum.values()) {
            for (RankEnum r : RankEnum.values()) {
                values.add(new playingCard(s, r));
            }
        }
    }
    
    //prints deck of cards
    private void printDeck(ArrayList<playingCard> values) {
        int count = 0;
        
        System.out.println("Printing from ArrayList:\n");
        
        //prints each card and goes into a new line
        //after 13 cards are printed
        for (playingCard c : values) {
            if (count < MAXC) {
                System.out.print(c);
                count++;
                if (count == MAXC) {
                    System.out.println();
                }
            }
            else if (count < MAXC*2) {
                System.out.print(c);
                count++;
                if (count == (MAXC*2)) {
                    System.out.println();
                }
            }
            else if (count < MAXC*3) {
                System.out.print(c);
                count++;
                if (count == (MAXC*3)) {
                    System.out.println();
                }
            }
            else {
                System.out.print(c);
            }
        }
        
        System.out.print(LINE);
    }    
    
    //creates a copy of each card from the list and puts it into an array
    private void listToArray(ArrayList<playingCard> values, playingCard[] valuesArray) {
        int i = 0;
        
        while (i < MAXD) {
            playingCard copy = new playingCard(values.get(i));
            valuesArray[i] = copy;
            i++;
        }
    }
    
    //shuffles the deck of cards using the extra array
    //initialized in main
    private void shuffle(playingCard[] valuesArray) {
        Random rand = new Random();
        int a = rand.nextInt(MAXD); //randomise which cards
        int b = rand.nextInt(MAXD); //are being shuffled
        
        valuesArray[MAXD] = valuesArray[a];
        valuesArray[a] = valuesArray[b];
        valuesArray[b] = valuesArray[MAXD];
    }
    
    //prints the deck of cards
    private void printDeck(playingCard[] valuesArray) {
        System.out.println("Printing from Array:");
        
        for (int i = 0; i < MAXD; i++) {
            if (i % MAXC == 0) { //if the modular of the counter against 13 is 0, it prints the next set of cards in a new line
                System.out.println();
            }
            System.out.print(valuesArray[i]);
        }
        
        System.out.print(LINE);
    }
    
    public static void main(String[] args) {
        ArrayList<playingCard> values = new ArrayList<playingCard>();
        playingCard valuesArray[] = new playingCard[53];
        Random rand = new Random();
        
        int a = rand.nextInt(100);
        int count = 0;
        
        //functions are done one by one
        Shafiq_A1 p = new Shafiq_A1();
        p.deckOfCards(values);
        p.printDeck(values);
        p.listToArray(values, valuesArray);
        p.printDeck(valuesArray);
        
        //randomly shuffles the card 'n' number of times
        while (count < a) {
            p.shuffle(valuesArray);
            count++;
        }
        System.out.println("Shuffle the cards --");
        p.printDeck(valuesArray);
    }
    
}

enum SuitEnum {
    Spade('S'),
    Heart('H'),  
    Diamond('D'), 
    Club('C');
    
    private char letter;
    
    //constructor
    SuitEnum (char letter) {
        this.letter = letter;
    }
    
    //accessor
    public char getLetter() {
        return letter;
    }
    
}

enum RankEnum {
    Two('2'), 
    Three('3'), 
    Four('4'), 
    Five('5'), 
    Six('6'), 
    Seven('7'), 
    Eight('8'), 
    Nine('9'), 
    Ten('T'), 
    Jack('J'), 
    Queen('Q'), 
    King('K'), 
    Ace('A');
    
    private char value;
    
    //constructor
    RankEnum (char value) {
        this.value = value;
    }
    
    //accessor
    public char getValue() {
        return value;
    }
    
}

class playingCard {
    private SuitEnum suit;
    private RankEnum rank;
    
    //default constructor
    public playingCard() {
        
    }
    
    //other constructor
    public playingCard(SuitEnum suit, RankEnum rank) {
        this.suit = suit;
        this.rank = rank;
    }
    
    //copy constructor
    public playingCard(playingCard pc) {
        this.suit = pc.suit;
        this.rank = pc.rank;
    }
    
    //accessors
    public SuitEnum getSuit() {
        return suit;
    }
    
    public RankEnum getRank() {
        return rank;
    }
    
    //mutator
    public void setCard(SuitEnum suit, RankEnum rank) {
        this.rank = rank;
        this.suit = suit;
    }
    
    //combines the rank and suit together
    public String toString() {
        return String.format("%4s%-2s", suit.getLetter(), rank.getValue());
    }
}