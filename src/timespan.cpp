#include "timespan.h"
#include <stdexcept>

using namespace std;

namespace jed_utils {
    timespan::timespan(int days, int hours, int minutes, int seconds) {
        // Check if the values submitted is valid
        if (hours < -23 || hours > 23) {
            throw std::invalid_argument("hours must be between 0 and 23");
        }
        if (minutes < -59 || minutes > 59) {
            throw std::invalid_argument("minutes must be between 0 and 59");
        }
        if (seconds < -59 || seconds > 59) {
            throw std::invalid_argument("seconds must be between 0 and 59");
        }
        this->days = days;
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;
    }

    int timespan::get_days() const {
        return days;
    }

    int timespan::get_hours() const {
        return hours;
    }

    int timespan::get_minutes() const {
        return minutes;
    }

    int timespan::get_seconds() const {
        return seconds;
    }

    int timespan::get_total_hours() const {
        return  (days * 24) + hours;
    }

    int timespan::get_total_minutes() const {
        return  (days * 60 * 24) + (hours * 60) + minutes;
    }

    int timespan::get_total_seconds() const {
        return  (days * 60 * 60 * 24) + (hours * 60 * 60) + (minutes * 60) + seconds;
    }

    bool operator<(const timespan &mts, const timespan &ots) {
        if (mts.days < ots.days) {
            return true;
        }
        if (mts.days > ots.days) {
            return false;
        }
        if (mts.hours < ots.hours) {
            return true;
        }
        if (mts.hours > ots.hours) {
            return false;
        }
        if (mts.minutes < ots.minutes) {
            return true;
        }
        if (mts.minutes > ots.minutes) {
            return false;
        }
        if (mts.seconds < ots.seconds) {
            return true;
        }

        return false;
    }

    bool operator>(const timespan &mts, const timespan &ots) {
        return ots < mts;
    }

    bool operator<=(const timespan &mts, const timespan &ots) {
        return !(mts > ots);
    }

    bool operator>=(const timespan &mts, const timespan &ots) {
        return !(mts < ots);
    }

    bool operator==(const timespan &mts, const timespan &ots) {
        return mts.days == ots.days &&
            mts.hours == ots.hours &&
            mts.minutes == ots.minutes &&
            mts.seconds == ots.seconds;
    }

    bool operator!=(const timespan &mts, const timespan &ots) {
        return !(mts == ots);
    }
}  // namespace jed_utils
