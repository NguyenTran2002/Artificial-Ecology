#ifndef SPECIES_CARNIVORES_H
#define SPECIES_CARNIVORES_H

#include <string>
#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Org.h"

using namespace std;

class Carnivore : public Organism {

    private:
        double species_reproduce_points = 1900;


    public:

        Carnivore (emp::Ptr<emp::Random> _random, double _evo_points = 0.0,
            double _health = 100, double _growth_rate = 100, int _age = 0) :
            Organism(_random, _evo_points, _health, _growth_rate, _age) {
                Organism::set_reproduce_points(species_reproduce_points);
        }

        bool un_fed() {

            // return false if the organism health reaches 0 (needs to be kill off)

            //get the health
            double health = Organism::get_health();

            health -= 2;

            Organism::set_health(health);

            if (health <= 0) {
                return false;
            }

            else {return true;}

        }

        // identifier function
        string get_type() {return "Carnivore";}

        emp::Ptr<Organism> CheckReproduction() {
            return carnivore_reproduction(species_reproduce_points);
        }

        emp::Ptr<Organism> carnivore_reproduction(double reproduce_points) {
            /* in subclasses, they will call this method and SET their specific requirement for reproduction,
            REGARDLESS of what is given as input for this function
            */

            // get evo_points
            double evo_points = Organism::get_points();

            // if organism has a given amount of points, they reproduce
            if (evo_points >= reproduce_points) {

                emp::Ptr<Organism> offspring = new Carnivore(*this);
        
                // *offspring.points = 0; // reset the offspring points to 0

                offspring->set_points(0);

                // parent organism loses reproduce points to reproduce IN A DIFFERENT FUNCTION
                // because there's no guarantee that an offspring will be born if no empty space can be found

                return offspring;

            }

            // return a null pointer if the organism doesn't reproduce
            return nullptr;

        }

        double get_portion () {
            // return the maximum amount of points that this organism can take from another organism
            double evo_points = Organism::get_points();
            return evo_points;
        }


};

#endif