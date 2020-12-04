#include <day4/passport.hpp>

#include <iterator>
#include <functional>
#include <sstream>
#include <vector>

#include "helpers.hpp"
#include "parsing.hpp"

Passport::Passport(
        std::string birth_year,
        std::string issue_year,
        std::string expiration_year,
        std::string height,
        std::string hair_color,
        std::string eye_color,
        std::string passport_id,
        std::string country_id) : birth_year(birth_year), issue_year(issue_year),
            expiration_year(expiration_year), height(height), hair_color(hair_color),
            eye_color(eye_color), passport_id(passport_id), country_id(country_id) {}

bool Passport::is_valid() {
    if(0 == birth_year.size()) {
        return false;
    }
    if(0 == issue_year.size()) {
        return false;
    }
    if(0 == expiration_year.size()) {
        return false;
    }
    if(0 == height.size()) {
        return false;
    }
    if(0 == hair_color.size()) {
        return false;
    }
    if(0 == eye_color.size()) {
        return false;
    }
    if(0 == passport_id.size()) {
        return false;
    }
    return true;
}

Passport Passport::from_string(std::string passport_description)  {
    std::istringstream passport(passport_description);
    std::vector<std::string> passport_fields{
        std::istream_iterator<std::string>{passport},
        std::istream_iterator<std::string>{}};

    std::string birth_year;
    std::string issue_year;
    std::string expiration_year;
    std::string height;
    std::string hair_color;
    std::string eye_color;
    std::string passport_id;
    std::string country_id;

    for(auto passport_field: passport_fields) {
        auto key_value_pair = aoc::grab_information(passport_field, "(\\w{3}):(.*)");
        switch(const_hash<3>(key_value_pair[1].c_str())) {
            case const_hash<3>("byr"): birth_year = key_value_pair[2];
                        break;
            case const_hash<3>("iyr"): issue_year = key_value_pair[2];
                        break;
            case const_hash<3>("eyr"): expiration_year  = key_value_pair[2];
                        break;
            case const_hash<3>("hgt"): height = key_value_pair[2];
                        break;
            case const_hash<3>("hcl"): hair_color = key_value_pair[2];
                        break;
            case const_hash<3>("ecl"): eye_color = key_value_pair[2];
                        break;
            case const_hash<3>("pid"): passport_id = key_value_pair[2];
                        break;
            case const_hash<3>("cid"): country_id = key_value_pair[2];
                        break;
            default: break;
        }
    }

    Passport pp(birth_year, issue_year, expiration_year, height, hair_color,
                eye_color, passport_id, country_id);
    return pp;
}

std::ostream& operator<< (std::ostream& out, const Passport& passport) {
    out << "byr:" <<  passport.birth_year;
    out << " iyr:" << passport.issue_year;
    out << " eyr:" << passport.expiration_year;
    out << " hgt:" << passport.height;
    out << " hcl:" << passport.hair_color;
    out << " ecl:" << passport.eye_color;
    out << " pid:" << passport.passport_id;
    out << " cid:" << passport.country_id;
    return out;
}
