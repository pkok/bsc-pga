package plviewer;

import java.io.PrintStream;
import java.util.Scanner;

/**
 * A logging tool.
 *
 * An especially bad one, though :(  More like a wrapper for
 * System.out.println
 */
public class Inform {
  /**
   * Print a message to the user.  The message is printed to System.out.
   *
   * @param message The message to be printed.
   *      the enter key.
   */
  public Inform(String message) {
    this(message, false, System.out);
  }

  /**
   * Print a message to the user.  The process will wait to continue if
   * waitForReply is true.  The message is printed to System.out.
   *
   * @param message The message to be printed.
   * @param waitForReply If true, the program will wait until the user pressed
   *      the enter key.
   */
  public Inform(String message, boolean waitForReply) {
    this(message, waitForReply, System.out);
  }

  /**
   * Print a message to the user.
   *
   * @param message The message to be printed.
   *      the enter key.
   * @param stream The stream to print to, e.g. System.out or System.err.
   */
  public Inform(String message, PrintStream stream) {
    this(message, false, stream);
  }

  /**
   * Print a message to the user.  The process will wait to continue if
   * waitForReply is true.
   *
   * @param message The message to be printed.
   * @param waitForReply If true, the program will wait until the user pressed
   *      the enter key.
   * @param stream The stream to print to, e.g. System.out or System.err.
   */
  public Inform(String message, boolean waitForReply, PrintStream stream) {
    stream.println(message);
    if (waitForReply) {
      Scanner scanner = new Scanner(System.in);
      scanner.nextLine();
    }
  }
}
