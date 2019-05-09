#include <vector>

#include "cache/associative_cache.hpp"
#include "cache/mock_direct_cache.hpp"
#include "example_module.h"
#include "system/System.h"

int main() {
	System system;
	
	//Initialize the system here by adding modules to the system object
	system.addModule(new ExampleModule("Alice"));
	system.addModule(new ExampleModule("Bob", 10));

	//Create a direct cache
	system.addModule(
		new AssociativeCache(system, "L1", "cpu", "L2", 2, 192000, 64, 2, 0, 0)
	);

	//Call run() to start the simulation
	system.run();
}
