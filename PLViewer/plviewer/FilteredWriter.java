package plviewer;

import java.io.Writer;
import java.io.FilterWriter;

public class FilteredWriter extends FilterWriter {
  protected Filter filter;

  public FilteredWriter(Writer in) {
    this(in, new IdentityFilter());
  }

  public FilteredWriter(Writer in, Filter filter) {
    super(in);
    if (filter == null) {
      filter = new IdentityFilter();
    }
    this.filter = filter;
  }
}
