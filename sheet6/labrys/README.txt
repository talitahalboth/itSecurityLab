==============================================================================

                                  L A B R Y S

         A game to demonstrate reverse engineering and exploitation

         by Tilo Müller (tilo.mueller@cs.fau.de)    version 12/2015

==============================================================================
			

INTRODUCTION

	'Labrys' is a doubleheaded axe, 'Labyrinth' is Greek for the house of
	the double axe and originates from the confuse architecture of the palace
	of Knossos in Crete. The different levels of the game should be part of
	this labyrinth. Initially the player's aim was to find the double axe.
	But since it became boring to search for only one item, so the player has
	to search for five artifacts now:
	
		- Helmet
		- Shield
		- Sword
		- Bow
		- and last but not least.. the Double Axe
	
	The game ends when the player found all five items in the labyrinth. To
	support the players with some magic, there are five spells he can cast:
	
		- Eye: Wall hack
		- Eagle: Flying mode
		- Horse: Running fast
		- Wingfoot: Long/high jumps
		- Sun: Illumination of the artifacts
	
	Furthermore the player is supported by the following instruments:
	clock, compass and torch, as shown in the HUD.

==============================================================================

START THE GAME

        You'll need SDL, SDL_image, SDL_mixer and freeglut to start the game.
        If you are using Ubuntu, you can install all those packages by:

          sudo apt-get install libsdl-image1.2 libsdl-mixer1.2 freeglut3

	Additionally, you need a user license key. To get a key, write an email
	to tilo.mueller@cs.fau.de and pay EUR 13.37 -- or just crack the game.

        To start the game, simply run:

          ./labrys
                
==============================================================================

CONTROLS

	W		Step forward
	S		Step backward
	A		Step left
	D		Step right
	
	LEFT		Rotate left
	RIGHT		Rotate right
	UP		Rotate up
	DOWN		Rotate down
	
	T		Toggle torch (also by mouse)
	
	C		Crouch
	SPACE		Jump
	
	F1-F12		Magic spell (also by mouse)
	ESC		Main menu
	
Magic spells and the torch can also be activated by mouse (by clicking on their
item in HUD). Pressing ESC returns to main menu. This can also be used as pause
button. When in main menu, pressing ESC again will resume your game. Otherwise
you can restart the current level, start another level or quit the game.

==============================================================================

LEVEL EDITOR

You can build your own levels for labrys by editing the ./level5/labyrinth file
in a text editor. Additionally, you may want to change the surface pictures for
earth, floor, house, roof, sky, stairs and wall (png files).

	#	Comment
	%	Change to next floor 

	oO	Walls
	-| 	Walls
	[]	Walls
	nu	Walls
	=	Walls
	+	Stairs
	^	House

	H	Helmet
	W	Sword
	S	Shield
	A	Axe
	B	Bow

	b	barrel
	c	chest
	f	fountain
	m	mill
	p	pillar
	s	stone
	t	trough

	y	spell: eye
	e	spell: eagle
	h	spell: horse
	w	spell: wingfoot
	z	spell: sun

	gG	fog
	i	start height
	0123	day time
	~!?	no shadows
	$	torch


After editing, you can share your new levels with your friends -- just send
them your labyrinth text files. But take care, I have been told there is a
bug in the level parsing!

==============================================================================
