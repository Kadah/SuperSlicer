#include <catch.hpp>
#include "test_data.hpp" // get access to init_print, etc

using namespace Slic3r::Test;
using namespace Slic3r;

SCENARIO("Original Slic3r Skirt/Brim tests", "[!mayfail]") {
    GIVEN("Configuration with a skirt height of 2") {
        auto config {Config::new_from_defaults()};
        config->set("skirts", 1);
        config->set("skirt_height", 2);
        config->set("perimeters", 0);
        config->set("support_material_speed", 99);

        // avoid altering speeds unexpectedly
        config->set("cooling", 0);
        config->set("first_layer_speed", "100%");

        WHEN("multiple objects are printed") {
            THEN("skirt_height is honored") {
                REQUIRE(false);
            }
        }
    }
    GIVEN("A default configuration") {
        auto config {Config::new_from_defaults()};
        config->set("support_material_speed", 99);

        // avoid altering speeds unexpectedly
        config->set("cooling", 0);
        config->set("first_layer_speed", "100%");
        // remove noise from top/solid layers
        config->set("top_solid_layers", 0);
        config->set("bottom_solid_layers", 0);

        WHEN("Brim width is set to 5") {
            config->set("perimeters", 0);
            config->set("skirts", 0);
            config->set("brim_width", 5);
            THEN("Brim is generated") {
                REQUIRE(false);
            }
        }

        WHEN("Skirt area is smaller than the brim") {
            config->set("skirts", 1);
            config->set("brim_width", 10);
            THEN("GCode generates successfully.") {
                REQUIRE(false);
            }
        }

        WHEN("Skirt height is 0 and skirts > 0") {
            config->set("skirts", 2);
            config->set("skirt_height", 0);

            THEN("GCode generates successfully.") {
                REQUIRE(false);
            }
        }

        WHEN("Perimeter extruder = 2 and support extruders = 3") {
            THEN("Brim is printed with the extruder used for the perimeters of first object") {
                REQUIRE(false);
            }
        }
        WHEN("Perimeter extruder = 2, support extruders = 3, raft is enabled") {
            THEN("brim is printed with same extruder as skirt") {
                REQUIRE(false);
            }
        }

        WHEN("Object is plated with overhang support and a brim") {
            config->set("layer_height", 0.4);
            config->set("first_layer_height", 0.4);
            config->set("skirts", 1);
            config->set("skirt_distance", 0);
            config->set("support_material_speed", 99);
            config->set("perimeter_extruder", 1);
            config->set("support_material_extruder", 2);
            config->set("cooling", 0);                     // to prevent speeds to be altered
            config->set("first_layer_speed", "100%");      // to prevent speeds to be altered

            auto print {Slic3r::Test::init_print(TestMesh::overhang, config)};
            print.process();
            
            config->set("support_material", true);      // to prevent speeds to be altered
            
            THEN("skirt length is large enough to contain object with support") {
                REQUIRE(false);
            }
        }
        WHEN("Large minimum skirt length is used.") {
            config->set("min_skirt_length", 20);
            auto print {Slic3r::Test::init_print(std::make_tuple<int,int,int>(20,20,20), config)};
            THEN("Gcode generation doesn't crash") {
                Slic3r::Test::gcode(gcode, print);
                auto exported {gcode.str()};
                REQUIRE(exported.size() > 0);
            }
    }
}
