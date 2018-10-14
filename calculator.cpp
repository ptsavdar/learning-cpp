/*
    Simple calculator
    Revision history:
    Revised by Bjarne Stroustrup November 2013
    Revised by Bjarne Stroustrup May 2007
    Revised by Bjarne Stroustrup August 2006
    Revised by Bjarne Stroustrup August 2004
    Originally written by Bjarne Stroustrup
    (bs@cs.tamu.edu) Spring 2004.
    This program implements a basic expression calculator.
    Input from cin; output to cout.
    The grammar for input is:
    Statement:
        Expression
        Print
        Quit
    Print:
        ;
    Quit:
        q
    Expression:
        Term
        Expression + Term
        Expression – Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        – Primary
        + Primary
    Number:
        floating-point-literal
    Input comes from cin through the Token_stream called ts.
*/


#include "../std_lib_facilities.h"
#include <cmath>
#include <utility>
#include <queue>

using namespace std;

const char number = '8';
const char name = 'a';
const char quit = 'q';
const char print = ';';
const char let = 'L';
const string prompt = ">";
const string result = "=";
const string declkey = "let";

class Token {
public:
    char kind;
    double value;
    string name;
    Token(): value{0}, name{""} {} // initializing empty
    Token(char ch): kind{ch}, value{0} {} // initializing with character
    Token(char ch, double val): kind{ch}, value{val} {} // initializing with character and value
    Token(char ch, string n): kind{ch}, name{move(n)}, value{0} {}
};

class Token_stream {
public:
    Token_stream(istream& inp): in{inp}{}
    Token get();
    void putback(Token t);
    void ignore(char c);

private:
    istream& in;
    queue<Token> buffer;
};

void Token_stream::putback(Token t)
{
    buffer.push(t);
}

Token Token_stream::get()
{
    if (!buffer.empty()) {
        Token t = buffer.front();
        buffer.pop();
        return t;
    }

    char ch;
    in.get(ch); // >> skips whitespace, tab, newline etc.
    while (isspace(ch) && ch != '\n')
        in.get(ch);
    switch (ch) {
        case '\n':
            return Token{print};
        case print:
        case quit:
        case '(':
        case ')':
        case '{':
        case '}':
        case '+':
        case '-':
        case '*':
        case '/':
        case '!':
        case '=':
            return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            in.putback(ch);
            double val;
            in >> val;
            return {number, val};
        }
        default:
            if (isalpha(ch)) {
                string s;
                s += ch;
                while(in.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch; // valid names containing only alphanumerics
                in.putback(ch);
                if (s == declkey) return Token(let); // check if declaration key
                return Token{name, s};
            }
            error("Bad token");
    }
}

void Token_stream::ignore(char c) {
    while (!buffer.empty() && c!=buffer.front().kind) {
        buffer.pop();
    }
    if (!buffer.empty()) {
        buffer.pop();
        return;
    }
    char ch = 0;
    while (in>>ch)
        if (ch==c) return;
}

class Variable {
public:
    string name;
    double value;
    Variable(string var, double val): name{move(var)}, value{val} {}
};

Token_stream ts(cin);

vector<Variable> var_table;

void calculate(const istream& in);

double statement();

double assignment();

double declaration();

double expression();

double term();

double primary();

void clean_up_mess();

int factorial(int value);

double get_value(const string& s);

void set_value(const string& s, double d);

bool is_declared(const string &var);

double define_name(const string &var, double val);

int maincalculator()
{
    cout << "Please enter expression (we can handle +, -, * and /)" << endl;
    cout << "add an x to end expression e.g., 1+2*3x: " << endl;
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);
    define_name("k", 1000);
    calculate(cin);

    keep_window_open();
    return 0;
}

void calculate(const istream& in)
{
    while(in)
    try {
        cout << prompt;
        Token t = ts.get();
        while(t.kind == print) t = ts.get();
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement() << endl;
    } catch(runtime_error& e) {
        cerr << e.what() << endl;
        clean_up_mess();
    }

}

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration();
        case name:
            ts.putback(t);
            return assignment();
        default:
            ts.putback(t);
            return expression();
    }
}

bool is_declared(const string &var) {
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

double define_name(const string &var, double val)
{
    if (is_declared(var)) error(var, "declared twice");
    var_table.push_back(Variable(var, val));
    return val;
}

double assignment()
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in assignment");
    string var_name = t.name;
    if (!is_declared(var_name)) error("not initialized variable ", var_name);
    Token t2 = ts.get();
    switch (t2.kind) {
        case '=': {
            double d = expression();
            set_value(var_name, d);
            return d;
        }
        default:
            ts.putback(t);
            ts.putback(t2);
            return expression();
    }
}

double declaration()
{
    Token t = ts.get();
    if(t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/': {
                double d = primary();
                if (d == 0) error("Divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%': {
                double d = primary();
                if (d == 0) error("Divide by zero");
                left = fmod(left, d);
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case '{': {
            double d = expression();
            t = ts.get();
            if (t.kind != '}') error("'}' expected");
            return d;
        }
        case number: {
            double val = t.value;
            t = ts.get();
            if (t.kind == '!') val = factorial(narrow_cast<int>(val));
            else ts.putback(t);
            return val;
        }
        case '-':
            return - primary();
        case '+':
            return primary();
        case name:
            return get_value(t.name);
        default:
            error("primary expected");

    }
}

void clean_up_mess() {
    ts.ignore(print);
}

int factorial(int v)
{
    int res = 1;
    while (v >= 1) {
        res *= v--;
    }

    return res;
}

double get_value(const string& s)
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined variable ", s);
}

void set_value(const string& s, double d)
{
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}