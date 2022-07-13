/**
 * Class that contains methods and attributes related to a gatherer
 */

public class Gatherer extends Actor {
    /**
     * TYPE is the type of actor
     */

    public static final String TYPE = "Gatherer";
    private int direction;
    private boolean carrying;
    private boolean active;
    private boolean performedTick;

    /**
     * Constructor to create a gatherer at a given position
     *
     * @param x x-coord
     * @param y y-coord
     */
    public Gatherer(int x, int y) {
        super("res/images/gatherer.png", TYPE, x, y);
    }

    /**
     * constructor to create a gatherer with a given direction
     *
     * @param direction direction of gatherer
     * @param x         x-coord
     * @param y         y-coord
     */
    public Gatherer(int direction, int x, int y) {
        super("res/images/gatherer.png", TYPE, x, y);
        this.direction = direction;

    }

    /**
     * check if the tick of gatherer has been performed
     *
     * @return bool true if performed
     */
    public boolean isPerformedTick() {
        return performedTick;
    }

    /**
     * set Performed tick. true if performed else false
     *
     * @param performedTick bool true or false
     */
    public void setPerformedTick(boolean performedTick) {
        this.performedTick = performedTick;
    }

    /**
     * get the current direction of the gatherer
     *
     * @return int the direction of gatherer
     */
    public int getDirection() {
        return direction;
    }

    /**
     * Set the direction of the gatherer
     *
     * @param direction the direction that gatherer should move
     */
    public void setDirection(int direction) {
        this.direction = direction;
    }

    /**
     * check if gatherer is carrying
     *
     * @return bool true if carrying else false
     */
    public boolean isCarrying() {
        return carrying;
    }

    /**
     * set the carrying status of gatherer
     *
     * @param carrying true if carrying else false
     */
    public void setCarrying(boolean carrying) {
        this.carrying = carrying;
    }

    /**
     * Check if gatherer is active
     *
     * @return bool true if active else false
     */
    public boolean isActive() {
        return active;
    }

    /**
     * set active status of gatherer
     *
     * @param active true if active else false
     */
    public void setActive(boolean active) {
        this.active = active;
    }

    /**
     * update position at each tick
     */
    @Override
    public void update() {

        if (this.isActive()) {
            moveGatherer();
            this.performedTick = true;
        }
    }

    /**
     * Update the state of the gatherer every tick
     *
     * @param actor takes another actor to see what should be the next state according to the algorithm
     */
    public void updateState(Actor actor) {

        if (actor instanceof Fence) gathererAtFence();
        else if (actor instanceof MitosisPool) gathererOnPool();
        else if (actor instanceof Sign) gathererOnSign((Sign) actor);
        else if (actor instanceof Tree) gathererAtTree((Tree) actor);
        else if (actor instanceof GoldenTree) gathererAtGoldenTree();
        else if (actor instanceof StockPile || actor instanceof Hoard) gathererOnHoardOrStockPile(actor);

    }

    /**
     * draw the image of the gatherer
     */
    @Override
    public void render() {
        getImage().drawFromTopLeft(getX(), getY());
    }

    /**
     * rotate the gatherer clockwise
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
     * rotate the gatherer anticlockwise
     */
    public void rotateAntiClockwise() {
        switch (direction) {
            case Direction.UP:
                this.direction = Direction.LEFT;
                break;
            case Direction.DOWN:
                this.direction = Direction.RIGHT;
                break;
            case Direction.LEFT:
                this.direction = Direction.DOWN;
                break;
            case Direction.RIGHT:
                this.direction = Direction.UP;
                break;
        }
    }

    /**
     * initialise the gatherer according to the algorithm
     *
     * @param gatherer gatherer to initialise
     */
    public void initialiseGatherer(Gatherer gatherer) {

        gatherer.setDirection(Direction.LEFT);
        gatherer.setCarrying(false);
        gatherer.setActive(true);
        gatherer.setPerformedTick(false);

    }

    /**
     * move the gatherer in its current direction
     */
    public void moveGatherer() {
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
     * Gatherer is at fence need to deactivate gatherer
     */
    public void gathererAtFence() {

        //rotate 180 degrees to return to previous position;
        rotateClockwise();
        rotateClockwise();
        moveGatherer();
        this.active = false;
        ShadowLife.setInactiveActors(ShadowLife.getInactiveActors() + 1);
    }

    /**
     * Gatherer on pool Create 2 new gatherer and destroy the current one
     */
    public void gathererOnPool() {

        Gatherer gatherer1 = new Gatherer(this.direction, this.getX(), this.getY());

        gatherer1.rotateAntiClockwise();
        gatherer1.moveGatherer();
        gatherer1.setActive(true);
        gatherer1.setPerformedTick(false);

        Gatherer gatherer2 = new Gatherer(this.direction, this.getX(), this.getY());
        gatherer2.rotateClockwise();
        gatherer2.moveGatherer();
        gatherer2.setActive(true);
        gatherer2.setPerformedTick(false);

        ShadowLife.getActorsToRemove().add(this);
        ShadowLife.getActorsToAdd().add(gatherer1);
        ShadowLife.getActorsToAdd().add(gatherer2);
        ShadowLife.setMoveableActors(ShadowLife.getMoveableActors() + 1);

    }

    /**
     * gatherer on sign change direction to match that of the sign
     *
     * @param sign the sign on which it is
     */
    public void gathererOnSign(Sign sign) {

        this.direction = sign.getDirection();
    }

    /**
     * Gatherer on tree do appropriate action based on the algorithm
     *
     * @param tree the tree on which the gatherer is on
     */
    public void gathererAtTree(Tree tree) {

        if (!this.carrying && tree.getFruits() > 0) {
            tree.setFruits(tree.getFruits() - 1);
            this.carrying = true;
            rotateClockwise();
            rotateClockwise();
        }
    }

    /**
     * Gatherer on  golden tree do appropriate action based on the algorithm
     */

    public void gathererAtGoldenTree() {

        if (!this.carrying) {
            this.carrying = true;
            rotateClockwise();
            rotateClockwise();
        }
    }

    /**
     * Gatherer is on a stockpile or Hoard, do what is necessary according to the algorithm
     *
     * @param actor Can be a Hoard or Stockpile
     */
    public void gathererOnHoardOrStockPile(Actor actor) {
        rotateClockwise();
        rotateClockwise();
        if (this.carrying) {
            this.carrying = false;
            if (actor instanceof Hoard) {
                ((Hoard) actor).setStock(((Hoard) actor).getStock() + 1);
            } else if (actor instanceof StockPile) {
                ((StockPile) actor).setStock(((StockPile) actor).getStock() + 1);
            }

        }
    }
}
