/**
 * Class that contains methods and attributes related to a Pad
 */
public class Pad extends Actor {
    /**
     * TYPE is the type of actor
     */
    public static final String TYPE = "Pad";

    /**
     * Constructor to create a pad at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public Pad(int x, int y) {
        super("res/images/pad.png", TYPE, x, y);

    }

    /**
     * render the image of the pad
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }

    /**
     * update state of pad at each tick
     */
    @Override
    public void update() {

    }
}
