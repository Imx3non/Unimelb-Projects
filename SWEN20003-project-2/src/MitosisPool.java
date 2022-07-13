/**
 * Class that contains methods and attributes related to a pool
 */
public class MitosisPool extends Actor {
    /**
     * TYPE is the type of actor
     */
    public static final String TYPE = "Pool";

    /**
     * Constructor to create a pool at the given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public MitosisPool(int x, int y) {
        super("res/images/pool.png", TYPE, x, y);
    }

    /**
     * update state of pool
     */
    @Override
    public void update() {

    }

    /**
     * render the pool image
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }
}
