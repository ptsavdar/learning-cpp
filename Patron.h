//
// Created by panos on 24/06/18.
//

#ifndef CPP_BEGINNERS_PATRON_H
#define CPP_BEGINNERS_PATRON_H

#include "Book.h"

namespace Library {
    class Patron {
        class InvalidPatron: public LibraryExecption {
        public:
            InvalidPatron(): LibraryExecption((char*)"Invalid Patron data") {}
        };

    public:
        Patron(string username, string cardnumber);
        string username() const { return un; }
        string cardnumber() const { return cn; }
        double fee() const { return f; }
        void setFee(double fee) { f = fee;}
        bool owes() const { return f > 0; }

    private:
        string un;
        string cn;
        double f;
    };
}

#endif //CPP_BEGINNERS_PATRON_H
