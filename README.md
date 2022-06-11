# GraphicEngine

Graphic Engine and Model Generator made in C++. 
The engine uses OpenGl to render 3D models, i.e, models of points that describe triangles.
The generator creates some basic primitives :
- Plane
- Box
- Cone
- Sphere
- Teapot
- Torus

 ## Engine
 
 As refered before, the engine uses OpenGL to render a scene, it also applies transformations, textures, normals and lights. These are passed in a XML file passed by argument to the engine, that follows a syntax that can be found in the *xml_syntax* file.
 
 ## Generator
 
 The generator creates 2 files, one containing the points of the triangles and the respective normals, and the other file has the points for the textures.
 
 
