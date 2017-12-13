#include "user_io.hpp"

unsigned get_x(){
	std::cout << "Enter x coord: ";
	std::string x_in;
	std::cin >> x_in;
	unsigned x=0;
	try{
		 x = stoi(x_in);
	}
	catch(std::invalid_argument& e){}
	catch(std::out_of_range& e){}
	catch(...){}
	return x;
}

unsigned get_y(){
	std::cout << "Enter y coord: ";
	std::string y_in;
	std::cin >> y_in;
	unsigned y=0;
	try{
		 y = stoi(y_in);
	}
	catch(std::invalid_argument& e){}
	catch(std::out_of_range& e){}
	catch(...){}
	return y;
}

Direction get_mov_dir(){
	std::cout<< "Enter move direction: ";
	std::string dir_in;
	std::cin >> dir_in;
	Direction dir;
	if(dir_in == "u") dir = u;
	else if(dir_in == "d") dir = d;
	else if(dir_in == "l") dir = l;
	else if(dir_in == "r") dir = r;
	else if(dir_in == "ul") dir = ul;
	else if(dir_in == "ur") dir = ur;
	else if(dir_in == "dl") dir = dl;
	else if(dir_in == "dr") dir = dr;
	else dir = no_dir;
	return dir;
}

Direction get_cap_dir(){
	std::cout<< "Enter capture direction: ";
	std::string dir_in;
	std::cin >> dir_in;
	Direction dir;
	if(dir_in == "u") dir = u;
	else if(dir_in == "d") dir = d;
	else if(dir_in == "l") dir = l;
	else if(dir_in == "r") dir = r;
	else if(dir_in == "ul") dir = ul;
	else if(dir_in == "ur") dir = ur;
	else if(dir_in == "dl") dir = dl;
	else if(dir_in == "dr") dir = dr;
	else dir = no_dir;
	return dir;
}
