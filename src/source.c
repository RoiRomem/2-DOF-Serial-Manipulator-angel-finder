#include "datatypes/anglePair.h"
#include "datatypes/target.h"
#include "datatypes/vector2.h"
#include "geometricSolver/geometricSolver.h"
#include <stdio.h>

int main() {
  float l1 = 0, l2 = 0;
  float x = 0, y = 0;
  printf("--- 2DOF inverse kinematics solver --- \n");
  printf("Enter your 2 limb's length: ");
  scanf("%f %f", &l1, &l2);
  printf("Enter the final wanted positon relative to the base: ");
  scanf("%f %f", &x, &y);

  vector2 vt = vec2(x, y);

  target t;
  t.targetPos = vt;
  t.limbLength1 = l1;
  t.limbLength2 = l2;

  anglePair s = solve(&t);

  if (s.a.radians == 0 && s.b.radians == 0) {
    printf("ERROR: Target is out of reach for this mechanism");
    return 1;
  }

  printf(
      "solution is as follows: \n - base angle = %f \n - joint angle = %f \n",
      s.a.radians, s.b.radians);

  return 0;
}
