//
//  main.cpp
//  lets
//
//  Created by Dragan Stepan on 29.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/lets.hpp"

int main(int argc, const char * argv[]) {

	try{
		Lets::init(argc, argv);
	} catch (std::exception& e){
		show_error("Error", e.what())
	}

	return 0;
}