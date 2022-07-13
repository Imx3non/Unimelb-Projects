package automail;

import exceptions.ExcessiveDeliveryException;
import exceptions.ItemTooHeavyException;
import simulation.IMailDelivery;

/**
 * Abstract Robot object that is a template for other Robots
 */
public abstract class Robot {

	
    /** Max weight for an object item */
    protected static final int INDIVIDUAL_MAX_WEIGHT = 2000;
    
    /** Delivery object that is used by a robot to deliver an item */
    private IMailDelivery delivery;
    
   
    /** Robot ID */
    private String id;

    /** Possible states the robot can be in */
    public enum RobotState { DELIVERING, WAITING, RETURNING }
    /** Current Robot state*/
    private RobotState current_state;

    /** Current Floor the robot is on */
    private int current_floor;
    
    /** Floor robot is moving towards*/
    private int destination_floor;

    
    /** mailpool object the robot is assinged to */
    protected MailPool mailPool;
    
    
    /** check if the robot has recieved an item */
    private boolean receivedDispatch;

    /** count the total number of items the robot has delivered */
    private int deliveryCounter;
    
    /** robot speed */
    private int speed;
    
    /** maximum number of items a robot can store in its  */
    private int maxItems;

    /** number of items the robot has */
    private int numItems = 0;


    /**
     * Initiates the robot's location at the start to be at the mailroom
     * also set it to be waiting for mail.
     * @param delivery governs the final delivery
     * @param mailPool is the source of mail items
     */
    public Robot(IMailDelivery delivery, MailPool mailPool, int number){
    	this.id = "R" + number;
        // current_state = RobotState.WAITING;
    	current_state = RobotState.RETURNING;
        current_floor = Building.getInstance().getMailroomLocationFloor();
        this.delivery = delivery;
        this.mailPool = mailPool;
        this.receivedDispatch = false;
        this.deliveryCounter = 0;
    }

    /**
     * This is called on every time step
     * @throws ExcessiveDeliveryException if robot delivers more than the capacity of the tube without refilling
     */
    public void operate() throws ExcessiveDeliveryException {   
    	switch(current_state) {
    		/** This state is triggered when the robot is returning to the mailroom after a delivery */
    		case RETURNING:
                incrementOperationalTime();
                /** If its current position is at the mailroom, then the robot should change state */
                if(current_floor == Building.getInstance().getMailroomLocationFloor()){
        			/** Tell the sorter the robot is ready */
        			mailPool.registerWaiting(this);
        			changeState(RobotState.WAITING);
                } else {
                	/** If the robot is not at the mailroom floor yet, then move towards it! */
                    int x = 0;
                    while(x < speed && getCurrent_floor() != Building.getInstance().getMailroomLocationFloor()) {
                        moveTowards(Building.getInstance().getMailroomLocationFloor());
                        x++;
                    }
                }
                break;
            case WAITING:
                /** If the StorageTube is ready and the Robot is waiting in the mailroom then start the delivery */
                if(!isEmpty() && receivedDispatch){
                	receivedDispatch = false;
                	deliveryCounter = 0; // reset delivery counter
                	setDestination();
                	changeState(RobotState.DELIVERING);
                }
                break;
    		case DELIVERING:
                incrementOperationalTime();
                if(getCurrent_floor() == getDestination_floor()){
                    this.deliver();
                } else {
                    int x = 0;
                    while(x < speed && getCurrent_floor() != getDestination_floor()) {
                        moveTowards(getDestination_floor());
                        x++;
                    }
                }
                break;
    	}
    }

    /*** Generic function that moves the robot towards the destination
     * @param destination the floor towards which the robot is moving
     */
    protected void moveTowards(int destination) {
        if(current_floor < destination){
            current_floor++;
        } else {
            current_floor--;
        }
    }

    /**
     * This is called when a robot is assigned the mail items and ready to dispatch for the delivery
     */
    public void dispatch() {
        receivedDispatch = true;
    }


    /**
     * Setter to set the Robot speed
     * @param speed, robot speed to be set
     */
    public void setSpeed(int speed) { this.speed = speed; }

    /**
     * Getter to get robot's speed 
     * @return robot speed
     */
    public int getSpeed(){ return this.speed; }

    /**
     * Set the id for the robot
     * @param new id of the robot
     */
    public void setID(String id) { this.id = id; }

    /**
     * Get the id for the robot
     * @return id of the robot
     */
    public String getID() { return id; }

    /**
     * Set the max number of items the robot can carry
     * @param maxItems the max items a robot can carry
     */
    public void setMaxItems(int maxItems) { this.maxItems = maxItems; }

    /**
     * Getter to get the max number of items a robot carries
     * @return the max items a robot can carry
     */
    public int getMaxItems() { return maxItems; }

    /**
     * Get teh MailDelivery object used by the robot
     * @return IMailDelivery objecte used to deliver an item
     */
    public IMailDelivery getDelivery() { 
    	return delivery; 
    }

    /**
     * Set the delivery counter for the robot
     * @param deliveryCounter amount needs to be set
     */
    public void setDeliveryCounter(int deliveryCounter) {
    	this.deliveryCounter = deliveryCounter; 
    }

    /**
     * Get the number of items to be delivered
     * @return return the number of items that have been delivered
     */
    public int getDeliveryCounter() { 
    	return deliveryCounter;
    }

    /**
     * Increment the delivery counter 
     */
    public void incrementDeliveryCounter() {
    	this.deliveryCounter++; 
    }

    /**
     * Update the status of delivery when an item was delivered
     * @param receivedDispatch new status
     */
    public void setReceivedDispatch(boolean receivedDispatch) { 
    	this.receivedDispatch = receivedDispatch; 
    }

    /**
     * Check if the Robot has recieved a dispatch
     * @return robot dispatch status
     */
    public boolean getReceivedDispatch() { 
    	return receivedDispatch; 
    }

    /**
     * Get the current floor the robot is on
     * @return  the floor the current robot is on
     */
    public int getCurrent_floor(){ 
    	return this.current_floor; 
    }

    /**
     * Set the robot's current floor
     * @param current_floor the robot is on
     */
    public void setCurrent_floor(int current_floor) { this.current_floor = current_floor; }

    /**
     * Set the Robot destintion floor that it needs to travel to
     * @param destination_floor which the robot is targetting
     */
    public void setDestination_floor(int destination_floor) { this.destination_floor = destination_floor; }

    /**
     * Get the destination floor the robot needs to go to
     * @return the destination floor the robot is moving towards
     */
    public int getDestination_floor() { return destination_floor; }

    /**
     * Get the number of items the robot currently has
     * @return number of items
     */
    public int getNumItems() {
    	return numItems; 
    }

    /**
     * Method to increment the number of items the robot currently has
     */
    public void incrementNumItems() { 
    	numItems++; 
    }

    /**
     * Method to decrement the number of items the robot currently has
     */
    public void decrementNumItems() { numItems--; }

    /**
     * Method to change the robot current state
     * @param newRobotState, new state the robot is set to
     */
    public void setCurrent_state(RobotState newRobotState){ 
    	this.current_state = newRobotState; 
    }

    /**
     * Get the current state the Robot is in
     * @return current state the robot is in
     */
    public RobotState getCurrent_state(){ 
    	return this.current_state; 
    }

    /**
     * Changes Robot to next state
     */
    protected abstract void changeState(RobotState nextState);

    /**
     * Checks if Robot is empty
     */
	public abstract boolean isEmpty();

    /**
     * Formats the ID of the Robot for printing
     */
    public abstract String getFormatID();

    /**
     * Formats the Robots operating time for printing
     */
    public abstract String OperatingTimeString();

    /**
     * Get maintenance amount for a Robot class 
     * @return the maintance amount for a robot
     */
    public abstract double getMaintenanceAmount();
    
    /**
     * Get maintenance cost for a Robot class 
     * @return the maintance cost for a robot
     */
    public abstract String MaintenanceCostString();
    
    /**
     * Increment total opeerational time for robot type 
     */
    public abstract void incrementOperationalTime();
    
    /**
     * Method to manage robot delivery
     * @throws ExcessiveDeliveryException
     */
    protected abstract void deliver() throws ExcessiveDeliveryException;
    
    /**
     * Load an item to the robot tube/hand
     * @param mailItem
     * @throws ItemTooHeavyException
     */
    protected abstract void loadItem(MailItem mailItem) throws ItemTooHeavyException;
    
    /**
     * Abstract class to set the robot
     */
    public abstract void setDestination();


}
