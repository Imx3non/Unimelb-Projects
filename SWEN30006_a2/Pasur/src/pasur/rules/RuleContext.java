package pasur.rules;

import ch.aplu.jcardgame.Card;
import ch.aplu.jcardgame.Hand;

import java.util.ArrayList;

public class RuleContext {
    private RulesStrategy strategy;

    public RuleContext(RulesStrategy strategy){
        this.strategy = strategy;
    }

    public int executeRule(ArrayList<Card> cards, Hand surs){
        return strategy.rule(cards, surs);
    }
}
