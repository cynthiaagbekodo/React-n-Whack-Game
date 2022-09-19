# React-n-Whack-Game

This project was completed as part of the _Embedded System Design_ course during my fourth year of university and had for goal to provide students the opportunity to apply theory acquired from lectures. This build was a mix of basic circuit connections and Arduino code to simulate two mini-games: a reaction timer and whack-a-mole. See the file _circuit_visual.jpg_ and _(circuit schematic)_ for details on the circuit.

The code begins by mapping LED pins to the Arduino port they are connected to in the circuit and initiating neccessary varibles for tracking time past. In the void setup() function, port associated to the LEDs are set as outputs and the IR remote's receiving statues is set to TRUE. The void loop() function is used a segway to run either the reactiontimer() function of the whackamole() function which launches each game respectfully. The following sections will briefly discuss the IR remote configuration and the functioning of both games.

### _IR Remote Configuration_
This project relied on an infrared remote to record player responce. As such, to make this tool functional, I first had to determine the signal immited by each button I intended to use such that they could be comfigured in the code accordingly and then used to compare the player's responce against the correct answer. The code for can be ssen in the file _find_IR_values.ino_; this portion was rather simple.

### _Reaction Timer_
On start up, this mode presents itself by printing "Reaction Timer" to the LCD prompt, then waits 2-4 seconds before turning on the first LED. 

### _Whack-a-Mole_

