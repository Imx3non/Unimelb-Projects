package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;

import java.util.ArrayList;

public interface RulesStrategy {
    int rule(ArrayList<Card> cards, Hand surs);
}
