import java.util.Random;

public class Gatherer extends Actor {

    private String direction;

    public Gatherer(double x, double y) {
        super(x, y);
    }

    public String getDirection() {
        return direction;
    }

    public void setDirection(String direction) {

        this.direction = direction;

    }

    public String randomDirection() {
        //select a random direction
        Random rand = new Random();
        String[] direction = {"up", "down", "left", "right"};
        return direction[rand.nextInt(direction.length)];
    }

    @Override
    public String toString() {
        return "Gather is at " + super.getX() + "," + super.getY();
    }

    public boolean equals(Gatherer other){
        // check if gatherers are at same location.

        if(this.getX() == other.getX() && this.getY() == other.getY()) return true;
        else return false;
    }

}
