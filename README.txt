COMPLEX ECOLOGY
_____________________________

SPECIES

	1. Plants (green)
	2. Herbivores (blue)
	3. Carnivores (red)
	4. Intelligent Omnivores (yellow)
_____________________________

How to Run
	
	Do the following steps or run the commands in terminal
	
	1. `git submodule update --init --recursive`
	2. `cd emsdk`, `./emsdk install 3.1.2`, `./emsdk activate 3.1.2`, `source ./emsdk_env.sh`
	3. `cd ..`
	4. `./compile-run.sh`
	
	If encounter error at `./emsdk install 3.1.2`, try adding the following 2 lines into the file `emsdk.py` within the folder `emsdk`
	`
	import ssl
	ssl._create_default_https_context = ssl._create_unverified_context
	`
	right below the line `from __future__ import print_function`
_____________________________

GENERAL
	- An organism doesn't birth if it cannot find an empty space for its offspring.
	- Plants cannot consume another organism.
	- Herbivores consume plants.
	- Carnivores consume herbivores and Intelligent Omnivores.
	- Intelligent Omnivores consume all, including plants, herbivores, and carnivores.
	- Except for plants, every species gets a base amount of 50 evolution points per turn.
_____________________________

PLANTS (green)

	critical statistics
		
		1. evolution points (determines available actions)
		2. health (determines survival)

	characteristics

		- reproduce at 2,500 evolution points
		- take in the most base amount of evolution points per turn, from photosynthesis, 100
		- static (don't move)
		- starts out abundant
		- take a penalty when overcrowded (not enough sunlight); a plant dies instantly if it cannot find an empty neighbor
_____________________________

HERBIVORES

	critical statistics

		1. evolution points (determines available actions)
		2. health (determines survival)

	characteristics

		- reproduce at 1,500 evolution points
		- consume plants (take evolution points from plants)
		- can take from plants a maximum of 1/4 of the herbivore's evolution points when it decides to consume a plant
		- for each turn that a herbivore cannot find food, it loses 25 health points
_____________________________

CARNIVORES

	critical statistics

		1. evolution points (determines available actions)
		2. health (determines survival)

	characteristics

		- reproduce at 1,900 evolution points
		- a carnivore can take from a herbivore or an Intelligent Omnivore as many points as it possesses
		- instantly set target points to zero regardless (they might not finish the prey, but the prey is dead already)
		- for each turn that a carnivore cannot find food, it loses 2 health points
_____________________________

INTELLIGENT OMNIVORES

	critical statistics

		1. evolution points (determines available actions)
		2. health (determines survival)

	characteristics

		- reproduce at 6,400 evolution points
		- an Intelligent Omnivore can take from other species as much as 1/2 of the evolution points that it possesses
		- instant kill target if it is either herbivore or carnivore (same idea as the carnivore)
		- for each turn that an Intelligent Omnivore cannot find food, it loses 45 health points
_____________________________
