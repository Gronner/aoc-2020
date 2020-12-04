#pragma once

#include <string>

class Passport {
    public:
        static Passport from_string(std::string passport_description);
        friend std::ostream& operator<< (std::ostream& out, const Passport& passport);
        bool is_valid();
    private:
        std::string birth_year;
        std::string issue_year;
        std::string expiration_year;
        std::string height;
        std::string hair_color;
        std::string eye_color;
        std::string passport_id;
        std::string country_id;

        Passport() {}
        Passport(std::string birth_year,
            std::string issue_year,
            std::string expiration_year,
            std::string height,
            std::string hair_color,
            std::string eye_color,
            std::string passport_id,
            std::string country_id);
};
