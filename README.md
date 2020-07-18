# Snake Game in Console (C++)
----

I started trying to get familiarized with C++. By the time this project has been made I haven't gone in too far (not even covered classes or pointers). However, I did want to apply some of my knowledge of what I learned to making of a small project (mostly in order to work on my skills). One of the ideas were to make a simple game in a console using ASCII style art for graphics.

In short: the game has been made. It's a fully playable game with it's own Menu screen where you can chose how fast you want the game to be (using left and right arrow keys):

![alt text](https://github.com/Si-ja/Snake-CPP/blob/master/Visuals/StartScreen.png "Start Screen")

The game play is...well it exists and the game could be played almost properly:

![alt text](https://github.com/Si-ja/Snake-CPP/blob/master/Visuals/GamePlay.PNG "Game Play")

And there is an end Screen informing the player of what their score is for the game they played:

![alt text](https://github.com/Si-ja/Snake-CPP/blob/master/Visuals/GameOverScreen.png "Game Play")

## Current issues that might need addressing:

1. For some reason the "Fruit" sometimes just does not appear in the game environment. For that so far an ability to press the 'z' button has been added, so it would be respawned into a new location.
2. The second piece of the tail that the snake spawns always appears on the right side of the Head of the snake and just stays there. It in terms messes up the graphics of the right wall. No issues with other pieces of the tail have ever been noticed.

## Features to add (TODO):
1. So far there is no way to get a game over by hitting your own tail, but only the walls. Collision with self parts is still in need of being added.
2. The game over screen does not lead anywhere. With the current build it was not possible to easily restart the game for the player. Maybe in the future the code can be refactored for this.

## Final Verdict:
This was a quite enjoable and interesting project to work on. The issues that have been noticed are a good ground for the future to improve upon. As the first game project writtein in the console - I'm quite happy with it.
