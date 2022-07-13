package pasur;

/**
 * @author Alireza Ostovar
 * 29/09/2021
 */

import ch.aplu.jcardgame.Card;

import java.io.IOException;

public class RandomPlayer extends Player
{
    public RandomPlayer(int id) throws IOException {
        super(id);
    }

    @Override
    Card selectToPlay()
    {
        return hand.isEmpty() ? null : Pasur.randomCard(hand);
    }
}
