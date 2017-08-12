#ifndef CHECK_ARGUMENTS_H
#define CHECK_ARGUMENTS_H

class ArgumentsCheck {
public:
	static void check(int expected, int got){
		if(got != expected)
			throw ParseException(func::string_format(
				"[%d %s expected, got %d]",  
				expected, ((expected == 1) ? "argument" : "arguments"), got
			));
	}

	static void check_at_least(int expected, int got){
		if(got < expected)
			throw ParseException(func::string_format(
				"[At least %d %s expected, got %d]",  
				expected, ((expected == 1) ? "argument" : "arguments"), got
			));
	}

	static void check_or_or(int expectedOne, int expectedTwo, int got){
		if(expectedOne != got && expectedTwo != got)
			throw ParseException(func::string_format(
				"[%d or %d arguments expected, got %d]",  
				expectedOne, expectedTwo, got
			));
	}

	static void check_range(int from, int to, int got){
		if(from > got || to > got)
			throw ParseException(func::string_format(
				"[From %d to %d arguments expected, got %d]",  
				from, to, got
			));
	}

};

#endif