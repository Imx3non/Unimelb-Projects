package pasur.PointsObserver;

import pasur.PasurGUI;
import pasur.Player;
import util.GameLogger;

import java.beans.PropertyChangeSupport;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class PointsTable {
    private static List<Player> observers = new ArrayList<Player>();
    private static GameLogger gameLogger;


    public PointsTable() throws IOException {
        gameLogger = GameLogger.getInstance();
        notifyAllObservers();
    }

    public static void setScore(Player player, int points) {

        for (PointsObserver observer : observers) {
            if(observer.equals(player)){
                observer.setScore(points);
            }
        }
        notifyAllObservers();
    }

    public static  void attach(Player observer){
        observers.add(observer);
    }

    public static void notifyAllObservers(){
        String scoreString = "";
        for (int i = 0; i < observers.size(); i++)
        {
            if(i != 0)
                scoreString += "        ";
            Player player = observers.get(i);
            scoreString += player.toString() + " = " + player.getScore() + " (" + player.getSurs().getNumberOfCards() + " Surs)";
        }
        PasurGUI.setScoreLabel(scoreString);
    }
}
