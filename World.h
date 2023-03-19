#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

#include "species_carnivores.h"
#include "species_herbivores.h"
#include "species_intelligent_omnivores.h"
#include "species_plants.h"

using namespace std;

emp::Random true_rand = emp::Random(-1);

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

    public:

        OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
            random_ptr.New(_random);
        }

        ~OrgWorld() {
    }

    void Update() {
    
        emp::World<Organism>::Update();

        // we dont need a random schedule here, but make it anyway for the sake of being able to copy paste code
        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
        
        // move the organism randomly, except plants
        for (int i : schedule) {
            if(!IsOccupied(i)) {continue;}
            move_organism_random(i); // this function handles plant exception already
        }

        // i. e. loop through every organism and give them resource for each update
        for (int i : schedule) {

            if(!IsOccupied(i)) {continue;} // if the square is NOT occupied, do NOT process it
            
            // variable pop stores the entire population (i. e. a bunch of organism)
            pop[i]->Process(50); // give each organism 50 points per update

        }

        // random schedule for food consumption
        emp::vector<size_t> schedule3 = emp::GetPermutation(random, GetSize());

        // let the organism consume stuffs
        for (int i : schedule3) {

            if(!IsOccupied(i)) {continue;}

            emp::Ptr<Organism> consumer = pop[i];
            string type = consumer->get_type();

            if (type == "Plant") {
                ; // do nothing if it's plant
            }

            else if (type == "Herbivore") {

                // all neighbors that MIGHT be eaten
                emp::vector<size_t> food_menu = GetValidNeighborOrgIDs(i);

                // max portion that this organism can take
                double max_portion = consumer.DynamicCast<Herbivore>()->get_portion();

                for (size_t dish : food_menu) {

                    string type = pop[dish]->get_type();

                    // can only consume plants
                    if (type == "Plant") {

                        // check the points of plant
                        double plant_points = pop[dish]->get_points();

                        // get the amount of points it can take out from the target organism
                        double portion_size = pop[dish]->max_to_take(max_portion);

                        // dig in
                        consumer->add_points(portion_size);
                        pop[dish]->add_points(-portion_size);

                        // record that it is fed
                        consumer->fed();

                        // set new health of plant
                        double original_heatlh = pop[dish]->get_health();
                        double deduct_health = portion_size / plant_points;
                        double final_health = original_heatlh - deduct_health;

                        pop[dish]->set_health(final_health);

                        // kill plant if health < 20
                        if (final_health < 20) {
                            ExtractOrganism(dish);
                        }

                    }

                    else {
                        
                        bool life = consumer->un_fed();

                        // cout << "NEXT IS KILL ORG" << endl;
                        
                        // kill org if health is 0
                        if (life == false) {
                            // RemoveOrgAt(i);
                            ExtractOrganism(i);
                            // cout << "ORG KILLED SUCCESSFULLY" << endl;
                        }

                    }

                }

            }

            else if (type == "Carnivore") {

                emp::vector<size_t> food_menu = GetValidNeighborOrgIDs(i);
                // max portion that this organism can take
                double max_portion = consumer.DynamicCast<Carnivore>()->get_portion();

                for (size_t dish : food_menu) {

                    string type = pop[dish]->get_type();

                    // can only consume herbivoress and IntelOmniovores
                    if (type == "Herbivore" || type == "IntelOmnivore") {

                        // get the amount of points it can take out from the target organism
                        double portion_size = pop[dish]->max_to_take(max_portion);

                        // dig in
                        consumer->add_points(portion_size);

                        // instant kill
                        pop[dish]->set_points(0);
                        ExtractOrganism(dish);

                        // record that the organism is fed
                        consumer->fed();

                    }

                    else {

                        bool life = consumer->un_fed();
                        
                        // kill org if health is 0
                        if (life == false) {
                            // RemoveOrgAt(i);
                            ExtractOrganism(i);
                        }
                    }

                }

            }

            else if (type == "IntelOmnivore") {

                emp::vector<size_t> food_menu = GetValidNeighborOrgIDs(i);
                // max portion that this organism can take
                double max_portion = consumer.DynamicCast<IntelOmnivore>()->get_portion();

                for (size_t dish : food_menu) {

                    string type = pop[dish]->get_type();

                    // can consume all
                    if (type == "Herbivore" || type == "Carnivore") {

                        // get the amount of points it can take out from the target organism
                        double portion_size = pop[dish]->max_to_take(max_portion);

                        // dig in
                        consumer->add_points(portion_size);

                        // instant kill
                        pop[dish]->set_points(0);
                        ExtractOrganism(pop[dish]);

                        // record fed
                        consumer->fed();

                    }

                    else if (type == "Plant") {

                        // check the points of plant
                        double plant_points = pop[dish]->get_points();

                        // get the amount of points it can take out from the target organism
                        double portion_size = pop[dish]->max_to_take(max_portion);

                        // dig in
                        consumer->add_points(portion_size);
                        pop[dish]->add_points(-portion_size);

                        // record that it is fed
                        consumer->fed();

                        // set new health of plant
                        double original_heatlh = pop[dish]->get_health();
                        double deduct_health = portion_size / plant_points;
                        double final_health = original_heatlh - deduct_health;

                        pop[dish]->set_health(final_health);

                        // kill plant if health < 20
                        if (final_health < 20) {
                            ExtractOrganism(dish);
                        }

                    }

                    else {

                        bool life = consumer->un_fed();
                        
                        // kill org if health is 0
                        if (life == false) {
                            // RemoveOrgAt(i);
                            ExtractOrganism(i);
                        }

                    }

                }

            }

        }

        // create a random schedule of which organism will be checked first for reproduction
        emp::vector<size_t> schedule2 = emp::GetPermutation(random, GetSize());

        for (int i : schedule2) {

            if(!IsOccupied(i)) {continue;} // if the square is NOT occupied, do NOT process it

            emp::Ptr<Organism> parent = pop[i];

            parent->increment_age(); // increment their age

            emp::Ptr<Organism> offspring;

            offspring = pop[i]->CheckReproduction();

            if(offspring) {
                // DoBirth(*offspring, i);  //i is the parent's position in the world
                // cout << "\n$$$$$ Reproduction Occurred $$$$$" << endl;
                // cout << "OFFSPRING TYPE: " << offspring->get_type() << endl;

                birth_custom(parent, offspring, i);
            }

        }

        // create a random schedule for plant to die due to not enough sun light
        emp::vector<size_t> schedule_plant = emp::GetPermutation(random, GetSize());

        for (int i : schedule_plant) {

            if(!IsOccupied(i)) {continue;} // if the square is NOT occupied, do NOT process it

            emp::Ptr<Organism> org = pop[i];

            if (org->get_type() == "Plant") {

                // find empty neighbors
                vector<emp::WorldPosition> neighbors = find_empty_neighbors(i);

                // if there is no neighbors, kill off the plant due to not enough sunlight
                if (neighbors.size() == 0) {
                    ExtractOrganism(i);
                }

            }

        }

    }

    void birth_custom (emp::Ptr<Organism> parent, emp::Ptr<Organism> offspring, emp::WorldPosition position) {
        /*
        DESCRIPTION:
            This is a custom version of the DoBirth function. The main difference being it takes in a pointer
            instead of an object.

        INPUT SIGNATURE:
            1. offspring: a pointer pointing to the organism that CAN birth

        CAUTION:
            Only run this function AFTER CheckReproduction() has determined that the organism can birth
        */
       
       // search for an empty position to birth
       vector<emp::WorldPosition> empty_positions = find_empty_neighbors(position); // not guarantee to find one even if one is there

        if (empty_positions.size() == 0) {
            return;
            cout << "FOUND NO EMPTY SPACE BUT BIRTHED ANYWAY" << endl; // just in case
        }

        emp::WorldPosition birth_location = random_position(empty_positions);

        // add the new organism to the world
        AddOrgAt(offspring, birth_location);

        // if birthed, subtract the evo_points of the parent
        parent->birth_deduction();

    }

    emp::Ptr<Organism> ExtractOrganism (int index) {
        emp::Ptr<Organism> subject = pop[index]; // extract the organism
        pop[index] = nullptr; // remove it from the world
        return subject; // return the organism for relocation
    }

    void move_organism_random (int index) {
        /*
        Move the organism to a random neighbor location, taking in their index in pop vector
        DO NOT MOVE THE ORGANISM IF IT IS A TREE
        */

        emp::Ptr<Organism> subject = GetOrgPtr(index);

        if (subject->get_type() != "Plant") {

            // search for some empty neighbors
            vector<emp::WorldPosition> empty_positions = find_empty_neighbors(index);

            if (empty_positions.size() != 0) {

                emp::WorldPosition destination = random_position(empty_positions);

                ExtractOrganism(index);
                
                AddOrgAt(subject, destination);

            }

        }

    }

    emp::WorldPosition my_get_neighbor(emp::WorldPosition position) {
        return GetRandomNeighborPos(position);
    }

    vector<emp::WorldPosition> find_empty_neighbors (emp::WorldPosition position) {
        /*
        DESCRIPTION
            Return a vector containing all possible empty neighbors
        
        CAUTION
            Not guaranteed to find all empty spaces
            After calling this function, the OUTER function needs to check if the vector returned is empty or not.
        */

        vector<emp::WorldPosition> neighbors;

        for (int i = 0; i < 10; i++) { // only random 10 times

            emp::WorldPosition current = GetRandomNeighborPos(position);

            if (!IsOccupied(current)) {
                neighbors.push_back(current);
            }

        }

        return neighbors;
       
    }

    emp::WorldPosition random_position (vector<emp::WorldPosition> list_of_positions) {
        /*
        DESCRIPTION
            Given a list of position, return one randomly

        CAUTION
            Need to make sure that the vector is NOT empty before calling this function
            I hate how everything needs to be type specific :v
        */

       int length = list_of_positions.size();

       int random_index = true_rand.GetUInt(0, length);

       return list_of_positions[random_index];

    }

};

#endif