import com.sun.glass.events.KeyEvent;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

public class staffRegistration extends javax.swing.JFrame {

    public staffRegistration() {
        initComponents();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        kGradientPanel2 = new keeptoo.KGradientPanel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        register = new javax.swing.JButton();
        jLabel8 = new javax.swing.JLabel();
        studentPage = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();
        username = new javax.swing.JTextField();
        password = new javax.swing.JPasswordField();
        confirmPassword = new javax.swing.JPasswordField();
        staffID = new javax.swing.JTextField();
        fName = new javax.swing.JTextField();
        dept = new javax.swing.JComboBox<>();
        phone = new javax.swing.JTextField();
        email = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        kGradientPanel2.setkBorderRadius(5);
        kGradientPanel2.setkEndColor(new java.awt.Color(255, 255, 255));
        kGradientPanel2.setkGradientFocus(300);
        kGradientPanel2.setkStartColor(new java.awt.Color(113, 199, 172));
        kGradientPanel2.setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jLabel2.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(51, 51, 51));
        jLabel2.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel2.setText("Email:");
        kGradientPanel2.add(jLabel2, new org.netbeans.lib.awtextra.AbsoluteConstraints(530, 260, 50, 30));

        jLabel3.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(51, 51, 51));
        jLabel3.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel3.setText("Username:");
        kGradientPanel2.add(jLabel3, new org.netbeans.lib.awtextra.AbsoluteConstraints(100, 160, 80, 30));

        jLabel5.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(51, 51, 51));
        jLabel5.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel5.setText("Password:");
        kGradientPanel2.add(jLabel5, new org.netbeans.lib.awtextra.AbsoluteConstraints(100, 210, 80, 30));

        jLabel6.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel6.setForeground(new java.awt.Color(51, 51, 51));
        jLabel6.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel6.setText("Confirm Password:");
        kGradientPanel2.add(jLabel6, new org.netbeans.lib.awtextra.AbsoluteConstraints(40, 260, 140, 30));

        jLabel7.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel7.setForeground(new java.awt.Color(51, 51, 51));
        jLabel7.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel7.setText("Full Name:");
        kGradientPanel2.add(jLabel7, new org.netbeans.lib.awtextra.AbsoluteConstraints(100, 360, 80, 30));

        register.setBackground(new java.awt.Color(75, 140, 113));
        register.setFont(new java.awt.Font("Times New Roman", 0, 24)); // NOI18N
        register.setForeground(new java.awt.Color(255, 255, 255));
        register.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons8_Add_User_Male_32px.png"))); // NOI18N
        register.setText("Register");
        register.setHorizontalAlignment(javax.swing.SwingConstants.LEADING);
        register.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                registerActionPerformed(evt);
            }
        });
        kGradientPanel2.add(register, new org.netbeans.lib.awtextra.AbsoluteConstraints(590, 330, 150, 60));

        jLabel8.setIcon(new javax.swing.ImageIcon(getClass().getResource("/logo.png"))); // NOI18N
        kGradientPanel2.add(jLabel8, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 10, -1, -1));

        studentPage.setFont(new java.awt.Font("Palace Script MT", 0, 80)); // NOI18N
        studentPage.setForeground(new java.awt.Color(255, 255, 255));
        studentPage.setText("Staff Registration");
        kGradientPanel2.add(studentPage, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 60, 380, 80));

        jLabel9.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel9.setForeground(new java.awt.Color(51, 51, 51));
        jLabel9.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel9.setText("Staff ID:");
        kGradientPanel2.add(jLabel9, new org.netbeans.lib.awtextra.AbsoluteConstraints(110, 310, 70, 30));

        jLabel4.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(51, 51, 51));
        jLabel4.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel4.setText("Department:");
        kGradientPanel2.add(jLabel4, new org.netbeans.lib.awtextra.AbsoluteConstraints(490, 160, -1, -1));

        jLabel10.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        jLabel10.setForeground(new java.awt.Color(51, 51, 51));
        jLabel10.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel10.setText("Contact Number:");
        kGradientPanel2.add(jLabel10, new org.netbeans.lib.awtextra.AbsoluteConstraints(450, 212, 130, 30));

        username.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        kGradientPanel2.add(username, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 160, 240, 30));

        password.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        kGradientPanel2.add(password, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 210, 240, 30));

        confirmPassword.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        kGradientPanel2.add(confirmPassword, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 260, 240, 30));

        staffID.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        staffID.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                staffIDKeyTyped(evt);
            }
        });
        kGradientPanel2.add(staffID, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 310, 240, 30));

        fName.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        fName.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                fNameKeyTyped(evt);
            }
        });
        kGradientPanel2.add(fName, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 360, 240, 30));

        dept.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "", "Psychology", "Computer Science", "Business" }));
        kGradientPanel2.add(dept, new org.netbeans.lib.awtextra.AbsoluteConstraints(590, 160, 240, 30));

        phone.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        phone.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                phoneKeyTyped(evt);
            }
        });
        kGradientPanel2.add(phone, new org.netbeans.lib.awtextra.AbsoluteConstraints(590, 210, 240, 30));

        email.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        kGradientPanel2.add(email, new org.netbeans.lib.awtextra.AbsoluteConstraints(590, 260, 240, 30));

        getContentPane().add(kGradientPanel2, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 910, 490));

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents
    
    private void registerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_registerActionPerformed
        
        String fileName = directory.staff;
        conflict2 c2 = new conflict2();
        Boolean check =c2.conflictCheck(fileName, username.getText(), staffID.getText());
        if (!check){
                JOptionPane.showMessageDialog(null, "Pls re-enter", "Error", JOptionPane.ERROR_MESSAGE);
            } 
        else{
        if ((username.getText().equals("     ")) || (username.getText().length() < 5)) { 
            JOptionPane.showMessageDialog(null, "Please enter a valid username that is more than 5 characters long", "Error", JOptionPane.ERROR_MESSAGE);
        }
        
        else if (password.getText().length() < 5) {
            JOptionPane.showMessageDialog(null, "Please enter a password that is more than 5 characters long", "Error", JOptionPane.ERROR_MESSAGE);
        }  
        
        else if ((staffID.getText().length() != 8)) {
            JOptionPane.showMessageDialog(null, "Please a valid Staff ID\neg. 10191234", "Error", JOptionPane.ERROR_MESSAGE);
        }
        
        else if ((fName.getText().length() < 5) || (fName.getText().contains("  "))) {
            JOptionPane.showMessageDialog(null, "Please enter a valid full name", "Error", JOptionPane.ERROR_MESSAGE);
        }
        
        else if (dept.getSelectedItem().equals("")) {
            JOptionPane.showMessageDialog(null, "Please select a department", "Error", JOptionPane.ERROR_MESSAGE);
        }
        
        else if ((phone.getText().equals("        ")) || (phone.getText().length() != 8) || (phone.getText().startsWith("0")) || (phone.getText().startsWith("1")) || (phone.getText().startsWith("2")) 
                || (phone.getText().startsWith("3")) || (phone.getText().startsWith("4")) || (phone.getText().startsWith("5")) || (phone.getText().startsWith("7"))) {
            JOptionPane.showMessageDialog(null, "Please enter a valid contact number", "Error", JOptionPane.ERROR_MESSAGE);
        }
        
        else if ((!email.getText().contains("@")) || ((!email.getText().contains(".sg")) && (!email.getText().contains(".com")))){
            JOptionPane.showMessageDialog(null, "Please enter a valid email address", "Error", JOptionPane.ERROR_MESSAGE);
        }
        
        else {
            if (password.getText().equals(confirmPassword.getText())){
                    String nw = username.getText() + "," + password.getText() + "," + staffID.getText() + "," + fName.getText() + "," + phone.getText() + "," + email.getText();
                    storeStaff s = new storeStaff();

                        try {
                            s.storeStaff(nw);
                        } 

                        catch (IOException ex) {
                            Logger.getLogger(staffRegistration.class.getName()).log(Level.SEVERE, null, ex);
                        }
                        JOptionPane.showMessageDialog(null, "Successful Registration!", "Success", JOptionPane.INFORMATION_MESSAGE);
                        staffRegistration.this.setVisible(false);
                    }
            else {
                JOptionPane.showMessageDialog(null, "Password does not match Confirm Password", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
       }
    }//GEN-LAST:event_registerActionPerformed
   
    private void staffIDKeyTyped(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_staffIDKeyTyped
        char c = evt.getKeyChar();
        
        if (!(Character.isDigit(c) || c == KeyEvent.VK_BACKSPACE || c == KeyEvent.VK_DELETE)) {
            evt.consume();
        }
    }//GEN-LAST:event_staffIDKeyTyped

    private void fNameKeyTyped(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_fNameKeyTyped
        char c = evt.getKeyChar();
        
        if (!(Character.isAlphabetic(c) || c == KeyEvent.VK_BACKSPACE || c == KeyEvent.VK_DELETE || c == KeyEvent.VK_SPACE)) {
            evt.consume();
        }
    }//GEN-LAST:event_fNameKeyTyped

    private void phoneKeyTyped(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_phoneKeyTyped
        char c = evt.getKeyChar();
        
        if (!(Character.isDigit(c) || c == KeyEvent.VK_BACKSPACE || c == KeyEvent.VK_DELETE)) {
            evt.consume();
        }
    }//GEN-LAST:event_phoneKeyTyped

    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(staffCreateEvent.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(staffCreateEvent.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(staffCreateEvent.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(staffCreateEvent.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new staffRegistration().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPasswordField confirmPassword;
    private javax.swing.JComboBox<String> dept;
    private javax.swing.JTextField email;
    private javax.swing.JTextField fName;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private keeptoo.KGradientPanel kGradientPanel2;
    private javax.swing.JPasswordField password;
    private javax.swing.JTextField phone;
    private javax.swing.JButton register;
    private javax.swing.JTextField staffID;
    private javax.swing.JLabel studentPage;
    private javax.swing.JTextField username;
    // End of variables declaration//GEN-END:variables
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class storeStaff extends staffRegistration {
    static StringBuffer stringBufferOfData = new StringBuffer();
    static String filename = directory.staff;
    
    public static void storeStaff(String nw) throws IOException {
        boolean fileRead = readFile();//call the method to read the file with the files name
        if (fileRead) {//if the read file was successfull
            replacement(nw);//call method to get text to replace, replacement text and output replaced String buffer
            writeToFile();
        }
    }
    
    private static boolean readFile() {
        Scanner fileToRead = null;
        
        try {
            fileToRead = new Scanner(new File(filename)); //point the scanner method to a file
            
            //check if there is a next line and it is not null and then read it in
            for (String line; fileToRead.hasNextLine() && (line = fileToRead.nextLine()) != null; ) {
                System.out.println(line);//print each line as its read
                stringBufferOfData.append(line).append("\r\n");//this small line here is to appened all text read in from the file to a string buffer which will be used to edit the contents of the file
            }
            
            fileToRead.close();//this is used to release the scanner from file
            return true;
        } 
        
        catch (FileNotFoundException ex) {//if the file cannot be found an exception will be thrown
            System.out.println("The file " + filename + " could not be found! " + ex.getMessage());
            return false;
        }
    }
    
    private static void writeToFile() {
        try {
            BufferedWriter bufwriter = new BufferedWriter(new FileWriter(filename));
            bufwriter.write(stringBufferOfData.toString());//writes the edited string buffer to the new file
            bufwriter.close();//closes the file
        } 
        
        catch (Exception e) {//if an exception occurs
            System.out.println("Error occured while attempting to write to file: " + e.getMessage());
        }
    }
    
    private static void replacement(String nw) throws FileNotFoundException, IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String replacementText = nw;//read the line to replace
        stringBufferOfData.append(nw);//this is where the actual replacement of the text happens
    }
}

class conflict2{
    public boolean conflictCheck(String fileName,String username, String id ){
        boolean r = true;
        String str[];
        try {
            
            
            
            Scanner scanner = new Scanner(new File(fileName)); //handle this
            //now read the file line by line...
            int lineNum = 0;
            
            while (scanner.hasNextLine()) {
                if(r){
                String line = scanner.nextLine();
                str = line.split(",");
                lineNum++;
                if(str[2].equals(id)){
                    JOptionPane.showMessageDialog(null, "User ID is already in use", "Error", JOptionPane.ERROR_MESSAGE);
                    r= false;
                    break;
                }
                if(str[0].equals(username)) {
                   
                    JOptionPane.showMessageDialog(null, "Username is already in use", "Error", JOptionPane.ERROR_MESSAGE);
                    r= false;
                    break;
                }
                
                
                }  
                
            }
            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(conflict.class.getName()).log(Level.SEVERE, null, ex);
        }
        return r;
    }
}