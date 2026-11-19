# ASD — kolokwium laboratoryjne: notatki

> Podgląd w VS Code: otwórz ten plik i naciśnij **Ctrl+Shift+V**.
> Wszystkie pliki `.cpp` w `biblioteka/` kompilują się i mają self-testy (porównanie z brute'em na tysiącach losowych testów).

---

## 0. Start na kolosie (pierwsze 3 minuty)

```bash
# 1. Pobierz swoje zgłoszenie "Backup" ze Szkopułu (lista zgłoszeń -> pobierz), potem:
cd ~ && unzip ~/Pobrane/asd-kolos.zip      # albo ~/Downloads/...; sprawdź: ls ~/Pobrane ~/Downloads
source ~/asd-kolos/szablony/setup.sh       # funkcje c, d, r, nowe, stres, czas

# 2. Katalog na zadanie
mkdir ~/kol && cd ~/kol
nowe zad                                   # zad.cpp z szablonu
code .                                     # VS Code w tym katalogu (albo: gedit zad.cpp &)
```

**Pliki w paczce**

| Ścieżka | Co tam jest |
|---|---|
| `szablony/szablon.cpp` | szablon rozwiązania (szybkie I/O, `ll`, `dbg`) |
| `szablony/stress.sh` | stress test: wzorcówka vs brute na losowych testach |
| `szablony/gen.cpp` | generator testów (do przerobienia pod format) |
| `szablony/testy.sh` | odpala program na `tests/*.in` i porównuje z `.out` |
| `szablony/setup.sh` | skróty: `c`, `d`, `r`, `nowe`, `stres`, `czas` |
| `biblioteka/01..11_*.cpp` | wzorcówki technik (patrz rozdz. 7) |
| `zadania/*.cpp` | rozwiązane zadania z poprzednich kolosów i labów |

---

## 1. Plan na 90 minut

1. **(0–10 min) Czytanie.** Przeczytaj treść dwa razy. Wypisz: ograniczenia na `n`, zakres wartości, czy przedziały są domknięte, czy wynik może przekroczyć `int`. **Ręcznie przelicz przykład.**
2. **(10–20 min) Pomysł.** Spójrz na `n` → dopuszczalna złożoność (rozdz. 5). Dopasuj do wzorca (rozdz. 6). Zanim zaczniesz pisać, sprawdź pomysł na przykładzie i na 1–2 własnych małych przypadkach brzegowych.
3. **(20–30 min) Najpierw brute.** Prosty O(n²)/O(n³), wprost z definicji. Często daje od razu podzadanie 1 (50 pkt za `n ≤ 5000`). **Wyślij go na Szkopuł**, bo to punkty w kieszeni.
4. **(30–55 min) Wzorcówka.** Napisz szybkie rozwiązanie i sprawdź je na przykładzie z treści.
5. **(55–70 min) Stress test.** `stres zad brute` (rozdz. 3). Gdy znajdzie różnicę, masz mały kontrprzykład do debugowania.
6. **(70–80 min) Test wydajności.** Wygeneruj maksymalny test i zmierz `czas zad big.in`. Wyślij.
7. **Zapas:** przypadki brzegowe: `n = 1`, wszystkie równe, `w = 0`, wartości maksymalne (przepełnienie!).

> Szkopuł pokazuje wynik na bieżąco. Wysyłaj od razu, gdy coś działa; liczy się zwykle najlepsze/ostatnie zgłoszenie — sprawdź w regulaminie kolosa.

---

## 2. Komendy i flagi

### Kompilacja

```bash
g++ -std=c++20 -O2 -Wall -Wextra -Wshadow zad.cpp -o zad          # normalnie (jak Szkopuł)
g++ -std=c++20 -O1 -g -Wall -Wextra -fsanitize=address,undefined \
    -D_GLIBCXX_DEBUG zad.cpp -o zad                                 # DEBUG: łapie błędy pamięci
```

| Flaga | Co robi |
|---|---|
| `-std=c++20` | standard C++20 (`contains`, structured bindings, `<=>`) |
| `-O2` | optymalizacja; **mierz czas tylko z -O2**, bez niej kod jest 3–10× wolniejszy |
| `-Wall -Wextra` | ostrzeżenia: nieużyte zmienne, porównanie `int` z `size_t`, brak `return` |
| `-Wshadow` | ostrzega, gdy zmienna zasłania inną (`int n` w pętli i globalnie) — częsty bug |
| `-g` | symbole debugowania (numery linii w błędach, `gdb`) |
| `-fsanitize=address` | wyjście poza tablicę, użycie zwolnionej pamięci → crash z numerem linii |
| `-fsanitize=undefined` | przepełnienie `int`, dzielenie przez 0, zły shift → komunikat z linią |
| `-D_GLIBCXX_DEBUG` | `vector[i]` sprawdza zakres, `sort` sprawdza komparator |
| `-DLOCAL` | definiuje `LOCAL` → działają `dbg(x)` z szablonu (na Szkopule znikają) |
| `-fno-sanitize-recover=all` | sanitizer **przerywa** program przy pierwszym błędzie (stress to wykryje) |

Skróty z `setup.sh`: `c zad` (normalnie), `d zad` (debug), `r zad` (kompiluj + uruchom na `zad.in`).

### Uruchamianie i porównywanie

```bash
./zad < zad.in                      # wejście z pliku
./zad < zad.in > moje.out           # wyjście do pliku
diff -w moje.out zad.out            # porównanie (-w ignoruje białe znaki); brak wyniku = identyczne
diff <(./zad < 1.in) 1.out          # bez pliku pośredniego
echo "3 5" | ./zad                  # szybkie wejście z linii
./zad <<< "3 5"                     # to samo
time ./zad < big.in > /dev/null     # czas (patrz "real")
/usr/bin/time -v ./zad < big.in > /dev/null   # + "Maximum resident set size" = pamięć w KB (jeśli jest zainstalowane)
czas zad big.in                     # skrót z setup.sh
ulimit -s unlimited                 # duży stos (głęboka rekurencja lokalnie) — Szkopuł tego NIE robi!
./testy.sh zad.cpp tests            # wszystkie tests/*.in vs tests/*.out
```

Tworzenie testu z przykładu: `nano tests/1.in` (wklej, **Ctrl+O, Enter, Ctrl+X**) albo w VS Code.

### Duży test do pomiaru czasu

```bash
c gen && ./gen 1 500000 2000000000 > big.in && c zad && czas zad big.in
```
Albo wprost w bashu: `python3 -c "import random; n=500000; print(n, 10**9); [print(random.randint(0,2*10**9)) for _ in range(n)]" > big.in`

### gdb (gdy crash, a sanitizer nic nie mówi)

```bash
d zad && gdb ./zad
(gdb) run < fail.in        # uruchom
(gdb) bt                   # po crashu: stos wywołań (gdzie padło)
(gdb) frame 2              # przejdź do ramki 2
(gdb) print i              # wartość zmiennej;  print a[i];  print v.size()
(gdb) break 42             # breakpoint w linii 42;  next / step / continue
```

---

## 3. Stress test (najważniejsze narzędzie)

**Po co:** wzorcówka przechodzi przykład, ale ma bug, który wychodzi na jakimś przypadku brzegowym. Stress test sam znajduje **mały** kontrprzykład.

**Potrzebujesz 3 plików w jednym katalogu:**
1. `zad.cpp` — Twoje szybkie rozwiązanie,
2. `brute.cpp` — głupie, oczywiste rozwiązanie z definicji (O(n²), O(n³), wszystkie podzbiory...),
3. `gen.cpp` — generator losowych **małych** testów w formacie z treści.

```bash
cp ~/asd-kolos/szablony/gen.cpp .     # przerób main() pod format wejścia
stres zad brute                       # 1000 testów, n <= 8, wartości <= 20
stres zad brute 5000 5 10             # 5000 testów, n <= 5, wartości <= 10 (bardzo małe = czytelne)
# bez setup.sh:
bash ~/asd-kolos/szablony/stress.sh zad.cpp brute.cpp gen.cpp 1000 8 20
```

**Wynik:**
- `WSZYSTKIE ... TESTÓW OK` → dobra wiadomość (ale zwiększ zakresy, spróbuj też `MAXV` = 3, czyli dużo równych wartości);
- `ZŁA ODPOWIEDŹ na teście i` → wypisze wejście, Twój wynik i wynik brute'a; test ląduje w `fail.in`;
- `CRASH/TIMEOUT wzorcówki` → sanitizer pokaże linię (wyjście poza tablicę, przepełnienie `int`).

**Debugowanie po znalezieniu:** `d zad && ./zad < fail.in` i `dbg(...)` / `cerr` w podejrzanych miejscach.

**gen.cpp — jak przerobić:** zmieniasz tylko fragment po `FORMAT WEJŚCIA`. Gotowe funkcje:
`rnd(a, b)` (liczba z [a, b]), `perm(n)` (permutacja), `distinct(k, lo, hi)` (różne liczby), `tree(n)`, `graph(n, m)`. Na dole są gotowce: ciąg w linii, przedziały, graf, zapytania.

**Zasady dobrego generatora:**
- **małe n** (≤ 8) i **małe wartości** (≤ 10–20) → dużo remisów i duplikatów, czyli tam, gdzie siedzą bugi;
- losuj też parametry (`w`, `k`) z małego zakresu, łącznie z **0**;
- pilnuj warunków z treści (np. „liczby parami różne” → `distinct`, „y1 < y2”, „bez wspólnych końców”).

**Brute — zasady:** ma być **oczywiście poprawny**, nie szybki. Bez sortowania i sprytu, wprost z definicji z treści. Pętla po wszystkich parach / przedziałach `[a, a+w]` / podzbiorach (`for mask < 1<<n`).

Przykład gotowy do odpalenia: `cd ~/asd-kolos/zadania && cp ../szablony/gen.cpp . && stres log log_brute`.

---

## 4. Wejście/wyjście

- **Zawsze:** `ios_base::sync_with_stdio(false); cin.tie(nullptr);` (jest w szablonie). Wtedy **nie mieszaj** `cin` z `scanf` ani `cout` z `printf`.
- `"\n"` zamiast `endl`! (`endl` opróżnia bufor → przy 5·10⁵ liniach TLE).
- Wczytanie do końca pliku: `while (cin >> x) {...}`.
- Cała linia: `getline(cin, s);` (po `cin >> n` najpierw `cin.ignore()`).
- Gdy `cin` za wolny (wiele milionów liczb), użyj `fread`:

```cpp
static char buf[1 << 25]; int bp = 0;                       // 32 MB bufor
int readInt() { while (buf[bp] != '-' && (buf[bp] < '0' || buf[bp] > '9')) bp++;
    bool neg = buf[bp] == '-'; if (neg) bp++; int x = 0;
    while (buf[bp] >= '0' && buf[bp] <= '9') x = x * 10 + (buf[bp++] - '0');
    return neg ? -x : x; }
// w main: fread(buf, 1, sizeof(buf) - 1, stdin);
```

---

## 5. Ograniczenia → złożoność (≈ 10⁸ prostych operacji / s)

| n | Dopuszczalna złożoność | Typowe techniki |
|---|---|---|
| ≤ 10 | O(n!) , O(n·n!) | permutacje (`next_permutation`) |
| ≤ 20 | O(2ⁿ · n) | podzbiory, DP na maskach |
| ≤ 500 | O(n³) | DP przedziałowe, Floyd |
| ≤ 5 000 | O(n²) | **podzadanie 1** = zwykle brute po parach |
| ≤ 10⁵ – 10⁶ | O(n log n) | **sort**, binsearch, set/map, kopiec, Fenwick |
| ≤ 10⁷ – 10⁸ | O(n) | dwa wskaźniki, prefiksy, stos/kolejka monotoniczna |
| wartości ≤ 10⁶ | tablica zliczająca `cnt[v]` | counting sort |
| wartości ≤ 10⁹ | kompresja / `map` / sort | |

**Pamięć:** 256 MB ≈ 64·10⁶ `int` ≈ 32·10⁶ `long long`. `vector<vector<int>>` n×n przy n = 10⁵ → NIE.
**Liczby:** `int` do ~2.1·10⁹; `long long` do ~9.2·10¹⁸. Iloczyn dwóch 10⁹ = 10¹⁸ (mieści się w `ll`); suma par n² przy n = 5·10⁵ to ~1.25·10¹¹ (**ll!**).

---

## 6. Rozpoznawanie zadania: słowa-klucze → technika

| W treści widzisz | Spróbuj | Plik |
|---|---|---|
| „kolejność nieistotna”, pary `i<j` z warunkiem na **różnicę/sumę** | **sortuj** + dwa wskaźniki / binsearch | 03, `sza.cpp` |
| „przedział długości w”, „okno”, „najwięcej w czasie w” | sort + **dwa wskaźniki** | 03, `log.cpp` |
| „spójny fragment” + suma ≤ S, **liczby nieujemne** | dwa wskaźniki (okno) | 03 E–G |
| „spójny fragment” + suma = K, **dowolne znaki** | **prefiksy + mapa** „ile było po lewej” | 04 |
| „suma na przedziale” wiele zapytań, tablica stała | **sumy prefiksowe** | 04 |
| „dodaj v na [l, r]” wiele razy, potem odczyt | **tablica różnicowa** | 04 |
| „zmaksymalizuj minimum” / „zminimalizuj maksimum” / „najmniejsze X, że da się” | **binsearch po wyniku** | 02 |
| „najbliższy większy / mniejszy”, „widoczność”, histogram | **stos monotoniczny** | 05 |
| „max/min w każdym oknie długości k” | **deque monotoniczna** | 05 |
| przedziały: „suma”, „ile naraz”, „najwięcej rozłącznych” | **sort** + zamiatanie / zachłan po końcu | 06 |
| przedziały z wagami, „max zysk z rozłącznych” | DP + binsearch | 06, `pro.cpp` |
| wstawianie/usuwanie + „sąsiad”, „najbliższy”, „k-ty” | **set / multiset** | 07, `sum.cpp` |
| usuwanie z ciągu + pytanie o sąsiadów | **lista na tablicach** | 07, `zol.cpp` |
| „zawsze bierz najmniejszy/największy”, symulacja w czasie | **priority_queue** | 07 |
| mediana dynamiczna | dwa kopce / dwa multisety | 07 |
| „ile podciągów/sposobów”, „max wartość”, wybory | **DP** | 08 |
| liczba podciągów rosnących, wartości małe | DP „ile kończy się na v” | 08, `pod.cpp` |
| trójki/pary z warunkiem, **wartości małe** (≤ 10–100) | tablice zliczające po wartościach | `tro.cpp` |
| graf, „najkrótsza ścieżka”, kroki | **BFS** (wagi 1) / Dijkstra | 09 |
| „podziel na dwie grupy”, „cykl nieparzysty”, 2 kolory | **dwudzielność BFS** | 09, `ski.cpp` |
| „czy połączone”, łączenie grup | **DSU** | 09 |
| zależności „A przed B” | **sort topologiczny** | 09 |
| inwersje, „ile zamian sąsiadów” | merge sort / Fenwick | 01, 10 |
| zmiany w tablicy + zapytania o sumę/min na przedziale | **Fenwick / drzewo przedziałowe** | 10 |
| potęgi dwójki, sumy 2^a, XOR | bity, licznik binarny | 11, `jed.cpp` |
| „modulo 10⁹+7” | arytmetyka modularna | 11 |

**Pytania, które warto sobie zadać:**
1. Czy kolejność elementów ma znaczenie? Jeśli **nie** → posortuj.
2. Czy optymalne rozwiązanie da się „przesunąć” do punktu z wejścia? (LOG: przedział zaczyna się w punkcie.)
3. Co się zmienia, gdy przesuwam prawy koniec o 1? Czy lewy koniec tylko rośnie? → dwa wskaźniki.
4. Czy da się odpowiedzieć „tak/nie” dla ustalonego wyniku X i czy to jest monotoniczne? → binsearch po wyniku.
5. Czy policzę **dopełnienie** łatwiej? (pary przecinające = wszystkie − rozłączne).
6. „Dokładnie K” = „≤ K” − „≤ K−1”.
7. Czy wartości są małe? → tablica zliczająca zamiast mapy.
8. Dla każdego elementu: ile **pasujących po lewej**? (mapa/tablica liczników, przechodzisz raz.)

---

## 7. Biblioteka — co gdzie jest

Każdy plik da się skompilować i uruchomić (`g++ -O2 -std=c++20 plik.cpp && ./a.out` → `OK`). Kopiujesz **samą funkcję**.

**01_sortowanie** — merge sort + **liczba inwersji**; counting sort; **radix sort** (2× po 16 bitów, stabilnie, od niższej cyfry); quickselect / `nth_element` (k-ty element, mediana); **kompresja współrzędnych**; argsort (indeksy po wartości); komparatory (ŚCISŁE `<`!).

**02_wyszukiwanie_binarne** — ściąga `lower_bound`/`upper_bound` (ile `== x`, ile w `[lo, hi]`, ostatni `≤ x`); `firstTrue` / `lastTrue` (szablon binsearcha, który się nie myli); binsearch po wyniku (krowy, podział na k kawałków); binsearch na `double` (100 iteracji); szczyt ciągu bitonicznego.

**03_dwa_wskazniki** — A: max punktów w oknie w (LOG); B: pary z różnicą ≤ w (SZA); różnica w `[A, B]`; C: pary z sumą ≤ S; D: two-sum; E: najdłuższy fragment z sumą ≤ S; F: **liczba** fragmentów z sumą ≤ S; G: najkrótszy z sumą ≥ S; H: najdłuższy z ≤ K różnymi (+ „dokładnie K”); I: najkrótsze okno ze wszystkimi kolorami; J: 3-sum (liczba trójek); K: przecięcie posortowanych.

**04_sumy_prefiksowe** — prefiksy 1D/2D; tablica różnicowa; Kadane; liczba fragmentów z sumą = K (mapa prefiksów); suma podzielna przez m; najdłuższy z sumą K; suma |aᵢ − aⱼ| po wszystkich parach.

**05_stos_kolejka** — next greater / prev smaller; największy prostokąt w histogramie; max w oknie (deque); najdłuższy fragment z max − min ≤ d; nawiasy; kolejka z minimum.

**06_przedzialy_zamiatanie** — scalanie; max liczba nachodzących (zdarzenia); max liczba rozłącznych (zachłan po końcu); ważony wybór (DP + binsearch); liczba par przecinających; ile przedziałów zawiera punkt; który przedział jest zawarty w innym.

**07_set_map_kopiec** — ściąga STL; suma kwadratów różnic sąsiadów (SUM) z usuwaniem; najbliższy element w secie; **lista na tablicach** (ZOL); mediana strumienia (2 kopce); mediana w oknie (2 multisety); top-k; scalanie k list; symulacja z kopcem.

**08_dp** — LIS O(n log n); plecak 0/1; monety (sposoby, minimum); LCS; edit distance; giełda (GIE); liczba podciągów rosnących (POD); ścieżki na kratce; DP przedziałowe (gra); bez sąsiednich; DP na maskach (TSP).

**09_grafy** — BFS; dwudzielność; składowe; DFS iteracyjny (rozmiary poddrzew); topo-sort (Kahn); Dijkstra; DSU + Kruskal; BFS na kratce.

**10_fenwick_drzewo_przedzialowe** — Fenwick (suma, „dodaj na przedziale”); inwersje Fenwickiem; drzewo przedziałowe iteracyjne (min/sum/max); leniwe (dodaj na przedziale, suma na przedziale).

**11_bity_matma_hash** — ściąga bitowa; licznik binarny (JED); potęgowanie mod, odwrotność, dwumian; sito; bezpieczny hash do `unordered_map`; hash napisów.

---

## 8. Wzorce, które wracają najczęściej (do zapamiętania)

**Dwa wskaźniki (okno):**
```cpp
for (int l = 0, r = 0; r < n; r++) {
    // dodaj a[r] do okna
    while (/* okno złe */) { /* usuń a[l] */ l++; }
    // okno [l, r] dobre: best = max(best, r - l + 1);  albo  ans += r - l + 1;
}
```

**Zlicz pasujących po lewej (jedno przejście):**
```cpp
unordered_map<ll, ll> cnt;  // albo vector, gdy wartości małe
for (int i = 0; i < n; i++) {
    ans += cnt[partner(a[i])];   // ile wcześniejszych pasuje do a[i]
    cnt[a[i]]++;
}
```

**Binsearch po wyniku:**
```cpp
ll lo = MIN, hi = MAX;            // ok(hi) == true na pewno
while (lo < hi) { ll mid = lo + (hi - lo) / 2; if (ok(mid)) hi = mid; else lo = mid + 1; }
// lo = najmniejszy dobry
```

**Grupowanie równych po sortowaniu:**
```cpp
for (int i = 0; i < n;) { int j = i; while (j < n && a[j] == a[i]) j++; /* grupa [i, j) */ i = j; }
```

**Zdarzenia (sweep):** `(x, typ)` → sort → przejście z licznikiem. Domknięte przedziały: start przed końcem przy tym samym x.

---

## 9. Pułapki — przejrzyj przed wysłaniem

- [ ] **Przepełnienie:** wynik (liczba par, suma) w `long long`? `a[i] + w` przy `a, w ~ 10⁹`? `x * y` → `1LL * x * y`. `1 << 40` → `1LL << 40`.
- [ ] **Domknięte / otwarte przedziały:** `<=` czy `<`? (LOG: `t[r] - t[l] > w` przesuwa; SZA: `<= w` liczy.)
- [ ] **Remisy / równe wartości:** czy przy równych sort i warunek dają dobrze? (stress z `MAXV=3`)
- [ ] **n = 1**, pusty wynik, wszystko równe, `w = 0`, `k = 0`.
- [ ] **Indeksowanie:** treść 1..n, kod 0..n-1? `vector(n + 1)` gdy indeksujesz od 1.
- [ ] **Graf niespójny** — pętla po wszystkich wierzchołkach startowych.
- [ ] **Rekurencja głęboka** (DFS na ścieżce 5·10⁵) → stack overflow na Szkopule. BFS / iteracyjnie.
- [ ] `multiset::erase(x)` usuwa **wszystkie** kopie → `erase(find(x))`.
- [ ] `std::lower_bound` na `set` jest O(n) → `s.lower_bound(x)`.
- [ ] `map[k]` przy sprawdzaniu tworzy wpis → `find` / `count`.
- [ ] Komparator `<=` w `sort` → UB/crash. Ma być ścisłe `<`.
- [ ] `v.size() - 1` gdy `v` pusty → ogromna liczba (`size_t`). Rzutuj: `(int)v.size() - 1`.
- [ ] `endl` w pętli → TLE. Debug na `cerr`, **usuń przed wysłaniem** (albo `dbg` z `-DLOCAL`).
- [ ] Zmienne globalne / tablice nie są zerowane między testami, gdy jest `t` testów.
- [ ] Format wyjścia: każda liczba w osobnej linii? `TAK`/`NIE` czy `YES`/`NO`?
- [ ] Ujemne modulo: `((x % m) + m) % m`.

---

## 10. Zadania z poprzednich kolosów — pomysły w 1–2 zdaniach

| Zadanie | Pomysł | Plik |
|---|---|---|
| **LOG** Logi serwera | sort; max okno `t[r] - t[l] <= w`; dwa wskaźniki | `log.cpp` (+ brute) |
| **SZA** Partie towarzyskie | sort; dla każdego `l` liczba `r` z `x[r] - x[l] <= w`; wynik `ll` | `sza.cpp` (+ brute) |
| **ZOL** Żołnierze | lista dwukierunkowa na tablicach z wartownikami 0 i n+1, O(n) | `zol.cpp` |
| **SUM** Suma kwadratów | `set`, przy wstawieniu x między p i nx: `+(x−p)² + (nx−x)² − (nx−p)²` | `sum.cpp` |
| **SKI** Skierowanie | wierzchołek = źródło albo ujście ⇔ graf dwudzielny; BFS | `ski.cpp` |
| **ODC** Odcinki pionowe | grupuj po x; pary − pary rozłączne (`y2_j < y1_i` binsearchem) | `odc.cpp` |
| **JED** Jedynki | licznik binarny: gaś jedynki, zapal zero; zamortyzowane O(1) | `jed.cpp` |
| **TRO** Trójki | wartości 1..10: `pairs[s]` = liczba par z sumą s po lewej; O(10n) | `tro.cpp` |
| **POD** Podciągi rosnące {1,2,3} | `end[v] += 1 + Σ end[u<v]` | `pod.cpp` |
| **GIE** Giełda | DP nie_mam/mam (−INF na start) albo suma dodatnich różnic | `gie.cpp` |
| **PRO** Projekty | sort po początku; `dp[i] = max(dp[i+1], w + dp[upper_bound(r)])` | `pro.cpp` |
| **PRZ** Przedziały | sort po początku przedziału, potem jedno przejście (szczegóły sprawdź w treści) | — |
| **SZY** Szyna | pary równych elementów → przedziały; max rozłącznych zachłannie, najbliższe poprzednie wystąpienie z mapy | — |

---

## 11. Ściąga STL (algorytmy)

```cpp
sort(all(v));  sort(all(v), greater<>());  stable_sort(...)
reverse(all(v));  rotate(v.begin(), v.begin() + k, v.end());
v.erase(unique(all(v)), v.end());          // usuń duplikaty (po sort!)
*max_element(all(v)); *min_element(all(v)); auto [mn, mx] = minmax_element(all(v));
accumulate(all(v), 0LL);                    // 0LL! inaczej suma w int
count(all(v), x);  find(all(v), x);
nth_element(v.begin(), v.begin() + k, v.end());   // v[k] = k-ty, O(n)
partial_sum(all(a), P.begin() + 1);
iota(all(idx), 0);                          // 0, 1, 2, ...
next_permutation(all(v));                   // do{...}while(next_permutation(all(v))) po sort
fill(all(v), 0);  v.assign(n, 0);
binary_search(all(v), x);                   // bool
__gcd(a, b);  gcd(a, b);  lcm(a, b);
memset(arr, 0, sizeof arr);                 // tylko 0 lub -1 (0x3f -> ~1e9 dla int)
```

Kontenery — złożoności: `vector` push_back O(1)*, `deque` oba końce O(1), `set/map` O(log n), `unordered_*` O(1) średnio, `priority_queue` push/pop O(log n), top O(1).

**cppreference.com jest dostępne na kolosie** — szukaj tam sygnatur (`lower_bound`, `priority_queue`, `std::set`).

---

## 12. VS Code / terminal — skróty

| Skrót | Akcja |
|---|---|
| Ctrl+` | terminal w VS Code |
| Ctrl+Shift+V | podgląd Markdown (ten plik) |
| Ctrl+P | szybkie otwieranie pliku |
| Ctrl+D | zaznacz kolejne wystąpienie (zmiana nazwy zmiennej) |
| Alt+↑/↓ | przesuń linię |
| Ctrl+/ | komentarz |
| Ctrl+Shift+K | usuń linię |
| Ctrl+R (bash) | szukanie w historii komend |
| ↑ (bash) | poprzednia komenda |
