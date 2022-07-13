package pasur;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;
import pasur.rules.*;

import java.util.ArrayList;

public class Scorer {

    private int total;

    public Scorer(Hand pickedCards, Hand surs) {

        int score = 0;
        int clubs = 0;

        ArrayList<Card> cards = pickedCards.getCardList();
        cards.addAll(surs.getCardList());

        /* add new rules to end of this loop */
        //clubs += RulesStrategy.rule(cards).getClubs();

        RuleContext context = new RuleContext(new AceRule());
        score += context.executeRule(cards, surs);

        context = new RuleContext(new HasClubsRule());
        score += context.executeRule(cards, surs);

        context = new RuleContext(new HasJackRule());
        score += context.executeRule(cards, surs);

        context = new RuleContext(new TenDiamondsRule());
        score += context.executeRule(cards, surs);

        context = new RuleContext(new TwoClubRule());
        score += context.executeRule(cards, surs);

        this.total = score;
    }

    public int getScore() { return total; }

}
