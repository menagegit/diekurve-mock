README

DieKurve_Mock is a reproduction of http://curvefever.com/ coded in C++, using Qt. I am currently working on a network stack on top of udp, in order to add networking to the game.

Program organizations:

The root class is game_status_t which schedules the messages to the view, game_view_t, and point_joueur_t. It implements the time of the game:
	on each clock tick (given by a qt timer):
		for each player p:
			p.move
		view.update

The state of the game is represented by the list of point_joueur_t, one for each player and the game_area_t, representing the board. The player state changes on each move and send signals to other part of the system using the observer/observable pattern. The player relly on and update the game_area which store the path of each player, and calculate collision (using functions from geometry).

The game_view_t class handle the view. It receives signals from the player (player moved). It keep the changes to print and print them when receiving a request to update the view from the game_status_t.

The keyboard class is a helper class caching the state of the pressed key on the keyboard. It is used by the point_joueur_t for calculating it's moves.

