class userID {
    protected static String id;
    static String getID;
   
    public userID() {
        
    }
    
    public userID(String id){
        this.id = id;
    }
    
    public void setID(String id){
        this.id = id;
    }
    
    public static String getID(){
        return id;
    }
}