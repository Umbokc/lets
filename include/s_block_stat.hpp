//
//  block_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef block_stat_hpp
#define block_stat_hpp

#include <string>
#include <vector>
#include "main.h"
#include "statement.h"

class BlockStatement : virtual public Statement {
public:

	lets_vector_t<Statement*> statements;

	BlockStatement();

	void add(Statement*);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();
};


#endif /* block_stat_hpp */
