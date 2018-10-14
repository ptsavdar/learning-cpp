//
// Created by panos on 24/06/18.
//

#include "Patron.h"

namespace Library {
    Patron::Patron(string username, string cardnumber): un{username}, cn{cardnumber}, f{0}
    {
        if (username.empty() || cardnumber.empty()) throw InvalidPatron{};
    }
}