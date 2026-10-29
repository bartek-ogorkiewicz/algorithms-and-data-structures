# Szablon do stress testów

Stress test porównuje Twoje rozwiązanie (`wzo.cpp`) z wolnym, ale pewnym
rozwiązaniem (`brute.cpp`) na tysiącach małych, losowych testów. Gdy wyniki
się różnią, dostajesz konkretny test, na którym wzorcówka się myli.

## Pliki

| Plik        | Co to jest                                        |
|-------------|---------------------------------------------------|
| `wzo.cpp`   | Twoje właściwe rozwiązanie                        |
| `brute.cpp` | wolne, proste, oczywiście poprawne rozwiązanie    |
| `gen.cpp`   | generator losowych testów: `./gen.e <ziarno>`     |
| `stress.sh` | kompiluje wszystko i porównuje wyniki             |

## Nowe zadanie — krok po kroku

1. Skopiuj szablon do folderu zadania:
   ```bash
   cp -r ~/mimuw/asd/stress-template ~/mimuw/asd/lab/labXX/nazwa-zadania
   cd ~/mimuw/asd/lab/labXX/nazwa-zadania
   ```
2. Napisz `wzo.cpp` (rozwiązanie) i `brute.cpp` (wersja prosta).
3. W `gen.cpp` zmień tylko część **LOSOWANIE TESTU**, tak żeby wypisywała
   wejście w formacie z treści zadania. Testy mają być **małe**, ale trafiać
   w trudne przypadki (skrajne wartości, puste wejście, duplikaty itp.).
4. Uruchom:
   ```bash
   bash stress.sh          # 2000 testów
   bash stress.sh 500      # albo dowolna inna liczba
   ```
   Skrypt sam kompiluje wszystkie trzy programy i pokazuje postęp.

## Kompilacja ręczna

`stress.sh` kompiluje sam, ale żeby odpalić pojedynczy program (np. sprawdzić
jeden test), kompilujesz ręcznie. Komenda zależy od systemu.

### Mac

Na Macu polecenie `g++` to tak naprawdę clang, który nie ma `bits/stdc++.h`.
Trzeba użyć prawdziwego GCC z Homebrew (`brew install gcc`), które nazywa się
z numerem wersji, np. `g++-15`:

```bash
g++-15 -O2 -std=c++17 wzo.cpp   -o wzo.e
g++-15 -O2 -std=c++17 brute.cpp -o brute.e
g++-15 -O2 -std=c++17 gen.cpp   -o gen.e
```

Jaką masz wersję, sprawdzisz przez `ls $(brew --prefix)/bin | grep g++`.
Żeby pisać samo `g++`, dodaj alias:

```bash
echo "alias g++='g++-15'" >> ~/.zshrc
source ~/.zshrc
```

### Linux (students, sprawdzaczka, Ubuntu itp.)

Tu `g++` to od razu prawdziwe GCC, więc bez numeru wersji:

```bash
g++ -O2 -std=c++17 wzo.cpp   -o wzo.e
g++ -O2 -std=c++17 brute.cpp -o brute.e
g++ -O2 -std=c++17 gen.cpp   -o gen.e
```

W `stress.sh` zmień wtedy na górze `CXX=g++-15` na `CXX=g++`.

### Co znaczą flagi

- `-O2` — optymalizacje, tak jak na sprawdzaczce.
- `-std=c++17` — standard języka (potrzebny m.in. do `auto& [a, b]`).
- `-o wzo.e` — nazwa pliku wynikowego.

### Kompilacja do debugowania

Wolniej, ale łapie błędy, zamiast po cichu liczyć bzdury.

Mac:

```bash
g++-15 -std=c++17 -Wall -Wextra -g -D_GLIBCXX_DEBUG wzo.cpp -o wzo.e
```

Linux:

```bash
g++ -std=c++17 -Wall -Wextra -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined wzo.cpp -o wzo.e
```

- `-Wall -Wextra` — ostrzeżenia (np. nieużyte zmienne, porównanie `int` z `size_t`).
- `-g` — informacje dla debuggera.
- `-D_GLIBCXX_DEBUG` — `vector`, `string` itp. sprawdzają indeksy: wyjście poza
  tablicę wywala program z opisem błędu.
- `-fsanitize=address,undefined` — łapie też przepełnienie `int` i błędy
  pamięci. Działa tylko na Linuksie; na Macu z GCC sanitizery zwykle nie działają.

### Uruchomienie z testem z pliku

Tak samo na obu systemach:

```bash
./wzo.e < test.in
```

## Wynik

- `OK, 2000 testów zgodnych` — brak różnic.
- `Różnica dla ziarna 734` + test + oba wyniki — wzorcówka (albo brute!)
  ma błąd na tym teście.

## Co robić z ziarnem

Ziarna nie podajesz ręcznie przy `stress.sh` — skrypt sam leci po
ziarnach 1, 2, 3, … Ziarno przydaje się, żeby odtworzyć konkretny test:

```bash
./gen.e 734 > test.in      # dokładnie ten sam test co w stress teście
cat test.in
./wzo.e   < test.in
./brute.e < test.in
```

Poprawiasz `wzo.cpp`, odpalasz `bash stress.sh` jeszcze raz (sam
przekompiluje) i powtarzasz, aż będzie OK.

## Gdy coś nie działa

- **Licznik stoi w miejscu** → któryś program się zawiesił. `Ctrl+C`,
  potem sprawdź ręcznie na tym ziarnie (komendy wyżej), który nie odpowiada.
  Najczęściej: zła pętla albo program wczytuje inny format niż generator wypisuje.
- **`bits/stdc++.h` not found** → kompilujesz clangiem. Skrypt używa
  `g++-15`; jeśli masz inną wersję GCC, zmień `CXX=` na górze `stress.sh`.
- **Zadanie dopuszcza kilka poprawnych odpowiedzi** → samo porównanie plików
  nie wystarczy. Potrzebny jest osobny program (checker), który sprawdza, czy
  odpowiedź wzorcówki jest *poprawna*, a nie czy jest *identyczna* z brute'em.
