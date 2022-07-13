package pasur.PointsObserver;

import ch.aplu.jcardgame.Hand;

public abstract class PointsObserver {
    private int score;
    public abstract void setScore(int points);
    public abstract int getScore();
    public abstract Hand getSurs();
    public abstract String toString();
}
