Welcome in the Gl Map Editor by Adrien Lenglet and Corentin Renard

ARGS : The program can be launch with and without arguments
The three arguments are : 
        -size -> This one will define the size of the map (default value : 32.0);
        -iter -> This one will define the generator iterrations (default value : 8);
        -Strengh -> This one will define the reliefs of the map [0.1 -> INF]. For an optimal experience choose between 0.1 and 0.75.(default value : 0.28);

Without arguments the programm will be set with default values;

Here is a short description of the six tools we gave you :
                    ->MOVE<-
With the Move tool you'll be able to select one or few vertices
and move them following the XYZ axes.
                    ->PAINT<-
With the paint tool you'll be able to paint any triangle in the world
with the Binded texture.
                   ->TEXTURE<-
With the texture tools you'll be able to select the texture you want to
apply. All the textures are located in "./res/textures/". You are free
to add any texture in the folder, the programm will take it in parametter.
                ->Lightmap Computer<-
With this tool you will acces the "lightmap compute" menu where you'll be able
to generate lightmap with a ray's density from 10 to 100000. CARE big density
can take a long time depending on your config.
                    ->FPS MODE<-
No more Edition Now YOU are the hero !! Move with ZQSD and jump with Space.
Care to not fall it's deep here.
                    ->Perspective<-
This tool change the perspective of the world


Here are some usefull binding : 
In menu : arrow_up and arrow_down to select menu and enter to comfirm
In edition mode : ZQSD to move the caméra
                  Hold shift allow you to select few points
                  With 3 points selected :
                        F allow you to flip the triangle selected
                        T allow you to create a triangle with the 3 selected vertex.
                        R will switch the uv of the triangle
                        U will switch the texture aplly point.
                  E active the extruder mode with allow you to dig or extrude large amount of points in the world
In both mode : hold right click to rotate the caméra
In both mode : P to activate/desactivate UI
But most important Have fun !!
