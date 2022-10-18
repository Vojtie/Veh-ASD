# Vehicle
Big task 1 solution for Algorithms and Data Structures classes at Uni.

### Problem statement in polish:
Profesor Makary potrzebuje wypróbować swój nowy, zasilany energią elektryczną, wehikuł. Dla bezpieczeństwa
będzie się poruszał po specjalnie skonstruowanym miasteczku. Profesor koniecznie chce przejechać z punktu
startowego do punktu końcowego najkrótszą, w sensie liczby mijanych skrzyżowań, trasą.
Testowe miasteczko ma specyficzną sieć dróg — na przejechanie każdego odcinka pomiędzy skrzyżowaniami
zużywa się tyle samo energii. Sieć dróg jest intensywnie rozbudowywana, mogą więc istnieć „skrzyżowania”
do których chwilowo dochodzi tylko jedna droga albo nawet nie dochodzi żadna. Ponieważ pojemność akumulatorów pojazdu jest ograniczona, po drodze może zajść potrzeba ich doładowania. Szczęśliwie, na każdym
skrzyżowaniu stoi gotowy do użycia powerbank. Niestety, korzystanie z powerbanków jest związane z kilkoma
zasadami:
• z każdego z nich można skorzystać tylko raz,
• trzeba pobrać całą zmagazynowaną energię,
• nie można przekroczyć pojemności akumulatorów, ani zakończyć ładowania na którejś z zabronionych
wartości, bo skończy się to awarią wehikułu.
Profesor może użyć powerbanku również po dotarciu na ostatnie skrzyżowanie, oczywiście o ile nie doprowadzi to do awarii wehikułu.
Dostępna na danym skrzyżowaniu porcja energii jest zależna od długości najkrótszej ścieżki do tego skrzyżowania od początku trasy, wyrażonej w liczbie skrzyżowań. Konkretne wartości to parametry zadania.
Kombinacja układu dróg, pojemności akumulatora, układu powerbanków i konieczności jazdy najkrótszą
trasą mogą spowodować, że wehikułem nie da się pokonać trasy.
Pomóż profesorowi Makaremu ustalić, czy da się pokonać trasę i jeśli tak, to na których skrzyżowaniach
powinien doładować baterię wehikułu, aby na końcu trasy zmaksymalizować pozostałą w wehikule energię.

### Wejście
W pierwszym wierszu wejścia znajdują się trzy liczby całkowite: p (1 ≤ p ≤ 5 000), pojemność akumulatora
wehikułu, który na początku trasy jest pełny, k (0 ≤ k ≤ p), koszt przejechania odcinka między skrzyżowaniami
i z (0 ≤ z ≤ p + 1), liczba zabronionych wartości.
Kolejny wiersz zawiera z różnych liczb całkowitych zw1, zw2, . . . , zwz, (0 ≤ zwi ≤ p), zabronione wartości,
które mogą doprowadzić do awarii.
W następnym wierszu wejścia znajdują się dwie liczby całkowite n i m (2 ≤ n ≤ 1 000, 1 ≤ m ≤ 100 000),
oznaczające odpowiednio liczbę skrzyżowań i dróg w mieście. W kolejnych m wierszach znajdują się pary liczb
całkowitych a, b oznaczające numery skrzyżowań (1 ≤ a < b ≤ n), końce pojedynczego odcinka drogi. Każda
para (a, b) pojawi się na wejściu co najwyżej raz. Wszystkie odcinki są dwukierunkowe. Trasa rozpoczyna się
na skrzyżowaniu 1 i kończy na skrzyżowaniu n.
W ostatnim wierszu znajduje się n liczb całkowitych e0, e1, . . . , en−1 (0 ≤ ei ≤ p), ilości energii zmagazynowanej w powerbankach umieszczonych na skrzyżowaniach, w kolejnych odległościach od punktu początkowego.
Wartość ei określa ilość energii zmagazynowanej na wszystkich skrzyżowaniach odległych o i od punktu początkowego, w szczególności wartość e0 oznacza ilość energii w powerbanku w punkcie początkowym.

### Wyjście
Jeśli nie da się pokonać zaplanowanej trasy, w pierwszym i jedynym wierszu należy wypisać liczbę −1. W
przeciwnym razie w pierwszym wierszu wyjścia należy wypisać trzy liczby całkowite: długość znalezionej trasy,
maksymalną końcową ilość energii pozostałą w wehikule po pokonaniu trasy oraz liczbę stacji, na których
należy doładować wehikuł w znalezionym rozwiązaniu. W drugim wierszu wyjścia należy wypisać numery
kolejnych skrzyżowań na znalezionej trasie. W trzecim wierszu wyjścia należy wypisać podciąg skrzyżowań na
znalezionej trasie, na których należy doładować wehikuł. Jeśli nie ma doładowań, należy wypisać pusty wiersz.
Jeśli istnieje wiele poprawnych rozwiązań, wypisz dowolne z nich.
