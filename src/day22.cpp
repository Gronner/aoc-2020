#include "days.hpp"

#include <iostream>

uint64_t pop_front(std::vector<uint64_t>& deck) {
    auto tmp = deck[0];
    deck.erase(deck.begin());
    return tmp;
}

using deck_t = std::vector<uint64_t>;

std::vector<deck_t> player1_deck_history;
std::vector<deck_t> player2_deck_history;

bool recursive_combat(deck_t player1_deck, deck_t player2_deck) {
    player1_deck_history.push_back(player1_deck);
    player2_deck_history.push_back(player2_deck);

    auto player1_card = pop_front(player1_deck);
    auto player2_card = pop_front(player2_deck);
    if(player1_card >= player1_deck.size() && player2_card >= player2_deck.size()) {
        auto winner = recursive_combat(player1_deck, player2_deck);
        if(winner) {
            player1_deck.push_back(player1_card);
            player1_deck.push_back(player2_card);
        } else {
            player2_deck.push_back(player1_card);
            player2_deck.push_back(player2_card);
        }
    } else {
        return player1_card > player2_card;
    }

    if(player1_deck_history.end() != std::find(player1_deck_history.begin(), player1_deck_history.end(), player1_deck)) {
        return true;
    }
    if(player1_deck_history.end() != std::find(player1_deck_history.begin(), player1_deck_history.end(), player1_deck)) {
        return true;
    }
    return false;
}

uint64_t solve_day22(input_t input_data) {
    input_data = {
        "Player 1:",
        "43",
        "19",
        "",
        "Player 2:",
        "2",
        "29",
        "14",
    };
    std::vector<uint64_t> player1_deck;
    std::vector<uint64_t> player2_deck;
    bool second_player = false;
    for(auto line: input_data) {
        if(line == "Player 1:" || line == "Player 2:") {
            continue;
        }
        if("" == line) {
            second_player = true;
            continue;
        }
        if(second_player) {
            player2_deck.push_back(std::stoll(line));
        } else {
            player1_deck.push_back(std::stoll(line));
        }
    }

    while(player1_deck.size() != 0 && player2_deck.size() != 0) {
        auto player1_card = pop_front(player1_deck);
        auto player2_card = pop_front(player2_deck);
        if(player1_card > player2_card) {
            player1_deck.push_back(player1_card);
            player1_deck.push_back(player2_card);
        } else {
            player2_deck.push_back(player2_card);
            player2_deck.push_back(player1_card);
        }
    }
        std::cout << player1_deck.size() << " " << player2_deck.size() << std::endl;
    auto winner_deck = player1_deck.size() !=0 ? player1_deck : player2_deck;

    auto enumerate = 1;
    auto sum = 0;
    for(auto card = winner_deck.rbegin(); card != winner_deck.rend(); card++) {
        sum += *card * enumerate;
        enumerate++;
    }
    return sum;
}
