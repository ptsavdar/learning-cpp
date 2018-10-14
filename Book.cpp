//
// Created by panos on 23/06/18.
//

#include "Book.h"

namespace Library {
    Book::Book(string isbn, string title, string author, Genre genre, const Date& copyright) :
            i{isbn}, t{title}, a{author}, c{copyright}, g{genre}, av{true}
    {
        if (!is_valid_book(isbn, title, author, genre)) throw InvalidBook{};
    }

    void Book::checkIn()
    {
        if (!av) av = true;
    }

    void Book::checkOut()
    {
        if (av) av = false;
        else throw BookNotAvailable{};
    }

    bool operator==(const Book& a, const Book& b)
    {
        return a.isbn() == b.isbn();
    }

    bool operator!=(const Book& a, const Book& b)
    {
        return ! (a == b);
    }

    ostream& operator<<(ostream& os, const Book& b)
    {
        return os <<
                  "Title: " << b.title() << "\n" <<
                  "Author: " << b.author() << "\n" <<
                  "ISBN: " << b.isbn() << "\n" <<
                  "Genre: " << b.genre() << endl;
    }

    ostream& operator<<(ostream& os, const Genre& g)
    {
        return os << genreName(g) << endl;
    }

    bool is_valid_book(const string& isbn, const string& title, const string& author, const Genre& genre)
    {
        if (
                isbn.empty() ||
                title.empty() ||
                author.empty() ||
                static_cast<int>(genre) < 0
                || 4 < static_cast<int>(genre)
         ) return false;

        return is_valid_isbn(isbn);
    }

    bool is_valid_isbn(const string& isbn)
    {
        if (isbn.empty()) return false;
        unsigned int idx{0};
        bool lastChar{false};
        for (char c : isbn) {
            if (c == '-') {
                idx++;
                if (idx > 3) return false;
            } else {
                if ((idx < 3 && !isdigit(c)) || (idx == 3 && !isalnum(c)) || (idx == 3 && lastChar)) return false;
                if (idx == 3) lastChar = true;
            }
        }

        return idx == 3 && lastChar;
    }

    string genreName(const Genre& g)
    {
        switch (g) {
            case Genre::fiction:
                return "Fiction";
            case Genre::nonfiction:
                return "Non-Fiction";
            case Genre::periodical:
                return "Periodical";
            case Genre::biography:
                return "Biography";
            case Genre::children:
                return "Children";
        }
    }
}

