# 2DOF Inverse Kinematics Solver

A lightweight C library and interactive Python visualizer for solving 2-degree-of-freedom planar arm kinematics. Given a target position and two limb lengths, it computes the joint angles required to reach that point - with support for both elbow-up and elbow-down configurations.

---

## Project Structure

```
.
├── engine/
│   ├── datatypes/
│   │   ├── angle.h          # Angle type with trig helpers
│   │   ├── anglePair.h      # Solver output struct
│   │   ├── target.h         # Solver input struct
│   │   └── vector2.h        # 2D float vector
│   ├── geometricSolver/
│   │   ├── geometricSolver.c  # IK solver implementation
│   │   └── geometricSolver.h
│   └── source.c             # CLI entry point
├── tests/
│   └── run_ui.py            # Interactive matplotlib visualizer
└── CMakeLists.txt
```

---

## Usage

### Interactive UI

```bash
python tests/run_ui.py
```

This compiles the library automatically and launches the visualizer. Requires CMake 3.20+, a C11-compatible compiler, and Python 3 with `matplotlib` and `numpy`.

- **Click** anywhere on the canvas to move the target
- **Limb 1 / Limb 2 sliders** adjust arm segment lengths
- **Elbow Up / Elbow Down** toggle switches between the two valid IK solutions

---

## Solver

The solver uses a standard geometric approach:

1. Checks reachability — the target must be within `|L1 - L2| ≤ dist ≤ L1 + L2`
2. Solves θ₂ (elbow angle) via the law of cosines
3. Solves θ₁ (base angle) via `atan2` with the elbow offset
4. Returns `invalid = 1` if the target is out of reach, `0` otherwise

The `elbowUp` parameter flips the sign of θ₂, selecting between the two geometrically valid configurations for any reachable point.

**Solver signature:**

```c
anglePair solve(target *t, int elbowUp);
```

---

## Data Types

| Type | Fields | Notes |
|---|---|---|
| `vector2` | `float x, y` | Target position |
| `angle` | `float radians` | Single joint angle |
| `anglePair` | `angle a, b; int invalid` | Solver output |
| `target` | `vector2 targetPos; double limbLength1, limbLength2` | Solver input |

---

## Dependencies

- **C standard library** — `math.h`, `float.h`
- **CMake** 3.20+
- **Python 3** — `matplotlib`, `numpy`, `ctypes` (stdlib)
