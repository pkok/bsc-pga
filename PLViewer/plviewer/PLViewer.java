package plviewer;

import java.util.Arrays;
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

/**
 * Wrapper for GAViewer to give PL3GA functionality.
 *
 * PLViewer is a wrapper for GAViewer.  Users can write with similar syntax
 * as used by GAViewer in PLViewer's CLI.  The formulae are interpreted in the
 * projective algebra of Plucker lines (see H. Li and L. Zhang, 2011) in
 * <!--R^{3,3}-->&#8477;<sup>3,3</sup>.  The basis elements are denoted by
 * <em>e<sub>01</sub></em>, <em>e<sub>02</sub></em>, <em>e<sub>03</sub></em>,
 * <em>e<sub>12</sub></em>, <em>e<sub>23</sub></em>, <em>e<sub>31</sub></em>.
 * If the user's input is terminated with a ``;'', the corresponding entity
 * will be displayed in GAViewer.  PLViewer will calculate which (set of)
 * elements in conformal geometric algebra represent the same object, and then
 * will send this entity over a {@link java.net.Socket} connection with
 * GAViewer.
 */
public class PLViewer {
  /**
   * The location of the configuration file.
   */
  public final static String DEFAULT_PROPERTIES = "default.properties";
  /**
   * Allowed no-argument command line options. Like {@code -r} in {@code rm -r /}.
   */
  public final static String[] flags = {};
  /**
   * Allowed command line options with value. Like {@code --color} in {@code
   * ls --color=always}.
   */
  public final static String[][] arguments = {
    {"-g", "--gaviewer"},
    {"-f", "--properties"},
    {"-p", "--port"},
    };

  public static void main(String[] args) {
    // Check command line arguments
    String custom_gaviewer = "";
    String custom_properties = "";
    String custom_port = "";
    if (args.length > 0) {
      for (int i = 0; i < args.length; i++) {
        if (Arrays.binarySearch(arguments[0], args[i]) > -1) {
          custom_gaviewer = args[++i];
        }
        else if (Arrays.binarySearch(arguments[1], args[i]) > -1) {
          custom_properties = args[++i];
        }
        else if (Arrays.binarySearch(arguments[2], args[i]) > -1) {
          custom_port = args[++i];
        }
        else {
          String legalArguments = "";
          for (String flag : flags) {
            legalArguments += flag + "\n";
          }
          for (String[] arggroup : arguments) {
            for (String arg : arggroup) {
              legalArguments += arg + " ";
            }
            legalArguments += "\n";
          }
          new Inform("Illegal command line argument. Legal arguments:\n" + legalArguments, System.err);
          System.exit(-1);
        }
      }
    }

    // 1. Read from configuration file where GAViewer is located.
    Properties configuration = new Properties(getDefaultConfiguration());
    InputStream is;
    try {
      if (custom_properties.isEmpty()) {
        is = PLViewer.class.getResourceAsStream("default.properties");
      }
      else {
        is = new FileInputStream(custom_properties);
      }
      configuration.load(is);
    }
    catch (FileNotFoundException e) {
      NullPointerException e2 = new NullPointerException(e.getMessage());
      e2.initCause(e.getCause());
      e2.setStackTrace(e.getStackTrace());
      throw e2;
    }
    catch (NullPointerException e) {
      new Inform("Configuration file not found. Generating default configuration file.", System.err);
      generateDefaultConfigurationFile();
    }
    catch (IOException e) {
      new Inform("Configuration file could not be loaded. The default configuration will be used.");
    }

    if (!custom_gaviewer.isEmpty()) {
      configuration.setProperty("GAViewer.custom", custom_gaviewer);
    }
    if (!custom_port.isEmpty()) {
      configuration.setProperty("GAViewer.port", custom_port);
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
    generateDefaultConfigurationFile(DEFAULT_PROPERTIES);
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
    defaultConfig.setProperty("GAViewer.Win.32", "./GAViewers/GAViewer_Win32.exe");
    defaultConfig.setProperty("GAViewer.Win.64", "./GAViewers/GAViewer_Win64.exe");
    defaultConfig.setProperty("GAViewer.Lin.32", "./GAViewers/gaviewer_linux_32");
    defaultConfig.setProperty("GAViewer.Lin.64", "./GAViewers/gaviewer_linux_64");
    defaultConfig.setProperty("GAViewer.OSX", "./GAViewers/gaviewer_osx");
    defaultConfig.setProperty("GAViewer.port", "666");
    defaultConfig.setProperty("GAViewer.options", "");
    return defaultConfig;
  }
}
