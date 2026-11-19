# Jak wgrać i pobrać paczkę

## Sposób 1 (zalecany): zgłoszenie "Backup" na Szkopule
1. Wejdź na https://szkopul.edu.pl/c/laboratorium-z-asd-2026/submit/191175/
2. Wyślij plik `asd-kolos.zip` (limit 2 MB, paczka ma znacznie mniej).
3. Na kolosie: Szkopuł -> Moje zgłoszenia -> Backup -> pobierz, potem:
   ```bash
   cd ~ && unzip ~/Pobrane/asd-kolos.zip      # albo ~/Downloads/asd-kolos.zip
   source ~/asd-kolos/szablony/setup.sh
   ```
4. **Sprawdź login i hasło do Szkopułu PRZED kolosem** (w sali nie zresetujesz hasła).

## Sposób 2 (zapasowy): strona na students
Instrukcja LK: https://lk.mimuw.edu.pl/pl/studenci/wlasna-strona-www
```bash
scp asd-kolos.zip bo479578@students.mimuw.edu.pl:~/
ssh bo479578@students.mimuw.edu.pl
mkdir -p ~/public_html && cd ~/public_html && unzip -o ~/asd-kolos.zip
chmod 711 ~ && chmod -R a+rX ~/public_html
```
Wtedy: https://students.mimuw.edu.pl/~bo479578/asd-kolos/NOTATKI.md (strona jest publiczna).
Na kolosie zip z tej strony pobierzesz przeglądarką albo przez `wget`.
