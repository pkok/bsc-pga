package plviewer;

/**
 * This filter does not change the input a single bit.  It can be used if a
 * method expects a Filter, but you do not want to filter anything.
 */
public class IdentityFilter implements Filter {
  /**
   * Returns its input.
   *
   * @param input The string to be filtered.
   * @return input
   */
  public String filter(String input) {
    return input;
  }
}
