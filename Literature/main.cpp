#include <bits/stdc++.h>

void FormatString (std::string& word);
void Print (const std::string& name, std::vector <std::string>& text);

int main ()
{
    std::ifstream in ("Evgeny Onegin.txt");

    std::vector <std::string> text;

    for (std::string word; std::getline (in, word, '\n');)
    {
        FormatString (word);

        if (word == " " || word == "\n")
            continue;

        if (!word.empty ())
            text.push_back (word);
    }

    std::sort (text.begin (), text.end ());

    Print ("output1.txt", text);

    for (int i = 0; i < text.size (); i++)
        std::reverse (text[i].begin (), text[i].end ());

    std::sort (text.begin (), text.end ());

    for (int i = 0; i < text.size (); i++)
        std::reverse (text[i].begin (), text[i].end ());

    Print ("output2.txt", text);

    return 0;
}

void FormatString (std::string& word)
{
    const std::string signs ("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789.,!?'\"(){}-_+=:[];");

    std::string result;

    for (int i = 0; i < word.size (); i++)
    {
        bool flag = false;

        for (int j = 0; j < signs.size (); j++)
        {
            if (word[i] == signs[j])
            {
                flag = true;

                break;
            }
        }

        if (!flag)
            result.push_back (word[i]);
    }

    word = result;
}

void Print (const std::string& name, std::vector <std::string>& text)
{
    std::ofstream out (name);

    for (int i = 0; i < text.size (); i++)
        out << text[i] << '\n';
}
