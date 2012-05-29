package plviewer;

import java.util.Queue;
import java.util.LinkedList;

public abstract class Function<T> {
  protected String name;
  protected int arity;

  public Function(String name, int arity) {
    this.name = name;
    this.arity = arity;
  }

  protected abstract T function(Queue<T> arguments);

  public T apply(Queue<T> arguments) {
    if (arguments == null) {
      arguments = new LinkedList<T>();
    }
    String msg = arguments.size() + " arguments supplied. ";
    if (arguments.size() != this.arity) {
      msg = "This function has arity " + this.arity + ". " + msg;
      throw new UnsupportedOperationException(msg);
    }
    return this.function(arguments);
  }
}
