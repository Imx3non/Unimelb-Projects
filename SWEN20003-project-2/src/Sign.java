/**
 * Class that contains methods and attributes for a sign
 */
public class Sign extends Actor {

    /**
     * TYPE1 used for up direction
     */
    public static final String TYPE1 = "SignUp";
    /**
     * TYPE1LOCATION stores the location of TYPE1 image
     */
    public static final String TYPE1LOCATION = "res/images/up.png";

    /**
     * TYPE2 used for down direction
     */
    public static final String TYPE2 = "SignDown";

    /**
     * TYPE2LOCATION stores the location of TYPE2 image
     */
    public static final String TYPE2LOCATION = "res/images/down.png";

    /**
     * TYPE13 used for left direction
     */
    public static final String TYPE3 = "SignLeft";

    /**
     * TYPE3LOCATION stores the location of TYPE3 image
     */
    public static final String TYPE3LOCATION = "res/images/left.png";

    /**
     * TYPE4 used for right direction
     */
    public static final String TYPE4 = "SignRight";

    /**
     * TYPE4LOCATION stores the location of TYPE4 image
     */
    public static final String TYPE4LOCATION = "res/images/right.png";

    private final int direction;

    /**
     * Constructor to create a sign at a given position and direction
     *
     * @param x         x coord
     * @param y         y coord
     * @param Filename  image path
     * @param type      type of actor
     * @param direction direction of sign
     */
    public Sign(int x, int y, String Filename, String type, int direction) {

        super(Filename, type, x, y);
        this.direction = direction;
    }

    /**
     * get the direction of the sign
     *
     * @return int direction of sign
     */
    public int getDirection() {
        return direction;
    }

    /**
     * update state of sign
     */
    @Override
    public void update() {

    }

    /**
     * draw the image of sign
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }

}

