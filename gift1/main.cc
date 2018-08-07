/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: gift1
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
    int num_persons;
    fin >> num_persons;

    map<string, int> name_pos_map;
    vector<string> name_list = vector<string>(num_persons);
    for (int i = 0; i < num_persons; i++) {
        string name;
        fin >> name;
        name_pos_map[name] = i;
        name_list[i] = name;
    }

    vector<int> money_list = vector<int>(num_persons);
    string giver_name, receiver_name;
    int money, num_receiver;
    for (int i = 0; i < num_persons; i++) {
        fin >> giver_name;
        fin >> money >> num_receiver;
        if (num_receiver == 0) {
            continue;
        }
        int given_money = money / num_receiver;
        int rest_money = money % num_receiver;
        money_list[name_pos_map[giver_name]] += (-money + rest_money);

        for (int j = 0; j < num_receiver; j++) {
            fin >> receiver_name;
            money_list[name_pos_map[receiver_name]] += given_money;
        }
    }

    for (int i = 0; i < num_persons; i++) {
        fout << name_list[i] << ' ' << money_list[i] << '\n';
    }

    return 0;
}