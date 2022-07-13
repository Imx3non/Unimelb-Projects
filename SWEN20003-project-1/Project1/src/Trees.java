public class Trees extends Actor {


    public Trees(double x, double y) {
        super(x, y);
    }

    @Override
    public String toString() {
        return "Tree is at " + super.getX() + "," + super.getY();
    }

    public boolean equals(Trees other){
        // check if trees are at same location.

        if(this.getX() == other.getX() && this.getY() == other.getY()) return true;
        else return false;
    }
}
