from camera import Camera
from element import Element
from gen_elements_xml import GenElementsXML
from transformations import Translation, Rotation, Scale

file = "solar_system.xml"

camera = Camera(
    "5", "5", "5",
    "0", "0", "0",
    "0", "1", "0",
    "60", "1", "1000"
)

U = 1 # Unit


#### SUN ####
transformations = [
    Scale(str(6 * U), str(6 * U), str(6 * U))
]
sun = Element("sphere.3d", transformations=transformations)


#### MERCURY ####
transformations = [
    Translation(str(7.5 * U), "0", "0"),
    Scale(str(.5 * U), str(.5 * U), str(.5 * U))
]
mercury = Element("sphere.3d", transformations=transformations)


#### VENUS ####
transformations = [
    Translation(str(9.5 * U), "0", "0"),
    Scale(str(.9 * U), str(.9 * U), str(.9 * U))
]
venus = Element("sphere.3d", transformations=transformations)


#### EARTH ####
transformations = [
    Translation(str(12 * U), "0", "0"),
    Scale(str(1 * U), str(1 * U), str(1 * U))
]
earth = Element("sphere.3d", transformations=transformations)


#### MARS ####
transformations = [
    Translation(str(14 * U), "0", "0"),
    Scale(str(.7 * U), str(.7 * U), str(.7 * U))
]
mars = Element("sphere.3d", transformations=transformations)


#### JUPITER ####
transformations = [
    Translation(str(19 * U), "0", "0"),
    Scale(str(2.5 * U), str(2.5 * U), str(2.5 * U))
]
jupiter = Element("sphere.3d", transformations=transformations)


#### SATURN ####
transformations = [
    Translation(str(24 * U), "0", "0"),
    Scale(str(2 * U), str(2 * U), str(2 * U))
]
saturn = Element("sphere.3d", transformations=transformations)


#### URANUS ####
transformations = [
    Translation(str(28 * U), "0", "0"),
    Scale(str(1.6 * U), str(1.6 * U), str(1.6 * U))
]
uranus = Element("sphere.3d", transformations=transformations)


#### NEPTUNE ####
transformations = [
    Translation(str(32 * U), "0", "0"),
    Scale(str(1.5 * U), str(1.5 * U), str(1.5 * U))
]
neptune = Element("sphere.3d", transformations=transformations)














solar_system = [
    sun,
    mercury,
    venus,
    earth,
    mars,
    jupiter,
    saturn,
    uranus,
    neptune
]


if __name__ == '__main__':
    elements_xml = GenElementsXML(file, camera, solar_system)
    elements_xml.generate()
