# PathOfLegends
Simulator for the Path of Legends

## Guiding Questions: 

- If 1% of players reach Ultimate Champ every season, how many games are played?
- If we remove *all* golden steps, how many steps are needed to ensure 1% of players reaching UC after *x* games?

## Roadmap:
 
### Development
 
- Fix issue with players matching with different leagues
- Make better way of finding when there is a new UC to implement second version of simulation that goes until $x\%$ are in UC. 
- Change PlayMatch and winsMatch to take in a POINTER to the arrays with league reqs and gold step rules 
 	- Allows for multipliers that let players skip entire leagues with a single win (Do we really want this???)
- Output: Sim that takes in UC pct used to calculate how many battles needed. Sim that takes in number of battles lets us experiment on parameters for the sytem. 
- For data analysis, having option to print all players to tsv file may be very useful (Can change `<<` operator in player class from `" "` to `\tsv`). 

### Experiments
- Find out how many battles are played to get a 1% UC
- Experiment with shortening the path and cutting down golden stps
	- 5-10 trials of 3-4 settings sims, probably on 10% scale: 
	- Path Length: 60,  no gold steps in leagues
	- Path Length: 50, dropping leagues is allowed (Set max multiplier to 4 or 5.)
	-  Path length 30: No golden steps, (Multiplier 3-4)
- Useful Data Points: 
	- wins for UC players
	- W/L ratio (overall, cannot adhere to master 1+ counts rule with league dropping allowed)
	- count of UC players. 

### Data Analysis

- Avg and Stdev of percent UC players
- Avg/ Stdev of wins required to get to UC. 
- Avg/Stdev of UC win percent
- 3-4 plots?

## Contents of this Repo: 

`Player.*pp`: Interface and implementation for the player class.  Mostly just storing data about the player. 

- `id` : Unique identifier for the player 
- `party pct`: How much a player plays party and not PoL. Maybe not useful for a PoL simulation but I left it anyway. 
- `oldPB` Legacy PB. How I indicate who wins a match. KT and Card level are less relevant since PoL has level caps. 
- `league` is the league. Sole factor in matchmaing
- `step` which step of the path the player is on
- `multiplier` is the win multiplier
- `winsToGold` How many more wins are required to get the next gold step. 
- `currentGold` The current gold step that the player cannot fall below. I have a boolean in the simulation object that says if dropping leagues is allowed. 

`hashQueue.*pp`: Interface and implementation for Hashqueue class. The hash queue is a "hash table" but the hash function is the identity function. The table itself is an array that stores the indices of the players in the mm queue. Constant time to find an opponent.  *This is a significant speed up for a PoL simulatior over the regular ladder simulator which uses a random BST*.

Stores an array of players in queue, a vector of player objects. The interface is just `findOpponent()`, taking in an index in the player vector. If there is an opponent, it returns it. If not, it returns the number of players (a known number in the simulation) and adds the player to the queue. 

`simulation.*pp` Interface and Implementation of the simulation. Constructor reads in a file (this is bugged!) with the parameters for the simulation. The settings file _MUST_ contain 9 pairs of numbers: The minimum number of steps required to reach a league and the frequency of the golden step, separated by a whitespace. `10 3` on the second line means "The second league begins at step 10 and has a golden step every 3 wins". Zero in the steps column means that there are no golden steps.  The number at the bottom is the end of the last league, in the current season, this is 93 steps. The last number is 1 or 0, if dropping leagues is allowed (if the golden step at the begining of each league will be turned on). Last number is the maximum multiplier. Partiulaly useful with investigating shorter paths.  

Simlation will use randomness to pick a player, try to find an opponent and play a match or add the player to the queue. I am using the *index* of the array of players ot pick the player since its simpler and avoid unnecessary copy constructors. 

### Final notes

Right now there are a lot of print statements to try to debug the reading in bug. There are overloaded `<<` operators for player and hashqueue classes for debugging I am fairly confident in my logic for `winsMatch`. Determining who wins a match is definitely my biggest assumption. Unfortunately there is near zero api data about the path of legends so its really hard to figure out who wins. I've tried multiple linear regression and found nothing, best I can do is something with legacy PBs. 

The performance goal is 1 million battles per second played with 500k players (I think this is about 10% of what the actual CR playerbase is since it was ~7.4 million in January 2022, but has been shrinking). I may generate 5 million players and see what happens (Each player object takes 32 bytes of space, 160 MB is more than reasonable space wise)