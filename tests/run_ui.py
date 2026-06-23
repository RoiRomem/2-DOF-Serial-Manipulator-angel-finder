import ctypes
import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.widgets import Slider, RadioButtons


class Vector2(ctypes.Structure):
    _fields_ = [("x", ctypes.c_float), ("y", ctypes.c_float)]


class Angle(ctypes.Structure):
    _fields_ = [("radians", ctypes.c_float)]


class Target(ctypes.Structure):
    _fields_ = [
        ("targetPos", Vector2),
        ("limbLength1", ctypes.c_double),
        ("limbLength2", ctypes.c_double),
    ]


class AnglePair(ctypes.Structure):
    _fields_ = [("a", Angle), ("b", Angle), ("invalid", ctypes.c_int)]


def compile_engine():
    project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    build_dir = os.path.join(project_root, "build")
    os.makedirs(build_dir, exist_ok=True)
    subprocess.run(["cmake", project_root], cwd=build_dir, check=True)
    subprocess.run(["cmake", "--build", build_dir], check=True)


compile_engine()

lib_path = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "..", "build", "libik_engine.so")
)
lib = ctypes.CDLL(lib_path)

lib.solve.argtypes = [ctypes.POINTER(Target), ctypes.c_int]
lib.solve.restype = AnglePair

fig, ax = plt.subplots(figsize=(7, 7))
plt.subplots_adjust(bottom=0.3)

ax_l1    = plt.axes([0.2, 0.17, 0.65, 0.03])
ax_l2    = plt.axes([0.2, 0.12, 0.65, 0.03])
ax_elbow = plt.axes([0.2, 0.01, 0.15, 0.09])

s_l1 = Slider(ax_l1, "Limb 1", 1.0, 20.0, valinit=10.0)
s_l2 = Slider(ax_l2, "Limb 2", 1.0, 20.0, valinit=10.0)
r_elbow = RadioButtons(ax_elbow, ("Elbow Up", "Elbow Down"), active=0)

last_pos = [5.0, 5.0]


def is_elbow_up():
    return 1 if r_elbow.value_selected == "Elbow Up" else 0


def get_angles(x, y, L1, L2):
    t = Target(targetPos=Vector2(x=x, y=y), limbLength1=L1, limbLength2=L2)
    result = lib.solve(ctypes.pointer(t), is_elbow_up())
    return (result.a.radians, result.b.radians) if not result.invalid else (None, None)


def draw_arm(x, y):
    L1, L2 = s_l1.val, s_l2.val
    t1, t2 = get_angles(x, y, L1, L2)
    ax.cla()
    if t1 is not None:
        x1 = L1 * np.cos(t1)
        y1 = L1 * np.sin(t1)
        x2 = x1 + L2 * np.cos(t1 + t2)
        y2 = y1 + L2 * np.sin(t1 + t2)
        ax.plot([0, x1, x2], [0, y1, y2], "o-", lw=4, color="royalblue")
        ax.plot(x, y, "x", color="red", markersize=10, markeredgewidth=2)
    else:
        ax.text(0, 0, "Out of Reach!", ha="center", va="center", color="red", fontsize=14)
    ax.set_xlim(-(L1 + L2 + 2), (L1 + L2 + 2))
    ax.set_ylim(-(L1 + L2 + 2), (L1 + L2 + 2))
    ax.grid(True)
    fig.canvas.draw()


def on_click(event):
    if event.inaxes and event.inaxes not in [ax_l1, ax_l2, ax_elbow]:
        last_pos[0], last_pos[1] = event.xdata, event.ydata
        draw_arm(event.xdata, event.ydata)


def update(val):
    draw_arm(last_pos[0], last_pos[1])


def update_elbow(label):
    draw_arm(last_pos[0], last_pos[1])


s_l1.on_changed(update)
s_l2.on_changed(update)
r_elbow.on_clicked(update_elbow)
fig.canvas.mpl_connect("button_press_event", on_click)

draw_arm(last_pos[0], last_pos[1])
plt.show()