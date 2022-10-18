#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include <list>

using namespace std;

vector<vector<int>> drogi;
unordered_set<int> zabronione_wart;
vector<int> powerbanki;
list<int> miejsca_ladowania;
vector<int> trasa, poprzednie_skrzyzowania;

int pojemnosc, koszt, l_zw, n, m, dlg_trasy;

bool poprawna_energia(int energia) {
    return energia > 0 && energia <= pojemnosc && zabronione_wart.count(energia) == 0;
}

void znajdz_miejsca_ladowania(int max_energia, int i_max,
                              const vector<vector<pair<int, bool>>> &energie_mozliwe) {
    int energia = max_energia;
    if (energie_mozliwe[dlg_trasy - 1][i_max].second) {
        miejsca_ladowania.push_front(n);
        energia -= powerbanki[dlg_trasy - 1];
    }
    energia += koszt;
    // złożonosc czasowa: O(n * p)
    for (int i = dlg_trasy - 2; i > 0; --i) {
        auto poprzednie_skrzyzowanie = trasa[i];
        pair<int, bool> poprzednie_ladowanie;

        for (auto &energia_ladowanie : energie_mozliwe[i]) {
            if (energia_ladowanie.first == energia) {
                poprzednie_ladowanie = energia_ladowanie;
                break;
            }
        }
        if (poprzednie_ladowanie.second) {
            energia -= powerbanki[i];
            miejsca_ladowania.push_front(poprzednie_skrzyzowanie);
        }
        energia += koszt;
    }
}

int znajdz_max_energie() {

    // dla i-tego skrzyżowania przechowuje informacje o możliwych wartościach
    // energii baterii i pamięta czy bateria była na tym skrzyżowaniu ładowana
    vector<vector<pair<int, bool>>> energie_mozliwe(dlg_trasy);

    // dla i-tego skrzyzowania przechowuje informacje
    // czy dana energia baterii była już rozpatrzona
    vector<vector<bool>> energie_dodane(dlg_trasy);

    for (auto &vec : energie_dodane)
        vec.resize(pojemnosc + 1, false);

    energie_mozliwe[0].push_back(make_pair(pojemnosc, false));

    // wyznaczanie mozliwych wartosci energii baterii na danym skrzyżowaniu trasy
    // zlozonosc czasowa: O(n * p)
    for (int i = 1; i < dlg_trasy; ++i) {
        for (size_t j = 0; j < energie_mozliwe[i - 1].size(); ++j) {
            auto energia = energie_mozliwe[i - 1][j].first - koszt;
            if (energia >= 0) {
                if (!energie_dodane[i][energia]) {
                    energie_mozliwe[i].push_back(make_pair(energia, false));
                    energie_dodane[i][energia] = true;
                }
                int energia_po_nalad = energia + powerbanki[i];
                if (poprawna_energia(energia_po_nalad) && !energie_dodane[i][energia_po_nalad]) {
                    energie_mozliwe[i].push_back(make_pair(energia_po_nalad, true));
                    energie_dodane[i][energia_po_nalad] = true;
                }
            }
        }
    }
    // szukanie max energii na końcu trasy
    int max_energia = -1, i_max;
    for (int i = 0; i < energie_mozliwe[dlg_trasy - 1].size(); ++i) {
        if (max_energia < energie_mozliwe[dlg_trasy - 1][i].first) {
            max_energia = energie_mozliwe[dlg_trasy - 1][i].first;
            i_max = i;
        }
    }
    if (max_energia != -1)
        znajdz_miejsca_ladowania(max_energia, i_max, energie_mozliwe);

    return max_energia;
}

bool znajdz_najkrotsza_trase() {

    queue<int> sasiednie_skrzyzowania;
    sasiednie_skrzyzowania.push(1);

    vector<bool> odwiedzone_skrzyzowania(n + 1, false);
    odwiedzone_skrzyzowania[1] = true;

    poprzednie_skrzyzowania.resize(n + 1, 0);

    // szukanie jakiejkolwiek najkrotszej trasy za pomocą bfs
    // zlozonosc czasowa: O(n + m)
    while (!sasiednie_skrzyzowania.empty()) {
        auto skrzyzowanie = sasiednie_skrzyzowania.front();
        sasiednie_skrzyzowania.pop();

        for (auto sasiad : drogi[skrzyzowanie]) {
            if (!odwiedzone_skrzyzowania[sasiad]) {
                poprzednie_skrzyzowania[sasiad] = skrzyzowanie;
                if (sasiad == n)
                    return true;
                sasiednie_skrzyzowania.push(sasiad);
                odwiedzone_skrzyzowania[sasiad] = true;
            }
        }
    }
    return false;
}

void odbuduj_trase() {
    
    for (int skrzyzowanie = n; skrzyzowanie != 0; skrzyzowanie = poprzednie_skrzyzowania[skrzyzowanie])
        trasa.push_back(skrzyzowanie);
    
    reverse(trasa.begin(), trasa.end());
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> pojemnosc;
    cin >> koszt;
    cin >> l_zw;

    for (int i = 0; i < l_zw; i++) {
        int temp;
        cin >> temp;
        zabronione_wart.insert(temp);
    }

    cin >> n;
    cin >> m;
    drogi.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int skrzyzowanie1, skrzyzowanie2;
        cin >> skrzyzowanie1;
        cin >> skrzyzowanie2;
        drogi[skrzyzowanie1].push_back(skrzyzowanie2);
        drogi[skrzyzowanie2].push_back(skrzyzowanie1);
    }
    powerbanki.resize(n);

    for (int i = 0; i < n; i++)
        cin >> powerbanki[i];

    if (!znajdz_najkrotsza_trase()) {
        cout << -1 << '\n';
        return 0;
    }
    else {
        odbuduj_trase();
        dlg_trasy = (int) trasa.size();
        int max_energia = znajdz_max_energie();
        
        // wyśjcie
        if (max_energia == -1) {
            cout << max_energia << '\n';
        }
        else {

            cout << dlg_trasy << ' ' << max_energia << ' ' << miejsca_ladowania.size() << '\n';

            for (int i = 0; i < dlg_trasy - 1; i++) {
                cout << trasa[i] << ' ';
            }
            cout << trasa[dlg_trasy - 1] << '\n';

            for (auto skrz: miejsca_ladowania)
                cout << skrz << ' ';
            cout << '\n';
        }
        return 0;
        // ostateczna zlozonosc: O(n * p) + O(n * p) + O(n + m) + O(n) = O(n * p + m)
    }
}