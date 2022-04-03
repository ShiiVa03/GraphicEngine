from camera import Camera
from element import Element
from gen_elements_xml import GenElementsXML
from transformations import Translation, Rotation, Scale

file = "solar_system.xml"

camera = Camera(
    "0", "2", "60",
    "0", "2", "0",
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
moons = [
    Element("sphere.3d", transformations=[Translation("0", str(1.3 * U), "0"), Scale(str(.2 * U), str(.2 * U), str(.2 * U))])
]

transformations = [
    Translation(str(12 * U), "0", "0"),
    Scale(str(1 * U), str(1 * U), str(1 * U))
]

earth = Element("sphere.3d", elements=moons, transformations=transformations)


#### MARS ####
moons = [
    Element("sphere.3d", transformations=[Translation("0", str(1.3 * U), "0"), Scale(str(.2 * U), str(.2 * U), str(.2 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(-1.7 * U), "0"), Scale(str(.1 * U), str(.1 * U), str(.1 * U))])
]

transformations = [
    Translation(str(14 * U), "0", "0"),
    Scale(str(.7 * U), str(.7 * U), str(.7 * U))
]
mars = Element("sphere.3d", elements=moons, transformations=transformations)


#### JUPITER ####
moons = [
    Element("sphere.3d", transformations=[Translation("0", str(1.3 * U), "0"), Scale(str(.15 * U), str(.15 * U), str(.15 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(-1.7 * U), "0"), Scale(str(.1 * U), str(.1 * U), str(.1 * U))]),
    Element("sphere.3d", transformations=[Translation(str(-1.4 * U), str(1.4 * U), str(1.4 * U)), Scale(str(.2 * U), str(.2 * U), str(.2 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(1.6 * U), str(1.8 * U)), Scale(str(.12 * U), str(.12 * U), str(.12 * U))]),
    Element("sphere.3d", transformations=[Translation(str(-1 * U), "0", str(1 * U)), Scale(str(.17 * U), str(.17 * U), str(.17 * U))]),
    Element("sphere.3d", transformations=[Translation(str(1.2 * U), "0", str(1.5 * U)), Scale(str(.14 * U), str(.14 * U), str(.14 * U))])
]
transformations = [
    Translation(str(19 * U), "0", "0"),
    Scale(str(2.5 * U), str(2.5 * U), str(2.5 * U))
]
jupiter = Element("sphere.3d", elements=moons, transformations=transformations)


#### SATURN ####
torus = Element("torus.3d")

moons = [
    Element("sphere.3d", transformations=[Translation("0", str(-1.3 * U), "0"), Scale(str(.15 * U), str(.15 * U), str(.15 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(1.7 * U), "0"), Scale(str(.1 * U), str(.1 * U), str(.1 * U))]),
    Element("sphere.3d", transformations=[Translation(str(1.4 * U), str(-1.4 * U), str(1.4 * U)), Scale(str(.2 * U), str(.2 * U), str(.2 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(-1.6 * U), str(-1.8 * U)), Scale(str(.12 * U), str(.12 * U), str(.12 * U))]),
    Element("sphere.3d", transformations=[Translation(str(1 * U), "0", str(-1.3 * U)), Scale(str(.17 * U), str(.17 * U), str(.17 * U))]),
    Element("sphere.3d", transformations=[Translation(str(-1.2 * U), "0", str(-1.5 * U)), Scale(str(.14 * U), str(.14 * U), str(.14 * U))])
]

transformations = [
    Translation(str(25 * U), "0", "0"),
    Scale(str(2 * U), str(2 * U), str(2 * U))
]
saturn = Element("sphere.3d", elements=[torus] + moons, transformations=transformations)


#### URANUS ####
moons = [
    Element("sphere.3d", transformations=[Translation("0", str(1.3 * U), str(-1 * U)), Scale(str(.15 * U), str(.15 * U), str(.15 * U))]),
    Element("sphere.3d", transformations=[Translation(str(1.2 * U), str(-1.7 * U), "0"), Scale(str(.1 * U), str(.1 * U), str(.1 * U))]),
    Element("sphere.3d", transformations=[Translation(str(-1.2 * U), str(1.6 * U), str(1.1 * U)), Scale(str(.2 * U), str(.2 * U), str(.2 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(1.2 * U), str(1.8 * U)), Scale(str(.12 * U), str(.12 * U), str(.12 * U))]),
    Element("sphere.3d", transformations=[Translation(str(-1 * U), "0", str(1 * U)), Scale(str(.17 * U), str(.17 * U), str(.17 * U))]),
]

transformations = [
    Translation(str(31 * U), "0", "0"),
    Scale(str(1.6 * U), str(1.6 * U), str(1.6 * U))
]
uranus = Element("sphere.3d", elements=moons, transformations=transformations)


#### NEPTUNE ####
moons = [
    Element("sphere.3d", transformations=[Translation("0", str(1.3 * U), "0"), Scale(str(.15 * U), str(.15 * U), str(.15 * U))]),
    Element("sphere.3d", transformations=[Translation("0", str(-1.5 * U), str(1.2 * U)), Scale(str(.1 * U), str(.1 * U), str(.1 * U))]),
    Element("sphere.3d", transformations=[Translation(str(-1.4 * U), str(1.4 * U), str(1.4 * U)), Scale(str(.2 * U), str(.2 * U), str(.2 * U))]),
    Element("sphere.3d", transformations=[Translation(str(1 * U), str(1.6 * U), str(1.8 * U)), Scale(str(.12 * U), str(.12 * U), str(.12 * U))])
]

transformations = [
    Translation(str(35 * U), "0", "0"),
    Scale(str(1.5 * U), str(1.5 * U), str(1.5 * U))
]
neptune = Element("sphere.3d", elements=moons, transformations=transformations)














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
