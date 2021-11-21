#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <cassert>

using namespace std;
vector<vector<int>> drogi;
set<int> zw;
vector<int> energie;
list<int> miejsca_ladowania;
vector<int> trasa;
int poj, koszt, l_zw, n, l_drog, dlg_trasy;
/*
 * musimy:
 * - wiedziec na jakich stacjach ladujemy
 * - ile energii mamy na koncu
 */

void print_vector(const vector<int> &vec) {
    cout << "printing vector:" << '\n';
    for (int i : vec)
        cout << i << ' ';
    cout << '\n';
}


bool czy_poprawna_energia(int energia) {
    return energia > 0 && energia <= poj && zw.count(energia) == 0;
}

/*energia_lad wyznacz_doladowania(int akt_stan_bater, int odl_od_startu, bitset<1001> ladowania) {
    int stan_bater_po_lad = akt_stan_bater + energie[odl_od_startu];
    energia_lad koncowa_energia_lad;
    if (akt_stan_bater < 0) {
        // nie dojechalismy
        return make_pair(-1 , ladowania);
    }
    //jesli nie mozna ladowac
    if (zw.count(stan_bater_po_lad) == 1 || stan_bater_po_lad < koszt || stan_bater_po_lad < 0 || stan_bater_po_lad > poj) {
        if (odl_od_startu == n) {
            // dojechalismy z energ > 0
            return make_pair(akt_stan_bater, ladowania);
        } else {
            // jedziemy dalej bez ladowania
            koncowa_energia_lad = wyznacz_doladowania(akt_stan_bater - koszt, odl_od_startu + 1, ladowania);
        }
    } else {
        // jesli mozna ladowac
    }


}
*/
int lala() {

  vector<vector<pair<int, bool>>> energ_na_skrz;
  energ_na_skrz.resize(n + 1);
  vector<unordered_set<bool>> energie_dodane;
  energie_dodane.resize(n + 1);
  energ_na_skrz[1].push_back(make_pair(poj, false));

  if (trasa.size() > 1) {

      for (int i = 2; i < dlg_trasy + 1; ++i) {
          for (size_t j = 0; j < energ_na_skrz[trasa[i - 2]].size(); ++j) {
              auto akt_energ = energ_na_skrz[trasa[i - 2]][j].first - koszt;
              if (akt_energ >= 0) {
                  // bez ladowania
                  if (energie_dodane[i].count(akt_energ) == 0)
                      energ_na_skrz[trasa[i - 1]].push_back(make_pair(akt_energ, false));

                  int energ_po_lad = akt_energ + energie[i - 1];
                  if (czy_poprawna_energia(energ_po_lad) && energie_dodane[i].count(energ_po_lad) == 0) {
                      energ_na_skrz[trasa[i - 1]].push_back(make_pair(energ_po_lad, true));
                  }
              }
          }
      }
      // szukanie max energii
      int max_energ = -1;
      size_t i_max;
      for (size_t i = 0; i < energ_na_skrz[n].size(); ++i) {
          if (max_energ < energ_na_skrz[n][i].first) {
              max_energ = energ_na_skrz[n][i].first;
              i_max = i;
          }
      }
      if (max_energ == -1) {
          // nie dojechalismy
          return max_energ;
      } else {
          // odzyskujemy miejsca ladowania
          int akt_energ = max_energ;
          if (energ_na_skrz[n][i_max].second) { // jesli ladowalismy to dodajemy do miejsc_ladowania
              miejsca_ladowania.push_front(n);
              akt_energ -= energie[dlg_trasy - 1] - koszt;
          }
          for (int i = dlg_trasy - 2; i > 0; --i) {
              int poprz_skrz = trasa[i];
              pair<int, bool> poprz_lad;
              for (auto &energ_lad : energ_na_skrz[poprz_skrz]) {
                  if (energ_lad.first == akt_energ) {
                      poprz_lad = energ_lad;
                      break;
                  }
              }
              if (poprz_lad.second) { // jezeli poprzednio ladowalismy to odejmujemy tyle ile ladowalismy
                  akt_energ -= energie[i];
                  miejsca_ladowania.push_front(poprz_skrz);
              }
              akt_energ += koszt;
          }
          assert(akt_energ == poj);
          return max_energ;
          }
      }
        return poj;
}

vector<int> znajdz_najkrotsza_trase() {

    queue<int> que;
    que.push(1);
    vector<int> visited(n + 1, 0);
    visited[1] = 1;
    vector<int> poprz;
    poprz.resize(n + 1);
    cout << "que empty:" << que.empty() << '\n';
    while (!que.empty()) {
        cout << "jestem w petli bfsa\n";
        auto skrz = que.front();
        cout << skrz << '\n';
        que.pop();

        if (skrz == n)
            break;

        for (auto sasiad : drogi[skrz]) {
            cout << sasiad << '\n';
            if (visited[sasiad] == 0) {
                cout << "nieodwiedzony sasiad " << sasiad << '\n';
                que.push(sasiad);
                visited[sasiad] = 1;
                poprz[sasiad] = skrz;
            }
        }
    }
    print_vector(poprz);
    return poprz;
}

void odbuduj_trase(vector<int> poprz) {

    for (int skrz = n; skrz != 0; skrz = poprz[skrz])
        trasa.push_back(skrz);

    reverse(trasa.begin(), trasa.end());

    if (trasa.empty())
        trasa = {-1};
    else if (trasa[0] != 1) {
        trasa.clear();
        trasa = {-2};
    }
}

void bfs() {

    //vector<int> poprz = znajdz_najkrotsza_trase();

    odbuduj_trase(znajdz_najkrotsza_trase());
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> poj;
    cin >> koszt;
    cin >> l_zw;

    for (int i = 0; i < l_zw; i++) {
        int temp;
        cin >> temp;
        zw.insert(temp);
    }

    cin >> n;
    cin >> l_drog;
    drogi.resize(l_drog + 1);

    for (int i = 0; i < l_drog; i++) {
        int droga1, droga2;
        cin >> droga1;
        cin >> droga2;
        drogi[droga1].push_back(droga2);
        drogi[droga2].push_back(droga1);
    }
    energie.resize(n);

    for (int i = 0; i < n; i++)
        cin >> energie[i];
    cout << "essunia zaraz bfsik lecimy\n";

    bfs();

    if (trasa[0] == -1)
        cout << "trasa pusta\n";
    else if (trasa[0] == -2)
        cout << "nie dotarto do konca\n";
    else {
        // jezeli nie da sie dotrzec
        if (trasa[0] == -1) {
            cout << -1 << "nie znaleziono najkrotszej sciezki";
            return 0;
        }


        dlg_trasy = static_cast<int>(trasa.size());
        /*
        for (auto skrz : trasa)
            cout << skrz;

        cout << '\n';

        int max_energ = lala(trasa);

        cout << "max energ: " << max_energ << '\n';

        cout << "miejsca ladowania: ";

        for (auto i : miejsca_ladowania)
            cout << i << ' ';

        cout << '\n';
        */
        // wyjscie
        /*
        int max_energ = lala();
        if (max_energ == -1) {
            cout << max_energ;
        } else {
            cout << dlg_trasy << ' ' << max_energ << ' ' << miejsca_ladowania.size() << '\n';

            for (int i = 0; i < dlg_trasy - 1; i++) {
                cout << trasa[i] << ' ';
            }
            cout << trasa[dlg_trasy - 1] << '\n';
            if (miejsca_ladowania.size() > 1) {
                for (int i: miejsca_ladowania) {
                    cout << i;
                    miejsca_ladowania.pop_front();
                    if (!miejsca_ladowania.empty())
                        cout << ' ';
                    else
                        cout << '\n';
                }
            } else
                cout << '\n';
        }
    }
    return 0;
*/
    }
}
