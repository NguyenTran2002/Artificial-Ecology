#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include <string>

using namespace std;

class Organism {

    private:

        // see README for meaning of each variable
        double evo_points; // starts at 0
        double health; // percentage value (0-100)
        double growth_rate; // percentage value (0-100)
        int age; // starts at 0
        double reproduce_points;

        emp::Ptr<emp::Random> random;

    public:

        // constructor
        Organism(emp::Ptr<emp::Random> _random, double _evo_points = 0.0,
            double _health = 100, double _growth_rate = 100, int _age = 0) :
            evo_points(_evo_points), random(_random), health(_health), growth_rate(_growth_rate), age(_age) {;
        }

        // identifier function
        virtual string get_type() {return "Organism";}

        // helper functions group to set private parameters
        void set_points(double _in) {evo_points = _in;}
        void add_points(double _in) {evo_points += _in;} // can use this to add negative points as well
        void set_health(double _in) {health = _in;}
        void set_growth_rate(double _in) {growth_rate = _in;}
        void set_age(int _in) {age = _in;}
        void set_reproduce_points (double _in) {reproduce_points = _in;}
        void increment_age() {age++;}

        // helper functions group to get private parameters
        double get_points() {return evo_points;}
        double get_health() {return health;}
        double get_growth_rate() {return growth_rate;}
        double get_age() {return age;}
        double get_reproduce_points() {return reproduce_points;}

        // public method to set hungriness
        virtual bool un_fed() {

            // return false if the organism health reaches 0 (needs to be kill off)
            health-=25;

            if (health <= 0) {
                return false;
            }

            else {return true;}

        }

        void fed() {
            
            // we don't reall care if health is max or not

            health += 25;

            // cannot have more than 100% health
            if (health > 100) {
                health = 100;
            }
        }

        virtual void Process(double base_earning_points) { // mental note to use a subclass function to call this function instead?
            // adding a base amount of points per turn for the organism
            // organism are expected to arquire points proactively in other ways

            evo_points = evo_points + base_earning_points;
        }

        virtual emp::Ptr<Organism> CheckReproduction() {
            /* 
            This function is just a template for subclassess' functions
            */

            // if organism has a given amount of points, they reproduce
            if (evo_points >= reproduce_points) {

                emp::Ptr<Organism> offspring = new Organism(*this);
        
                // *offspring.points = 0; // reset the offspring points to 0

                offspring->set_points(0);

                // parent organism loses points to reproduce
                evo_points = evo_points - reproduce_points;

                return offspring;

            }

            // return a null pointer if the organism doesn't reproduce
            return nullptr;

        }
    
        virtual void birth_deduction() {
            add_points(-reproduce_points); // if this raise an error, a subclass has not set its reproduce points
        }

        double max_to_take (double request) {
            /*
            DESCRIPTION
                Another organism will put in a request for an X amount of points that it wants to take
                This functions will return what are the max amount of points that can be taken
            */

            if (request <= evo_points) {
                return request;
            }

            return evo_points;

        }

};

#endif