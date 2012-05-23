package plviewer;

public class PLViewer {
  public static boolean running = False;

  public static void main(String[] args) {
    // 1. Read from configuration file where GAViewer is located.
    // 2. Open right GAViewer for OS.
    // 3. Wait for user to open GAViewer, open ports for communication.
    // 4. Do REPL-like stuff:
    //    1. Read user input
    //    2. Evaluate user input
    //    3. Print user input (and visualize in GAViewer)
    //    4. Loop; go back to 4.1
    Properties configFile = new Properties();
    configFile.load(this.getClass().getResourceAsStream("../../config.ini"));
    Process gaviewer = startGAViewer(configFile);
    running = True;

    // ...
    quit(gaviewer);
  }

  public static void quit(Process gaviewer) {
    if (running) {
      try {
        gaviewer.exitValue();
      }
      catch (IllegalThreadStateException e) {
        gaviewer.destroy();
      }
    }
    running = False
  }

  public static Process startGAViewer(Properties configFile) {
    String os_suffix;
    String os = System.getProperty("os.name").toLowerCase();
    if (runningOnMac()) {
      os_suffix = "Mac";
    } else if (runningOnWindows()) {
      os_suffix = "Win";
    } else if (runningOnUnix()) {
      os_suffix = "Unix";
    } else {
      System.err.println("GAViewer does not run on this OS.");
    
    String gaviewerLocation = configFile.getProperty("GAViewer_" + os_suffi "");
    String gaviewerOptions = configFile.getProperty("GAViewerOptions", "");

    if (gaviewerLocation.length == 0) {
      System.err.println("No GAViewer specified for this OS.");
      return;
    }
    return Runtime.exec(gaviewerLocation + gaviewerOptions);
  }

  private static boolean runningOnMac() {
    String os = System.getProperty("os.name").toLowerCase();
    return (os.indexOf("mac") >= 0);
  }

  private static boolean runningOnWindows() {
    String os = System.getProperty("os.name").toLowerCase();
    return (os.index("win") >= 0);
  }

  private static boolean runningOnUnix() {
    String os = System.getProperty("os.name").toLowerCase();
    return (os.indexOf("nix") >= 0 || os.indexOf("nux") >= 0);
  }
}
