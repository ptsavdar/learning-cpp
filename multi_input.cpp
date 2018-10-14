//
// Created by panos on 07/07/18.
//

#include "../std_lib_facilities.h"

void buildUpperFile(const string& filename)
{
    ofstream os {filename};

    if (!os) error("Cannot open/create file " + filename + " for writing");

    os << "This Is A Camel Case File Having All First Letters Capitalized \n"
          << "Every Line Every Word \n"
          << "Every Line Every Word \n"
             << "All of them\n"
             << "All of them\n";
}

void exportUpperToLower(const string& fromFileName, const string& toFileName)
{
    ifstream is {fromFileName};
    if (!is) error("Cannot open " + fromFileName + " file for reading");
    ofstream os {toFileName};
    if (!os) error("Cannot open/create " + toFileName + " file for writing");
    char ch;
    while (is.get(ch))
    {
        if (isalpha(ch))
            ch = static_cast<char>(tolower(ch));
        os<<ch;
    }
}

bool isVowel(char& ch)
{
    string vowels = "AEIOU";
    return vowels.find_first_of(static_cast<char>(toupper(ch))) != string::npos;
}

void removeVowels(const string& fromFileName, const string& toFileName)
{
    ifstream is {fromFileName};
    if (!is) error("Cannot open " + fromFileName + " file for reading");
    ofstream os {toFileName};
    if (!os) error("Cannot open/create " + toFileName + " file for writing");
    char ch;
    while (is.get(ch))
    {
        if (isVowel(ch))
            continue;
        os<<ch;
    }
}

void findWordOccurencies(const string& fileName, const string& word)
{
    ifstream is {fileName};
    if (!is) error("Cannot open " + fileName + " file for reading");
    string line;
    unsigned int idx = 1;
    while (getline(is, line))
    {
        unsigned long found = line.find(word);
        if (found != string::npos) {
            cout<<"Word '"<<word<<"' found in line "<<idx<<" in position "<<found + 1<<": "<<line<<endl;
        }
        idx++;
    }
}

void readMultiInput()
{
    vector<string> inNums;
    vector<string> outNums;
    vector<string> types;
    long maxInLen = 0;
    long maxOutLen = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        cout << "Enter decimal, octal or hexadecimal number: \n";
        stringstream buffer;
        string num;
        cin>>num;
        buffer.str(num);
        if (num.length() > 0)
        {
            int inum;
            string type = "decimal\t\t";
            if (num.size() > 2 && num[0] == '0' && num[1] == 'x') {
                type = "hexadecimal\t";
                buffer>>hex>>inum;
            }
            else if (num[0] == '0' && num.size() > 1) {
                type = "octal\t\t";
                buffer>>oct>>inum;
            }
            else
                buffer>>inum;
            if (num.length() > maxInLen)
                maxInLen = num.length();
            if (to_string(inum).length() > maxOutLen)
                maxOutLen = to_string(inum).length();
            inNums.push_back(num);
            outNums.push_back(to_string(inum));
            types.push_back(type);
        }
    }

    for (int i = 0; i < inNums.size(); i++)
    {
        cout<<setw(maxInLen)<<inNums[i]<<" "<<types[i]<<" converts to "<<setw(maxOutLen)<<outNums[i]<<" decimal\n";
    }
}

int mainmultiinput()
{
    buildUpperFile("upperChars.txt");
    exportUpperToLower("upperChars.txt", "lowerChars.txt");
    removeVowels("upperChars.txt", "noVowels.txt");
    findWordOccurencies("upperChars.txt", "All");
    readMultiInput();
    return 0;
}