#include "propositional_function.h"
#include "grounded_prop.h"

/**
 * Mark Benjamin 30th May 2017
 */

bool GroundedProp::isTrue(OOState s) { return pf.isTrue(move(s), params); }
