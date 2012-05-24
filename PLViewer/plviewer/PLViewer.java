package plviewer;

import java.util.Scanner;
import java.util.Properties;
import java.io.Closeable;
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
  /**
   * The location of the configuration file.
   */
  public final static String CONFIG_INI = "./config.ini";

  public static void main(String[] args) {
    // 1. Read from configuration file where GAViewer is located.
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

    // 2. Open right GAViewer for OS.
    GAViewerClient gaviewer = new GAViewerClient(configuration);

    // 3. Wait for user to open GAViewer, open ports for communication.
    while (!gaviewer.connect()) {
      new Inform("Obviously, something is going wrong when connecting to GAViewer. Check if it's running.", true);
    }

    // 4. Do REPL-like stuff:
    //    1. Read user input
    //    2. Evaluate user input
    //    3. Print user input (and visualize in GAViewer)
    //    4. Loop; go back to 4.1

    // 5. Finish the process.
    quit(new Closeable[]{gaviewer});
  }

  /**
   * Cleans up when the program should terminate.  
   *
   * It should call {@link java.io.Closeable#close()} on every element of its
   * input.
   *
   * @param closeable An array of {@link java.io.Closeable}s that should have
   * called <code>close()</code> on them.
   */
  public static void quit(Closeable[] closeable) {
    for (Closeable c : closeable) {
      try {
      c.close();
      }
      catch (IOException e) {
      }
    }
  }

  /**
   * Writes the default configurations to the default configuration file
   * location. 
   *
   * The settings are read from {@link #getDefaultConfiguration()}.
   */
  protected static void generateDefaultConfigurationFile() {
    generateDefaultConfigurationFile(CONFIG_INI);
  }

  /**
   * Writes the default configurations to a file.
   *
   * The settings are read from {@link #getDefaultConfiguration()}.
   *
   * @param filename The name of the file to which the configuration should be
   *       written to.
   */
  protected static void generateDefaultConfigurationFile(String filename) {
    try {
      Properties defaultConfig = getDefaultConfiguration();
      Writer file = new FileWriter(filename);
      defaultConfig.store(file, "Default configuration for PLViewer.");
    }
    catch (IOException e) {
      new Inform("A new configuration file could not be created.", System.err);
    }
  }

  /**
   * Gives the default {@link java.util.Properties} objects.
   *
   * It is used as a fallback when the configuration file cannot be read, or
   * does not contain the necessary values.
   *
   * @return A {@link java.util.Properties} object representing the default
   *    configuration.
   */
  protected static Properties getDefaultConfiguration() {
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
}
