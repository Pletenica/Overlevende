# OVERLEVENDE
This is an engine done by Roger Pérez Romera and Josep Sànchez Arbona.
This project began from a subject in the grade Videogamaes Design and Development in CITM UPC Terrassa, we are two in-progress developers that want to give the best experience
through our engine: Overlende. 

In the next link you will find all the game information and documentation in the project's repository:

* https://github.com/Pletenica/Overlevende


## Credits

### Josep Sànchez Arbona
* Responsability: Code
* Github account: daskza19(https://github.com/daskza19)

### Roger Pérez Romera
* Responsability: Code
* Github account: Rugiacreed(https://github.com/Rugiacreed)


## Pletenica's Motor

# How to use Overlevende Engine:

First of all you will want to identificate the menu bar in the engine, it has 3 drop down options that you can select by left clicking on one of them and moving around the
other. The first one, the “edit” menu will allow you to configure the engine at your own taste and exit the engine, with the new version of the engine you can use the 
following new options: open project and save project. The “help” menu can be used to look for the engine’s information like documentation, 
versions and user’s help. Finally the “Github” menu contains all the links to the contributors of these projects for more information, content and their own engine’s project.

![Menu Bar](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/MenuBar.PNG?raw=true)

Once you are inside the engine you will see at least 5 different windows, you should be able to identicate the scene window at first sight and the others windows will be 
explained later on. Every window is able to be moved wherever you want on the engine window or outside without affecting its performance. You can do this by selecting the 
title bar of the window with the left click of the mouse and drag the window into a new position.
If the window is inside the engines window you can hide the title bar of each window using the upper left arrow, if they are outside the engines window you can use the same 
button to minimize the entire window.



- The configuration window:
	You can open the configuration window to edit some features of the motor or see some performance data. One of the new and remarkable features is the theme and color 
	editor, we think you will enjoy the motor more if you can personalize the aesthetic of your working space with the help of our designers to avoid eye-damaging 
	creations.

	In the last version we have added the Time Configuration. This data will give you information about the motor like the time since the start-up, the time of the game
	this is running and other features. Some of this features will start from the time you start working in Overlevende but some of thesewssee are linked to the options
	window(see below).

![Configuration](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/ConfigurationW.PNG?raw=true)

- The scene window:
	
	These will be where you will be working major of the time, so you can move around the camera using the mouse or the keyboard:
	* Mouse functionalities:
	Middle click and drag to move the camera around.
	Use the mouse wheel to get closer or further from an object.
	se right click and drag to turn the camera around.

	* Key functionalities:
	Use W/S to get closer or further in the scene.
	A/D will let you move left and right.
	F will focus your camera to the gameobject.
	While Right clicking, “WASD” fps-like movement and free look around is enabled.
	Shift will double the speed of movement.

	* Extra functionalities:
	You can use F1 to disable the grid in the scene window.
	You can use 0 to deselect every gameobject from the inspector.

	* Transformations functionalities:
	In the new version you can work with the gameobjects by editing them, you can control this by using the following controls:
	1 to enable the position gizmo, drag it to move the gameobject at your disered position.
	2 to enable the rotation gizmo, drag it to rotate the gameobject at your disered position.
	3 to enable the escale gizmo, drag it to escale the gameobject at your disered size.
	Note that you can modify any of these features in the inspector window too.
	

	You can drag a fbx to create a gameobject and see it in the scene, you can select this object and drop its texture too. If the model you import comes with textures 
	linked and they are in the same folder they will be imported at the same time as the fbx. Be aware that Overlevende shares some default assets to work with in the folder 
	“Assets” on files folder.
	Note that, if a gameobjects contanis different meshes this ones will be added as a children of the main gameobject, you can select and edit every gameobject that have a
	mesh independently, this feature has been added to the last version of overlevende's engine.

![Windows](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/windows.PNG?raw=true)

- Hierarchy window:
	This is a simple window where you will see every game object, scene and components of your work. You can open tree groups to select every part of it.
	With the version Overlevende Engine 0.7 yo have some option you will want to know before working with this window: the first one is that you can create empty objects in
	the scene, then you have the option to create an empty object inside an existing gameobject that you have selected, finally be careful with the clear option because it 
	will delete all the gameobjects from the scene or root.
	Knowing this features you wll want to youse too the drag and reaprent feature that will help you making more agile your work, you can select and delete from the hierarchy 
	too.

- Options window:
	This window will help the user to take short cuts and make some actions when working with Overlevende: add primitive objects, enable or disable some options on 
	the scene window.
	Now we have added to more enable/disable options: the AABB and OBB drawing that can help you when working with bounding boxes. 
	
	The scene options are:
	* The play button: this will save a temporary scene and start a timer for the game running.
	* Pause button: will pause the temporary scene and timer.
	* Stop button: this will reset the temporary scene to the initial scene and reset the game timing.
	* World/Local option: this feature will allow to make a toggle to move and edit the gameobjects among local or global coordinates.
	
	These new options have been added to the Overlevende Engine v0.7.

- Inspector window:
	This window shows you all the information to work with your gameobjects, by selecting your gameobject it will display its options like renaming the gameobject. 
	You can delete game objects from there too if necessary.

	Now with the new version of the engine you can modify the position, the rotation and the scale of every game object in the scene. You can drag every coordinate to
	change it or just introduce the desired value. For the camera's options note the you can change the priority, enable or disable de culling and edit some more options 
	for the Frustum Culling feature.

![Inspector](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/inspector.PNG?raw=true)

- Console:
	The console window shows errors, warnings and other messages generated by Overlevende. This will help you while working with the engine like showing some LOGs while 
	creating meshes.

# Additional features in Overlevende Engine:

* We have added some interface themes, that was when we discovered ImGui and although is not hard code we think its good for the user to have a variety of interfaces colors 
to adapt at their necessities and make a better experience. So you will be able to change the base colors of the engine in a dark, light and bright theme and a few colors for
the active window and buttons.

* The camera of the main scene is linked to the scene window, so you can work with the scene in any position you like more and that’s a helpful tool.

* The option window has different new functionalities: for the game objects you can change to depth sight, activate the cull face, see or unsee the textures, the wireframe 
or normals. For the entire scene you can enable or disable the light too.

![Options](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/options.PNG?raw=true)

* With the version 0.7 the cameras have been added and modified as a gameobjects. These have the priority feature that will allow the user to enable a priority organitzation 
within them for a better control of the Frustum Culling option. The scene will manage the priorities doing the FC of the camera with more priority allowing you to play with 
different cameras in the game easily.
