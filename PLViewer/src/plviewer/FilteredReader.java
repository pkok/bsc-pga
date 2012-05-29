package plviewer;

import java.io.Reader;
import java.io.BufferedReader;

/**
 * Reads text from a character-input stream, buffers characters, and applies a
 * filter to the returned characters.
 *
 * The filter, represented by a {@link plviewer.Filter} object, is meant to 
 * do jobs like:
 * <ul>
 * <li> Filtering out repeated input;
 * <li> Translating from one language to another;
 * <li> Transform mathematical formulae from one algebra to another
 * </ul>
 */
public class FilteredReader extends BufferedReader {
  /**
   * The filtering object.  This object should supply the method to transform
   * the read text.
   */
  protected Filter filter;

  /**
   * The {@link java.io.Reader} that is decorated.  
   */
  protected Reader in;

  /**
   * Create a new BufferedReader, without any filtering.  As the filter is set
   * to the {@link plviewer.IdentityFilter}, no filtering of the read text 
   * will occur.  The buffer size is set for {@link java.io.BufferedReader}'s
   * default buffer size.
   *
   * @param in The {@link java.io.Reader} to decorate.
   */
  public FilteredReader(Reader in) {
    this(in, new IdentityFilter());
  }

  /**
   * Create a new Reader that alters what it has read, according to
   * the {@link Filter}.  The buffer size is set for {@link
   * java.io.BufferedReader}'s default buffer size.
   *
   * @param in The {@link java.io.Reader} to decorate.
   * @param filter Filters the text read from <code>in</code>.
   */
  public FilteredReader(Reader in, Filter filter) {
    super(in);
    if (filter == null) {
      filter = new IdentityFilter();
    }
    this.filter = filter;
  }
}
