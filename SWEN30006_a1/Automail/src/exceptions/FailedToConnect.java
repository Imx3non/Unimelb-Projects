package exceptions;

/**
 * An exception thrown when a mail that is already delivered attempts to be delivered again.
 */
public class FailedToConnect extends Throwable    {
    public FailedToConnect(){
        super("Failed to connect to WifiModem!");
    }
}
