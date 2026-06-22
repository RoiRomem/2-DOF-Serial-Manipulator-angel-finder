#include "datatypes/anglePair.h"
#include "datatypes/target.h"
#include "datatypes/vector2.h"
#include "geometricSolver/geometricSolver.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
  float l1 = 0, l2 = 0;
  float x = 0, y = 0;
  int config = 0;

  printf("--- 2DOF inverse kinematics solver --- \n");
  printf("Enter your 2 limb's length: ");
  scanf("%f %f", &l1, &l2);
  printf("Enter the target position (x y): ");
  scanf("%f %f", &x, &y);
  printf("Choose configuration (1 for Elbow Up, 0 for Elbow Down): ");
  scanf("%d", &config);

  vector2 vt = {x, y};

  target t;
  t.targetPos = vt;
  t.limbLength1 = l1;
  t.limbLength2 = l2;

  anglePair s = solve(&t, (bool)config);

  if ((s.a.radians == 0 && s.b.radians == 0 && x != 0 && y != 0) || s.invalid) {
    printf("ERROR: Target is out of reach for this mechanism!\n");
    return 1;
  }

  printf("Solution: \n - Base angle: %.4f rad \n - Joint angle: %.4f rad \n",
         s.a.radians, s.b.radians);

  return 0;
}
