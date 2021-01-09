#include "tinytime.hpp"

#include <bits/stdint-intn.h>
#include <sys/types.h>
// #include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>

int checkDays(int n, uint y) {
    return (((y - 1970) % 4 == 0) ? (n + 1) : n);
}

int64_t calculateTime(uint YYYY, uint MM, uint DD, uint hh, uint mm, uint ss, uint ms = 0) {
    int64_t res = 0;

    for (auto i = 1970U; i <= YYYY; i++)
        res += (i % 4 == 0) ?
            366UL * Times::day :
            365UL * Times::day;

    res += 335UL * Times::day;
    switch (MM) {
        case 11:
            res += 334UL * Times::day;
            break;
        case 10:
            res += 304UL * Times::day;
            break;
        case 9:
            res += 273UL * Times::day;
            break;
        case 8:
            res += 243UL * Times::day;
            break;
        case 7:
            res += 212UL * Times::day;
            break;
        case 6:
            res += 181UL * Times::day;
            break;
        case 5:
            res += 151UL * Times::day;
            break;
        case 4:
            res += 120UL * Times::day;
            break;
        case 3:
            res += 90UL * Times::day;
            break;
        case 2:
            res += 59UL * Times::day;
            break;
        case 1:
            res += ((YYYY % 4 == 0) ? 30UL : 31UL) * Times::day;
            break;
        default:
            break;
    }

    res += DD * Times::day;
    res += hh * hour;
    res += mm * minute;
    res += ss * second;
    res += ms;

    return res;
}

tinytime::tinytime(int64_t time) {
    int64_t copy = time;
    tinytime::years += static_cast<uint>(std::floor(copy / Times::day / 31 / 12)) + 1;

    for (auto i = 1970U; i < years; i++)
        tinytime::raw += Times::day * ((i % 4 == 0) ? 366 : 365);
    copy -= tinytime::raw;

    double diffDays = std::floor(static_cast<double>(copy) / Times::day);

    if (diffDays > checkDays(MonthsString::Nov, tinytime::years)) {
        tinytime::months = 11;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Nov, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Oct, tinytime::years)) {
        tinytime::months = 10;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Oct, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Sep, tinytime::years)) {
        tinytime::months = 9;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Sep, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Aug, tinytime::years)) {
        tinytime::months = 8;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Aug, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Jul, tinytime::years)) {
        tinytime::months = 7;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Jul, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Jun, tinytime::years)) {
        tinytime::months = 6;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Jun, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::May, tinytime::years)) {
        tinytime::months = 5;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::May, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Apr, tinytime::years)) {
        tinytime::months = 4;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Apr, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Mar, tinytime::years)) {
        tinytime::months = 3;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Mar, tinytime::years)));
    }
    else if (diffDays > checkDays(MonthsString::Feb, tinytime::years)) {
        tinytime::months = 2;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Feb, tinytime::years)));
    }
    else if (diffDays > MonthsString::Jan) {
        tinytime::months = 1;
        tinytime::days = static_cast<uint>(std::ceil(diffDays - checkDays(MonthsString::Jan, tinytime::years)));
    }
    else {
        tinytime::months = 0;
        tinytime::days = static_cast<uint>(diffDays);
    }

    copy -= static_cast<int64_t>(std::trunc(diffDays * Times::day));
    tinytime::raw += static_cast<int64_t>(std::trunc(diffDays * Times::day));
    if (raw < time)
        tinytime::days += 1;

    tinytime::hours = static_cast<uint>(copy / Times::hour);
    copy -= Times::hour * tinytime::hours;
    tinytime::raw += copy;

    tinytime::minutes = static_cast<uint>(copy / Times::minute);
    copy -= Times::minute * tinytime::minutes;
    tinytime::raw += copy;

    tinytime::seconds = static_cast<uint>(copy / Times::second);
    copy -= Times::second * tinytime::seconds;
    tinytime::raw += copy;

    tinytime::milliseconds = static_cast<uint>(copy);
    tinytime::raw = time;
}

tinytime::tinytime() {}

tinytime tinytime::start() {
    return tinytime{};
}

tinytime tinytime::now() {
    return tinytime{ std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) * 1000 };
}

int64_t tinytime::toInt64() {
    return tinytime::raw;
}

std::string tinytime::toString() {
    std::stringstream res{};

    if (tinytime::months + 1 < 10)
        res << '0' << tinytime::months + 1;
    else
        res << tinytime::months + 1;
    res << '/';

    if (tinytime::days < 10)
        res << '0' << tinytime::days;
    else
        res << tinytime::days;
    res << '/';

    res << tinytime::years << ' ';

    if (tinytime::hours < 10)
        res << '0' << tinytime::hours;
    else
        res << tinytime::hours;
    res << ':';

    if (tinytime::minutes < 10)
        res << '0' << tinytime::minutes;
    else
        res << tinytime::minutes;
    res << ':';

    if (tinytime::seconds < 10)
        res << '0' << tinytime::seconds;
    else
        res << tinytime::seconds;
    res << '.';

    if (tinytime::milliseconds < 10)
        res << "00" << tinytime::milliseconds;
    else if (tinytime::milliseconds < 100)
        res << '0' << tinytime::milliseconds;
    else
        res << tinytime::milliseconds;

    return res.str();
}

std::string tinytime::toJSONString() {
    std::stringstream res{};

    res << tinytime::years << '-';

    if (tinytime::months < 10)
        res << '0' << tinytime::months;
    else
        res << tinytime::months;
    res << '-';

    if (tinytime::days < 10)
        res << '0' << tinytime::days;
    else
        res << tinytime::days;
    res << 'T';

    if (tinytime::hours < 10)
        res << '0' << tinytime::hours;
    else
        res << tinytime::hours;
    res << ':';

    if (tinytime::minutes < 10)
        res << '0' << tinytime::minutes;
    else
        res << tinytime::minutes;
    res << ':';

    if (tinytime::seconds < 10)
        res << '0' << tinytime::seconds;
    else
        res << tinytime::seconds;
    res << '.';

    if (tinytime::milliseconds < 10)
        res << "00" << tinytime::milliseconds;
    else if (tinytime::milliseconds < 100)
        res << '0' << tinytime::milliseconds;
    else
        res << tinytime::milliseconds;
    res << 'Z';

    return res.str();
}

void tinytime::setYears(uint y) {
    tinytime::years = y;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

void tinytime::setMonths(uint m) {
    tinytime::months = m;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

void tinytime::setDays(uint d) {
    tinytime::days = d;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

void tinytime::setHours(uint h) {
    tinytime::hours = h;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

void tinytime::setMinutes(uint m) {
    tinytime::minutes = m;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

void tinytime::setSeconds(uint s) {
    tinytime::seconds = s;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

void tinytime::setMilliseconds(uint m) {
    tinytime::milliseconds = m;
    tinytime::raw
        = calculateTime(
            tinytime::years,
            tinytime::months,
            tinytime::days,
            tinytime::hours,
            tinytime::minutes,
            tinytime::seconds,
            tinytime::milliseconds
        );
}

uint tinytime::getYears() {
    return tinytime::years;
}

uint tinytime::getMonths() {
    return tinytime::months;
}

uint tinytime::getDays() {
    return tinytime::days;
}

uint tinytime::getHours() {
    return tinytime::hours;
}

uint tinytime::getMinutes() {
    return tinytime::minutes;
}

uint tinytime::getSeconds() {
    return tinytime::seconds;
}

uint tinytime::getMilliseconds() {
    return tinytime::milliseconds;
}
