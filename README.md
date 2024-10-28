
# **Complex Ecology**  
Explore the intricate interactions within a dynamic, evolving ecosystem of plants, herbivores, carnivores, and intelligent omnivores.  

---

## **Technologies Used**  

![C++](https://img.shields.io/badge/Language-C++-blue)  
![Emscripten](https://img.shields.io/badge/Compiler-Emscripten-orange)  
![SDL](https://img.shields.io/badge/Graphics-SDL2-red)  
![Git](https://img.shields.io/badge/VersionControl-Git-lightgrey)

---

## **Species Overview**

In this digital ecosystem, four distinct species interact based on simple rules:

1. 🌿 **Plants** (Green)  
   Provide the essential foundation of the food web.
   
2. 🐦 **Herbivores** (Blue)  
   Feed on plants to survive and reproduce.
   
3. 🦊 **Carnivores** (Red)  
   Prey on herbivores and omnivores to sustain themselves.
   
4. 🧠 **Intelligent Omnivores** (Yellow)  
   The apex species, consuming all life forms to thrive.

---

## **How to Run the Project**

Follow these steps to set up and run the simulation:

1. **Clone the Repository** (if you haven’t already):
   ```bash
   git submodule update --init --recursive
   ```

2. **Install EMSDK (Emscripten SDK):**
   ```bash
   cd emsdk
   ./emsdk install 3.1.2
   ./emsdk activate 3.1.2
   source ./emsdk_env.sh
   ```

3. **Navigate back to the root folder:**
   ```bash
   cd ..
   ```

4. **Compile and Run the Simulation:**
   ```bash
   ./compile-run.sh
   ```

### **Troubleshooting Tips**

- If you encounter errors during the EMSDK installation (`./emsdk install 3.1.2`), add the following lines to `emsdk.py` (within the `emsdk` folder) just below the line `from __future__ import print_function`:
   ```python
   import ssl
   ssl._create_default_https_context = ssl._create_unverified_context
   ```

---

## **General Rules of the Ecosystem**

- An organism cannot reproduce unless it finds an **empty space** for its offspring.
- **Plants** are producers and cannot consume other organisms.
- **Herbivores** feed on plants.
- **Carnivores** prey on herbivores and omnivores.
- **Intelligent Omnivores** consume any species—including plants, herbivores, and carnivores.
- **Evolution Points** (EP) determine the actions each species can take. Except for plants, every species gains 50 EP per turn.

---

## 🌿 **Plants (Green)**

Plants serve as the primary producers in the ecosystem, offering food for herbivores.

**Key Statistics:**
- **Evolution Points (EP):** Determines available actions.
- **Health:** Determines survival.

**Characteristics:**
- **Reproduction:** 2,500 EP required.
- **Photosynthesis:** Gain 100 EP per turn.
- **Static:** Plants do not move.
- **Abundant:** Plants start out plentiful in the ecosystem.
- **Overcrowding Penalty:** Plants that lack access to sunlight (i.e., no neighboring empty space) die instantly.

---

## 🐦 **Herbivores (Blue)**

Herbivores depend on plants for survival and must manage their food intake wisely to thrive.

**Key Statistics:**
- **Evolution Points (EP):** Determines available actions.
- **Health:** Determines survival.

**Characteristics:**
- **Reproduction:** 1,500 EP required.
- **Feeding:** Can extract up to 25% of its EP from plants during consumption.
- **Hunger Penalty:** Loses 25 health points per turn without food.

---

## 🦊 **Carnivores (Red)**

Carnivores prey on herbivores and omnivores, thriving by efficiently eliminating weaker species.

**Key Statistics:**
- **Evolution Points (EP):** Determines available actions.
- **Health:** Determines survival.

**Characteristics:**
- **Reproduction:** 1,900 EP required.
- **Prey:** Can extract as many EP as it possesses from herbivores and omnivores.
- **Instant Kill:** A carnivore’s prey dies immediately, regardless of how much EP it takes.
- **Hunger Penalty:** Loses 2 health points per turn without food.

---

## 🧠 **Intelligent Omnivores (Yellow)**

The ultimate survivors, omnivores can consume all other species, adapting to any situation.

**Key Statistics:**
- **Evolution Points (EP):** Determines available actions.
- **Health:** Determines survival.

**Characteristics:**
- **Reproduction:** 6,400 EP required.
- **Feeding:** Can extract up to 50% of its EP from any other species.
- **Instant Kill:** Prey (herbivores or carnivores) dies immediately if attacked.
- **Hunger Penalty:** Loses 45 health points per turn without food.

---

## **Project Summary**

This simulation offers a glimpse into the dynamics of artificial life and digital evolution. Through carefully crafted rules and interactions, each species demonstrates survival strategies in response to environmental pressures. The balance of the ecosystem reflects real-world scenarios, where overpopulation, competition, and food scarcity can lead to collapse—or adaptation. 

Use this project to explore complex behaviors, observe emergent phenomena, and understand how simple rules can create intricate ecosystems.
