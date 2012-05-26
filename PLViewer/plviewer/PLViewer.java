package plviewer;

import java.util.Arrays;
import java.util.Properties;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.io.PrintWriter;
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
   * <p>
   * Each element should have the following layout:
   * {@code {flag1, ...}, {Properties key, Properties value Human readable comment}}
   */
  public final static String[][][] flags = {
    // {{flag1, ...}, {Properties key, Properties value, Human readable comment}}
    {{"-h", "--help"}, {"DisplayHelp", "true", "This help text."}},
  };
  /**
   * Allowed command line options with value. Like {@code --color} in {@code
   * ls --color=always}.
   * <p>
   * Each element should have the following layout:
   * {@code {flag1, ...}, {Properties key, Human readable comment}}
   */
  public final static String[][][] arguments = {
    // {{flag1, ...}, {Properties key, Human readable comment}}
    {{"-g", "--gaviewer"}, {"GAViewer.custom", "The path to a user defined GAViewer."}},
    {{"-f", "--properties"}, {"proppath", "The path to a custom properties file."}},
    {{"-p", "--port"}, {"GAViewer.port", "Network port to use for communication with GAViewer."}},
    };

  /**
   * The main loop for user interaction.
   */
  public static void main(String[] args) {
    // 1. Read from configuration file where GAViewer is located.
    Properties custom = processArgs(args);
    Properties configuration = readPropertiesFile(custom.getProperty("proppath"));
    custom.remove("proppath");
    configuration.putAll(custom);
    
    // 2. Open right GAViewer for OS.
    GAViewerClient gaviewer = new GAViewerClient(configuration);

    // 3. Wait for user to open GAViewer, open ports for communication.
    while (!gaviewer.connect()) {
      new Inform("Obviously, something is going wrong when connecting to GAViewer. Check if it's running.", true);
    }

    // 4. Do REPL-like stuff.
    BufferedReader userReader = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter userWriter = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    BufferedReader gavReader = new BufferedReader(new FilteredReader(gaviewer.getReader(), 
        new ConformalToPluckerFilter()));
    PrintWriter gavWriter = new PrintWriter(new FilteredWriter(gaviewer.getWriter(), 
        new PluckerToConformalFilter()));

    repl(userReader, userWriter, gavReader, gavWriter);

    // 5. Finish the process.
    quit(new Closeable[]{gaviewer});
  }

  /**
   * The user interface to PLViewer.  Acts like a REPL:
   * <ol>
   * <li>Read user input
   * <li>Evaluate user input
   * <li>Print user input (and visualize in GAViewer)
   * <li>Loop; go back to 4.1
   * </ol>
   * @param userReader Reads user input.
   * @param userWriter Writes information to the user screen.
   * @param systemReader Reads data from the processing system.  In our case,
   * that would be GAViewer.
   * @param systemWriter Writes data to the processing system.  In our case,
   * that would be GAViewer.
   */
  public static void repl(BufferedReader userReader, PrintWriter userWriter, BufferedReader systemReader, PrintWriter systemWriter) {
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
   * Parses the command line arguments, and put their values in a {@link
   * java.util.Properties}.
   *
   * @param args The command line arguments that should be processed.
   * @return A mapping representing the user defined settings.
   */
  protected static Properties processArgs(String[] args) {
    Properties custom = new Properties();
    boolean optionFound = false;
    if (args.length > 0) {
      for (int i = 0; i < args.length; i++) {
        for (String[][] flaggroup : flags) {
          if (Arrays.binarySearch(flaggroup[0], args[i]) > -1) {
            custom.setProperty(flaggroup[-1][0], flaggroup[-1][1]);
            optionFound = true;
            break;
          }
        }
        if (!optionFound) {
          for (String[][] arggroup : arguments) {
            if (Arrays.binarySearch(arggroup[0], args[i]) > -1) {
              custom.setProperty(arggroup[-1][0], args[++i]);
              optionFound = true;
              break;
            }
          }
        }
        if (!optionFound) {
          new Inform("Illegal command line argument: " + args[i] + ".", System.err);
          displayArgs(System.err);
          System.exit(-1);
        }
        optionFound = false;
      }
    }

    if (custom.getProperty("DisplayHelp").equals("true")) {
      displayArgs(System.out);
      System.exit(-1);
    }

    return custom;
  }

  /**
   * Display all valid command line arguments with explanation.
   *
   * @param os The stream to which this information is printed.
   */
  protected static void displayArgs(PrintStream os) {
    String legalArguments = "";
    for (String[][][] arggroups : new String[][][][]{flags, arguments}) {
      for (String[][] arggroup : arggroups) {
        for (String arg : arggroup[0]) {
          legalArguments += " " + arg;
        }
        if (arggroup.length > 1) {
          if (arggroup[-1].length > 1 && !arggroup[-1][-1].isEmpty()) {
            legalArguments += " -- " + arggroup[-1][-1];
          }
        }
        legalArguments += "\n";
      }
    }
    new Inform("Possible command line arguments:\n" + legalArguments, os);
  }

  /**
   * Read a .properties file and return the representing {@link
   * java.util.Properties}.  If no file is given, the {@link
   * #DEFAULT_PROPERTIES} file is read.
   *
   * @param filename The file that is read. If {@code filename} is the empty
   * string, the {@link #DEFAULT_PROPERTIES} file is read.
   * @return A map that represents the settings in {@code filename}.
   */
  protected static Properties readPropertiesFile(String filename) {
    Properties configuration = new Properties(getDefaultConfiguration());
    InputStream is;
    try {
      if (filename.isEmpty()) {
        is = PLViewer.class.getResourceAsStream(DEFAULT_PROPERTIES);
      }
      else {
        is = new FileInputStream(filename);
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

    return configuration;
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
