import bagel.Font;

/**
 * Class that contains attributes and methods for Tree
 */
public class Tree extends Actor {

    /**
     * TYPE is the type of actor
     */

    public static final String TYPE = "Tree";
    private final Font font = new Font("res/VeraMono.ttf", 15);
    private int fruits;

    /**
     * constructor to create a tree at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public Tree(int x, int y) {
        super("res/images/tree.png", TYPE, x, y);
    }

    /**
     * get the number of fruits at the a tree
     *
     * @return number of fruits
     */
    public int getFruits() {
        return fruits;
    }

    /**
     * set the number of fruits at a tree
     *
     * @param fruits number of fruits
     */
    public void setFruits(int fruits) {
        this.fruits = fruits;
    }

    /**
     * render the image of a tree and draw the number of fruits
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
        font.drawString(Integer.toString(fruits), getX(), getY());

    }

    /**
     * update the state at each tick
     */
    @Override
    public void update() {
    }
}
