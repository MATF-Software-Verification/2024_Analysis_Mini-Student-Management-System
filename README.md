# Seminarski rad iz kursa: Verifikacija Softvera

## Opis projekta

Projekat koji je analiziran u okviru ovog seminarskog rada je:  
**Mini Student Management System (MSMS)**  

Ovaj projekat pruža osnovne funkcionalnosti za upravljanje akademskim podacima, kao što su:  
- Kreiranje i uređivanje predmeta.  
- Evidencija prisustva studenata.  
- Upravljanje profesorima i studentima.  
- Izvoz podataka u CSV format.  

Projekat je preuzet sa sledećeg GitHub repozitorijuma:  
[Mini Student Management System - GitHub Repozitorijum](https://github.com/quyenjd/Mini-Student-Management-System.git)  

**Analizirana grana:** `master`  
**Heš kod commit-a:** `[a5178934b6fa6e9bd3263ce7b18999209b3a6423]`  

---

## Priprema projekta za analizu na Linux sistemu

S obzirom da je originalni projekat razvijen za Windows operativni sistem, potrebno je izvršiti određene izmene kako bi se uspešno kompajlirao i pokrenuo na Linux sistemu.  

Pre pokretanja alata za analizu, potrebno je primeniti sve izmene koje su sačuvane u fajlu `custom.patch`.  
Ovaj fajl sadrži:  
- Izmene u originalnom kodu kako bi bio kompatibilan sa Linux okruženjem.  
- Dodatni `Makefile` koji omogućava kompilaciju projekta na Linuxu.  

#### Primena `custom.patch`:
```bash
cd Mini-Student-Management-System
git apply ../custom.patch
```


## Korišćeni alati za analizu

U analizi ovog projekta korišćeni su sledeći alati:

1. **Jedinični testovi i LCOV (Pokrivenost koda)**
   - Jedinični testovi su napisani koristeći `Catch2` biblioteku.  
   - Testovi su implementirani sa ciljem provere funkcionalnosti ključnih komponenti sistema (npr. `scoreboard.cpp`, `interface.cpp`, itd.).  
   - **LCOV alat** je korišćen za generisanje izveštaja o pokrivenosti koda na osnovu izvršenih jediničnih testova.  
   - Generisani su HTML izveštaji koji pokazuju koji delovi koda su pokriveni testovima.  
   - Preduslov za pokretanje:
     ```bash
     sudo apt install lcov
     cd unit_tests
     chmod +x run_tests_with_coverage.sh
     ```
    - Komanda za pokretanje:  
     ```bash
     ./run_tests_with_coverage.sh
     ```
2. **Clang-Tidy (Statička analiza)**  
   - Korišćen za identifikaciju potencijalnih problema u kodu, kao što su neinicijalizovane promenljive, nepravilan način oslobađanja memorije i generalne greške u pisanju C++ koda.  
   - Pokretanje alata i generisanje izveštaja izvršeno je putem pripremljene `run_clang.sh` skripte.  
   - Preduslov za pokretanje:
     ```bash
     sudo apt install clang-tidy
     cd clang
     chmod +x run_clang_tidy.sh
     ```
   - Komanda za pokretanje:  
     ```bash
     ./run_clang_tidy.sh
     ```

#**Napomena:** Pre pokretanja Valgrind alata (Memcheck i Callgrind) neophodno je prevesti program.

Program se prevodi korišćenjem `Makefile` komandom u sabmodulu Mini-Student-Management-System:

```bash
cd Mini-Student-Management-System
make
```


3. **Valgrind - Memcheck (Dinamička analiza)**  
   - Korišćen za detekciju curenja memorije i nepravilnog upravljanja memorijskim resursima.  
   - Generisani izveštaj sadrži informacije o `HEAP Summary`, `LEAK Summary` i detektovanim greškama.  
   - Pokretanje alata i generisanje izveštaja izvršeno je putem pripremljene `run_memcheck.sh` skripte.  
    - Preduslov za pokretanje:
     ```bash
        
     sudo apt install valgrind     
     cd valgrind/memcheck
     chmod +x run_memcheck.sh
     ```
   - Komanda za pokretanje:  
     ```bash
     ./run_memcheck.sh
     ```

4. **Valgrind - Callgrind (Analiza performansi)**  
   - Korišćen za profilisanje aplikacije i identifikaciju najintenzivnijih delova koda.  
   - Rezultati su analizirani pomoću `callgrind_annotate` alata, a vizualizacija je urađena sa `KCachegrind`.  
   - Pokretanje alata i generisanje izveštaja izvršeno je putem pripremljene `run_callgrind.sh` skripte.  
    - Preduslov za pokretanje:
     ```bash
     sudo apt install valgrind  
     sudo apt-get install kcachegrind
     cd valgrind/callgrind
     chmod +x run_callgrind.sh
     ```
    - Komanda za pokretanje:  
     ```bash
     ./run_callgrind.sh
     ```


---

## Zaključci

Na osnovu analize izvršene ovim alatima, identifikovani su sledeći problemi i predložena su sledeća poboljšanja:

- **Statička analiza (Clang-Tidy):**  
  - Detektovane su greške u alokaciji i oslobađanju memorije, korišćenju neinicijalizovanih promenljivih i nepravilnom korišćenju pokazivača.  
  - Preporučena je zamena `delete` sa `delete[]` gde je to neophodno i primena pametnih pokazivača za bolje upravljanje memorijom.  

- **Dinamička analiza (Memcheck):**  
  - Utvrđeno je ozbiljno curenje memorije, pri čemu su najveći deo memorije `Definitely lost` i `Indirectly lost`.  
  - Preporučeno je pravilno oslobađanje svih alociranih resursa i implementacija pametnih pokazivača.  

- **Analiza performansi (Callgrind):**  
  - Identifikovane su funkcije koje najviše utiču na performanse aplikacije, posebno one koje se nalaze u `csv.h` biblioteci.  
  - Predložene su optimizacije kao što su smanjenje poziva na `malloc()` i optimizacija operacija poređenja.  

- **Pokrivenost koda (LCOV):**  
  - Pokrivenost koda testovima je proverena i prikazana u generisanim HTML izveštajima.  

---
## Autor
**Nikola Stojanović** *1024/2024*