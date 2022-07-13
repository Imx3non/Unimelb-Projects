package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;
import pasur.cards.Rank;

import java.util.ArrayList;

public class HasJackRule implements RulesStrategy{
    @Override
    public int rule(ArrayList<Card> cards, Hand surs) {
        int score = 0;
        for(Card card: cards) {
            if(card.getRank() == Rank.JACK) {
                score += 1;
            }
        }
        return score;
    }
}
