# Tetris

 Methodology
The approach to solving this problem was methodical and involved several steps:

1. Algorithm Development: Core algorithms were developed for tetromino rotation, line clearance, and collision detection. The rotation was particularly challenging, requiring matrix manipulation to transpose and reverse rows accurately. 

2.  Learning and Applying SFML : SFML was chosen for its comprehensive support for 2D graphics and event handling. Learning to use SFML for rendering shapes, handling user input, and managing game windows was an integral part of the project.

3.  Game Logic : The game logic, crucial in replicating the Tetris experience, was meticulously crafted to manage the different states and behaviors of the game, from piece spawning to line completion and score updating.

4.  Testing and Debugging : Iterative testing and debugging were employed to ensure the game runs smoothly, with particular attention to the correct implementation of game rules and graphical output.

 Implementation
The implementation was divided into several phases:

-  Design of Data Structures : The game utilized 2D arrays for representing the shapes of tetrominos and the game board. These structures were crucial for the manipulation and tracking of the game state.

-  Modular Class Design : The code was organized into classes - `Shape`, `Piece`, `Board`, and `Game`. This modular approach facilitated easier management and modification of different game components. 

-  Use of SFML : SFML was utilized for graphical rendering (drawing shapes and texts) and event handling (keyboard inputs). This choice was driven by SFML's efficiency in handling 2D graphics and its simplicity in event management.

-  Trade-offs and Decisions : The focus was placed on implementing robust and accurate game mechanics over advanced graphical features or sound integration. A key decision was to prioritize the clarity and simplicity of the user interface to ensure that the game was easily understandable and playable.

 Results
The completed project yielded a fully functional Tetris game with the following features:

-  Core Tetris Mechanics : Including piece movement, rotation, line clearing, and game-over conditions.
-  Scoring System : A scoring algorithm that awards points based on the number of lines cleared simultaneously.
-  Graphical User Interface : A simple, clean interface that displays the game board, falling pieces, and the current score.
-  Interactive Controls : Responsive keyboard controls for moving and rotating tetrominos.
