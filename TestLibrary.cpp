//
// Created by panos on 24/06/18.
//

#include "Book.h"
using namespace Library;

int maintestlibrary() {
    Book book1("1234-2323-232-A", "Moby Dick", "Herman Melville", Genre::fiction, Date(1851, Month::oct, 18));
    Book book2("1234-2323-232-C", "Moby Dick 2", "Herman Melville", Genre::fiction, Date(1851, Month::oct, 18));
    book1.checkOut();
    try {
        book1.checkOut();
    } catch (const Book::BookNotAvailable& e)
    {
        cerr << e.what() << endl;
    }

    cout << (book1 == book2) << endl;
    cout << book1 << endl;
    //Book book2("1234-2323-232-A", "", "Herman Melville", Date(1851, Month::oct, 18));
    //Book book3("1234-2323-232-AB", "Moby Dick", "", Date(1851, Month::oct, 18));
    //Book book4("1234-2323-232-A", "Moby Dick", "Herman Melville", Date(1851, Month::oct, 18));
}