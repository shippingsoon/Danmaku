#include "../include/main.h"

namespace stg
{
	void errorLog(std::string message, std::string filename)
	{
		std::ofstream file;
		file.open (filename, std::fstream::app);
		file << message << "\n";
		file.close();
	}
}
/* Copyleft 2013, Anonymous */
