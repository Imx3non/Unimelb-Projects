package automail;

public class Floor {

    /**
     * Assigned Floor Number
     */
    private int floorNumber = 0;

    /**
     * Most Recent Service Fee
     */
    private double recentServiceFee = 0;

    /**
     * Constructor for Floor class
     * @param setfloorNumber, floor number assigned
     */
    public Floor(int setfloorNumber){
        this.floorNumber = setfloorNumber;
    }

    /**
     * Getter for floor number
     * @return floor number
     */
    public int getFloorNumber() {
        return floorNumber;
    }

    /**
     * Get most recent service fee for floor
     * @return recent service fee
     */
    public double getRecentServiceFee() {
        return recentServiceFee;
    }

    /**
     * Set the floor number
     * @param floorNumber, set floor number
     */
    public void setFloorNumber(int floorNumber) {
        this.floorNumber = floorNumber;
    }

    /**
     * Update service fee with most recent service fee
     * @param recentServiceFee, service fee to be set
     */
    public void setRecentServiceFee(double recentServiceFee) {
        // update service fee, unless negative value
        this.recentServiceFee = recentServiceFee > 0 ? recentServiceFee:this.recentServiceFee;
    }

    /**
     * Format String for recent service fee
     * @return string with most recent service fee
     */
    public String RecentServiceFeeString(){
        return String.format(" | Service Fee: %.2f", this.getRecentServiceFee());
    }


}
