#include "days.hpp"

#include <cassert>

uint64_t solve_day25() {
    const uint64_t card_pub = 11239946;
    const uint64_t door_pub = 10464955;

    auto retrieved_card_pub = 1;
    auto card_loop_count = 0;
    while(card_pub != retrieved_card_pub) {
        retrieved_card_pub *= 7;
        retrieved_card_pub %= 20201227;
        card_loop_count++;
    }

    auto retrieved_door_pub = 1;
    auto door_loop_count = 0;
    while(door_pub != retrieved_door_pub) {
        retrieved_door_pub *= 7;
        retrieved_door_pub %= 20201227;
        door_loop_count++;
    }

    EncryptionBreaker card(card_loop_count);
    EncryptionBreaker door(door_loop_count);
    auto card_encryption_key = card.compute_key(retrieved_door_pub);
    auto door_encryption_key = door.compute_key(retrieved_card_pub);
    assert(card_encryption_key == door_encryption_key);
    return card_encryption_key;
}
