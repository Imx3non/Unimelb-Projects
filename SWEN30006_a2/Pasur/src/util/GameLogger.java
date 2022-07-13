package util;
import java.io.File;  // Import the File class
import java.io.FileWriter;
import java.io.IOException;  // Import the IOException class to handle errors

public class GameLogger {
    private static FileWriter LogWriter;
    private static  File LogFile;

    private static GameLogger logger;


    private GameLogger() throws IOException {
        try {
            LogFile = new File("pasur.log");
            LogFile.createNewFile();
            LogWriter = new FileWriter(LogFile);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static GameLogger getInstance() throws IOException {
        if(logger==null) {
            logger = new GameLogger();
        }
        return logger;
    }


    public void write(String message){
        try{
            LogWriter.write(message + "\n");
            LogWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

//    public GameLogger() throws IOException {
//        try {
//            LogFile = new File("pasur.log");
//            LogFile.createNewFile();
//            LogWriter = new FileWriter(LogFile);
//
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    public static void writeToFile(String message) throws IOException {
//        try{
//            LogWriter.write(message + "\n");
//            LogWriter.flush();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
