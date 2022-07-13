import bagel.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ShadowLife extends AbstractGame {

    public final int pixel = 64;
    private final Image background;
    private final Image gatherer;
    private final Image tree;
    private final Trees[] trees = new Trees[4];
    private final Gatherer[] gatherers = new Gatherer[2];
    private int ticks = 0;

    public ShadowLife() {

        // create the images and add read the csv file.
        super();
        background = new Image("res/images/background.png");
        gatherer = new Image("res/images/gatherer.png");
        tree = new Image("res/images/tree.png");
        read_csv();

    }

    public static void main(String[] args) {

        ShadowLife game = new ShadowLife();

        game.run();

    }

    public void read_csv() {
        String line = "";
        int treeIndex = 0;
        int gatherersIndex = 0;

        //read the csv file and put the data in the respective array
        try {
            BufferedReader br = new BufferedReader(new FileReader("res/worlds/test.csv"));
            while ((line = br.readLine()) != null) {

                String[] data = line.split(",");
                
                if (data[0].equals("Tree")) {
                    trees[treeIndex] = new Trees(Double.parseDouble(data[1]), Double.parseDouble(data[2]));

                    treeIndex++;

                } else {
                    gatherers[gatherersIndex] = new Gatherer(Double.parseDouble(data[1]), Double.parseDouble(data[2]));
                    gatherersIndex++;
                }


            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void update(Input input) {

        long currentTime = System.currentTimeMillis();
        while (true) {

            //make sure at least 500ms has passed.
            if (System.currentTimeMillis() - currentTime >= 500) {
                ticks++;
                break;
            }
        }

        background.drawFromTopLeft(0, 0);

        if (input.wasPressed(Keys.ESCAPE)) {
            System.out.println("Exit");
            Window.close();
        }


        for (Trees value : trees) {
            tree.draw(value.getX(), value.getY());
        }


        for (Gatherer value : gatherers) {
            if (value.getDirection() == null) {

                value.setDirection(value.randomDirection());

            }

            if (ticks % 5 == 0) {
                value.setDirection(value.randomDirection());
            }

            if (value.getDirection().equals("up")) {
                value.setY(value.getY() - pixel);

            }
            if (value.getDirection().equals("down")) {
                value.setY(value.getY() + pixel);

            }
            if (value.getDirection().equals("left")) {
                value.setX(value.getX() - pixel);

            }
            if (value.getDirection().equals("right")) {
                value.setX(value.getX() + pixel);
            }
        }

        for (Gatherer value : gatherers) {
            //Draw the gathers with the updated coordinates.
            gatherer.draw(value.getX(), value.getY());

        }
    }
}
