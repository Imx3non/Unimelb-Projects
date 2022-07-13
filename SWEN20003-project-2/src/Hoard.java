import bagel.Font;

/**
 * Class that contains methods and attributes related to a hoard
 */
public class Hoard extends Actor {
    /**
     * TYPE is the type of actor
     */
    public static final String TYPE = "Hoard";
    private final Font font = new Font("res/VeraMono.ttf", 15);
    private int stock;

    /**
     * create a hoard at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public Hoard(int x, int y) {
        super("res/images/hoard.png", TYPE, x, y);
    }

    /**
     * get the stock of the hoard
     *
     * @return the stock of hoard
     */
    public int getStock() {
        return stock;
    }

    /**
     * set the hoard stock
     *
     * @param stock the new stock
     */
    public void setStock(int stock) {
        this.stock = stock;
    }

    /**
     * update the state at each tick
     */
    @Override
    public void update() {

    }

    /**
     * render the image of the hoard and draw the stock
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
        font.drawString(Integer.toString(stock), getX(), getY());
    }
}
