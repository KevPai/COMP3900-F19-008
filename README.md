# COMP3900-F19-008
1.  3D Game Engine with a tank game

2.  Download repo

3.  Create a new visual studio project with the c++ desktop wizard

4.  Select console application and checkbox empty project

5.  Create

6.  Copy everything but the OpenGl and Assimp Folder into the project directory

7.  Include the copied files into the project by dragging them into the solution viewer

8.  Copy the openGl and Assimp folder outside the repo, we will be linking these to the project

9.  Go to project properties, VC++ Directories

10. Click on the include dropdown and select edit

11. Add a newline and press the … button

12. Navigate to the opengl folder and select the include folder, do the same for Assimp

13. Repeat steps 9-11 for Library

14. Then, navigate to Linker, then input

15. Add additional dependencies

16. Type in the text box separated by newline “glfw3.lib”, “opengl32.lib”, “assimp-vc142-mtd.lib”.

17. Press apply

18. Then run from debugger

19. Done



NOTE: To run the .exe from Debug folder, follow the structure of the Debug folder provided. 

Your folder should include the Models, Shaders, Textures, folders and the assimp-vc142-mtd.dll.
