#include <iostream>
#include <string>
#include <cstdio>
#include "tiny.h"

using namespace std;

// Definitions of static members
const char* ColorConsole::fg_blue = "\033[34m";
const char* ColorConsole::bg_white = "\033[47m";

// Implementation of ConsoleBox methods
void ConsoleBox::new_text() {
    // Implementation here
}

void ConsoleBox::set_text(const string &text) {
    cout << text << endl;
}

// Global instance of ConsoleBox
ConsoleBox *consoleBox = new ConsoleBox;

void load_script(const char* filename, bool show_script)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void cargarscrip()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}