package plviewer;

/**
 * Changes the input string according to a grammar.  Should be used with
 * classes like FilteredInputStream and FilteredOutputStream.
 *
 * @see FilterdInputStream
 * @see FilteredOutputStream
 */
interface Filter {
  /**
   * Call when a string should be manipulated according to some grammar.
   *
   * @param text The text to be transformed.
   * @return The transformed text.
   */
  public String filter(String text);
}
