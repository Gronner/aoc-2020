#include "days.hpp"

#include "parsing.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

uint64_t solve_day21(input_t input_data) {
    std::cout << std::endl;
    std::map<std::string, std::set<std::string>> all_allergens;
    std::vector<std::string> all_ingredients;
    for(auto line: input_data) {
        auto information = aoc::grab_information(line, "(.*) \\(contains (.*)\\)");
        auto ingredients_tmp = aoc::split_on_delimiter(information[1], " ");
        auto ingredients = std::set<std::string>(ingredients_tmp.begin(), ingredients_tmp.end());
        auto allergens = aoc::split_on_delimiter(information[2], ", ");
        all_ingredients.insert(all_ingredients.end(), ingredients.begin(), ingredients.end());
        for(auto& allergen: allergens) {
            if(!all_allergens.contains(allergen)) {
                all_allergens[allergen] = ingredients;
            } else {
                std::vector<std::string> allergens_intersection;
                std::set_intersection(all_allergens[allergen].begin(), all_allergens[allergen].end(),
                                      ingredients.begin(), ingredients.end(),
                                      std::back_inserter(allergens_intersection));
                all_allergens[allergen] = std::set<std::string>(allergens_intersection.begin(), allergens_intersection.end());
            }
        }
    }

    std::vector<std::string> all_allergenic_ingredients;
    for(auto allergens: all_allergens) {
        all_allergenic_ingredients.insert(all_allergenic_ingredients.end(), allergens.second.begin(), allergens.second.end());
    }
    auto result = 0;
    for(auto ingredient: all_ingredients) {
        if(all_allergenic_ingredients.end() == find(all_allergenic_ingredients.begin(), all_allergenic_ingredients.end(), ingredient)) {
            result++;
        }
    }

    bool all_solo = false;
    while(!all_solo) {
        for(auto c_allergen: all_allergens) {
            if(c_allergen.second.size() == 1) {
                for(auto& allergen: all_allergens) {
                    if(c_allergen.first == allergen.first) {
                        continue;
                    }
                    auto found = std::find(allergen.second.begin(), allergen.second.end(), *c_allergen.second.begin());
                    if(found != allergen.second.end()) {
                        allergen.second.erase(found);
                    }
                }
                all_solo = true;
            } else {
                all_solo = false;
            }
        }
    }

    std::cout << std::endl;
    for(auto c_allergen: all_allergens) {
        for(auto i: c_allergen.second) {
            std::cout << i << ",";
        }
    }
    std::cout << std::endl;

    return result;
}
