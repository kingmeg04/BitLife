//
// Created by kingm on 10/01/2025.
//

#include "NamingStuff.h"

using namespace std;

string generateName() {
    genName:
    string name ="";
    char chosenLetter;

    array<char, 26> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    set<char> vouls = {'a','e','i','o','u'};
    set<char> followConsonant = {'r','l','s','z','k'};
    set<char> leadConsonant = {'b','c','f','g','j','k','l','m','n','r','s','v','w','z'};

    auto temp = [alphabet](string &name) -> string {name += toupper(alphabet[round(random(0,25))]); return name; };

    name = temp(name);

    for (int namePos = 1; namePos <= round(random(3,12)); namePos++ ) {
        chosenLetter = alphabet[round(random(0,25))];
        if (namePos >= 1 && name[namePos - 1] == chosenLetter && name.back() != 'b' && name.back() != 'd' && name.back() != 'f' && name.back() != 'g' && name.back() != 'l' && name.back() != 'm' && name.back() != 'n' && name.back() != 'o' && name.back() != 'p' && name.back() != 'r' && name.back() != 's' && name.back() != 't') {
            namePos--;
            continue;
        }
        else if (namePos >= 2 && name[namePos - 2] == chosenLetter) {
            namePos--;
            continue;
        }
        if (namePos >= 2 && vouls.count(name[namePos - 2]) && vouls.count(name[namePos - 1]) && vouls.count(chosenLetter)) {
            namePos--;
            continue;
        }
        if (namePos >= 3 && !vouls.count(name[namePos - 3]) && !vouls.count(name[namePos - 2]) && !vouls.count(name[namePos - 1]) && !vouls.count(chosenLetter)) {
            namePos--;
            continue;
        }
        if (namePos >= 1 && !vouls.count(name[namePos - 1]) && !leadConsonant.count(name[namePos - 1]) && !vouls.count(chosenLetter)) {
            namePos--;
            continue;
        }
        if (namePos >= 2 && !vouls.count(name[namePos - 2]) && followConsonant.count(name[namePos - 1]) && !vouls.count(chosenLetter)) {
            namePos--;
            continue;
        }
        name += chosenLetter;
    }
    checkForConsonantEnd:
    if (!vouls.count(name[name.size() - 1]) && !vouls.count(name[name.size() - 2])) {
        name.pop_back();
        goto checkForConsonantEnd;
    }
    if (name.size() < 4) {
        goto genName;
    }
    return name;
}
