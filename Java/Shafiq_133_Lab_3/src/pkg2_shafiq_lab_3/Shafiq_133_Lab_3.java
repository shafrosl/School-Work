//Mohamed Shafiq Bin Roslan
//Full Time
//Tutorial Group 1
//Class no. 133
//10193369 / 6098253
//I swear that this is my work, please believe me

package pkg2_shafiq_lab_3;

import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.FlowLayout;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.JButton;

class introduce extends JFrame {
    private final JButton jButts;
    private final JTextField[] textField;
    private final JLabel[] label;
    private final String[] info = {"Mohamed Shafiq Bin Roslan", "20 March 1994", "iam.shafiq@live.com", "I wish the scope for the labs and assignments were clearer", "I want a HD"};
    private final String[] labels = {"            Name: ", "Date of Birth: ", "            E-Mail: ", "                   My Comments for the Subject"};
    int i = 0;
    
    public introduce() {
        super("Introduction of Myself");
        setLayout(new FlowLayout(10, 10, 8));
        
        textField = new JTextField[info.length]; //sets the number of text fields to be as many as the amount of content in the info array
        label = new JLabel[labels.length]; //sets the the number of labels to be as many as the amount of content in the labels array
        
        //creates labels and text fields and sets the texts
        //according to what is inside the labels and info arrays
        for (i = 0; i < 3; i++) {
            label[i] = new JLabel();
            label[i].setText(labels[i]);
            add(label[i]);
            
            textField[i] = new JTextField();
            textField[i].setColumns(15);
            textField[i].setText(info[i]);
            textField[i].setEditable(false); //sets non-editable text field
            add(textField[i]);
        }
        
        //pulls the picture and resizes it to fit the jFrame
        ImageIcon img = new ImageIcon(getClass().getResource("avatar.png"));
        Image img2 = img.getImage().getScaledInstance(250, 250, Image.SCALE_SMOOTH);
        ImageIcon img3 = new ImageIcon(img2);
        
        //unsure whether lab 3 is asking for an actionListener on the
        //editable text fields or a jButton to press
        //this is a label for a picture if buttons are not to be used
        /*
        label[i] = new JLabel(img3);
        label[i].setToolTipText("I am Shafiq");
        add(label[i]);
        i++;
        */
        
        //creates jButton and sets the above image as the icon
        jButts = new JButton(img3);
        jButts.setContentAreaFilled(false);
        jButts.setBorderPainted(false);
        jButts.setToolTipText("I am Shafiq");
        add(jButts);
        ButtonHandler bHandler = new ButtonHandler();
        jButts.addActionListener(bHandler);

        //creates another label
        label[i] = new JLabel();
        label[i].setText(labels[i]);
        add(label[i]);
        
        //creates the remaining textFields
        TextFieldHandler tfHandler = new TextFieldHandler();
        for (i = 3; i < 5; i++) {
            textField[i] = new JTextField();
            textField[i].setColumns(25);
            textField[i].setText(info[i]);
            add(textField[i]);
            textField[i].addActionListener(tfHandler);
        }
        
        //set info
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setSize(320, 480);
	setVisible(true);
        setLocationRelativeTo(null);
        
    }
    
    //handler for the jButton
    //opens a new dialog and displays the content
    //in the text fields when the picture is clicked
    private class ButtonHandler implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent event) {
            JOptionPane.showMessageDialog(introduce.this, String.format("1. %s\n2. %s", textField[3].getText(), textField[4].getText()), "My Suggestions", JOptionPane.WARNING_MESSAGE);
        }
    }    
        
    //handler for the jTextField
    //opens a new dialog and displays the content
    //in the text fields when you press enter 
    private class TextFieldHandler implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent event) {
            // user pressed Enter
            if ((event.getSource() == textField[3]) || (event.getSource() == textField[4])) {
                JOptionPane.showMessageDialog(introduce.this, String.format("1. %s\n2. %s", textField[3].getText(), textField[4].getText()), "My Suggestions", JOptionPane.WARNING_MESSAGE);
            }
        }
    }
}

class Shafiq_133_Lab_3 {
    public static void main(String[] args) {
        introduce i = new introduce();
    } 
}