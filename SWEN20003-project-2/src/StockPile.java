import bagel.Font;

/**
 * Class that contains methods and attributes for a stockpile
 */
public class StockPile extends Actor {
    /**
     * TYPE is the type of actor
     */
    public static final String TYPE = "Stockpile";
    private final Font font = new Font("res/VeraMono.ttf", 15);
    private int stock;

    /**
     * Constructor to create a stockpile at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public StockPile(int x, int y) {
        super("res/images/cherries.png", TYPE, x, y);
    }

    /**
     * get the current stock of the stockpile
     *
     * @return current stock
     */
    public int getStock() {
        return stock;
    }

    /**
     * set the stock of the stockpile
     *
     * @param stock the stock value
     */
    public void setStock(int stock) {
        this.stock = stock;
    }

    /**
     * update state of stockpile at each tick
     */
    @Override
    public void update() {

    }

    /**
     * render the image of the stockpile and draw the stock
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
        font.drawString(Integer.toString(stock), getX(), getY());

    }
}
