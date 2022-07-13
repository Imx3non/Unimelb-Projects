package automail;

import simulation.IMailDelivery;


/**
 * Automail class which is used to intialize and store the different robot objects and mailpool system
 */
public class Automail {

    private Robot[] robots;
    private MailPool mailPool;


    /**
     * Automail class that initializes the different robot typs and mailpool
     * @param mailPool mailpool object used to store and assign MailItems to robot
     * @param delivery object used by a Robot to deliver mail once it has arrived at the correct location
     * @param numRegRobots the number of Regular Robots in the system
     * @param numFastRobots the number of Fast Robots
     * @param numBulkRobots the number of Bulk Robots in the system
     */
    public Automail(MailPool mailPool, IMailDelivery delivery, int numRegRobots, int numFastRobots, int numBulkRobots) {
    	// Initialize the MailPool
    	
    	this.mailPool = mailPool;

        // Initialize robots with Robot class with the total number of Robots
        robots = new Robot[numRegRobots + numFastRobots + numBulkRobots];

        for (int i = 0; i < numRegRobots; i++) robots[i] = new RegRobot(delivery, mailPool, i);
        for (int i = numRegRobots; i < numRegRobots+numFastRobots; i++) robots[i] = new FastRobot(delivery, mailPool, i);
        for (int i = numRegRobots+numFastRobots; i < numRegRobots+numFastRobots+numBulkRobots; i++) robots[i] = new BulkRobot(delivery, mailPool, i);

        // set the static number of robots for each robot type
        RegRobot.setRobotCount(numRegRobots);
        FastRobot.setRobotCount(numFastRobots);
        BulkRobot.setRobotCount(numBulkRobots);
    }

    /**
     * Getter method to get all robots.
     * @return all robots stored in array
     */
    public Robot[] getRobots() {
        return robots;
    }

    /**
     * Getter to get the mailpool system
     * @return the mailpool object used to distribute mailitems
     */
    public MailPool getMailPool() {
        return mailPool;
    }

    /**
     * Method to calculate string for a delivery, it calls the Robot maintenance fee and Floor Fee
     * @param assignedRobot, robot that was assigned to a delivery
     * @param assignedFloor, floor that was assigned 
     * @return string which displays the sum of robot maintenace amount and floor service amount
     */
    public static String calculateFeeString(Robot assignedRobot, Floor assignedFloor){
        return String.format(" | Total Charge: %.2f", assignedRobot.getMaintenanceAmount() + assignedFloor.getRecentServiceFee());
    }
}

