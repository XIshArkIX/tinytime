#ifndef _H_TINYTIME
#define _H_TINYTIME

#include <bits/stdint-intn.h>
#include <sys/types.h>
// #include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>

enum Times {
	second = 1000UL,
	minute = second * 60UL,
	hour = minute * 60UL,
	day = hour * 24UL,
	week = day * 7UL,
	month = week * 4UL,
	year = month * 12UL
};

enum MonthsString {
	Jan = 31, // January
	Feb = Jan + 28, // February
	Mar = Feb + 31, // March
	Apr = Mar + 30, // April
	May = Apr + 31, // May
	Jun = May + 30, // June
	Jul = Jun + 31, // Jule
	Aug = Jul + 31, // August
	Sep = Aug + 30, // September
	Oct = Sep + 31, // October
	Nov = Oct + 30, // November
	Dec = Nov + 31 // December
};

class tinytime {
	private:
		uint years = 1970;
		uint months = 0;
		uint weeks = 0;
		uint days = 0;
		uint hours = 0;
		uint minutes = 0;
		uint seconds = 0;
		uint milliseconds = 0;
		int64_t raw = 0;

	public:
		/* constructors */
		tinytime(int64_t);
		tinytime();

		static tinytime start();
		static tinytime now();
		int64_t toInt64();
		std::string toString();
		std::string toJSONString();

		/* setters */
		void setYears(uint);
		void setMonths(uint);
		void setDays(uint);
		void setHours(uint);
		void setMinutes(uint);
		void setSeconds(uint);
		void setMilliseconds(uint);

		/* getters */
		uint getYears();
		uint getMonths();
		uint getDays();
		uint getHours();
		uint getMinutes();
		uint getSeconds();
		uint getMilliseconds();
};

#endif