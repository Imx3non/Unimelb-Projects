package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;
import pasur.cards.Rank;
import pasur.cards.Suit;

import java.util.ArrayList;

/* check for 10 of diamonds */
public class TenDiamondsRule implements RulesStrategy {
    @Override
    public int rule(ArrayList<Card> cards, Hand surs) {
        int clubs = 0;
        int score = 0;
        for(Card card: cards) {
            if(card.getSuit() == Suit.DIAMONDS && card.getRank() == Rank.TEN) {
                score += 3;
            }
        }
        return score;
    }
}
