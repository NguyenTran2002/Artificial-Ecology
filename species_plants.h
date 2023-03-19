#ifndef SPECIES_PLANTS
#define SPECIES_PLANTS

#include <string>
#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Org.h"

using namespace std;

class Plant : public Organism {

    private:

        double species_reproduce_points = 2500;


    public:

        Plant (emp::Ptr<emp::Random> _random, double _evo_points = 0.0,
            double _health = 100, double _growth_rate = 100, int _age = 0) :
            Organism(_random, _evo_points, _health, _growth_rate, _age) {
                Organism::set_reproduce_points(species_reproduce_points);
        }

        // identifier function
        string get_type() {return "Plant";}

        void Process (double base_earning_points) {
            // get a species-specific amount of base points every turn

            // set plant-specific base points
            base_earning_points = 100;

            Organism::Process(base_earning_points);
        }

        emp::Ptr<Organism> CheckReproduction() {
            return plant_reproduction(species_reproduce_points);
        }

        emp::Ptr<Organism> plant_reproduction(double reproduce_points) {
            /* in subclasses, they will call this method and SET their specific requirement for reproduction,
            REGARDLESS of what is given as input for this function
            */

            // get evo_points
            double evo_points = Organism::get_points();

            // if organism has a given amount of points, they reproduce
            if (evo_points >= reproduce_points) {

                emp::Ptr<Organism> offspring = new Plant(*this);
        
                // *offspring.points = 0; // reset the offspring points to 0

                offspring->set_points(0);

                // parent organism loses points to reproduce IN A DIFFERENT FUNCTION
                // because there's no guarantee that an offspring will be born if no empty space can be found

                return offspring;

            }

            // return a null pointer if the organism doesn't reproduce
            return nullptr;

        }


};

#endif