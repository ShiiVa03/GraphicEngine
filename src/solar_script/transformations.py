from dataclasses import dataclass

class Transformation:
    pass


@dataclass
class Translation(Transformation):
    x: float = 0
    y: float = 0
    z: float = 0


@dataclass
class Rotation(Transformation):
    angle : float = 0
    axisX: float = 0
    axisY: float = 0
    axisZ: float = 0


@dataclass
class Scale(Transformation):
    x: float = 0
    y: float = 0
    z: float = 0
