package pasur.rules;

public enum Score {

    /* Points awarded for each achievement */
    MOST_CLUBS(7), TEN_DIAMOND(3), TWO_CLUB(2), ACE(1), JACK(1), SUR(5);

    private final int value;

    Score(int value) {this.value = value; }

    public int getValue() { return value; }

}
