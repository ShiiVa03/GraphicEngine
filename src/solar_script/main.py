from random import random
from camera import Camera
from element import Element
from orbit import create_orbit
from gen_elements_xml import GenElementsXML
from transformations import Translation, Rotation, Scale

file = "solar_system.xml"

camera = Camera(
    "0", "2", "60",
    "0", "2", "0",
    "0", "1", "0",
    "60", "1", "1000"
)

def get_rand():
    return round(random(), 3)

def get_3rand():
    return (get_rand() for i in range(3))

#### SUN ####
transformations = [
    Scale(6, 6, 6),
    Rotation(13, 0, get_rand(), 0)
]
sun = Element("sphere.3d", transformations=transformations)


#### MERCURY ####
transformations = [
    Translation(5, create_orbit((7.5, 0, 0))),
    Scale(0.5, 0.5, 0.5),
    Rotation(5, 0, get_rand(), 0)
]
mercury = Element("sphere.3d", transformations=transformations)


#### VENUS ####
transformations = [
    Translation(7, create_orbit((9.5, 0, 0))),
    Scale(0.9, 0.9, 0.9),
    Rotation(7, 0, get_rand(), 0)
]
venus = Element("sphere.3d", transformations=transformations)


#### EARTH ####
moons = [
    Element("sphere.3d", transformations=[Translation(5, create_orbit((0, 1.3, 0))), Scale(0.2, 0.2, 0.2), Rotation(6, *get_3rand())])
]

transformations = [
    Translation(10, create_orbit((12, 0, 0))),
    Scale(1, 1, 1),
    Rotation(8, 0, get_rand(), 0)
]

earth = Element("sphere.3d", elements=moons, transformations=transformations)


#### MARS ####
moons = [
    Element("sphere.3d", transformations=[Translation(20, create_orbit((0, 1.3, 0))), Scale(0.2, 0.2, 0.2), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(20, create_orbit((0, -1.7, 0))), Scale(0.1, 0.1, 0.1), Rotation(6, *get_3rand())])
]

transformations = [
    Translation(12, create_orbit((14, 0, 0))),
    Scale(0.7, 0.7, 0.7),
    Rotation(8, 0, get_rand(), 0)
]
mars = Element("sphere.3d", elements=moons, transformations=transformations)


#### JUPITER ####
moons = [
    Element("sphere.3d", transformations=[Translation(20, create_orbit((0, 1.3, 0))), Scale(0.15, 0.15, 0.15), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(20, create_orbit((0, -1.7, 0))), Scale(0.1, 0.1, 0.1), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(20, create_orbit((-1.4, 1.4, 1.4))), Scale(0.2, 0.2, 0.2), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(20, create_orbit((0, 1.6, 1.8))), Scale(0.12, 0.12, 0.12), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(20, create_orbit((-1, 0, 1))), Scale(0.17, 0.17, 0.17), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(20, create_orbit((1.2, 0, 1.5))), Scale(0.14, 0.14, 0.14), Rotation(6, *get_3rand())])
]
transformations = [
    Translation(15, create_orbit((19, 0, 0))),
    Scale(2.5, 2.5, 2.5),
    Rotation(12, 0, get_rand(), 0)
]
jupiter = Element("sphere.3d", elements=moons, transformations=transformations)


#### SATURN ####
torus = Element("torus.3d")

moons = [
    Element("sphere.3d", transformations=[Translation(8, create_orbit((0, -1.3, 0))), Scale(0.15, 0.15, 0.15), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(8, create_orbit((0, 1.7, 0))), Scale(0.1, 0.1, 0.1), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(8, create_orbit((1.4, -1.4, 1.4))), Scale(0.2, 0.2, 0.2), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(8, create_orbit((0, -1.6, -1.8))), Scale(0.12, 0.12, .12), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(8, create_orbit((1, 0, -1.3))), Scale(0.17, 0.17, 0.17), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(8, create_orbit((-1.2, 0, -1.5))), Scale(0.14, 0.14, 0.14), Rotation(6, *get_3rand())])
]

transformations = [
    Translation(18, create_orbit((25, 0, 0))),
    Scale(2, 2, 2),
    Rotation(10, 0, get_rand(), 0)
]
saturn = Element("sphere.3d", elements=[torus] + moons, transformations=transformations)


#### URANUS ####
moons = [
    Element("sphere.3d", transformations=[Translation(9, create_orbit((0, 1.3, -1))), Scale(0.15, 0.15, 0.15), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(9, create_orbit((1.2, -1.7, 0))), Scale(0.1, 0.1, 0.1), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(9, create_orbit((-1.2, 1.6, 1.1))), Scale(0.2, 0.2, 0.2), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(9, create_orbit((0, 1.2, 1.8))), Scale(0.12, 0.12, 0.12), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(9, create_orbit((-1, 0, 1))), Scale(0.17, 0.17, 0.17), Rotation(6, *get_3rand())]),
]

transformations = [
    Translation(20, create_orbit((31, 0, 0))),
    Scale(1.6, 1.6, 1.6),
    Rotation(9, 0, get_rand(), 0)
]
uranus = Element("sphere.3d", elements=moons, transformations=transformations)


#### NEPTUNE ####
moons = [
    Element("sphere.3d", transformations=[Translation(6, create_orbit((0, 1.3, 0))), Scale(0.15, 0.15, 0.15), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(6, create_orbit((0, -1.5, 1.2))), Scale(0.1, 0.1, 0.1), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(6, create_orbit((-1.4, 1.4, 1.4))), Scale(0.2, 0.2, 0.2), Rotation(6, *get_3rand())]),
    Element("sphere.3d", transformations=[Translation(6, create_orbit((1, 1.6, 1.8))), Scale(0.12, 0.12, 0.12), Rotation(6, *get_3rand())])
]

transformations = [
    Translation(25, create_orbit((35, 0, 0))),
    Scale(1.5, 1.5, 1.5),
    Rotation(9, 0, get_rand(), 0)
]
neptune = Element("sphere.3d", elements=moons, transformations=transformations)



#### COMET ####

transformations = [
    Translation(15, create_orbit((40, 30, 0)), True),
    Scale(0.1, 0.1, 0.1),
    Rotation(9, *get_3rand())
]

comet = Element("bezier.3d", transformations=transformations)












solar_system = [
    sun,
    mercury,
    venus,
    earth,
    mars,
    jupiter,
    saturn,
    uranus,
    neptune,
    comet
]


if __name__ == '__main__':
    elements_xml = GenElementsXML(file, camera, solar_system)
    elements_xml.generate()
