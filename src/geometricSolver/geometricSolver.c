#include "geometricSolver.h"
#include <math.h>

// output error tracking: 0,0 out of reach
anglePair solve(target *t, int elbowUp) {
  double x = t->targetPos.x;
  double y = t->targetPos.y;
  double l1Sq = t->limbLength1 * t->limbLength1;
  double l2Sq = t->limbLength2 * t->limbLength2;
  double distSq = x * x + y * y;

  // Reachability check
  double dist = sqrt(distSq);
  if (dist > (t->limbLength1 + t->limbLength2) ||
      dist < fabsf(t->limbLength1 - t->limbLength2)) {
    return (anglePair){{0}, {0}, 1};
  }

  // Solve for theta2 (elbow angle)
  double cosTheta2 =
      (distSq - l1Sq - l2Sq) / (2.0 * t->limbLength1 * t->limbLength2);
  cosTheta2 = fmax(-1.0, fmin(1.0, cosTheta2));

  // Choose elbow configuration
  double theta2 = acos(cosTheta2);
  if (elbowUp)
    theta2 = -theta2;

  // Solve for theta1 (base angle)
  double theta1 =
      atan2(y, x) - atan2(t->limbLength2 * sin(theta2),
                          t->limbLength1 + t->limbLength2 * cos(theta2));

  return (anglePair){{theta1}, {theta2}, 0};
}
