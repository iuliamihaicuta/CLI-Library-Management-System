**Nume: Mihaicuta Iulia**
**Grupa: 314CA**

## Tema 1 - The Library of HashBabel

### Descriere:

* Programul efectueaza diferite operatii ce stau la baza administrarii unei
biblioteci, pe baza unor operatii citite de la tastatura.

* functia validate_command(uint nr_arg, uint *idx1, uint *idx2) verifica daca
numarul argumentelor continute de comanda este corect si face parsarea acesteia.
Returneaza 1 daca comanda este corecta, sau 0 in caz contrar

* functia add_book() citeste numele unei carti si definitiile acestia de la
tastatura; creeaza o variabila de tip book_t in care stocheaza toate
definitiile cartii, si o adauga pe aceasta in library, variabila de tip
hashtable_t *, cu cheia book_name

* get_book() verifica daca cartea este in biblioteca cu ajutorul functiei
ht_has_key(), preia valoarea - ht_get(), si afiseaza numele, ratingul si
numarul de achizitii ale acesteia

* rmv_book() elimina o carte din biblioteca cu ajutorul functiei rmv(); rmv()
primeste ca argumente dictionarul library si numele cartii ce se doreste a fi
eliminata: verifica daca cartea exista - ht_has_key(), si o sterge din
memorie - ht_remove_entry()

* functia add_def() adauga o noua definitie la o carte deja existenta in
biblioteca - ht_put()

* get_def() afiseaza valoarea unei chei aflate intr-o carte specificata; folosim
functiile ht_has_key si ht_get

* rmv_def() elimina o valoare data dintr-o carte specificata; folosim functia
ht_remove_entry pentru a sterge elementul si free_def pentru a aloca memoria

* add_user() adauga un nou utilizator in baza de date; initializam variabila
user de tip user_t cu ajutorul functiei new_user(), si adaugam structura in
dictionarul users cu ht_put

* borrow_book() citeste de la tastatura numele utilizatorului ce doreste sa
imprumute cartea, numele acesteia si numarul de zile pe care se desfasoara
imprumutul; functia seteaza cartea ca fiind imprumutata (book->is_borrowed = 1),
si utilizatorului i se atribuie cartea (user->has_book = 1)

* return_book() citeste de la tastatura numele utilizatorului ce doreste sa
returneze o carte, numele cartii si numarul de zile de la imprumut; verificam
daca utilizatorul mai are acces la biblioteca (user->points < 0) si daca
acesta doreste sa returneze cartea imprumutata; calculam noul scor al
utilizatorului

* lost_book() raporteaza o carte ca pierduta si o elimina din datele bibliotecii
(functia rmv); scade 50 de puncte din punctajul utilizatorului si elibereaza
memoria folosita

* functia top_books() sorteaza cartile salvate in memorie in functie de rating,
numarul de achizitii si numele cartii; parcurgem manual toate elementele
dictionarului library si cream vectorul de structuri rank_t, book_rating, ce
contine datele necesare sortarii - functia new_userpoints(); folosind qsort()
si functiile de sortare compare_names(), compare_num(), compare_rating(), aducem
vectorul la forma dorita; afisam elementele si eliberam memoria

* top_users() sorteaza utilizatorii ce nu au pierdut acces la biblioteca in
ordinea punctelor acumulate; vectorul users_points de tip rank_t salveaza
numele si numarul de puncte aferent; sortam folosind qsort

* La finalul executiei programului toata memoria programului este eliberata
folosinf functia ht_tree ce apeleaza functia de free a valorii salvata in
structura dictionarului - free_book(), free_user(), free_def()


### Comentarii asupra temei

* Se pot adauga anumite verificari folosite in programarea defensiva, pentru a
asigura a buna functionare a programului