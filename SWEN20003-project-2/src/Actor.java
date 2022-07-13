/*Used actor class provided in sample solution of project 1*/

import bagel.Image;

/**
 * Class that contains attributes of each actor
 * stores the position, type and image
 */
public abstract class Actor {
    /**
     * TYPE is the type of actor
     */
    public final String type;
    private final Image image;
    private int x;
    private int y;

    /**
     * Constructor to initialise the type and Image to null
     */
    public Actor() {
        this.type = null;
        this.image = null;
    }

    /**
     * constructor to create the image of the actor, assign the type and the coordinates
     *
     * @param filename path of the image
     * @param type     type of actor
     * @param x        x-coord
     * @param y        y-coord
     */
    public Actor(String filename, String type, int x, int y) {
        image = new Image(filename);
        this.type = type;
        this.x = x;
        this.y = y;
    }

    /**
     * update the actors after each tick
     */
    public final void tick() {
        update();
    }

    /**
     * render each actor
     */
    public abstract void render();

    /**
     * move the actor by the Tile spacing
     *
     * @param deltaX 0 if moving in y direction
     * @param deltaY 0  if moving in x direction
     */
    public void move(int deltaX, int deltaY) {
        x += deltaX;
        y += deltaY;
    }

    /**
     * Check to see if 2 actors are at same position
     *
     * @param OtherActor Other actor to compare with
     * @return bool true if at same position
     */
    public boolean equals(Actor OtherActor) {

        return (this.x == OtherActor.x && this.y == OtherActor.y);

    }

    /**
     * get the image of the actor
     *
     * @return image of actor
     */
    public Image getImage() {
        return image;
    }

    /**
     * update state of each actor
     */
    public abstract void update();

    /**
     * get x coord
     *
     * @return x coord
     */
    public int getX() {
        return x;
    }

    /**
     * set the x-coord
     *
     * @param x the x-coord
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * get y-coord
     *
     * @return the y-coord
     */
    public int getY() {
        return y;
    }

    /**
     * set the y-coord
     *
     * @param y the y-coord
     */
    public void setY(int y) {
        this.y = y;
    }
}
