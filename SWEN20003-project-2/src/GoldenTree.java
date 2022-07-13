/**
 * Class that contains methods and attributes related to a golden tree
 */
public class GoldenTree extends Actor {
    /**
     * TYPE is the type of actor
     */
    public static final String TYPE = "GoldenTree";

    /**
     * Constructor to create a golden tree at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public GoldenTree(int x, int y) {
        super("res/images/gold-tree.png", TYPE, x, y);
    }

    /**
     * update the golden tree
     */
    @Override
    public void update() {

    }

    /**
     * render the image of the golden tree
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }
}
