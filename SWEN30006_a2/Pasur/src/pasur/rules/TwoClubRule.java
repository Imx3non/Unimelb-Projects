package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;
import pasur.cards.*;

import java.util.ArrayList;

/* check for 2 of clubs */
public class TwoClubRule implements RulesStrategy{
    @Override
    public int rule(ArrayList<Card> cards, Hand surs) {
        int score = 0;
        for(Card card: cards) {
            if(card.getSuit() == Suit.CLUBS && card.getRank() == Rank.TWO) {
                score += 2;
            }
        }
        return score;
    }
}
