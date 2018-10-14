//
// Created by panos on 08/07/18.
//

#include "../std_lib_facilities.h"

class PunctDictionaryStream {
public:
    explicit PunctDictionaryStream(istream& is): source{is}, sensitive{true}, is_container_opened{false} {}
    void whitespace(const string& s) {white = s;}
    void set_container(const char& ch) {container = ch;}
    void add_white(char c) {white += c;}
    bool is_whitespace(char c);
    bool is_container(char c){return c==container;}
    void case_sensitive(bool b) {sensitive = b;}
    bool is_case_sensitive() {return sensitive;}
    PunctDictionaryStream& operator>>(string& s);
    operator bool();

private:
    istream& source;
    istringstream buffer;
    string white;
    bool sensitive;
    char container;
    bool is_container_opened;
};

PunctDictionaryStream::operator bool() {
    return !(source.bad() || source.fail()) && source.good();
}

PunctDictionaryStream& PunctDictionaryStream::operator>>(string &s) {
    while(!(buffer>>s)) {
        if (buffer.bad() || !source.good()) return *this;
        buffer.clear();

        string word;
        source>>word;
        if (word.length() == 0)
            continue;
        if (word[0] == '"')
            is_container_opened = !is_container_opened;
        if(!is_container_opened)
        {
            for(int i = 0; i < word.length(); i+=word.length() - 1)
                if (is_whitespace(word[i]))
                    word[i] = ' ';
            for (char& c: word)
                c = static_cast<char>(tolower(c));

            if (word[word.length() - 2] == '\'' && word[word.length() - 1] == 't') {
                if (word == "shan't")
                    word = "shall not";
                else if (word == "won't")
                    word = "will not";
                else if (word == "can't")
                    word = "cannot";
                else {
                    word.insert(word.length() - 3, 1, ' ');
                    word[word.length() - 2] = 'o';
                }
            }
        }
        if (word[word.length() - 1] == '"')
            is_container_opened = !is_container_opened;

        buffer.str(word);
    }
    return *this;
}

bool PunctDictionaryStream::is_whitespace(char c) {
    for (char w: white)
        if (c==w) return true;
    return false;
}


int mainpunddict()
{
    PunctDictionaryStream pds{cin};
    pds.whitespace(".;,?-'");
    pds.set_container('"');
    pds.case_sensitive(true);

    cout<<"please enter words\n";
    for (string word; pds>>word;)
        cout<<word<<endl;
    return 0;
}