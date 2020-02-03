
#include <string>
#include <iostream>
#include <fstream>

#include "App.hpp"

int main()
{
	try
	{
		App app("OpenGL", 800, 800);
		app.run();
	}
	catch(std::runtime_error& re)
	{
		std::cerr << "ERROR: " << re.what() << std::endl;
	}
}