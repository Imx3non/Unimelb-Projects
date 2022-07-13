package automail;

import com.unimelb.swen30006.wifimodem.WifiModem;
import util.Configuration;
import exceptions.FailedToConnect;

/**
 * Building class which stores the different floor objects and assigned mailroom floor
 */
public class Building
{
    /** The number of floors in the building **/
    private final int nFloors;
    
    /** Represents the ground floor location */
    private final int lowestFloor;
    
    /** Represents the mailroom location */
    private final int mailroomLocationFloor;

    /** Static building class object */
    private static Building building;
    
    
    /** Floor objects assigned to the building */
    private final Floor[] floors;

    /**
     * Constructor for Building class which initializes floor objects
     * @param nFloors, total number of floors
     * @param lowestFloor, lowest floor for the building
     * @param mailroomLocationFloor, location of mail room
     */
    private Building(int nFloors, int lowestFloor, int mailroomLocationFloor)
    {
        this.nFloors = nFloors;
        this.lowestFloor = lowestFloor;
        this.mailroomLocationFloor = mailroomLocationFloor;
        this.floors = new Floor[nFloors];
        // Initialize each floor objects
        for (int i = lowestFloor; i < lowestFloor+nFloors; i++) {
            floors[i-lowestFloor] = new Floor(i);
        }

    }

    /**
     * Getter to get Building instance
     * @return building object
     */
    public static Building getInstance() {
    	// check if there is an existing building object
        if(building == null)
        {
            Configuration configuration = Configuration.getInstance();
            int nFloors = Integer.parseInt(configuration.getProperty(Configuration.N_FLOORS_KEY));
            int lowestFloor = Integer.parseInt(configuration.getProperty(Configuration.LOWEST_FLOOR_KEY));
            int mailroomLocationFloor = Integer.parseInt(configuration.getProperty(Configuration.MAILROOM_LOCATION_FLOOR_KEY));
            building = new Building(nFloors, lowestFloor, mailroomLocationFloor);
        }

        return building;
    }
    
    /**
     * Get number of floors assigned to a building
     * @return number of floors in a building
     */
    public int getnFloors() {
        return nFloors;
    }
    
    /**
     * Get lowest floor in a building
     * @return number of floors in a building
     */
    public int getLowestFloor() {
        return lowestFloor;
    }


    /**
     * Get specific floor object
     * @param floorNumber floor being searched for
     * @return floor object for requested floor
     */
    public Floor getFloor(int floorNumber){
        return floors[floorNumber-lowestFloor];
    }

    
    /**
     * Get mailroom floor number for building 
     * @return mailroom number
     */
    public int getMailroomLocationFloor() {
        return mailroomLocationFloor;
    }
    
    /**
     * Update service fee for specific floor
     * @param floorNumber whose service needs to be updated
     */
    public void updateFloorServiceFee(int floorNumber){
        try {
            WifiModem connection = WifiModem.getInstance(floorNumber);
            double ServiceFee = connection.forwardCallToAPI_LookupPrice(floorNumber);
            floors[floorNumber-lowestFloor].setRecentServiceFee(ServiceFee);
        } catch (Exception FailedToConnect) {
        	FailedToConnect.printStackTrace();
        }
    }


}
