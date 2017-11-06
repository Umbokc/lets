//
//  u_time_measurement.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/u_time_measurement.hpp"


void TimeMeasurement::clear() {
    finished.clear();
    running.clear();
}

void TimeMeasurement::start(lets_str_t name) {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    running[name] = time;
}

void TimeMeasurement::pause(lets_str_t name) {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    if (running.find(name) != running.end()) {
        add_time(name, time - running[name]);
        running.erase(name);
    }
}

void TimeMeasurement::stop(lets_str_t name) {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    if (running.find(name) != running.end()) {
        add_time(name, time - running[name]);
    }
}

lets_map_t<lets_str_t, std::chrono::nanoseconds> TimeMeasurement::get_finished() {
    return finished;
}

lets_str_t TimeMeasurement::summary() {
    return summary("seconds", true);
}

lets_str_t TimeMeasurement::summary(lets_str_t unit_name, bool show_summary) {
    lets_str_t result;
    double summary_time = 0L;
    
    for (lets_map_t<lets_str_t, std::chrono::nanoseconds>::iterator it = finished.begin(); it != finished.end(); ++it) {
        double converted_time = convert(unit_name, it->second);
        summary_time += converted_time;
        
        result += (it->first + ": " + std::to_string(converted_time) + " " + unit_name + "\n");
    }
    
    if (show_summary) {
        result += ("Summary: " + std::to_string(summary_time) + " " + unit_name + "\n");
    }
    
    return result;
}

void TimeMeasurement::add_time(lets_str_t name, std::chrono::nanoseconds time) {
    std::chrono::nanoseconds already_elapsed = (finished.find(name) != finished.end()) ? finished[name] : std::chrono::nanoseconds(0);
    finished[name] = std::chrono::nanoseconds(already_elapsed.count() + time.count());
}

double TimeMeasurement::convert(lets_str_t unit_name, std::chrono::nanoseconds time) {
    
    double nano_sec = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
    
    if (unit_name == "ns") {
        return (double)nano_sec;
    }
    if (unit_name == "us") {
        return nano_sec / 1000.0;
    }
    if (unit_name == "s") {
        return nano_sec / 1000000000.0;
    }
    
    return nano_sec / 1000000.0;
}

