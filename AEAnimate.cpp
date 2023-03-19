#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "species_carnivores.h"
#include "species_herbivores.h"
#include "species_plants.h"
#include "species_intelligent_omnivores.h"

using namespace std;

emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    // arena width and height
    const int num_h_boxes = 100;
    const int num_w_boxes = 100;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};
    emp::Random random{5};
    OrgWorld world{random};

    emp::web::Canvas canvas{width, height, "canvas"};

    public:

    AEAnimator() {

        // cout << "\nCheck Point 0\n";

        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        // create a new organism and inject it into the world
        // Plant* new_org_plant = new Plant(&random);
        Herbivore* new_org_herbivore = new Herbivore(&random);
        Carnivore* new_org_carnivore = new Carnivore(&random);
        IntelOmnivore* new_org_IntelOmni = new IntelOmnivore(&random);

        // cout << "\nCheck Point 7\n";

        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        // world.AddOrgAt(new_org_plant, 4900);
        // world.AddOrgAt(new_org_herbivore, 5000);
        // world.AddOrgAt(new_org_carnivore, 5100);
        // world.AddOrgAt(new_org_IntelOmni, 5204);

        // add a some well distributed plants
        for (int i = 21; i < 10000; i += 63) {
            Plant* new_org_plant = new Plant(&random);
            world.AddOrgAt(new_org_plant, i);
        }

        // add some herbivores
        for (int i = 33; i < 10000; i += 100) {
            Herbivore* new_org = new Herbivore(&random);
            world.AddOrgAt(new_org, i);
        }

        // add some carnivores and herbivore next to them
        for (int i = 37; i < 10000; i += 500) {
            Carnivore* new_org = new Carnivore(&random);
            world.AddOrgAt(new_org, i);
            Herbivore* new_org_support = new Herbivore(&random);
            world.AddOrgAt(new_org_support, (i+1));
        }

        // add some IntelOmnivores in a cluster
        for (int i = 9980; i < 10000; i += 1) {
            IntelOmnivore* new_org = new IntelOmnivore(&random);
            world.AddOrgAt(new_org, i);
        }
        

        // resize the world for 100 organisms (10 by 10 grid)
        world.Resize(100, 100);

        // cout << "\nCheck Point 2\n";

    }

    void DoFrame() override {

        // cout << "\nCheck Point 3\n";

        canvas.Clear();

        world.Update();

        // cout << "\nCheck Point 4\n";

        int org_num = 0;

        for (int x = 0; x < num_w_boxes; x++){

            // cout << "x: " << x << endl;

            // cout << "\nCheck Point 5\n";

            for (int y = 0; y < num_h_boxes; y++) {

                // cout << "y: " << y << endl << endl;

                // cout << "\nCheck Point 6\n";

                if (world.IsOccupied(org_num)) {

                    string species = world.GetOrgPtr(org_num)->get_type();
                    // cout << species << endl;

                    // if it is carnivore, red
                    if (species == "Carnivore") {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorRGB(255, 42, 0, 1.0), "gray");
                    }

                    // if it is plant, green
                    else if (species == "Plant") {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorRGB(65, 204, 157, 1.0), "gray");
                    }

                    // if it is herbivore, blue
                    else if (species == "Herbivore") {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorRGB(0, 128, 255, 1.0), "gray");
                    }

                    // if it is IntelOmnivore, yellow
                    else if (species == "IntelOmnivore") {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorRGB(255, 213, 0, 1.0), "gray");
                    }

                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "gray");
                }
                org_num++;
            }
        }

    }

};

AEAnimator animator;

int main() {animator.Step();}