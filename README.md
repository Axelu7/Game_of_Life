1. Introducere și Autori
Prezentul raport detaliază un proiect universitar axat pe implementarea și explorarea Jocului Vieții al lui Conway, o simulare de automat celular. Proiectul demonstrează o progresie de la simularea fundamentală a regulilor jocului la optimizarea structurilor de date și aplicarea conceptelor de teorie a grafurilor. Acesta servește ca o demonstrație practică a principiilor fundamentale în proiectarea algoritmilor și utilizarea structurilor de date complexe. Lucrarea a fost elaborată de George-Vlad Popescu și Andra Băltoiu  în cadrul disciplinei "Proiectarea algoritmilor", subliniind aplicarea practică a cunoștințelor teoretice în contextul modelării computaționale.   

2. Prezentare Generală a Jocului Vieții al lui Conway
Jocul Vieții al lui Conway este un "joc fără jucători" sau, mai precis, un automat celular. Acesta reprezintă un model matematic conceput pentru a descrie funcționarea sistemelor de calcul, atât hardware, cât și software. Jocul a fost creat de matematicianul John Conway.   

Simularea se desfășoară pe o grilă bidimensională de celule pătrate, fiecare celulă putând fi într-una din două stări: "vie" (reprezentată prin caracterul 'X') sau "moartă" (reprezentată prin caracterul '4'). Evoluția grilei are loc în pași de timp discreți, denumiți generații. În fiecare generație, celulele interacționează cu cele opt celule vecine, influențând tranzițiile de stare ale acestora.   

Regulile fundamentale care guvernează nașterea și moartea celulelor sunt simple, dar determină comportamente complexe :   

Subpopulare: Orice celulă vie cu mai puțin de doi vecini în viață moare.   
Supraviețuire: Orice celulă vie cu doi sau trei vecini vii trăiește în continuare.   
Suprapopulare: Orice celulă vie cu mai mult de trei vecini vii moare.   
Reproducere: Orice celulă moartă cu exact trei vecini vii devine o celulă vie.   
În ciuda simplității acestor reguli, Jocul Vieții manifestă comportamente emergente remarcabil de complexe. În funcție de configurația inițială a grilei, pot apărea tipare stabile, structuri oscilante (cum ar fi "blinkere") sau chiar "nave spațiale" care se deplasează prin grilă. Semnificația teoretică a jocului este profundă, deoarece este complet Turing, ceea ce înseamnă că poate simula orice calcul pe care o mașină Turing universală îl poate efectua. Această proprietate demonstrează puterea sa ca model computațional. Progresia de la reguli simple la comportamente emergente complexe subliniază principiile fundamentale ale automatelor celulare și relevanța lor în înțelegerea sistemelor complexe. Implementarea acestui proiect implică nu doar codificarea unui set de reguli, ci și angajarea cu concepte fundamentale din teoria computațională, știința complexității și proiectarea sistemelor, conferind proiectului o valoare academică și intelectuală superioară unei simple exerciții de programare.   

3. Structura Proiectului și Detalii de Implementare
Întregul proiect este implementat în limbajul de programare C, conform cerințelor specificate ("In fisierele C se afla functiile pentru fiecare task"). Această alegere a limbajului indică un accent pe controlul de nivel scăzut, gestionarea memoriei și optimizarea performanței, obiective comune în cursurile universitare de proiectare a algoritmilor.

Proiectul este structurat modular, cu fișiere C sau funcții distincte dedicate fiecărei sarcini specifice. Această abordare promovează lizibilitatea, mentenabilitatea și reutilizarea codului, aderând la bunele practici de inginerie software.

Pentru compilarea și execuția proiectului, sunt necesare următoarele instrucțiuni:

Precondiții: Un compilator C standard, cum ar fi GCC (GNU Compiler Collection), este necesar pentru a construi proiectul.
Instrucțiuni de Compilare: Pentru a compila fișierele sursă într-un executabil, se poate utiliza o comandă similară cu următoarea (presupunând că main.c coordonează apelurile către funcțiile definite în fișierele taskX.c pentru fiecare sarcină):bash gcc -o gameoflife main.c task1.c task2.c task3.c task4.c -Wall -Wextra
Rularea Aplicației: După compilare, programul poate fi executat, specificând argumentele necesare pentru fișierele de intrare și ieșire, care variază ușor în funcție de sarcină. De exemplu:
./gameoflife <cale_fisier_intrare> <cale_fisier_iesire>
```

4. Task 1: Simularea de Bază a Jocului Vieții
Obiectivul principal al Taskului 1 este implementarea regulilor fundamentale ale Jocului Vieții al lui Conway. Pornind de la o configurație inițială a grilei, programul trebuie să simuleze și să genereze un număr specificat de generații ulterioare (K).   

Grila de joc este reprezentată ca o matrice bidimensională de caractere, având dimensiunile N rânduri pe M coloane. Celulele vii sunt reprezentate explicit prin caracterul 'X', în timp ce celulele moarte sunt indicate prin caracterul '4'. Această alegere specifică a caracterelor este esențială pentru analiza corectă a intrărilor și generarea precisă a ieșirilor. Alegerea explicită a caracterelor 'X' pentru celule vii și '4' pentru celule moarte, spre deosebire de reprezentări mai comune precum '0'/'1' sau '.'/'#', reprezintă un detaliu de implementare specific care dictează logica de parsare și generare a ieșirilor programului. Acest aspect subliniază importanța aderării stricte la specificații în proiectele tehnice și implică necesitatea unei testări precise, conform acestor alegeri de caractere. Orice abatere în citirea intrărilor sau scrierea ieșirilor programului ar duce la rezultate incorecte sau eșecuri la testare.   

Formatul fișierului de intrare  este structurat după cum urmează:   

Linia 1: T - Numărul sarcinii (întotdeauna '1' pentru acest task).   
Linia 2: N M - Dimensiunile grilei (N rânduri, M coloane).   
Linia 3: K - Numărul de generații de calculat.   
Liniile următoare: Matricea N x M inițială, reprezentând Generația 0.   
Programul scrie generațiile calculate într-un fișier de ieșire. Matricea fiecărei generații este tipărită consecutiv, cu o linie goală separând matricea unei generații de următoarea.   

Un exemplu ilustrativ al comportamentului așteptat este prezentat în tabelul de mai jos:

Intrare 	Ieșire 
```	```
1	++++++
6 6	+++X++
2	++XXX+
++++++	+++X++
++++X+	++++++
++XX++	++++++
+++X++	
+X++++	++++++
++++++	++XXX+
```	++X+X+
++XXX+
++++++
++++++
```
  
Acest tabel demonstrează vizual transformarea grilei de la o stare inițială prin generații succesive, servind ca o referință clară pentru înțelegerea cerințelor sarcinii și verificarea corectitudinii implementării.

5. Task 2: Stocarea Eficientă a Generațiilor
Stocarea fiecărei generații ca o matrice completă N x M este ineficientă, în special pentru grile mari sau un număr mare de generații. Acest lucru se datorează faptului că, în majoritatea scenariilor, doar o mică parte a celulelor își modifică starea de la o generație la alta. Taskul 2 abordează această problemă prin concentrarea pe stocarea eficientă a diferențelor.   

Pentru a optimiza stocarea, proiectul utilizează o stivă de liste :   

Fiecare element adăugat în stivă corespunde unei singure generații.   
Fiecare element al generației este reprezentat de o listă de coordonate (l, c). Aceste coordonate identifică în mod specific celulele care și-au schimbat starea față de generația imediat anterioară.   
l indică indicele rândului (rândurile sunt numerotate de sus), iar c indică indicele coloanei (coloanele sunt numerotate din stânga).   
În cadrul fiecărei liste, coordonatele trebuie să fie strict ordonate: mai întâi după indicele rândului, apoi după indicele coloanei. Această ordonare asigură o ieșire deterministă și simplifică procesarea.   
Elementele listei stochează doar coordonatele (l, c) ale celulelor modificate; ele nu stochează noua stare (vie/moartă) a celulei. Starea poate fi dedusă prin aplicarea secvenței de modificări de la generația inițială.   
Formatul fișierului de intrare pentru Task 2 este identic cu cel al Taskului 1.   

Conținutul stivei, după ce au fost calculate K generații, este scris într-un fișier de ieșire. Formatul este k: (l_i, c_i), unde k este numărul generației (de la 1 la K), iar (l_i, c_i) sunt coordonatele celulelor care și-au modificat starea în acea generație.   

Un exemplu de ieșire care ilustrează conținutul stivei este prezentat în tabelul de mai jos:

Generația 0	Generația 1	Generația 2	Conținutul stivei la Generația 1 și 2 
+++++	+++++	+++++	1: (1,2) (3,2) (3,3)
+X+++	+XX++	+XX++	2: (2,1) (2,2) (2,3) (3,1)
+XX++	+XX++	+++X+	
+++X+	++X++	+XX++	
+++++	+++++	+++++	
  
Acest tabel este esențial pentru ilustrarea conceptului de stocare eficientă. Prin afișarea stărilor originale ale grilei alături de lista compactă a doar coordonatelor modificate, se demonstrează clar avantajul de economisire a spațiului al acestei structuri de date. De asemenea, se arată explicit ordonarea necesară a coordonatelor în cadrul fiecărei liste.

O cerință bonus a proiectului implică implementarea operației inverse. Aceasta presupune ca, având conținutul unei stive pentru K generații (adică toate listele diferențiale) și matricea finală corespunzătoare Generației K, programul să reconstruiască și să afișeze matricea inițială (Generația 0). Includerea unei sarcini bonus pentru operația inversă, care reconstruiește Generația 0 din Generația K și stiva de diferențe, indică o proiectare robustă și reversibilă a structurii de date. Acest lucru testează nu doar capacitatea de a stoca diferențele, ci și de a le aplica în sens invers, demonstrând o înțelegere mai profundă a gestionării stărilor, a integrității datelor și a naturii bidirecționale a tranzițiilor de stare. Această sarcină bonus servește ca o validare critică a implementării de bază a Taskului 2, arătând că structura de date aleasă este suficient de robustă pentru reconstrucția înapoi, care este adesea o provocare algoritmică mai complexă.   

6. Task 3: Reguli Alternative și Analiza Arborelui Generațiilor
Taskul 3 își propune să analizeze și să compare dinamica Jocului Vieții al lui Conway sub un set alternativ de reguli ("Regula B") cu regulile standard. Această comparație este facilitată prin construirea și traversarea unei structuri de arbore binar care reprezintă căile generaționale divergente.   

Noua regulă, denumită "Regula B", simplifică condiția de reproducere a Jocului Vieții: "Orice celulă cu exact doi vecini vii devine celulă vie". Aceasta contrastează cu regula standard de reproducere, care necesită exact trei vecini vii.   

Pentru a observa diferențele dintre cele două variante ale jocului, se utilizează o reprezentare sub formă de arbore binar :   

Nodul Rădăcină: Rădăcina arborelui reprezintă configurația inițială a grilei (Generația 0). Spre deosebire de nodurile ulterioare, aceasta stochează coordonatele tuturor celulelor vii din configurația inițială.   
Logica de Ramificare: Pentru fiecare nod din arbore, sunt generate două noduri copil:
Nodul Copil Stânga: Reprezintă următoarea generație obținută prin aplicarea noii "Reguli B".   
Nodul Copil Dreapta: Reprezintă următoarea generație obținută prin aplicarea regulilor standard ale Jocului Vieții. Acest proces de ramificare este aplicat recursiv pentru toate nodurile nou create, extinzând arborele până la o adâncime specificată K (numărul de generații). Aceasta creează un arbore binar complet, unde fiecare cale de la rădăcină reprezintă o secvență unică de aplicări ale regulilor. Utilizarea unui arbore binar pentru a compara două seturi de reguli distincte reprezintă o abordare sofisticată pentru analiza divergenței dinamicii sistemului. Această structură permite o explorare structurată și ramificată a spațiului de stări sub diferite condiții, oferind o metodă puternică pentru analiza comparativă care depășește simplele simulări liniare.   
Conținutul nodurilor arborelui este similar cu cel din Taskul 2: fiecare nod non-rădăcină stochează o listă de coordonate ale celulelor care și-au modificat starea față de nodul părinte. Acest mecanism eficient de stocare este reutilizat de la Taskul 2.   

Formatul fișierului de intrare pentru Task 3 rămâne consistent cu sarcinile anterioare.   

Arborele generat trebuie parcurs în preordine (Rădăcină, Subarbore Stânga, Subarbore Dreapta). Pentru fiecare nod vizitat în timpul traversării, matricea completă a grilei corespunzătoare (nu doar lista de modificări) este reconstruită și scrisă în fișierul de ieșire. De exemplu, pentru K=1, secvența de ieșire ar fi: 1) Matricea Generației 0 (rădăcina), 2) Matricea Generației 1 utilizând Regula B (copilul stânga), 3) Matricea Generației 1 utilizând Regulile Standard (copilul dreapta). Cerința de a afișa matricile complete pentru fiecare nod, chiar dacă nodurile stochează doar diferențe de coordonate, implică faptul că programul trebuie să poată reconstrui starea completă a grilei la cerere. Aceasta reconfirmă importanța și reutilizabilitatea mecanismului de stocare eficient dezvoltat în Taskul 2 și capacitatea sa de a facilita reconstrucția stării prin aplicarea iterativă a modificărilor. Pentru a reconstrui matricea completă pentru orice nod dat din arbore, programul trebuie să pornească de la matricea Generației 0 și să aplice secvența de modificări de coordonate stocate în listele diferențiale de-a lungul căii de la rădăcină la nodul curent.   

7. Task 4: Drumuri Hamiltoniene în Grafurile Jocului
Pentru fiecare nod (reprezentând o generație specifică) din arborele binar construit în Taskul 3 (până la generația K), obiectivul este de a determina și de a afișa cel mai lung drum Hamiltonian găsit în reprezentarea grafică a celulelor vii ale acelei generații.   

Reprezentarea grafică a unei generații se realizează astfel:

Vârfuri: Fiecare celulă vie ('X') din grila Jocului Vieții este considerată un vârf în graf.   
Muchii: O muchie există între două vârfuri dacă celulele vii corespondente sunt vecine directe pe grilă (adică, partajează o latură sau un colț).   
Conectivitate: Graful unei generații poate fi neconex dacă conține mai multe grupuri separate de celule vii. În astfel de cazuri, graful constă din multiple componente conexe.   
Definițiile relevante pentru această sarcină sunt :   

Lanț/Drum: O succesiune de vârfuri cu proprietatea că orice pereche de vârfuri consecutive în această succesiune sunt adiacente.
Lanț Elementar: Un lanț în care toate vârfurile sunt distincte (niciun vârf nu este vizitat mai mult de o dată).
Lanț Hamiltonian: Un lanț elementar care conține toate vârfurile grafului exact o dată. Acest concept se aplică și componentelor conexe individuale dintr-un graf neconex.
Criteriile de selecție a drumului (reguli de departajare) sunt cruciale pentru a asigura o ieșire deterministă și unică atunci când există mai multe drumuri Hamiltoniene valide sau componente :   

Prioritate Lungime Maximă: Criteriul principal este găsirea drumului Hamiltonian cu cea mai mare lungime (numărul de muchii).   
Selecția Componentei: Dacă graful este neconex și multiple componente conexe conțin drumuri Hamiltoniene, se alege componenta al cărei cel mai lung drum Hamiltonian este global cel mai lung.   
Nodul de Start (Indice Rând): Dacă există mai multe drumuri de aceeași lungime maximă (fie într-o singură componentă, fie între componente dacă drumurile lor cele mai lungi sunt egale), se selectează drumul care începe dintr-un nod cu cel mai mic indice de rând.   
Nodul de Start (Indice Coloană): Dacă persista o egalitate după considerarea indicelui de rând, se alege drumul al cărui nod de start are cel mai mic indice de coloană.   
Ordonarea Întregii Secvențe: Acest principiu de prioritizare a indicilor de rând mai mici, apoi a indicilor de coloană mai mici, se aplică în mod consecvent întregii secvențe de vârfuri din drumul ales, nu doar nodului de start.   
Absența Drumului: Dacă nu există niciun drum Hamiltonian în graf sau în oricare dintre componentele sale conexe, ieșirea trebuie să fie -1.   
Problema găsirii drumurilor Hamiltoniene este NP-completă. Cerința proiectului de a găsi cel mai lung drum Hamiltonian, combinată cu regulile complexe de departajare, indică o provocare algoritmică semnificativă. Această sarcină este probabil cea mai intensivă din punct de vedere computațional și necesită o înțelegere aprofundată a algoritmilor grafici, posibil implicând backtracking cu prunări agresive sau algoritmi de aproximare pentru grile foarte mari.

Formatul fișierului de intrare pentru Task 4 este același cu cel al sarcinilor anterioare.   

Pentru fiecare nod (generație) din arborele generat în Taskul 3, fișierul de ieșire va conține :   

L_i (Lungimea celui mai lung drum Hamiltonian găsit pentru nodul i).   
(l_j, c_j) (Secvența de coordonate (rând, coloană) pentru fiecare vârf j din drum, unde j variază de la 1 la L+1).   
Exemplele detaliate din documentația proiectului, inclusiv scenarii complexe cu departajare și cazuri în care nu există un drum Hamiltonian, sunt prezentate în tabelele următoare pentru a clarifica formatul de ieșire și regulile de selecție.

Intrare 	Ieșire 
```	```
4	4
6 7	(1,3) (2,4) (3,4) (3,3) (3,2)
1	9
+++++++	(1,3) (1,4) (2,4) (2,5) (3,4) (3,5) (4,4) (3,3) (3,2) (4,2)
+++X+++	4
++++X++	(2,2) (3,3) (2,4) (3,4) (4,3)
++XXX++	```
+++++++	
+++++++	
```	
  
Intrare 	Ieșire 
```	```
4	4
6 7	(1,1) (1,2) (1,3) (1,4) (1,5)
0	```
+++++++	
+XXXXX+	
+++++++	
+++++X+	
+++XXX+	
+++++++	
```	
  
Intrare 	Ieșire 
```	```
4	-1
6 7	```
0	
+++++++	
+X+X+++	
++X+X++	
++XXX++	
+X+++X+	
+++++++	
```	
  
Exemplul 3 demonstrează o situație în care nu există un drum Hamiltonian. Se observă că în acest caz, există trei noduri "marginale" (noduri cu grad 1, având o singură muchie). Prezența a mai mult de două astfel de noduri într-un graf împiedică existența unui drum Hamiltonian, deoarece un drum trebuie să viziteze fiecare vârf exact o dată, iar nodurile cu grad 1 acționează ca "puncte moarte" care nu pot fi integrate într-o singură cale continuă care să acopere toate nodurile. Această observație demonstrează o înțelegere teoretică a proprietăților grafurilor relevante pentru drumurile Hamiltoniene, dincolo de simpla implementare a unui algoritm de căutare.   

8. Îmbunătățiri Viitoare și Extensii Potențiale
Proiectul actual poate fi extins și îmbunătățit în mai multe direcții:

Interfață Grafică (GUI): Dezvoltarea unei interfețe grafice ar oferi o vizualizare mai intuitivă și interactivă a simulării Jocului Vieții, permițând utilizatorilor să definească ușor modele inițiale, să controleze generațiile și să observe comportamentele emergente.
Optimizarea Performanței: Explorarea tehnicilor algoritmice și a structurilor de date mai avansate pentru gestionarea grilelor extrem de mari sau a unui număr foarte mare de generații, în special pentru problema NP-completă a drumului Hamiltonian din Taskul 4 (de exemplu, procesare paralelă, algoritmi grafici specializați sau euristici pentru probleme la scară largă).
Recunoașterea și Analiza Modelelor: Implementarea algoritmilor pentru detectarea și clasificarea automată a modelelor cunoscute din Jocul Vieții (de exemplu, blinkere, glidere, nave spațiale, oscilatoare), oferind o analiză analitică mai profundă a simulării.
Editor de Seturi de Reguli Personalizate: Extinderea Taskului 3 prin permiterea utilizatorilor să definească și să experimenteze cu propriile seturi de reguli pentru automate celulare, dincolo de "Regula B" și setul standard, permițând o explorare mai amplă a dinamicii emergente.
Procesare Paralelă: Investigarea utilizării tehnicilor de multithreading sau de calcul paralel pentru a accelera calculul generațiilor, în special pentru sarcinile intensive computațional, cum ar fi actualizările grilei sau traversările grafurilor.
9. Referințe și Mulțumiri
Acest proiect a fost realizat în cadrul disciplinei "Proiectarea algoritmilor" și se aduc mulțumiri profesorilor și asistenților universitari care au ghidat dezvoltarea sa. Se recunoaște contribuția lui John Conway ca și creator al Jocului Vieții și se acknowledgează fundațiile teoretice ale automatelor celulare. Pentru o înțelegere mai aprofundată a structurilor complexe ce pot fi generate în joc, se recomandă consultarea cărții "Conway's Game of Life".   

10. Informații despre Licență
Codul sursă al proiectului este distribuit sub o licență open-source (de exemplu, Licența MIT, Licența Apache 2.0, GPLv3). Aceasta informează utilizatorii despre drepturile și responsabilitățile lor atunci când utilizează, modifică sau distribuie codul.
