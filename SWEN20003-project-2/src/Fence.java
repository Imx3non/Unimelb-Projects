/**
 * Class that contains methods and attributes related to a fence
 */

public class Fence extends Actor {
    /**
     * TYPE is the type of actor
     */
    public static final String TYPE = "Fence";

    /**
     * Constructor to create a fence at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public Fence(int x, int y) {
        super("res/images/fence.png", TYPE, x, y);
    }

    /**
     * update state of fence
     */
    @Override
    public void update() {

    }

    /**
     * render the image of the fence
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }
}
