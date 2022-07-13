package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;
import pasur.cards.Suit;

import java.util.ArrayList;

/* check if club */
public class HasClubsRule implements RulesStrategy {

    @Override
    public int rule(ArrayList<Card> cards, Hand surs) {
        int clubs = 0;
        int score = 0;
        for(Card card: cards) {
            if(card.getSuit() == Suit.CLUBS) {
                clubs++;
            }
        }

        if(clubs >= 7) {
            score += 7;
        }
        score += surs.getNumberOfCards() * 5;
        return score;
    }
}
