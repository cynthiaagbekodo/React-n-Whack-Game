# React-n-Whack Game

This project was completed as part of the _Embedded System Design_ course during my fourth year of university and had for goal to provide students the opportunity to apply theory acquired from lectures. This build was a mix of basic circuit connections and Arduino code to simulate two mini-games: a reaction timer and whack-a-mole. See the file _circuit_visual.jpg_ and _(circuit schematic TBA)_ for details on the circuit.

The code begins by mapping LED pins to the Arduino port they are connected to in the circuit and initiating necessary variables for tracking time past. In the _void setup()_ function, port associated to the LEDs are set as outputs and the IR remote's receiving statues is set to TRUE. The _void loop()_ function is used a segway to run either the _reactiontimer()_ function of the _whackamole()_ function which launches each game respectfully. The following sections will briefly discuss the IR remote configuration and the functioning of both games.

### _IR Remote Configuration_
This project relied on an infrared remote to record player response. As such, to make this tool functional, I first had to determine the signal emitted by each button I intended to use such that they could be configured in the code accordingly and then used to compare the player's response against the correct answer. The code for can be seen in the file _find_IR_values.ino_; this portion was rather simple.

### _Reaction Timer_
Visual: https://1drv.ms/v/s!Ake-3pFxkd39gZgg_K6KJhO-1xgJLg?e=OVzSmY /n
On start up, this mode presents itself by printing "Reaction Timer" to the LCD prompt, then waits 2-4 seconds before turning on the LED and simultaneously taking note of the current time. The player then has 10 seconds to react by pressing the '0' button on the remote. If the player succeeds, the point in time at which the button is pressed with be noted and the difference between the two variables will be printed to the LCD prompt; this was the player's reaction time. If the player takes too long or presses the incorrect button, the prompt will display "Time Out!" or "Wrong Button!", respectfully. In all cases, the player is given a few seconds to view this feedback before the game begins again.
Please reference file _react_n_whack.ino_ for more details.

### _Whack-a-Mole_
Visual: https://1drv.ms/v/s!Ake-3pFxkd39gZghasRtrVeI1k7ChA?e=ZtNovy /n
This mode begins by prompting the player to get ready; the score is set to zero at the start of every game. There are four LEDs each associated with a specific button on the IR remote. While playing, a random LED will turn on and the player has 2 seconds to 'whack the mole' and turn off the LED by clicking the corresponding button. If successful, the score will be incremented and this process loops infinitely. When the player makes a mistake or times out, the loop is broken, and the player will be informed by the appropriate message on the LCD. Within a few seconds, their score will be displayed followed by a prompt that the game will restart.
Please reference file _react_n_whack.ino_ for more details.

