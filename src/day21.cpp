#include "days.hpp"

#include "parsing.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

uint64_t solve_day21(input_t input_data) {
    std::cout << std::endl;
    input_data = {
        "mxmxvkd kfcds sqjhc nhms (contains dairy, fish)",
        "trh fvjkl sbzzf mxmxvkd (contains dairy)",
        "sqjhc fvjkl (contains soy)",
        "sqjhc mxmxvkd sbzzf (contains fish)",
    };
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

    for(auto allergens: all_allergens) {
        std::cout << allergens.first << ": ";
        for(auto pos_ing: allergens.second) {
            std::cout << pos_ing << " ";
        }
        std::cout << std::endl;
    }
    return result;
}
