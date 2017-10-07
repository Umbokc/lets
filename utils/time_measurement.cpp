#ifndef UTIL_TIME_MEASUREMENT_CPP
#define UTIL_TIME_MEASUREMENT_CPP

#include <map>
#include <string>
#include <chrono>

class TimeMeasurement {
private:
	std::map<std::string, std::chrono::steady_clock::time_point> running;
	std::map<std::string, std::chrono::nanoseconds> finished;

public:
	TimeMeasurement(){}
	TimeMeasurement(const TimeMeasurement& s){}

	void clear(){
		finished.clear();
		running.clear();
	}
	
	void start(std::string name){
		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
		running[name] = time;
	}

	void pause(std::string name){
		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
		if(running.find(name) != running.end()){
			add_time(name, time - running[name]);
			running.erase(name);
		}
	}
	
	void stop(std::string name){
		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
		if(running.find(name) != running.end()){
			add_time(name, time - running[name]);
		}
	}

	std::map<std::string, std::chrono::nanoseconds> get_finished(){
		return finished;
	}

	std::string summary(){
		return summary("seconds", true);
	}

	std::string summary(std::string unit_name, bool show_summary){
		std::string result;
		long summary_time = 0L;

		for (std::map<std::string, std::chrono::nanoseconds>::iterator it = finished.begin(); it != finished.end(); ++it) {
			long converted_time =	convert(unit_name, it->second);
			summary_time += converted_time;

			result += (it->first + ": " + std::to_string(converted_time) + " " + unit_name + "\n");
		}

		if(show_summary){
			result += ("Summary: " + std::to_string(summary_time) + " " + unit_name + "\n");
		}

		return result;
	}

	TimeMeasurement& operator=(const TimeMeasurement& s){ return *this; }
	~TimeMeasurement(){}
private:
	void add_time(std::string name, std::chrono::nanoseconds time){
		std::chrono::nanoseconds already_elapsed = (finished.find(name) != finished.end()) ? finished[name] : std::chrono::nanoseconds(0);
		finished[name] = std::chrono::nanoseconds(already_elapsed.count() + time.count());
	}

	long convert(std::string unit_name, std::chrono::nanoseconds time){
		
		if(unit_name == "nanoseconds"){
			return std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
		}
		if(unit_name == "microseconds"){
			return std::chrono::duration_cast<std::chrono::microseconds>(time).count();
		}
		if(unit_name == "seconds"){
			return std::chrono::duration_cast<std::chrono::seconds>(time).count();
		}

		return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
	}
};

#endif