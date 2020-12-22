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
static uint64_t round = 1;
static uint64_t game = 1;

static bool recursive_combat(deck_t& player1_deck, deck_t& player2_deck);

static bool next_game(deck_t& winner_deck, deck_t& loser_deck, uint64_t winner_card, uint64_t loser_card, bool winner) {
    winner_deck.push_back(winner_card);
    winner_deck.push_back(loser_card);
    if(winner) {
        return recursive_combat(winner_deck, loser_deck);
    } else {
        return recursive_combat(loser_deck, winner_deck);
    }
}

static bool recursive_combat(deck_t& player1_deck, deck_t& player2_deck) {
    round++;
    if(player1_deck_history.end() != std::find(player1_deck_history.begin(), player1_deck_history.end(), player1_deck)) {
        if(player1_deck_history.end() != std::find(player1_deck_history.begin(), player1_deck_history.end(), player1_deck)) {
            return true;
        }
    }

    player1_deck_history.push_back(player1_deck);
    player2_deck_history.push_back(player2_deck);

    if(0 == player1_deck.size() || 0 == player2_deck.size()) {
        return 0 != player1_deck.size() ? true : false;
    }

    auto player1_card = pop_front(player1_deck);
    auto player2_card = pop_front(player2_deck);
    if(player1_card <= player1_deck.size() && player2_card <= player2_deck.size()) {
        game++;
        auto tmp_round = round;
        round = 1;
        auto prev_history_player1 = player1_deck_history;
        player1_deck_history.clear();
        auto prev_history_player2 = player2_deck_history;
        player2_deck_history.clear();

        deck_t tmp_player1_deck(player1_deck.begin(), player1_deck.begin() + player1_card);
        deck_t tmp_player2_deck(player2_deck.begin(), player2_deck.begin() + player2_card);
        auto winner = recursive_combat(tmp_player1_deck, tmp_player2_deck);

        player1_deck_history = prev_history_player1;
        player2_deck_history = prev_history_player2;
        round = tmp_round;
        game--;
        if(winner) {
            return next_game(player1_deck, player2_deck, player1_card, player2_card, winner);
        } else {
            return next_game(player2_deck, player1_deck, player2_card, player1_card, winner);
        }
    } else {
        auto winner = player1_card > player2_card;
        if(winner) {
            return next_game(player1_deck, player2_deck, player1_card, player2_card, winner);
        } else {
            return next_game(player2_deck, player1_deck, player2_card, player1_card, winner);
        }
    }

}

uint64_t solve_day22(input_t input_data) {
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

    auto winner = recursive_combat(player1_deck, player2_deck);
    auto winner_deck = winner ? player1_deck : player2_deck;

    auto enumerate = 1;
    auto sum = 0;
    for(auto card = winner_deck.rbegin(); card != winner_deck.rend(); card++) {
        sum += *card * enumerate;
        enumerate++;
    }
    return sum;
}
