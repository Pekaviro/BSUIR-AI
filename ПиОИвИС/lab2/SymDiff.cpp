#include "SymDiff.h"

using namespace std;

void runTestcase(string filename, int& num_sets, vector<vector<string>>& sets) {
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Файл не открыт!\n";
    }
    else
    {
        char h;

        sets.resize(num_sets);
        for (int i = 0; i < num_sets; ++i)
        {
            char line[100];

            string element;
            int n = 0, t = 0;
            file >> h;

            file.getline(line, 100, '\n');

            for (t; line[t] != '\0'; t++);
            while (line[n] != '{')
                n++;
            n++;
            while (n < t) {
                switch (line[n]) {

                case '{':
                    while (line[n] != '}')
                        element += line[n++];
                    element += line[n];
                    if (!element.empty())
                    {
                        sets[i].push_back(element);
                        element.clear();
                    }
                    break;

                default:
                    while ((line[n] != ',') && (line[n] != '}') && (line[n] != '\0')) {
                        element += line[n];
                        n++;
                    }
                    if (!element.empty())
                    {
                        sets[i].push_back(element);
                        element.clear();
                    }
                    n++;
                    break;
                }
            }
        }
    }
    file.close();
}

void symDiff(vector<vector<string>>& sets, int cur, int& num_sets, vector<string>& symdiff) {
    for (int i = 0; i < sets[cur].size(); i++) {
        int k = 0;
        for (int n = 0; n < sets[cur + 1].size(); n++) {
            if (sets[cur][i] != sets[cur + 1][n])
                k++;
        }
        if (k == sets[cur + 1].size())
            symdiff.push_back(sets[cur][i]);
    }
    for (int i = 0; i < sets[cur + 1].size(); i++) {
        int k = 0;
        for (int n = 0; n < sets[cur].size(); n++) {
            if (sets[cur + 1][i] != sets[cur][n])
                k++;
        }
        if (k == sets[cur].size())
            symdiff.push_back(sets[cur + 1][i]);
    }
    if (cur != num_sets - 2) {
        sets.at(cur + 1) = symdiff;
        symdiff.clear();
        symDiff(sets, cur + 1, num_sets, symdiff);
    }
}