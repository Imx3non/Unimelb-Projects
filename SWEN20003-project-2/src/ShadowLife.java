import bagel.AbstractGame;
import bagel.Image;
import bagel.Input;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Class that runs the game and contains the main method
 */
public class ShadowLife extends AbstractGame {

    /**
     * TILE_SIZE is by how much can be move in the x-y plane
     */
    public static final int TILE_SIZE = 64;
    private static long tickInterval;
    private static long ticksPassed;
    private static ArrayList<Actor> actors;
    private static ArrayList<Actor> actorsToAdd;
    private static ArrayList<Actor> actorsToRemove;
    private static int maxTicks;
    private static int moveableActors = 0;
    private static int inactiveActors = 0;
    private final Image background = new Image("res/images/background.png");
    private long lastTick = 0;


    /**
     * construstor to create ShadowLife with a given interval and max ticks and load the actors from the world
     *
     * @param tickInterval the tick interval
     * @param maxTicks     maximum tick rate
     * @param fileName     world to load from
     */
    public ShadowLife(long tickInterval, int maxTicks, String fileName) {
        ShadowLife.maxTicks = maxTicks;
        ShadowLife.tickInterval = tickInterval;
        loadActors(fileName);
        initialiseActors(actors);
    }


    /**
     * get all new actors created in the mitosis pool
     *
     * @return ArrayList of the actors to add
     */
    public static ArrayList<Actor> getActorsToAdd() {
        return actorsToAdd;
    }

    /**
     * get all the actors that has to be removed due to mitosis pool
     *
     * @return ArrayList of actors to remove
     */
    public static ArrayList<Actor> getActorsToRemove() {
        return actorsToRemove;
    }

    /**
     * main method that runs shadowLife
     *
     * @param args the tick rate, max ticks and the world file respectively
     */
    public static void main(String[] args) {

        if (args.length != 3) {
            System.out.println("usage: ShadowLife <tick rate> <max ticks> <world file>");
            System.exit(-1);
        }
        //check for non negative valid values
        if (!((args[0]).matches("-?\\d+(\\.\\d+)?")) || !args[1].matches("-?\\d+(\\.\\d+)?")) {
            System.out.println("usage: ShadowLife <tick rate> <max ticks> <world file>");
            System.exit(-1);
        }
        //check for negative values
        if (Integer.parseInt(args[0]) < 0 || Integer.parseInt(args[1]) < 0) {
            System.out.println("usage: ShadowLife <tick rate> <max ticks> <world file>");
            System.exit(-1);
        }

        new ShadowLife(Long.parseLong(args[0]), Integer.parseInt(args[1]), args[2]).run();

    }

    /**
     * get the number of  the moveable actors
     *
     * @return number of movable actors
     */
    public static int getMoveableActors() {
        return moveableActors;
    }

    /**
     * This is a method to set the number of movable Actors
     *
     * @param moveableActors Takes number of movableActors as arg
     */
    public static void setMoveableActors(int moveableActors) {

        ShadowLife.moveableActors = moveableActors;
    }


    /**
     * Method to get the number of Inactive actors
     */
    public static int getInactiveActors() {
        return inactiveActors;
    }

    /**
     * This is a method to set the number of movable Actors
     *
     * @param inactiveActors Takes number of movableActors as arg
     */
    public static void setInactiveActors(int inactiveActors) {
        ShadowLife.inactiveActors = inactiveActors;
    }

    /**
     * Method to load the actors in an array list
     *
     * @param fileName The file path
     */
    public void loadActors(String fileName) {

        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            /*
            The code solution for project1 was adapted for this part.
             */
            actors = new ArrayList<Actor>();
            actorsToAdd = new ArrayList<Actor>();
            actorsToRemove = new ArrayList<Actor>();
            String line;
            while ((line = reader.readLine()) != null) {
                // Line format is: type,x,y
                String[] parts = line.split(",");
                String type = parts[0];
                int x = Integer.parseInt(parts[1]);
                int y = Integer.parseInt(parts[2]);

                switch (type) {
                    case Tree.TYPE:
                        actors.add(new Tree(x, y));
                        break;
                    case Gatherer.TYPE:
                        actors.add(new Gatherer(x, y));
                        moveableActors++;
                        break;
                    case Thief.TYPE:
                        actors.add(new Thief(x, y));
                        moveableActors++;
                        break;
                    case GoldenTree.TYPE:
                        actors.add(new GoldenTree(x, y));
                        break;
                    case Hoard.TYPE:
                        actors.add(new Hoard(x, y));
                        break;
                    case MitosisPool.TYPE:
                        actors.add(new MitosisPool(x, y));
                        break;
                    case StockPile.TYPE:
                        actors.add(new StockPile(x, y));
                        break;
                    case Fence.TYPE:
                        actors.add(new Fence(x, y));
                        break;
                    case Pad.TYPE:
                        actors.add(new Pad(x, y));
                        break;
                    case Sign.TYPE1:
                        actors.add(new Sign(x, y, Sign.TYPE1LOCATION, Sign.TYPE1, Direction.UP));
                        break;
                    case Sign.TYPE2:
                        actors.add(new Sign(x, y, Sign.TYPE2LOCATION, Sign.TYPE2, Direction.DOWN));
                        break;
                    case Sign.TYPE3:
                        actors.add(new Sign(x, y, Sign.TYPE3LOCATION, Sign.TYPE3, Direction.LEFT));
                        break;
                    case Sign.TYPE4:
                        actors.add(new Sign(x, y, Sign.TYPE4LOCATION, Sign.TYPE4, Direction.RIGHT));
                        break;
                }
            }
        } catch (IOException e) {
            System.out.println("error: file \" " + fileName + "\" not found");
            System.exit(-1);
        }

    }

    /**
     * Method to initialise the actors to their initial states
     *
     * @param actors the list of actors
     */
    public void initialiseActors(ArrayList<Actor> actors) {

        for (Actor actor : actors) {
            if (actor instanceof Gatherer) {
                ((Gatherer) actor).initialiseGatherer((Gatherer) actor);
            } else if (actor instanceof Thief) {
                ((Thief) actor).initialiseThief((Thief) actor);
            } else if (actor instanceof StockPile) {
                ((StockPile) actor).setStock(0);
            } else if (actor instanceof Hoard) {
                ((Hoard) actor).setStock(0);
            } else if (actor instanceof Tree) {
                ((Tree) actor).setFruits(3);
            }
        }
    }

    /**
     * method that keeps on getting called until all moveable actors are inactive or max ticks is reached
     *
     * @param input keyboard input
     */
    @Override
    protected void update(Input input) {

        // code was adapted from the solution provided by project 1
        //checks if a tick has passed
        if (System.currentTimeMillis() - lastTick > tickInterval) {
            lastTick = System.currentTimeMillis();
            ticksPassed++;

            if (ticksPassed > maxTicks) {
                System.out.println("Timed out");
                System.exit(0);
            }
            //loop for each actor and apply tick
            for (Actor actor : actors) {
                actor.tick();

                //for each actor we loop through list again to compare each actor with the other
                for (Actor otherActor : actors) {

                    if (actor.equals(otherActor)) {
                        //only gatherer and thief has an action upon a tick
                        if (actor instanceof Gatherer) ((Gatherer) actor).updateState(otherActor);
                        else if (actor instanceof Thief) ((Thief) actor).updateState(otherActor);
                    }
                }
            }
        }

        //add the actors created by the mitosis pool to the list of actors
        for (Actor actor : actorsToAdd) {
            if (!actors.contains(actor)) {
                actors.add(actor);
            }
        }

        //remove actors that needs to be destroyed by the mitosis pool
        for (Actor actor : actorsToRemove) {
            actors.remove(actor);
        }

        actors.trimToSize();

        background.drawFromTopLeft(0, 0);
        for (Actor actor : actors) {
            actor.render();
        }

        //check if all actors are inactive
        if (inactiveActors == moveableActors) {
            System.out.println(ticksPassed + " ticks");
            //print all the stock of fruits in order they appear in the list
            for (Actor actor : actors) {
                if (actor instanceof Hoard || actor instanceof StockPile) {
                    if (actor instanceof Hoard) System.out.println(((Hoard) actor).getStock());
                    else System.out.println(((StockPile) actor).getStock());
                }
            }
            System.exit(0);
        }

    }
}
