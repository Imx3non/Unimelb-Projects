package automail;

import exceptions.ExcessiveDeliveryException;
import exceptions.ItemTooHeavyException;
import simulation.Clock;
import simulation.IMailDelivery;



/**
 * 
 * @author acmah
 */
public class BulkRobot extends Robot {

    /**
     * Fast Robot speed that is x3 than a regular robot
     */
    private static final int SPEED = 1;

    /**
     * The max number of items a bulk robot moves
     */
    private static final int MAX_ITEMS = 5;

    /**
     * Maintance rate for Bulk Robot
     */
    private static final double rate = 0.01;

    /**
     * MailItem Array tube
     */
    private final MailItem[] tube = new MailItem[MAX_ITEMS];


    /**
     * static variable to store total number of robots of a specific class
     */
    private static int robotCount = -1;

    /**
     * static variable to store total operating time of a robot
     */
    private static int totalOperationTime= 0;

    /**
     * Constructor for Bulk robot
     * @param delivery governs the final delivery
     * @param mailPool mailpool its assigned to
     * @param number fast robot number its assigned to
     */
    public BulkRobot(IMailDelivery delivery, MailPool mailPool, int number) {
        super(delivery, mailPool, number);
        super.setSpeed(SPEED);
        super.setMaxItems(MAX_ITEMS);
        super.setID("B" + number);
    }

    /**
     * Give a mailitem to the immediate hand for robot
     * @param mailItem
     * @throws ItemTooHeavyException
     */
    public void addToTube(MailItem mailItem) throws ItemTooHeavyException {
        assert(tube[getNumItems()] == null);
        tube[getNumItems()] = mailItem;
        if (tube[getNumItems()].weight > INDIVIDUAL_MAX_WEIGHT) throw new ItemTooHeavyException();
        incrementNumItems();
    }

    /**
     * Override delivery for parent
     * @throws ExcessiveDeliveryException
     */
    @Override
    public void deliver() throws ExcessiveDeliveryException {
        decrementNumItems();
        super.getDelivery().deliver(this, tube[getNumItems()], "");
        tube[getNumItems()] = null;
        incrementDeliveryCounter();
        if(getDeliveryCounter() > 5){  // Implies a simulation bug
            throw new ExcessiveDeliveryException();
        }
        // Check if want to return, i.e. if there is no item in the tube
        if(getNumItems() == 0){
            changeState(RobotState.RETURNING);
        }
        else{
            // If there is another item, set the robot's route to the location to deliver the item
            setDestination();
            changeState(RobotState.DELIVERING);
        }
    }

    /**
     * Add item to robot hand
     * @param mailItem to
     * @throws ItemTooHeavyException
     */
    @Override
    public void loadItem(MailItem mailItem) throws ItemTooHeavyException {
        addToTube(mailItem);
    }

    /**
     * Check if the robot has no delivery item
     * @return boolean if the robot has no delivery item
     */
    @Override
    public boolean isEmpty() {
        return getNumItems() == 0;
    }


    /**
     * Update Robot destination based on currently delivery item
     */
    @Override
    public void setDestination() {
        setDestination_floor(tube[getNumItems() - 1].getDestFloor());
    }

    /**
     * Change Robot state based on nextstate
     * @param nextState which needs to be updated
     */
    protected void changeState(RobotState nextState){
        assert(tube[getNumItems() - 1] == null);
        if (getCurrent_state() != nextState) {
            System.out.printf("T: %3d > %7s changed from %s to %s%n", Clock.Time(), getFormatID(), getCurrent_state(), nextState);
        }
        setCurrent_state(nextState);
        if(nextState == RobotState.DELIVERING){
            System.out.printf("T: %3d > %7s-> [%s]%n", Clock.Time(), getFormatID(), tube[getNumItems() - 1].toString());
        }
    }

    /**
     * To String method that get the Robot ID
     * @return robot id string
     */
    public String getFormatID() {
        return String.format("%s(%1d)", super.getID(), getNumItems());
    }

    /**
     * Getter to get the robot count
     * @return get the total number of count
     */
    public static int getRobotCount() {
        return robotCount;
    }

    /**
     * Update total number of Fast Robots
     * @param robots
     */
    public static void setRobotCount(int robots) {
        robotCount = robots;
    }

    /**
     * Increment total operational time of a fast time
     */
    public void incrementOperationalTime(){
        totalOperationTime++;
    }

    /**
     * Get average operating time of a robot type
     * @return average time of a robot type
     */
    public double getAverageOperatingTime(){
        return ((double) totalOperationTime /getRobotCount());
    }

    /**
     * Get the maintance amount based on Average Time multiplied by type rate
     * @return maintance amount based on Average Time
     */
    public double getMaintenanceAmount(){
        return getAverageOperatingTime() * rate;
    }

    /**
     * Get maintenance cost string
     * @return maintenance cost string
     */
    public String MaintenanceCostString() {
        return String.format(" | Maintenance: %.2f",getMaintenanceAmount());
    }

    /**
     * Get Operational time string
     * @return Operational time string
     */
    public String OperatingTimeString(){
        return String.format(" | Avg. Operating Time: %.2f", getAverageOperatingTime());
    }

}
