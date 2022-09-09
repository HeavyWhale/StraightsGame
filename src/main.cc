#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include "controller.h"
#include "textView.h"

using namespace std;


void readCmd(std::istream* in, Controller& ctr) {
    bool isEnd = false;
    string option;
    string s;

    for (int i = 0; i < ctr.MAX_PLAYER; i++) {
        do {
            cout << "Is Player" << std::to_string(i+1) 
                 << " a human (h) or a computer (c)?\n>";
            std::getline(*in, option);
        } while (!ctr.addPlayer(option));
    }

    while (true) {
        while (!ctr.gameIsOver() && (cout << ">") && std::getline(*in, s)) {
            istringstream iss{s};
            string par;
            while( iss >> par ) {
                if (par == "play") {
                    iss >> option;
                    ctr.play(option);
                } else if (par == "discard") {
                    iss >> option;
                    ctr.discard(option);
                } else if (par == "deck") {
                    ctr.deck();
                } else if (par == "quit") {
                    ctr.quit();
                    break;
                } else if (par == "ragequit") {
                    ctr.ragequit();
                } else {
                    cerr << "Invalid command." << endl;
                }
            }
        }

        if (!ctr.gameIsOver()) {
            in = &cin;
        } else {
            break;
        }
    }
}

int main ( int argc, char **argv ) {
    istream *in = nullptr;
    unsigned seed;
    seed = std::stoi(argv[1]);

    if (seed == 0) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    if (argc >= 3) {
        string fname = std::string(argv[2]);
        in = new ifstream{ fname };
        if ( in->fail() ) {
            std::cerr << "Unable to open file " << fname << std::endl;
            delete in;
            in = nullptr;
            return 1;
        }
    } else {
        in = &cin;
    }

    Controller ctr {seed};

    readCmd(in, ctr);

    if (in != &cin) delete in;
}

/*
int main ( int argc, char **argv ) {
    istream *in = nullptr;
    unsigned seed;

    string fname;

    if (argc > 1) {
		seed = std::stoi(argv[1]);
        if (argc >= 3) {
            fname = std::string(argv[2]);
            in = new ifstream{ fname };
            if ( in->fail() ) {
                std::cerr << "Unable to open file " << fname << std::endl;
                delete in;
                in = nullptr;
                return 1;
            }
        } else {
            in = &cin;
        }
	} else {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    Controller ctr {seed};
    string cmd;
    string option;

    for (int i = 0; i < ctr.MAX_PLAYER; i++) {
        do {
            cout << "Is Player" << std::to_string(i+1) 
                 << " a human (h) or a computer (c)?\n>";
            cin >> option;
        } while (!ctr.addPlayer(option));
    }

    cout << ">";
    while (!ctr.gameIsOver() && in >> cmd) {
        if (cmd == "play") {
            in >> option;
            ctr.play(option);
        } else if (cmd == "discard") {
            in >> option;
            ctr.discard(option);
        } else if (cmd == "deck") {
            ctr.deck();
        } else if (cmd == "quit") {
            break;
        } else if (cmd == "ragequit") {
            ctr.ragequit();
        } else {
            cerr << "Invalid command." << endl;
        }
        cout << ">";
    }
}
*/
