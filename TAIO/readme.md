# Instrukcja budowania i uruchamiania projektu

## Budowanie
Aby zbudowa� i uruchomi� projekt, upewnij si� �e masz zainstalowane: Visual Studio 2022

Nast�pnie otwieramy i budujemy rozwi�zanie.

## Uruchamianie
Aplikacja jest aplikacj� konsolow�. Aby j� uruchomi� musimy poda� 1-2 pliki tekstowe jako argumenty. Program pozwoli nam na wczytanie i wybranie graf�w z odpowiednich plik�w, oraz wykonanie na nich operacji.

## Przyk�adowe wywo�anie programu
```
taio.exe data/test1.txt data/test2.txt
```

## Format pliku
### Przykladowy plik z jednym grafem
```
4
0 0 1 0
0 1 0 0
0 0 0 0
0 1 1 0
```
### Przyk�adowy plik z wieloma grafami
```
2
3
1 1 1
1 1 1
1 1 1

2
0 1
1 0
```

### Przyk�adowy plik z wieloma grafami i ich opisem
```
2
3
1 1 1
1 1 1
1 1 1
some text 
which describes graph

2
0 1
1 0
```