//
//  include/statements/multi_assignment_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 15.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_multi_assignment_stat_hpp
#define include__s_multi_assignment_stat_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"
#include "../accessible.h"

class MultiAssignmentStatement : virtual public Statement{
public:
	lets_vector_t<Accessible*> targets;
	Expression *expression;

	MultiAssignmentStatement(lets_vector_t<Accessible*>, Expression*);
  void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();
	~MultiAssignmentStatement();
};

#endif /* include__s_multi_assignment_stat_hpp */

