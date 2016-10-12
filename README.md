# Midterm Project: GuildWars #
## Guild Info ##
Name: ***Undercity Community College***  
Member Information:

Name          | Hero Name            | Email
--------------|----------------------|--------------------------
Kento Okamoto | Eric Cartman         | kokamoto@mymail.mines.edu
Jacob Wilson  | Shuhei Son of Atlas  | jacwilso@mymail.mines.edu
Zheming Deng  | Nima                 | zdeng@mymail.mines.edu

## Description ##
The project runs a program in which three heroes (created by each member of the guild) are placed in a world with hills, valleys, trees and huts. Two of the heros (the board and the donkey) are fixed to a track that is made up of bezier curves that are c1 continuous.   
The third character (Eric Cartman) is free to move around the world as he pleases. Eric Cartman has a number of options, He can walk up a hill while being perfectly normal to the surface no matter what angle the hill is at, and sing while he's moving around.  
The world is made up of N number of bezier surfaces which is read in from a file(See file format for more information) and M number of bezier curves. The objects are placed based on where the file tells it to be placed. Most of the objects are drawn using 3D Drawing and animation

## How to Run ##
Depending on what system you are running the program. Enter one of the following:
### Windows ###
`gmake`

`.\GuildWars.exe <CSVFile>`
### macOS/Linux ###
`make`
`./GuildWars <CSVFile>`

where \<CSVFile\> is replaced with some CSV file of a particular format (See file format for more details. It is important to note that the CSV file must be in the same directory as the executable. 

## Controls ##
### Mouse Movement ###
The mouse is mostly used to adjust the view the window. Here are he basic controls:
 * Left-Click + Drag: If the user has set the particular window to arcball mode, then They can adjust the arcball view by clicking and dragging on the screen. If the mini view ports are present, they can also click and drag within those viewports as well.
 * Right-Click: This Brings up a variety of options to choose from. They go as follows:
	* Turn SplitScreen ON/OFF: Depending on if the split screen at the bottom is present, it will toggle between options displaying/hiding the split screen respectively.
  * Free Cam: This toggles the main window to be in freecam mode.
  * Turn FPS ON/OFF: This toggles the Frames Per Second indicator at the bottom left of the screen.
  * Eric Cartman/Board/Donkey: All three of these options have the following options which toggle the view of the hero on the main screen.
   * ArcBall: Sets the main window's viewmode to arcball for the selected hero.
   * 1st Person: Sets the main window's view mode to 1st person POV for the selected hero.
   * SkyCam: Sets the main window's view mode to a top/down view for the selected hero.
  * Quit: Exits the program.

The following options only appear when the split screen view is turned on
  * Main Screen/Screen 2/Screen 3: All three of these options have the following options which change the view for a given screen.
   * Eric: ArcBall: Sets the screen to arcball mode with the focus on Eric Cartman.
   * Eric: 1st Person: Sets the screen to 1st person POV with the focus on Eric Cartman.
   * Eric: Sky Cam: Sets the screen to top/down view with the focus on Eric Cartman.
   * Board: ArcBall: Sets the screen to arcball mode with the focus on the board.
   * Board: 1st Person: Sets the screen to 1st person POV with the focus on the board.
   * Board: Sky Cam: Sets the screen to top/down view with the focus on the board.
   * Donkey: ArcBall: Sets the screen to arcball mode with the focus on the donkey.
   * Donkey: 1st Person: Sets the screen to 1st person POV with the focus on the donkey.
   * Donkey: Sky Cam: Sets the screen to top/down view with the focus on the donkey.

### Keyboard Controls ###
 * w or W: Moves Eric Cartman Forward
 * s or S: Moves Eric Cartman Backward
 * a or A: Turns Eric Cartman Left
 * d or D: Turns Eric Cartman Right
 * In Free Cam mode:
 * i or I: Moves Free Cam Forward
 * k or K: Moves Free Cam Backward
 * j or J: Shifts Free Cam view left
 * l or L: Shifts Free Cam view right
 * q or Q or ESC: Quits the program
 * 0: Toggles main view to free cam mode.
 * 1: Toggles main view to 3rd Person on selected hero.
 * 2: Toggles main view to 1st person on selected hero.
 * 3: Toggles main view to reverse 3rd person on selected hero.
 * 4: Toggles main view to sky cam view for selected hero.
 * 5: Toggles main view to arcball view for selected hero.

## Bug Report ##
No Know at this time

## File Format ##
The file format is set in the following way
```
< N Number of Bezier Surfaces for the Ground >
 p1x, p1y, p1z
 p2x, p2y, p2z
 ...
 p(N*16)x, p(N*16)y, p(N*16)

 < M Number of Control Points for Bezier Curve>
 <1 control points x>,<1 control point y>, <1 control point z>
 ...
 <(M*4) control points x > ,<(M*4) control points y > ,<(M*4) control points z > 

 <number of Objects >
 <object type>, <object position x>, <object position y>, <object position z>, <object orientation x>, <object orientation y> ,<object orientation z>, <object size>
```
it is important to note the following:
For Bezier surface, there must be N\*16 points in total otherwise the program will close.  
For Bezier curves, there must be exactly N\*4 points in total otherwise the program will close.  
For Object types, use the following numbers to clasify a type:  
 * 0: Draw a tree
 * 1: Draw a hut
 * default: draw a tree
The position of the object can be in decimal form
The orientation of the object is read in degrees rather than radians. 
To keep it easy to read, break up the bezier surface/curves into block of 4 points for readability. The program will automatically skip empty lines without causing issues.

The input files for compiling are:
 * track1.csv
 * track2.csv
Each file contains the same 4 bezier surfaces and the bezier curve which comprises the track because they were hand crafted and really emphasize our programs abilities. However, each file differs in the number of objects and location, rotation, and size of those objects. 

## Contributions ##
Name          | Contribution %       
--------------|----------------------
Kento Okamoto | CONTRIBUTION PERC         
Jacob Wilson  | CONTRIBUTION PERC  
Zheming Deng  | CONTRIBUTION PERC    


## Other Things ##
* Time spent on Assignment: Too long .............................
* Help from lab: \<INSERT RATING HERE \>
* Funness of lab: \<INSERT FUNNESS LEVEL HERE\> I'm aware funness is not a word
