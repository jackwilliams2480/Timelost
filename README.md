# Timelost
Taking inspiration from Betrayal at House on the Hill, this game focuses on the the idea of getting a new experience every time you play the game. The game includes randomized, secret scenarios provide surprising story lines and different rules for different items each game.

The game is written in C and usilizses the terminal as a means to play the game. Due to limitations, the game is singleplayer exploration. 

### Introduction

Using the C programming language, I implemented a variation of the game Betrayal at House on the Hill using some of the lore within the Destiny universe.
The game follows a researcher as he explores his own facility in search for answers about the complexities of his research subject. His goal is to delve
into the mind of the Vex and prevent the simulation paradox from altering, and eventually compromising the research on the Vex.

### Implementation
I created and dynamically allocated memory for the following structures: Room, useItems, Player, and Keyword using malloc, and made sure to free them after using  each within the respective \*.c file. I made sure to implement each of the required structures, along with some of my own that helped me with the overall gameloop. 

For the main game mechanic, entering commands, I created a parse_command() method in order to accept commands on one line of code, and also prevents you from  accidentally entering a wrong command. In the parse_command() method, I can handel the "inventory", "take", "look", "go", "drop", "exit", and a secret command called "hezen_corrective". This was passed as a required list of keywords, and then using that list I check the passed in command if its valid, then proceed accordingly. In this method I also make sure to move the player accordingly, even in terms of the event room and also have a case for when you run out of rooms. I have implemented 2 omens, more than two items which you need for one of the possible win conditions, and also 2 event rooms. My player has an inventory and can drop and take items. The main idea comes from the mechanics of the original game. 

Link to video [demo](https:https://youtu.be/dO2io4h03Bg)
