//
//  statement.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__statement_h
#define ast__statement_h

#include <string>
#include "main.h"
#include "node.h"

class Statement : virtual public Node {
protected:
	size_t __statement__row = 1;
	size_t __statement__col = 1;
public:
	void set_position(size_t r, size_t c){
		__statement__row = r;
		__statement__col = c;
	}
	lets_str_t get_position(){ return to_str(__statement__row) + ":" + to_str(__statement__col); }
	const size_t get_position_row() const { return __statement__row;}
	const size_t get_position_col() const { return __statement__col;}

	virtual void execute() = 0;
	virtual lets_str_t to_s() = 0;
};


#endif /* statement_h */
