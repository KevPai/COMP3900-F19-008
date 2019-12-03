# COMP3900-F19-008
3D Game Engine with a tank game

Download repo
Create a new visual studio project with the c++ desktop wizard
Select console application and checkbox empty project
Create
Copy everything but the OpenGl and Assimp Folder into the project directory
Include the copied files into the project by dragging them into the solution viewer
Copy the openGl and Assimp folder outside the repo, we will be linking these to the project
Go to project properties, VC++ Directories
Click on the include dropdown and select edit
Add a newline and press the … button
Navigate to the opengl folder and select the include folder, do the same for Assimp
Repeat steps 9-11 for Library
Then, navigate to Linker, then input
Add additional dependencies
Type in the text box separated by newline “glfw3.lib”, “opengl32.lib”, “assimp-vc142-mtd.lib”.
Press apply
Then run from debugger
Done

NOTE: To run the .exe from Debug folder, follow the structure of the Debug folder provided. Your folder should include the Models, Shaders, Textures, folders and the assimp-vc142-mtd.dll.
