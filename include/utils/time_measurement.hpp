//
//  include/utils/time_measurement.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__utils__time_measurement_hpp
#define include__utils__time_measurement_hpp

#include <string>
#include <map>
#include <chrono>
#include "../main.h"

class TimeMeasurement {
private:
	lets_map_t<lets_str_t, std::chrono::steady_clock::time_point> running;
	lets_map_t<lets_str_t, std::chrono::nanoseconds> finished;
public:
	void clear();

	void start(lets_str_t name);

	void pause(lets_str_t name);

	void stop(lets_str_t name);

	lets_map_t<lets_str_t, std::chrono::nanoseconds> get_finished();

	lets_str_t summary();

	lets_str_t summary(lets_str_t unit_name, bool show_summary);
private:

	void add_time(lets_str_t, std::chrono::nanoseconds);

	double convert(lets_str_t, std::chrono::nanoseconds);
};

#endif /* include__utils__time_measurement_hpp */
