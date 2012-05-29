package plviewer;

import java.util.Map;
import java.util.TreeMap;
import java.util.AbstractMap;
import java.util.Queue;
import java.util.LinkedList;

import org.antlr.runtime.Parser;
import org.antlr.runtime.RecognizerSharedState;
import org.antlr.runtime.TokenStream;

import pl3ga_pkg.mv;
import pl3ga_pkg.pl3ga;

import plviewer.Function;

public abstract class CustomParser extends Parser {
  /**
   * Maps constant names to values.
   */
  protected Map<String, mv> constantMap;
  /**
   * Maps variable names to values.
   */
  protected Map<String, mv> variableMap;
  /**
   * Mapping of <function name, arity> to a {@link plviewer.Function}.
   */
  protected Map<Map.Entry<String, Integer>, Function<mv>> functionMap;

  public CustomParser(TokenStream input) {
    this(input, new RecognizerSharedState());
  }

  public CustomParser(TokenStream input, RecognizerSharedState state) {
    super(input, state);

    this.constantMap = new TreeMap<String, mv>();
    this.variableMap = new TreeMap<String, mv>();
    this.functionMap = new TreeMap<Map.Entry<String, Integer>, Function<mv>>();

    // Define which constants are predefined.  When adding more constants, 
    // consider updating the grammar as well.
    setConstant("e01", pl3ga.e01.to_mv());
    setConstant("e02", pl3ga.e02.to_mv());
    setConstant("e03", pl3ga.e03.to_mv());
    setConstant("e12", pl3ga.e12.to_mv());
    setConstant("e23", pl3ga.e23.to_mv());
    setConstant("e31", pl3ga.e31.to_mv());

    // Define which functions can be called.  This can be done without
    // updating the grammar.
    setFunction(new Function<mv>("dual", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.dual(arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("undual", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.undual(arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("equals", 2) { 
      protected mv function(Queue<mv> arguments) { 
        if (pl3ga.equals(arguments.poll(), arguments.poll(), 0.005f)) {
          return new mv(1.0f); 
        }
        return new mv();
      } 
    });
    setFunction(new Function<mv>("grade", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.extractGrade(arguments.poll(), (int)arguments.poll().get_scalar()); 
      } 
    });
    setFunction(new Function<mv>("hp", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.hp(arguments.poll(), arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("ihp", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.ihp(arguments.poll(), arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("hip", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.hip(arguments.poll(), arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("mhip", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.mhip(arguments.poll(), arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("lc", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.lc(arguments.poll(), arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("rc", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.rc(arguments.poll(), arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("sp", 2) { 
      protected mv function(Queue<mv> arguments) { 
        return new mv(pl3ga.sp(arguments.poll(), arguments.poll())); 
      } 
    });
    setFunction(new Function<mv>("norm", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return new mv(pl3ga.norm(arguments.poll())); 
      } 
    });
    setFunction(new Function<mv>("norm2", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return new mv(pl3ga.norm2(arguments.poll())); 
      } 
    });
    setFunction(new Function<mv>("exp", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.exp(arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("sin", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.sin(arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("cos", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.cos(arguments.poll());
      }
    });
    setFunction(new Function<mv>("sinh", 1) { 
      protected mv function(Queue<mv> arguments) { 
        return pl3ga.sinh(arguments.poll()); 
      } 
    });
    setFunction(new Function<mv>("cosh", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.cosh(arguments.poll());
      }
    });
    setFunction(new Function<mv>("reverse", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.reverse(arguments.poll());
      }
    });
    setFunction(new Function<mv>("clifford_conjugate", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.cliffordConjugate(arguments.poll());
      }
    });
    setFunction(new Function<mv>("grade_involution", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.gradeInvolution(arguments.poll());
      }
    });
    setFunction(new Function<mv>("unit", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.unit(arguments.poll());
      }
    });
    setFunction(new Function<mv>("inverse", 1) {
      protected mv function(Queue<mv> arguments) {
      return pl3ga.versorInverse(arguments.poll());
      }
    });
  }

  /**
   * Returns the value of the constant with this name.
   *
   * @param name The name of the constant.
   * @return The multivector representation of the constant's value.
   */
  protected mv getConstant(String name) {
    mv value = constantMap.get(name);
    if (value == null) {
      String msg = "The constant \"" + name + "\" does not exist.";
      throw new RuntimeException(msg);
    }
    return value;
  }

  /**
   * Sets a constant, and returns its old value.  When adding constants, 
   * consider updating the grammar as well.
   * <p>
   * Specified constants are:
   * e01, e02, e03, e12, e23, e31
   *
   * @param name The name of the constant that should be added.
   * @param value The value that should be bound to this {@code name}.
   * @return The previous value associated with {@code name}, or {@code null} 
   *  if there was no mapping for {@code name}. (A {@code null} return can 
   *  also indicate that the map previously associated {@code null} with 
   *  {@code name}.)
   */
  protected mv setConstant(String name, mv value) {
    return constantMap.put(name, value);
  }

  /**
   * Returns the value of the variable with this name.
   *
   * @param name The name of the variable.
   * @return The multivector representation of the variable's value.
   */
  protected mv getVariable(String name) {
    mv value = variableMap.get(name);
    if (value == null) {
      /*
      String msg = "The variable \"" + name + "\" is not set.";
      throw new RuntimeException(msg);
      */
      value = new mv();
    }
    return value;
  }

  /**
   * Sets a variable, and returns its old value.  
   *
   * @param name The name of the variable that should be added.
   * @param value The value that should be bound to this {@code name}.
   * @return The previous value associated with {@code name}, or {@code null} 
   *  if there was no mapping for {@code name}. (A {@code null} return can 
   *  also indicate that the map previously associated {@code null} with 
   *  {@code name}.)
   */
  protected mv setVariable(String name, mv value) {
    return variableMap.put(name, value);
  }

  /**
   * Returns the function object mapped with this name and arity.  If there 
   * is no function with the same name and arity stored, a 
   * UnsupportedOperationException is raised.
   *
   * @param name The name of the function.
   * @param arity The number of arguments this function should accept.
   * @return The function with this {@code name} and {@code arity}.
   */
  protected Function<mv> getFunction(String name, int arity) {
    Function<mv> function = functionMap.get(new AbstractMap.SimpleEntry<String,Integer>(name, arity));
    if (function == null) {
      String msg = "The function \"" + name + "\"/" + arity + " is not defined.";
      throw new UnsupportedOperationException(msg);
    }
    return function;
  }

  /**
   * Stores a function.  It can be retrieved with 
   * {@link #getFunction(String, int)}, given its name and arity.
   *
   * @param function The function that is to be stored.
   * @return The previous value associated with this name and arity, or 
   * {@code null} if there was no such mapping. (A {@code null} return can also 
   * indicate that the map previously associated {@code null} with this name 
   * and arity.)
   */
  protected Function<mv> setFunction(Function<mv> function) {
    Map.Entry<String, Integer> e = new AbstractMap.SimpleEntry<String, Integer>(function.name, function.arity);
    return functionMap.put(e, function);
  }

  /**
   * Applies a function to its arguments.  The {@link java.util.Queue} 
   * representing the argument list should have the exact same number of 
   * arguments as the function that is being called.
   *
   * @param function The name of the function
   * @param arglist This contains the arguments the function.
   *
   * @return The result of {@code function}({@code arglist[0]}, ...).
   */
  protected mv applyFunction(String function, Queue<mv> arglist) {
    return getFunction(function, arglist.size()).apply(arglist);
  }

  /**
   * Converts a string representation of a float to a {@link pl3ga_pkg.mv}.  This is needed, as all operations will be based on {@code mv}.  Writing it so it can be used on {@code float}s and {@code mv}s would be too tedious.
   *
   * @param number A string representation of a {@code float} or {@code int}.
   * @return A {@link pl3ga_pkg.mv} representation of a {@code float} or {@code int}.
   */
  protected mv toMV(String number) {
    if (number != null) {
      return new mv(new Float(number));
    }
    return new mv();
  }

  /**
   * Sets {@code ans}, and if needed, sends the expression to a GAViewer 
   * instance.
   *
   * @param expression A complete expression in our PLViewer language.
   * @param display Whether this element should be displayed in GAViewer.  
   *  If set to {@code true}, it will be transformed to a (set of) elements in 
   *  CGA/PGA, and will be drawn.
   */
  protected void completeExpr(mv result, boolean display) {
    if (display) {
      // recompute as CGA/PGA
      // send to GAViewer
    }
    setVariable("ans", result);
  }

  /**
   * Applies a unary operator to its operand.  Its token code is used to 
   * identify which operator it is.  Subclasses only need to implement this 
   * method and {@link applyOperator(int, pl3ga_pkg.mv, pl3ga_pkg.mv}.
   *
   * @param op The token code for a certain operator.
   * @param x The only argument to this operator.
   *
   * @return The result of op(x).
   */
  protected abstract mv applyOperator(int op, mv x);
  /**
   * Applies a binary operator to its operands.  Its token code is used to 
   * identify which operator it is.  Subclasses only need to implement this 
   * method and {@link applyOperator(int, pl3ga_pkg.mv}.
   *
   * @param op The token code for a certain operator.
   * @param x The left operand to this operator.
   * @param y The right operand to this operator.
   *
   * @return The result of op(x, y).
   */
  protected abstract mv applyOperator(int op, mv x, mv y);
}
