public class directory {
    private final static String home = "C:\\Users\\Shafiq\\Documents\\NetBeansProjects\\Booking System\\src";
    protected final static String file = home + "\\eventsDatabase";
    protected final static String slotpath = home + "\\eventsDatabase\\slots\\slots.txt";
    protected final static String student = home + "\\loginDatabase/studentLogin.txt";
    protected final static String staff = home + "\\loginDatabase/staffLogin.txt";
    
    public directory() {
        
    }
    
    public static String getFile(){
        return file;
    }
    
    public static String getSlot(){
        return slotpath;
    }
    
    public static String getStudent(){
        return student;
    }
    
    public static String getStaff(){
        return staff;
    }
}
