import xml.dom.minidom
import xml.etree.ElementTree as ET

from typing import Tuple
from camera import Camera
from element import Element
from dataclasses import dataclass
from transformations import Translation, Rotation, Scale


@dataclass
class GenElementsXML:
    file: str
    camera_options: Camera
    elements: Tuple[Element]
        

    def generate(self):
        world = ET.Element("world")

        camera = ET.SubElement(world, "camera")
        group = ET.SubElement(world, "group")

        ET.SubElement(camera, "position",
                      x=self.camera_options.position_x,
                      y=self.camera_options.position_y,
                      z=self.camera_options.position_z)
        ET.SubElement(camera, "lookAt",
                      x=self.camera_options.center_x,
                      y=self.camera_options.center_y,
                      z=self.camera_options.center_z)
        ET.SubElement(camera, "up",
                      x=self.camera_options.up_x,
                      y=self.camera_options.up_y,
                      z=self.camera_options.up_z)
        ET.SubElement(camera, "projection",
                      fov=self.camera_options.fov,
                      near=self.camera_options.near,
                      far=self.camera_options.far)

        for element in self.elements:
            sub_group = ET.SubElement(group, "group")
            self._generate_group(sub_group, element)


        dom = xml.dom.minidom.parseString(ET.tostring(world))
        xml_string = dom.toprettyxml()

        with open(self.file, "w") as f:
            f.write(xml_string)

        


    def _generate_group(self, group: ET.ElementTree, element: Element):
        if element.transformations:
            transformations = ET.SubElement(group, "transform")
            

            for transformation in element.transformations:
                match transformation.__class__.__name__:
                    case "Translation":
                        ET.SubElement(transformations, "translate", x=transformation.x, y=transformation.y, z=transformation.z)
                    case "Rotation":
                        ET.SubElement(transformations, "rotate", angle=transformation.angle, x=transformation.axis_x, y=transformation.axis_y, z=transformation.axis_z)
                    case "Scale":
                        ET.SubElement(transformations, "scale", x=transformation.x, y=transformation.y, z=transformation.z)


        models = ET.SubElement(group, "models")
        ET.SubElement(models, "model", file=element.file)

        
        for sub_element in element.elements:
            sub_group = ET.SubElement(group, "group")
            self._generate_group(sub_group, sub_element)
                
                

        

        

        
    




