#include "Application.hpp"
#include <iostream>

int main() 
{
	try {			
		Application app;
		app.run();
	}
	catch(std::exception& e) {
		std::cerr << "\nException: " << e.what() << "\n";
	}
	
	return 0;
}
