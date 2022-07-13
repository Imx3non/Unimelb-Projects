package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;
import pasur.cards.Rank;

import java.util.ArrayList;

/* check if ace */
public class AceRule implements RulesStrategy {
    @Override
    public int rule(ArrayList<Card> cards, Hand surs) {
        int score = 0;
        for(Card card: cards) {
            if(card.getRank() == Rank.ACE) {
                score += 1;
            }
        }
        return score;
    }
}