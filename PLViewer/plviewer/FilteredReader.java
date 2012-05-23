package plviewer;

import java.io.Reader;
import java.io.BufferedReader;

/**
 */
public class FilteredReader extends BufferedReader {
  protected Filter filter;

  public FilteredReader(Reader in) {
    this(in, new IdentityFilter());
  }

  public FilteredReader(Reader in, Filter filter) {
    this(in, filter, 8192);
  }

  public FilteredReader(Reader in, int size) {
    this(in, new IdentityFilter(), size);
  }

  public FilteredReader(Reader in, Filter filter, int size){
    super(in, size);
    if (filter == null) {
      filter = new IdentityFilter();
    }
    this.filter = filter;
  }
}
