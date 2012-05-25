package plviewer;

import java.io.Writer;
import java.io.BufferedWriter;

/**
 * Writes text from a character-input stream, buffers characters, and applies
 * a filter to the returned characters.
 *
 * The filter, represented by a {@link plviewer.Filter} object, is meant to 
 * do jobs like:
 * <ul>
 * <li> Filtering out repeated input;
 * <li> Translating from one language to another;
 * <li> Transform mathematical formulae from one algebra to another
 * </ul>
 */
public class FilteredWriter extends BufferedWriter {
  /**
   * The filtering object.  This object should supply the method to transform
   * the text that will be written to {@link #out}.
   */
  protected Filter filter;

  /**
   * The {@link java.io.Writer} that is decorated.
   */
  protected Writer out;

  /**
   * Create a new BufferedWriter, without any filtering.  As the filter is set
   * to the {@link plviewer.IdentityFilter}, no filtering of the written text
   * will occur.  The buffer size is set for {@link java.io.BufferedWriter}'s
   * default buffer size.
   *
   * @param out The {@link java.io.Writer} to decorate.
   */
  public FilteredWriter(Writer out) {
    this(out, new IdentityFilter());
  }

  /**
   * Create a new Writer that alters what it has read, according to
   * the {@link Filter}.  The buffer size is set for {@link
   * java.io.BufferedWriter}'s default buffer size.
   *
   * @param out The {@link java.io.Writer} to decorate.
   * @param filter Filters the text read from <code>out</code>.
   */
  public FilteredWriter(Writer out, Filter filter) {
    this(out, filter, -1);
  }

  /**
   * Create a new BufferedWriter, without any filtering.  As the filter is set
   * to the {@link plviewer.IdentityFilter}, no filtering of the read text 
   * will occur.
   *
   * @param out The {@link java.io.Writer} to decorate.
   * @param size The buffer size, as specified for {@link
   * java.io.BufferedWriter}
   */
  public FilteredWriter(Writer out, int size) {
    this(out, new IdentityFilter(), size);
  }

  /**
   * Create a new Writer that alters what it has read, according to
   * the {@link plviewer.Filter}.
   *
   * @param out The {@link java.io.Writer} to decorate.
   * @param filter Filters the text read from <code>out</code>.
   * @param size The buffer size, as specified for {@link java.io.BufferedWriter}.
   */
  public FilteredWriter(Writer out, Filter filter, int size) {
    super(out);
    if (filter == null) {
      filter = new IdentityFilter();
    }
    this.filter = filter;
  }
}
