package config;

import util.GameLogger;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Configuration
{
    private static final String SEED_KEY = "Seed";
    private static final String ANIMATE_KEY = "Animate";
    private static final String PLAYER0_KEY = "Player0";
    private static final String PLAYER1_KEY = "Player1";

    private static Configuration configuration = null;

    private int seed;
    private boolean animate;
    private String player0class;
    private String player1class;
    private GameLogger gameLogger;

    public static Configuration getInstance()
    {
        if(configuration == null)
        {
            configuration = new Configuration();

            try {
                configuration.setUp();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return configuration;
    }

    private void setUp() throws IOException 
    {
        // Default properties

        // Read properties
        Properties properties = new Properties();
        FileReader inStream = null;
        try {
            inStream = new FileReader("pasur.properties");
            properties.load(inStream);
        } finally {
            if (inStream != null) {
                inStream.close();
            }
        }
        GameLogger gameLogger = GameLogger.getInstance();

        // Seed
        seed = Integer.parseInt(properties.getProperty(SEED_KEY));
        gameLogger.write("#Seed: " + seed);

        // Animate
        animate = Boolean.parseBoolean(properties.getProperty(ANIMATE_KEY));
        gameLogger.write("#Animate: " + animate);

        // Player0
        player0class = properties.getProperty(PLAYER0_KEY);
        gameLogger.write("#Player0: " + player0class);

        // Player1
        player1class = properties.getProperty(PLAYER1_KEY);
        gameLogger.write("#Player1: " + player1class);
    }

    public int getSeed()
    {
        return seed;
    }

    public boolean isAnimate()
    {
        return animate;
    }

    public String getPlayer0class()
    {
        return player0class;
    }

    public String getPlayer1class()
    {
        return player1class;
    }
}
