from dataclasses import dataclass

class Transformation:
    pass


class Translation(Transformation):

    def __init__(self, *args):
        if len(args) == 2:
            self.time, self.positions = args
            if not isinstance(self.positions, list):
                raise Exception("Positions must be a list")
        elif len(args) == 3:
            self.x, self.y, self.z = args
        else:
            raise Exception("Must contain only 2 or 3 args")


@dataclass
class Rotation(Transformation):
    time : float = 0
    axis_x: float = 0
    axis_y: float = 0
    axis_z: float = 0
    alpha : float = 0


@dataclass
class Scale(Transformation):
    x: float = 0
    y: float = 0
    z: float = 0
