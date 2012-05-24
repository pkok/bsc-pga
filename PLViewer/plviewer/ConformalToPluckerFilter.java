package plviewer;

/**
 * Changes a string denoting a CGA entity into one denoting a PLGA entity.
 */
public class ConformalToPluckerFilter implements Filter {
  /**
   * This constructor does nothing.
   */
  public ConformalToPluckerFilter() {
  }

  /**
   * Changes a string denoting a CGA entity into one denoting a PLGA entity.
   *
   * @param conformal A string representing entities in conformal geometric
   *      algebra.
   * @return A string representing corresponding entities in the geometric
   *      algebra of Plucker lines.
   */
  public String filter(String conformal) {
    return "";
  }
}
