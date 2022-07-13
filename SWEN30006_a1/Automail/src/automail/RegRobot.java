package automail;

import exceptions.ExcessiveDeliveryException;
import exceptions.ItemTooHeavyException;
import simulation.Clock;
import simulation.IMailDelivery;

public class RegRobot extends Robot {

    /**
     * Fast Robot speed that is x3 than a regular robot
     */
    private static final int SPEED = 1;

    /**
     * The max number of items a fast robot moves
     */
    private static final int MAX_ITEMS = 2;

    /**
     * Maintance rate for fast Robot
     */
    private static final double rate = 0.025;

    /**
     * MailItem in the Robot hand
     */
    private MailItem deliveryItem = null;

    /**
     * MailItem Tube
     */
    private MailItem tube = null;


    /**
     * static variable to store total number of robots of a specific class
     */
    private static int robotCount = -1;

    /**
     * static variable to store total operating time of a robot
     */
    private static int totalOperationTime= 0;


    /**
     * Constructor for Regular robot
     * @param delivery governs the final delivery
     * @param mailPool mailpool its assigned to
     * @param number fast robot number its assigned to
     */
    public RegRobot(IMailDelivery delivery, MailPool mailPool, int number) {
        super(delivery, mailPool, number);
        super.setSpeed(SPEED);
        super.setMaxItems(MAX_ITEMS);
        super.setID("R" + number);
    }

    /**
     * Give a mailitem to the immediate hand for robot
     * @param mailItem
     * @throws ItemTooHeavyException
     */
    public void addToHand(MailItem mailItem) throws ItemTooHeavyException {
        assert(deliveryItem == null);
        deliveryItem = mailItem;
        incrementNumItems();
        if (deliveryItem.weight > INDIVIDUAL_MAX_WEIGHT) throw new ItemTooHeavyException();
    }

    /**
     * Give a mailitem to the immediate hand for robot
     * @param mailItem
     * @throws ItemTooHeavyException
     */
    public void addToTube(MailItem mailItem) throws ItemTooHeavyException {
        assert(tube == null);
        tube = mailItem;
        incrementNumItems();
        if (tube.weight > INDIVIDUAL_MAX_WEIGHT) throw new ItemTooHeavyException();
    }

    /**
     * Override delivery for parent
     * @throws ExcessiveDeliveryException
     */
    @Override
    public void deliver() throws ExcessiveDeliveryException {

        /** Delivery complete, report this to the simulator! */
        super.getDelivery().deliver(this, deliveryItem, "");
        deliveryItem = null;
        decrementNumItems();
        incrementDeliveryCounter();


        if(getDeliveryCounter() > 2){  // Implies a simulation bug
            throw new ExcessiveDeliveryException();
        }
        /** Check if want to return, i.e. if there is no item in the tube*/
        if(tube == null){
            changeState(RobotState.RETURNING);
        }
        else{
            /** If there is another item, set the robot's route to the location to deliver the item */
            deliveryItem = tube;
            tube = null;
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
        if(deliveryItem == null) {
            addToHand(mailItem);
        } else {
            addToTube(mailItem);
        }
    }

    /**
     * Update Robot destination based on currently delivery item
     */
    @Override
    public void setDestination() {
        setDestination_floor(deliveryItem.getDestFloor());
    }

    /**
     * Check if the robot has no delivery item
     * @return boolean if the robot has no delivery item
     */
    @Override
    public boolean isEmpty() {
        if(deliveryItem == null && tube == null) {
            return true;
        }
        return false;
    }

    /**
     * Change Robot state based on nextstate
     * @param nextState which needs to be updated
     */
    protected void changeState(RobotState nextState){
        assert(!(deliveryItem == null && tube != null));
        if (getCurrent_state() != nextState) {
            System.out.printf("T: %3d > %7s changed from %s to %s%n", Clock.Time(), getFormatID(), getCurrent_state(), nextState);
        }
        setCurrent_state(nextState);
        if(nextState == RobotState.DELIVERING){
            System.out.printf("T: %3d > %7s-> [%s]%n", Clock.Time(), getFormatID(), deliveryItem.toString());
        }
    }

    /**
     * To String method that get the Robot ID
     * @return robot id string
     */
    public String getFormatID() {
        return String.format("%s(%1d)", super.getID(), (tube == null ? 0 : 1));
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
     * Get average operating time of a robot type
     * @return average time of a robot type
     */
    public double getAverageOperatingTime(){
        return Double.valueOf(totalOperationTime)/getRobotCount();
    }

    /**
     * Get Operational time string
     * @return Operational time string
     */
    public String OperatingTimeString(){
        return String.format(" | Avg. Operating Time: %.2f", getAverageOperatingTime());
    }

}