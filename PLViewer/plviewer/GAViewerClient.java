package plviewer;

import java.util.Properties;
import java.util.ServiceConfigurationError;
import java.io.IOException;
import java.io.Closeable;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.net.Socket;
import java.net.UnknownHostException;

import java.io.BufferedReader;

/**
 * An interface to an instance of GAViewer.
 *
 * It should be used to start and stop an instance of GAViewer, and to send
 * and receive data from that instance.
 */
public class GAViewerClient implements Closeable {
  /**
   * A reference to the external GAViewer process.
   */
  protected Process process;
  /**
   * Contains the settings for running the right GAViewer with the right
   * settings.
   *
   * Currently, the following keys are needed:
   * <ul>
   * <li> GAViewer.OSX: the path to the GAViewer executable for OS X
   * <li> GAViewer.Win.32: the path to the GAViewer executable for 32-bit
   * <li>   installations of Windows
   * <li> GAViewer.Win.64: the path to the GAViewer executable for 64-bit
   * <li>   installations of Windows
   * <li> GAViewer.Lin.32: the path to the GAViewer executable for 32-bit 
   * <li>   installations of Linux.
   * <li> GAViewer.Lin.64: the path to the GAViewer executable for 64-bit 
   * <li>   installations of Linux.
   * <li> GAViewer.port: the socket port to connect to.
   * <li> GAViewer.options: the command line options that should be passed on.
   * </ul>
   */
  protected Properties configuration;
  /**
   * A socket to the GAViewer process.
   */
  protected Socket connection;
  /**
   * A Reader object connected to the GAViewer socket.
   */
  protected Reader reader;
  /**
   * A Writer object connected to the GAViewer socket.
   */
  protected Writer writer;

  /**
   * Starts an instance of GAViewer.
   *
   * @param configuration User definable settings for GAViewer.
   * @exception ServiceConfigurationError Thrown if there is no version of
   *     GAViewer specified for the user's OS.
   * @exception RuntimeError Thrown if GAViewer could not be started.
   */
  public GAViewerClient(Properties configuration) {
    this.configuration = configuration;
    String gaviewerOptions = this.configuration.getProperty("GAViewer.options", "");
    String gaviewerLocation = this.configuration.getProperty("GAViewer.custom");

    if (gaviewerLocation == null) {
      String os_suffix = "Unix";
      String os = System.getProperty("os.name").toLowerCase();
      String arch_bit = System.getProperty("sun.arch.data.model");
      if (runningOnMac()) {
        os_suffix = ".OSX";
      } else if (runningOnWindows()) {
        os_suffix = ".Win." + arch_bit;
      } else if (runningOnLinux()) {
        os_suffix = ".Lin." + arch_bit;
      } else {
        System.err.println("GAViewer does not run on this OS.");
      }

      gaviewerLocation = this.configuration.getProperty("GAViewer" + os_suffix);

    }
    if (gaviewerLocation.endsWith(".exe")) {
      gaviewerLocation = gaviewerLocation.substring(0, gaviewerLocation.length() - 4);
    }

    if (gaviewerLocation.length() == 0) {
      throw new ServiceConfigurationError("No GAViewer specified for this OS.");
    }

    try {
      try {
        gaviewerLocation = this.getClass().getClassLoader().getResource(gaviewerLocation).getFile();
      }
      catch (NullPointerException e) {
      }
      this.process = Runtime.getRuntime().exec(gaviewerLocation + gaviewerOptions);
    }
    catch (IOException e) {
      throw new RuntimeException("GAViewer could not be started.");
    }
  }

  /**
   * Connect to an instance of GAViewer at the default port.  It should be
   * running at localhost.
   */
  public boolean connect() {
    return this.connect(new Integer(this.configuration.getProperty("GAViewer.port")));
  }

  /**
   * Connect to an instance of GAViewer.  It should be running at localhost
   * and listening at the given port.
   *
   * @param port The port the instance of GAViewer is listening at.
   * @return true if connection could be established.
   */
  public boolean connect(int port) {
    if (this.connection == null) {
      new Inform("Let GAViewer listen at port " + port + " by entering this:");
      new Inform("    add_net_port(" + port + ");", true);
      try {
        this.connection = new Socket("localhost", port);
        this.writer = new OutputStreamWriter(this.connection.getOutputStream());
        this.reader = new InputStreamReader(this.connection.getInputStream());
        // GAViewer always dumps all variable values it is currently holding.
        // Clear the stream from this.
        try {
          while (this.reader.ready()) {
            this.reader.read();
          }
        }
        catch (IOException e) {
        }
      }
      catch (UnknownHostException e) {
        new Inform("Host 'localhost' unreachable.  Wow.  You screwed up.", System.err);
        return false;
      }
      catch (IOException e) {
        new Inform("No application is listening at port " + port + ". We will retry this.");
        return this.connect(port);
      }
    }
    else {
      // Do something in case this.connection != null
      new Inform("There already exists a connection to an instance of GAViewer.");
    }
    return true;
  }

  /**
   * Returns the Reader object connected to GAViewer's socket.  With this 
   * object, one can read what GAViewer returns.
   *
   * @return The Reader connected to the GAViewer instance.
   */
  public Reader getReader() {
    return this.reader;
  }

  /**
   * Returns the Writer object connected to GAViewer's socket.  With this
   * object, one can give GAViewer new commands.
   *
   * @return The Writer connected to the GAViewer instance.
   */
  public Writer getWriter() {
    return this.writer;
  }

  /**
   * Terminates the GAViewer instance and closes the socket.
   */
  public void close() {
    try {
      this.connection.close();
      this.process.destroy();
    }
    catch (IOException e) {
      // this.connection was already closed, or cannot be closed.
    }
    catch (IllegalThreadStateException e) {
      this.process.destroy();
    }
    this.process = null;
    this.connection = null;
    this.reader = null;
    this.writer = null;
  }

  /* Helper functions */

  /**
   * Check if the OS is Mac OSX Snow Leopard (10.6).  This is used to choose
   * the right version of GAViewer.
   */
  private static boolean runningOnMac() {
    String os = System.getProperty("os.name").toLowerCase();
    return (os.indexOf("mac") >= 0);
  }

  /**
   * Check if the OS is Windows.  This is used to choose the right version of
   * GAViewer.
   */
  private static boolean runningOnWindows() {
    String os = System.getProperty("os.name").toLowerCase();
    return (os.indexOf("win") >= 0);
  }

  /**
   * Check if the OS is Linux.  This is used to choose the right version of
   * GAViewer.
   */
  private static boolean runningOnLinux() {
    String os = System.getProperty("os.name").toLowerCase();
    return (os.indexOf("linux") >= 0);
  }

}
