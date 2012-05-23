package plviewer;

import java.util.Scanner;
import java.util.Properties;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.PrintStream;
import java.io.Writer;

import java.io.FileNotFoundException;
import java.io.IOException;

import plviewer.GAViewerClient;
import plviewer.Inform;

public class PLViewer {
  public static boolean running = false;
  private final static String CONFIG_INI = "./config.ini";

  public static void main(String[] args) {
    // 1. Read from configuration file where GAViewer is located.
    // 2. Open right GAViewer for OS.
    // 3. Wait for user to open GAViewer, open ports for communication.
    // 4. Do REPL-like stuff:
    //    1. Read user input
    //    2. Evaluate user input
    //    3. Print user input (and visualize in GAViewer)
    //    4. Loop; go back to 4.1
    Properties configuration = new Properties(getDefaultConfiguration());
    InputStream is;
    try {
      is = new FileInputStream(CONFIG_INI);
      configuration.load(is);
    }
    catch (FileNotFoundException e) {
      new Inform("Configuration file not found. Generating default configuration file.", System.err);
      generateDefaultConfigurationFile();
    }
    catch (IOException e) {
      new Inform("Configuration file could not be loaded. The default configuration will be used.");
    }

    GAViewerClient gaviewer = new GAViewerClient(configuration);

    running = true;
    // ...
    quit(gaviewer);
  }

  public static void quit(GAViewerClient gav) {
    gav.close();
  }

  private static Properties getDefaultConfiguration() {
    Properties defaultConfig = new Properties();
    defaultConfig.setProperty("GAViewer.Win.32", "../GAViewers/GAViewer_Win_32.exe");
    defaultConfig.setProperty("GAViewer.Win.64", "../GAViewers/GAViewer_Win_64.exe");
    defaultConfig.setProperty("GAViewer.Lin.32", "../GAViewers/gaviewer_lin_32");
    defaultConfig.setProperty("GAViewer.Lin.64", "../GAViewers/gaviewer_lin_64");
    defaultConfig.setProperty("GAViewer.OSX", "../GAViewers/gaviewer_osx_6");
    defaultConfig.setProperty("GAViewer.port", "666");
    defaultConfig.setProperty("GAViewer.options", "");
    return defaultConfig;
  }

  private static void generateDefaultConfigurationFile() {
    try {
      Properties defaultConfig = getDefaultConfiguration();
      Writer file = new FileWriter(CONFIG_INI);
      defaultConfig.store(file, "Default configuration for PLViewer.");
    }
    catch (IOException e) {
      new Inform("A new configuration file could not be created.", System.err);
    }
  }
}
