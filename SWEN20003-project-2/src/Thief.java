/**
 * Class that contains methods and attributes for a thief
 */

public class Thief extends Actor {
    /**
     * TYPE is the type of actor
     */

    public static final String TYPE = "Thief";
    private int direction;
    private boolean carrying;
    private boolean active;
    private boolean consuming;

    /**
     * Constructor to create a thief at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public Thief(int x, int y) {
        super("res/images/thief.png", TYPE, x, y);
    }

    /**
     * Constructor to create a thief with a given position and direction
     *
     * @param direction direction of thief
     * @param x         x-coord
     * @param y         y-coord
     */
    public Thief(int direction, int x, int y) {
        super("res/images/thief.png", TYPE, x, y);
        this.direction = direction;
    }

    /**
     * get the current direction of the thief
     *
     * @return int direction of thief
     */
    public int getDirection() {
        return direction;
    }

    /**
     * set the direction of the thief
     *
     * @param direction the direction the the thief
     */
    public void setDirection(int direction) {
        this.direction = direction;
    }

    /**
     * check if thief is carrying
     *
     * @return bool true if carrying
     */
    public boolean isCarrying() {
        return carrying;
    }

    /**
     * set the carrying status of the thief
     *
     * @param carrying bool true if carrying else false
     */
    public void setCarrying(boolean carrying) {
        this.carrying = carrying;
    }

    /**
     * check if thief is active
     *
     * @return bool true if active
     */
    public boolean isActive() {
        return active;
    }

    /**
     * set the thief active
     *
     * @param active bool
     */
    public void setActive(boolean active) {
        this.active = active;
    }

    /**
     * check if thief is consuming
     *
     * @return bool
     */
    public boolean isConsuming() {
        return consuming;
    }

    /**
     * set consuming status
     *
     * @param consuming bool
     */
    public void setConsuming(boolean consuming) {
        this.consuming = consuming;
    }

    /**
     * render the image of the thief
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }

    /**
     * move thief at each tick
     */
    @Override
    public void update() {
        if (this.active) moveThief();
    }

    /**
     * update the state of the thief according to the algorithm
     *
     * @param actor the actor on which the theif is on
     */
    public void updateState(Actor actor) {

        if (actor instanceof Fence) thiefAtFence();
        else if (actor instanceof MitosisPool) thiefOnPool();
        else if (actor instanceof Sign) thiefOnSign((Sign) actor);
        else if (actor instanceof Pad) thiefOnPad();
        else if (actor instanceof Gatherer && ((Gatherer) actor).isPerformedTick()) thiefOnGatherer();
        else if (actor instanceof Tree) thiefOnTree((Tree) actor);
        else if (actor instanceof GoldenTree) thiefOnGoldenTree();
        else if (actor instanceof Hoard) thiefOnHoard((Hoard) actor);
        else if (actor instanceof StockPile) thiefOnStockPile((StockPile) actor);

    }

    /**
     * initialise the thief according to the algorithm
     *
     * @param thief thief to initialise
     */
    public void initialiseThief(Thief thief) {

        thief.setDirection(Direction.UP);
        thief.setCarrying(false);
        thief.setConsuming(false);
        thief.setActive(true);
    }

    /**
     * rotate thief clockwise by 90 degrees
     */
    public void rotateClockwise() {
        switch (direction) {
            case Direction.UP:
                this.direction = Direction.RIGHT;
                break;
            case Direction.DOWN:
                this.direction = Direction.LEFT;
                break;
            case Direction.LEFT:
                this.direction = Direction.UP;
                break;
            case Direction.RIGHT:
                this.direction = Direction.DOWN;
                break;
        }
    }

    /**
     * rotate thief anticlockwise by 90 degrees
     */
    public void rotateAntiClockwise() {
        switch (direction) {
            case Direction.UP:
                this.direction = Direction.LEFT;
                break;
            case Direction.DOWN:
                this.direction = Direction.RIGHT;
            case Direction.LEFT:
                this.direction = Direction.DOWN;
            case Direction.RIGHT:
                this.direction = Direction.UP;
        }
    }

    /**
     * move thief in its current direction
     */
    public void moveThief() {
        switch (direction) {
            case Direction.UP:
                move(0, -ShadowLife.TILE_SIZE);
                break;
            case Direction.DOWN:
                move(0, ShadowLife.TILE_SIZE);
                break;
            case Direction.LEFT:
                move(-ShadowLife.TILE_SIZE, 0);
                break;
            case Direction.RIGHT:
                move(ShadowLife.TILE_SIZE, 0);
                break;
        }
    }

    /**
     * deactivate thief
     */
    public void thiefAtFence() {

        //rotate 180 degrees to return to previous position;
        rotateClockwise();
        rotateClockwise();
        moveThief();
        this.active = false;
        ShadowLife.setInactiveActors(ShadowLife.getInactiveActors() + 1);

    }

    /**
     * create 2 new thieves and delete the old one at the pool
     */
    public void thiefOnPool() {

        Thief thief1 = new Thief(this.getDirection(), this.getX(), this.getY());
        thief1.rotateAntiClockwise();
        thief1.moveThief();
        thief1.setActive(true);


        Thief thief2 = new Thief(this.getDirection(), this.getX(), this.getY());
        thief2.rotateClockwise();
        thief2.moveThief();
        thief2.setActive(true);

        ShadowLife.getActorsToAdd().add(thief1);
        ShadowLife.getActorsToAdd().add(thief2);
        ShadowLife.getActorsToRemove().add(this);
        ShadowLife.setMoveableActors(ShadowLife.getMoveableActors() + 1);


    }

    /**
     * change the direction of the thief to match that if the sign
     *
     * @param sign the direction to change to
     */
    public void thiefOnSign(Sign sign) {
        this.direction = sign.getDirection();
    }

    /**
     * set consuming  true
     */
    public void thiefOnPad() {
        this.consuming = true;
    }

    /**
     * rotate thief anticlockwise
     */
    public void thiefOnGatherer() {
        rotateAntiClockwise();
    }

    /**
     * Thief on tree set state of tree and thief according to the algorithm
     *
     * @param tree the tree on which thief is on
     */
    public void thiefOnTree(Tree tree) {
        if (!this.carrying) {
            if (tree.getFruits() > 0) {
                tree.setFruits(tree.getFruits() - 1);
                this.carrying = true;
            }
        }
    }

    /**
     * thief on golden tree set thief state according to algorithm
     */
    public void thiefOnGoldenTree() {

        if (!this.carrying) {
            this.carrying = true;
        }
    }

    /**
     * Thief on hoard set state of hoard and thief according to the algorithm
     *
     * @param hoard the hoard on which the thief is on
     */
    public void thiefOnHoard(Hoard hoard) {


        if (this.consuming) {
            this.consuming = false;
            if (!carrying) {
                if (hoard.getStock() > 0) {
                    carrying = true;
                    hoard.setStock(hoard.getStock() - 1);
                } else rotateClockwise();
            }
        } else if (carrying) {
            this.carrying = false;
            hoard.setStock(hoard.getStock() + 1);
            rotateClockwise();
        }
    }

    /**
     * Thief on stockpile set state of stockpile and thief according to the algorithm
     *
     * @param stockPile stockpile on which thief is on
     */
    public void thiefOnStockPile(StockPile stockPile) {
        if (!carrying) {
            if (stockPile.getStock() > 0) {
                this.carrying = true;
                this.consuming = false;
                stockPile.setStock(stockPile.getStock() - 1);
                rotateClockwise();
            }
        } else rotateClockwise();
    }

}
