class eventInfo {
    protected static String venue, date, time, name, slot;
   
    public eventInfo() {
        
    }
    
    public eventInfo(String venue, String date, String time){
        this.venue = venue;
        this.date = date;
        this.time = time;
    }
    
    public eventInfo(String venue, String date, String time, String name, String slot){
        this.venue = venue;
        this.date = date;
        this.time = time;
        this.name = name;
        this.slot = slot;
    }
    
    public void setInfo(String venue, String date, String time, String name, String slot){
        this.venue = venue;
        this.date = date;
        this.time = time;
        this.name = name;
        this.slot = slot;
    }
    
    public static String getVenue(){
        return venue;
    }
    
    public static String getDate(){
        return date;
    }
    
    public static String getTime(){
        return time;
    }  
    
    public static String getName(){
        return name;
    }
    
    public static String getSlot(){
        return slot;
    }
}
