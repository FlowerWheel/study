#include "Person.h"

#include <iostream>
#include <string>
using namespace std;

int main (int argc, char **argv)
{
	string		name("LiMing"), addr("hnust");
	Person		LiMing(1, name, addr, 20);
	Person		LM(1, "LM", "HNUST", 20);

	std::cout << LiMing.get_name() << " " << LiMing.get_addr() <<endl;
	std::cout << LM.get_name() << " " << LM.get_addr() <<endl;
	return 0;
}
