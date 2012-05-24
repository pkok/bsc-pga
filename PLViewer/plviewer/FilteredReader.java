package plviewer;

import java.io.Reader;
import java.io.BufferedReader;

/**
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
    this(in, new IdentityFilter(), -1);
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
    this(in, filter, -1);
  }

  /**
   * Create a new BufferedReader, without any filtering.  As the filter is set
   * to the {@link plviewer.IdentityFilter}, no filtering of the read text 
   * will occur.
   *
   * @param in The {@link java.io.Reader} to decorate.
   * @param size The buffer size, as specified for {@link
   * java.io.BufferedReader}
   */
  public FilteredReader(Reader in, int size) {
    this(in, new IdentityFilter(), size);
  }

  /**
   * Create a new Reader that alters what it has read, according to
   * the {@link plviewer.Filter}.
   *
   * @param in The {@link java.io.Reader} to decorate.
   * @param filter Filters the text read from <code>in</code>.
   * @param size The buffer size, as specified for {@link java.io.BufferedReader}.
   */
  public FilteredReader(Reader in, Filter filter, int size){
    super(in, size);
    if (filter == null) {
      filter = new IdentityFilter();
    }
    this.filter = filter;
  }
}
