//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 133
//10193369 / 6098253
//I swear that this is my work, please believe me

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.stream.IntStream;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import static javax.swing.SwingConstants.CENTER;
import static javax.swing.SwingConstants.RIGHT;
import static javax.swing.SwingConstants.TOP;

class lucky8 extends JFrame {
    protected static final JButton[] jButts = new JButton[64];
    protected static final JLabel[] label = new JLabel[16];
    protected static final int[] wiener = new int[8];
    protected static final String[] position = {"8th", "7th", "6th", "5th", "4th", "3rd", "2nd", "Winner"};
    private static final String goodluck = "GOODLUCK";
    private static int i = 1;
    
    public lucky8() {
        super("Lucky 8");
        setLayout(new GridLayout(10, 8, 0, 5));
        ButtonHandler bHandler = new ButtonHandler();
        Font bigFont = new Font("Serif", Font.BOLD, 80);
        Font smallFont = new Font("Serif", Font.BOLD, 20);
        
        //pulls the picture and resizes it to fit the jFrame
        ImageIcon img = new ImageIcon(getClass().getResource("blackeyes.png"));
        Image img2 = img.getImage().getScaledInstance(260, 260, Image.SCALE_SMOOTH);
        ImageIcon img3 = new ImageIcon(img2);
        
        //generates winning list
        IntStream.range(0, 8).forEach(j -> {
            wiener[j] = rng();
            for (int k = j-1; k >= 0; k--) {
                if (wiener[j] == (wiener[k])) {
                    wiener[j] = rng();
                    k = j-1; //starts the check from the end of the array again
                }
            }
        });
        
        //sorts the winning number on index 0 - 6
        //in ascending order
        Arrays.sort(wiener, 0, 7);
        
        //creates 64 jButtons to be placed into the program
        IntStream.range(0, 64).forEach(i -> {
           jButts[i] = new JButton(img3);
        });
        
        //converts array to list
        //sets the jButtons and attaches a number to each jButton
        //adds an action listener to each JButton,
        //shuffles the JButtons
        //and then adds the buttons into the program
        List <JButton> buttList = Arrays.asList (jButts);
        buttList.forEach(b -> { b.setContentAreaFilled(false);
                                b.setBorderPainted(false);
                                b.setToolTipText("Sure not?");
                                b.setHorizontalTextPosition(RIGHT);
                                b.setText(String.valueOf(i++));
                                b.addActionListener(bHandler);
        });                        
        Collections.shuffle(buttList);
        buttList.forEach(b -> add(buttList.get(buttList.indexOf(b))));
        
        //creates and adds 8 labels to be placed under the buttons 
        //to show the winning numbers and to say goodluck
        IntStream.range(0, 8).forEach(i -> {    
            label[i] = new JLabel();
            label[i].setText(String.valueOf(goodluck.charAt(i)));
            label[i].setHorizontalAlignment(CENTER);
            label[i].setFont(bigFont);
            add(label[i]);
        });
        
        //creates and adds 8 labels to be placed under the goodluck label
        //to be used to show the position of each number later
        IntStream.range(8, 16).forEach(i -> {
            label[i] = new JLabel();
            label[i].setHorizontalAlignment(CENTER);
            label[i].setVerticalAlignment(TOP);
            label[i].setFont(smallFont);
            add(label[i]);
        });
        
        //sets jframe info
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setSize(1450, 1120);
	setVisible(true);
        setLocationRelativeTo(null);
    }
    
    //random number generator method
    private int rng() {
        Random r = new Random();
        
        return (r.nextInt(63) + 1);
    }
}

class ButtonHandler implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent event) {
        //formats image for when button is clicked
        ImageIcon img = new ImageIcon(getClass().getResource("blackcat.png"));
        Image img2 = img.getImage().getScaledInstance(80, 80, Image.SCALE_SMOOTH);
        ImageIcon img3 = new ImageIcon(img2);
        
        Font winner = new Font("Serif", Font.BOLD, 45); //winner font
        Font others = new Font("Serif", Font.PLAIN, 25); //default font
        
        //converts array to list and sets the default icon and font
        List <JButton> buttList = Arrays.asList (lucky8.jButts);
        buttList.forEach(b -> { b.setIcon(img3);
                                b.setFont(others);
        });
        
        //fonts, background changed depending if the number is picked for prizes
        //GOODLUCK changes to the number
        //the label below GOODLUCK changes to position of the number
        buttList.forEach((JButton j) -> {
            IntStream.range(0, 8).forEach(i -> {
                if (i == 7) {
                    if (j.getText().equals(Integer.toString((lucky8.wiener[i])))) {
                        j.setFont(winner);
                        j.setForeground(new Color(240, 240, 240));
                        j.setOpaque(true);
                        j.setBackground(new Color(200, 55, 75));
                        lucky8.label[i].setText(Integer.toString(lucky8.wiener[i]));
                        lucky8.label[i].setForeground(new Color(200, 55, 75));
                        lucky8.label[i + 8].setText(lucky8.position[i]);
                    }
                }
                
                else if (j.getText().equals(Integer.toString((lucky8.wiener[i])))) {
                    j.setFont(winner);
                    j.setForeground(new Color(200, 200, 200));
                    j.setOpaque(true);
                    j.setBackground(new Color(95, 95, 95));
                    lucky8.label[i].setText(Integer.toString(lucky8.wiener[i]));
                    lucky8.label[i + 8].setText(lucky8.position[i]);
                }
            });
        });
    }    
}

public class Shafiq_133_A3 {
    
    public static void main(String[] args) {
        lucky8 l = new lucky8();
    }
}