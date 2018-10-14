//
// Created by panos on 23/06/18.
//

#ifndef CPP_BEGINNERS_BOOK_H
#define CPP_BEGINNERS_BOOK_H

#include "Chrono.h"
#include <utility>
#include <vector>
#include <exception>

using namespace Chrono;

namespace Library {

    class LibraryExecption: public exception {
    public:
        explicit LibraryExecption(char* message): msg{message}{};
        const char* what() const noexcept override { return msg; }
    private:
        char* msg;
    };

    enum class Genre {
        fiction, nonfiction, periodical, biography, children
    };

    class Book {
    public:
        class BookNotAvailable: public LibraryExecption{
        public:
            BookNotAvailable(): LibraryExecption((char*)"Book Not Available") {}
        };

        class InvalidBook: public LibraryExecption{
        public:
            InvalidBook(): LibraryExecption((char*)"Book is invalid") {}
        };

        Book(string isbn, string title, string author, Genre genre, const Date& copyright);
        string isbn() const { return i; }
        string title() const { return t; }
        string author() const { return a; }
        Genre genre() const { return g; }
        Date copyright() const { return c; }
        bool available() const { return av;}
        void checkOut();
        void checkIn();
    private:
        string i;
        string t;
        string a;
        Genre g;
        Date c;
        bool av;
    };

    bool operator==(const Book& a, const Book& b);
    bool operator!=(const Book& a, const Book& b);

    ostream& operator<<(ostream& os, const Book& b);
    ostream& operator<<(ostream& os, const Genre& g);

    bool is_valid_book(const string& isbn, const string& title, const string& author, const Genre& genre);
    bool is_valid_isbn(const string& isbn);
    string genreName(const Genre& g);
}

#endif //CPP_BEGINNERS_BOOK_H
