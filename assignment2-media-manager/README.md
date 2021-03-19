# Inlämningsuppgift 2 , 'Media Manager'
Mattias har bara tre sorters medier hemma, PlayStation2-spel, vinylskivor samt
böcker. Han behöver en mediehanterare för att hålla koll på sina media. I och
med att han älskar C++, textgränssnitt och program som körs från terminalen
blir din uppgift att skapa ett program som körs från terminalen där han kan
mata in sina olika media och sedan printa ut dem i sin  terminal. Du behöver
inte spara biblioteket på disk (om du inte vill).

#### [Mall att utgå från](https://bth.instructure.com/files/456965/download?download_frd=1)

Syfte
-----
Den här uppgiften syftar till att examinera dig på:
1. Förståelse för enumererade klasser (eng: enum classes)
2. Förståelse för klasser
3. Förståelse för operatoröverlagring
4. Förståelse för arv
5. Förståelse för polymorfism
6. Korrekt hantering av dynamiskt allokerat minne
7. Förståelse för pekare och referenser

## Innehåll
- [Inlämningsuppgift 2 , 'Media Manager'](#inlämningsuppgift-2--media-manager)
      - [Mall att utgå från](#mall-att-utgå-från)
  - [Syfte](#syfte)
  - [Innehåll](#innehåll)
  - [Vad ska du göra?](#vad-ska-du-göra)
  - [Du ska alltså](#du-ska-alltså)
    - [Ditt användargränssnitt](#ditt-användargränssnitt)
    - [Överblick](#överblick)
  - [Hur kommer man igång?](#hur-kommer-man-igång)
  - [Hur kompilerar jag och kör mitt program?](#hur-kompilerar-jag-och-kör-mitt-program)
  - [Tester](#tester)
  - [Inlämning och examination](#inlämning-och-examination)
  - [Klasserna och deras signaturer](#klasserna-och-deras-signaturer)
    - [För samtliga klasser](#för-samtliga-klasser)
    - [Medier](#medier)
      - [Media](#media)
      - [Book](#book)
      - [Ps2Game](#ps2game)
      - [Vinyl och dess hjälpklasser](#vinyl-och-dess-hjälpklasser)
    - [MediaManager](#mediamanager)
  - [Minnesläckor](#minnesläckor)
  - [Statisk kodanalys](#statisk-kodanalys)

Vad ska du göra?
----------------
En exempelkörning följer
nedan, ditt program behöver inte se exakt likadant ut, men det ska ha liknande
funktionalitet:

```
mattias@TRS-80:/tmp$ ./app
Välkommen till din mediehanterare! Vad vill du göra?
1. Lista samtliga media
2. Lista böcker
3. Lista ps2-spel
4. Lista vinyler
5. Lägg in en ny bok
6. Lägg in ett nytt ps2-spel
7. Lägg in en ny vinyl
8. Avsluta programmet
> 2

1. "Liftarens guide till galaxen" av "Douglas Adams"
   2 upplagan. 42 sidor. isbn: 9789132212697

Vad vill du göra? (skriv 'h' för att få upp alternativen igen)
> 5

Titel?
> Revelation Space
Författare?
> Alastair Reynolds
Upplaga?
> 1
Sidor?
> 576
ISBN?
> 9780575083097

Vad vill du göra? (skriv 'h' för att få upp alternativen igen)
> 2

1. "Liftarens guide till galaxen" av "Douglas Adams"
   2 upplagan. 42 sidor. isbn: 9789132212697
2. "Revelation Space" av "Alastair Reynolds"
   1 upplagan. 576 sidor. isbn: 9780575083097

Vad vill du göra? (skriv 'h' för att få upp alternativen igen)
> 8
```

Mattias har skickat med en klass, `Time`, för att enkelt kunna hantera tid,
exempelvis längd på en skiva eller ett spår.


## Du ska alltså
Du ska implementera ett bibliotek som sparar information om ett antal medier.
De medier ditt bibliotek ska kunna hantera är:

- Böcker - För en bok behöver titel, författare, ISBN-nummer, antal sidor och
  utgåva sparas.
- Vinylskivor - För en vinylskiva behöver titel och längd på skivan sparas.
- Spel för Playstation 2 - För ett spel behöver titel, studio (skapare) och
  utgivningsår sparas.

Eftersom alla dessa tre är någon form av media, och har information samt
funktioner som delas av alla tre, så kommer vardera media implementeras som
en egen klass (`Book`, `Vinyl` och `PS2Game`). De kommer ärva från den
abstrakta klassen `Media` som innehåller den information och de funktioner som
är generella för alla medier.

Du ska alltså skapa en arvshierarki med klasser enligt följande:

<img src="http://yuml.me/diagram/scruffy/class/[Media]^-[Ps2Game], [Media]^-[Book], [Media]^-[Vinyl]" >

Här är `Media` en abstrakt basklass vilken `Ps2Game`, `Book` och `Vinyl` ärver
från.

All mediainformation måste sparas någonstans, vilket ska hanteras av en klass
med namnet `MediaManager`. `MediaManager` sparar all media internt, och har
funktioner för att lägga till media, generera en utskriftssträng för att skriva
ut nuvarande media samt för att hämta en samling av önskad mediatyp.

Utöver de signaturer och krav som finns angivna nedan finns det inga krav på
hur klasserna fungerar eller vilka funktioner du har valt att lägga till.

### Ditt användargränssnitt
Du behöver utöver klasserna beskrivna ovan, skapa ett användargränssnitt där
användaren från terminalen kan lägga till, och visa innehållet i sin
mediesamling. Du får gärna skapa ditt användargränssnitt som en egen klass.

Du ska i main-funktionen i `main.cpp` starta ditt användargränssnitt. Ditt
användargränssnitt skall sedan interagera med en instans av `MediaManager` för
att hantera medier.  `MediaManager` har metoden, `printMedia()`, som är lämplig
att använda när man vill skriva ut sina medier. Get-metoderna för de olika
medietyperna är bra att använda om man bara vill printa ut en typ av media. Det
behöver inte finnas funktionalitet för att spara biblioteket till disk. Det
finns inga krav på gränssnittet utöver de som är stipulerade ovan.


### Överblick
Följande bild ger en överblick över de olika klasserna och deras relationer. Om
du är osäker på vad de olika symbolerna betyder, titta på Föreläsning 13.

![Klassdiagram](https://bth.instructure.com/files/455413/download?download_frd=1)

## Hur kommer man igång?
Testfallen som beskrivs nedan kommer till att börja med fallera. Förslagsvis
börjar du med att implementera en av de enklare klasserna, förslagsvis `Ps2Game`,
och löser sedan ett testfall i taget. Jobba dig uppifrån och ned mot noll
fallerande testfall.

## Hur kompilerar jag och kör mitt program?
I mappen du fått finns det en makefil för att bygga och testa ditt program.
Placera dina källfiler i katalogen `src/` och dina headerfiler i `include/` .
Bygg sedan ditt program genom att köra `make clean all`. Då kommer den
exekverbara filerna `app` och `runtests` byggas

För att få en överblick över hur de olika objektfilerna länkas samman till
exekverbara filer, se följande bild:

<img src="https://bth.instructure.com/files/456963/download?download_frd=1" alt="Komponentdiagram">
<style>
img:before {
    content: ' ';
    display: block;
    position: absolute;
    height: 50px;
    width: 50px;
    background-image: url(docs/componentDiagram.svg);
</style>

Om du vill köra ditt program, skriv då `./app` på linux/macOS. Använder du WSL
på windows är det en liten linuxmaskin du jobbar i och då gör du som på linux.

Om du vill debugga ditt program så följer det med två konfigurationer till VS
Code för det. En för att debugga ditt spel (den exekverbara filen `app`) och en
för att debugga testerna (den exekverbara filen `runtests`).

För att se hur du kommer igång och debuggar, titta på sidan "Debugga projekt
med make i Visual Studio Code" i moduler på Canvas

## Tester
Ett test som finns i katalogen `tests` kommer provköra din lösning för att se
att inlämningens regler är uppfyllda.

För att testa ditt program med testet finns det ett make-mål (eng. make
target). Kör det genom skriva `make clean test` i terminalen när du står i
samma katalog som makefilen.

***Testerna används för att verifiera att din inlämning faktiskt fungerar.
Ändra därför inte i test-main.cpp utan skapa istället en egen .cpp om du vill
testa din inlämning***.

Hur man testar med `Catch` ligger utanför scopet för denna kurs. För den
nyfikne som vill prova kan man dock titta på Catchs dokumentation:
https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

## Inlämning och examination
När alla tester går igenom utan minnesläckor, och du är redo att lämna in kör
du kommandot `make zip`, givet att du står i projektets mapp. Du kommer då få
en zipfil i projektmappen. Det är denna zipfil du ska lämna in på CodeGrade.
CodeGrade når du genom att trycka på den stora knappen längst ner här på sidan
märkt *"Ladda Inlämningsuppift 2 - Omexamination mars i ett nytt fönster"*.

Notera att det kan ta flera minuter för CodeGrade att bygga och testa din kod.
Om det inte ser ut att hända något kan det vara att testmiljön installeras för
att bygga och testa din kod.

För betyget G ska följande kriterier vara uppfyllda:

* Ditt program ska gå att kompilera.
* Alla test ska passera i testprogrammet (`runtests` / `make test`) utan att
  minnesläckor genereras.
* Din kod ska vara korrekt uppdelad i `.hpp`- och `.cpp`.filer. `.hpp` ska
  ligga i mappen `include` och `.cpp` i mappen `src`.
* Din kod ska hålla hålla god struktur. Kör `make static-code-analysis` och se
  till att du åtgärdat de varningar och fel som du känner till och kan fixa
  själv. Vissa varningar och fel har vi inte pratat om än och vissa är inte
  aktuella för uppgiften. Jag kommmer gå igenom output från static-code-analysis
  manuellt när ni lämnat in. Ni behöver inte ha noll varningar i
  static-code-analysis för att få ett G.
* Alla olika mediatyper ska lagras i en och samma dynamiskt allokerade array.
  Arrayen ska vara åtkomlig med en dubbelpekare som är medlem i klassen
  `MediaManager`.
* ***Inga medlemmar*** får vara av typen `std::vector` i klassen MediaManager.
* Minnet ska tas bort när det inte används. D.v.s Inga minnesläckor får
  förekomma. Kör `make memcheck` och säkerställ detta. CodeGrade kommer även
  köra detta.
* Ditt program ska gå att köra genom att starta det med `./app`. Ett
  användargränssnitt ska då starta. Du skall minst ha funktionalitet för:
  1. Lägga till medier (`Book`, `Vinyl`, `Ps2Game`)
  2. Lista innehållet i mediehanteraren
  3. Avsluta programmet

## Klasserna och deras signaturer
Nedan beskrivs de klasser och deras funktioner som du måste implementera för
att testerna skall kunna köras.

### För samtliga klasser
Utöver medlemsfunktionerna i klasserna listade nedan, skall `operator==` och
`operator!=` implementeras så att instanser av dina klasser kan jämföras.
Samtliga medlemsfunktioner som hämtar data och inte ska påverka objektet
(d.v.s. de ska inte ändra på medlemmarna) ***skall*** vara markerade `const`.
Notera att bara för att returvärdet på en funktion är `const` betyder inte det
att funktionen är det. På föreläsning 5 pratar vi om vad en medlemsfunktion
markerad som `const` innebär och hur man skapar dem.

### Medier
Mediehanteraren ska hantera tre medieklasser: `Vinyl`, `Book`, `Ps2Game`.  De
tre medieklasserna ska ärva från en gemensam abstrakt basklass `Media`.
Mediehanteraren (beskriven längre ned) kan då tack vare polymorfism lagra och
hantera medierna som klassen `Media` genom att jobba med pekare till `Media`.
Tack vare polymorfiska funktioner kommer subklassernas olika implementationer
av samma funktion i `Media` köras, även om de anropas genom `Media`. Om du är
osäker på polymorfism, kolla på föreläsning 8 och läs aktuella kapitel i
kurslitteraturen (se kurs-pm). Du kommer även behöva förstå vad en pekare och
en referens är, samt klasser och arv.

#### Media
Media skall ha en rent virtuell funktion `prettyPrint`, som skall returnera en
textsträng med mediets innehåll. Den ska sedan implementeras av subklasserna.
klassen `Book`s implementation skall då returnera författare, antal sidor etc. 

| returtyp             | namn        | parametrar | kommentar                                                                                                                        |
| -------------------- | ----------- | ---------- | -------------------------------------------------------------------------------------------------------------------------------- |
| `const std::string`  | prettyPrint | inga       |                                                                                                                                  |
| `const std::string&` | getTitle    | inga       | returnerar mediets titel. Kan implementeras i basklassen, eller i subklasserna funktionen sätts som virtuell eller rent virtuell |

Utöver metoden ovan ska de klasser som ärver från Media ha vissa metoder med
särskilda signaturer. Dessa används av testfall för att se att din lösning är
korrekt implementerad. Signaturerna följer nedan.

#### Book
| returtyp             | namn        | parametrar                                                                                            | kommentar                     |
| -------------------- | ----------- | ----------------------------------------------------------------------------------------------------- | ----------------------------- |
| -                    | Book        | `const std::string& title, const std::string& author,const std::string& isbn, int pages, int edition` | konstruktor                   |
| `const std::string&` | getAuthor   | inga                                                                                                  | returnerar bokens författare  |
| `const std::string&` | getIsbn     | inga                                                                                                  | returnerar bokens isbn-nummer |
| `int`                | getPages    | inga                                                                                                  | returnerar bokens antal sidor |
| `int`                | getEdition  | inga                                                                                                  | returnerar bokens utgåva      |
| `const std::string`  | prettyPrint | inga                                                                                                  |                               |

#### Ps2Game
| returtyp             | namn        | parametrar                                                      | kommentar                                 |
| -------------------- | ----------- | --------------------------------------------------------------- | ----------------------------------------- |
| -                    | Ps2Game     | `const std::string& title, const std::string& studio, int year` | konstruktor                               |
| `const std::string&` | getStudio   | inga                                                            | returnerar vilken studio som gjort spelet |
| `int`                | getYear     | inga                                                            | returnerar året spelet gavs ut            |
| `const std::string`  | prettyPrint | inga                                                            |                                           |

#### Vinyl och dess hjälpklasser

Vinyl har tre hjälpklasser. `Time` som följer med, `Track` och `VinylTypes`.
`VinylTypes` är en enum-klass med värdena `LONG_PLAY` och `EXTENDED_PLAY`.


`Track`-klassens signaturer följer nedan:
| returtyp             | namn      | parametrar                                    | kommentar               |
| -------------------- | --------- | --------------------------------------------- | ----------------------- |
| -                    | Track     | `const std::string& name, const Time& length` | konstruktor             |
| `const std::string&` | getName   | inga                                          | returnerar låtens titel |
| `const Time&`        | getLength | inga                                          | returnerar låtens längd |

Vinylklassen har följande signaturer:

| returtyp                    | namn        | parametrar                                                                                           | kommentar                             |
| --------------------------- | ----------- | ---------------------------------------------------------------------------------------------------- | ------------------------------------- |
| -                           | Vinyl       | `const std::string& title, VinylTypes type, int year,const std::string& artist, const Time& runtime` | konstruktor                           |
| `void`                      | addTrack    | `const Track& track`                                                                                 | lägg till en låt till skivan          |
| `int`                       | getYear     | inga                                                                                                 | returnerar året skivan gavs ut        |
| `VinylTypes`                | getType     | inga                                                                                                 | returnerar typ av skiva (EP eller LP) |
| `const std::string&`        | getArtist   | inga                                                                                                 | returnerar skivans artist             |
| `const Time&`               | getRuntime  | inga                                                                                                 | returnerar skivans speltid            |
| `const std::vector<Track>&` | getTracks   | inga                                                                                                 | returnerar skivans spår               |
| `const std::string`         | prettyPrint | inga                                                                                                 |                                       |


### MediaManager
Mediamanager är klassen som hanterar själva mediesamlingen. Den skall ha ***en*** (1)
dynamiskt allokerad array av typen `Media**` (d.v.s. en dynamiskt allokerad
array med pekare till Media-instanser) som medlem så att alla media-instanser
samlas i en och samma array. Du får alltså inte ha fler av en (ex en dynamiskt allokerad array per typ)En vector ***får ej användas*** som
medlemsvariabel. Detta då syftet med uppgiften (hantering av dynamiskt
allokerat minne, förståelse för polymorfism, förståelse för pekare) helt eller
delvis försvinner.

| returtyp               | namn         | parametrar            | kommentar                                                                                                                                                                                                                                                                             |
| ---------------------- | ------------ | --------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| -                      | MediaManager | `size_t size`         | konstruktor. Size är storleken på den dynamiska arrayen. Skickas ex 20 in ska det finnas plats för 20 medier.                                                                                                                                                                         |
| -                      | addMedia     | `Media* media`        | lägg ett medium till den dynamiska arrayen. Mediet kan vara av typen Book, Vinyl, Ps2Game. Här skickas det in som en pekare till basklassen                                                                                                                                           |
| -                      | addBook      | `const Book& book`    | lägg en bok till den dynamiska arrayen.                                                                                                                                                                                                                                               |
| -                      | addVinyl     | `const Vinyl& vinyl`  | lägg en vinyl till den dynamiska arrayen.                                                                                                                                                                                                                                             |
| -                      | addPs2Game   | `const Ps2Game& game` | lägg ett ps2-spel till den dynamiska arrayen.                                                                                                                                                                                                                                         |
| `std::string`          | printMedia   | inga                  | returnerar en sträng med mediehanterarens innehåll, formaterat på ett sätt som gör det lättförståligt från ett textgränssnitt. För inspriation, titta på exempelkörningen ovan. Ett tips är att använda polymorfism. Ni kanske redan har en funktion i subklasserna som kan användas? |
| `std::vector<Book>`    | getBooks     | inga                  | returnerar alla böcker som mediehanteraren lagrar                                                                                                                                                                                                                                     |
| `std::vector<Vinyl>`   | getVinyls    | inga                  | returnerar alla vinyler som mediehanteraren lagrar                                                                                                                                                                                                                                    |
| `std::vector<Ps2Game>` | getPs2Games  | inga                  | returnerar alla ps2-spel som mediehanteraren lagrar                                                                                                                                                                                                                                   |
| `**Media`              | getMedias    | inga                  | returnerar alla medier som mediehanteraren, dvs din dynamiskt allokerade array av `*Media` lagrar                                                                                                                                                                                     |

Notera att addMedia, addBook, addVinyl och addPs2Game tar emot en pekare
respektive en referens. Du kommer behöva göra en kopia och allokera i
MediaManager, förslagsvis m.h.a. copykonstruktorn. Du kan med andra ord
***inte*** bara ta pekaren i addMedia, eller ta addressen i övriga fall och
stoppa in i din dynamiska array. Om du känner dig osäker på hur du kan
konvertera mellan Media och subklasserna, eller vice versa, titta på
föreläsning 8 och läs aktuella kapitel i kurslitteraturen (se kurs-pm).

Minnesläckor
------------
*Minnesläckeskontroll sker inte automatiskt när du kör testerna. Detta måste
göras manuellt enligt nedan.*

Tack vare att vi använder oss av kompilatorn clang kan vi enkelt kontrollera om
vi har minnesläckor i vårt program. Om du kompilerar ditt program med `make
memcheck` kommer du baka in funktionalitet för att skriva ut felmeddelanden när
ditt program läcker minne. När du kör `make memcheck` kommer testprogrammet och
`app` kompileras med specialflaggor för minneskontroll. Efter det kommer
testerna köras. Om du har minnesläckor, kommer du efter att testerna körts, att
få en utskrift i stil med:

```
===============================================================================
All tests passed (158 assertions in 5 test cases)


=================================================================
==4734==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 128000 byte(s) in 16 object(s) allocated from:
    #0 0x49ddcd in malloc (/mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/runtests+0x49ddcd)
    #1 0x7fda6e85ac28 in operator new(unsigned long) (/lib/x86_64-linux-gnu/libstdc++.so.6+0xaac28)
    #2 0x5c8dc6 in void ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____0<42, MediaManager, Media, Book, Ps2Game, Vinyl, VinylTypes, Track>() /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/testMediaManager.cpp:149:26
    #3 0x68160c in Catch::TestInvokerAsFunction::invoke() const /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:14213:9
    #4 0x6714d7 in Catch::TestCase::invoke() const /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:14056:15
    #5 0x671324 in Catch::RunContext::invokeActiveTestCase() /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:12915:27
    #6 0x66c892 in Catch::RunContext::runCurrentTest(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&) /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:12888:17
    #7 0x66a658 in Catch::RunContext::runTest(Catch::TestCase const&) /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:12649:13
    #8 0x6783f6 in Catch::(anonymous namespace)::TestGroup::execute() /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:13243:45
    #9 0x6765db in Catch::Session::runInternal() /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:13449:39
    #10 0x675fc5 in Catch::Session::run() /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:13405:24
    #11 0x70f531 in int Catch::Session::run<char>(int, char const* const*) /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:13127:30
    #12 0x6b257f in main /mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/test/include/catch.hpp:17392:29
    #13 0x7fda6e4170b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)

SUMMARY: AddressSanitizer: 264000 byte(s) leaked in 33 allocation(s).
make: *** [makefile:86: memcheck] Error 1
```

* #0 Berättar att det är `malloc` som allokerat minnet som läcker. Det säger
  oss inte så mycket.
* #1 Berättar att `malloc` anropats av `new`. Läckan härstammar alltså från när
  vi anropar `new` ngnstans.
* #2 Berättar att läckan sker på rad 149 i `test/testMediaManager.cpp`. Tittar
  vi på den raden ser vi att vi skapar en MediaManager där. Alltså sker läckan
  i konstruktorn. I konstruktorn hittar vi mycket riktigt att vi gör ett anrop
  till `new` för att allokera minne. Det minnet tar vi aldrig bort i 
  destruktorn. Här har vi funnit läckan.
* #3 och nedåt innehåller *call-stacken* från testramverket.

Minnesläckor i ditt program kan också hittas när man kör testerna. Du får då en
eller flera liknande utskrifter i din terminal beroende på hur många gånger
ditt program läckt under testkörningarna.

Statisk kodanalys
-----------------
*Statisk kodanalys sker inte automatiskt när du kör testerna. Detta måste göras
manuellt enligt nedan.*

Tack vare att vi använder oss av kompilatorn clang kan vi enkelt kolla efter
vanliga fel i vår källkod. Det kallas för *linting* eller statisk kodanalys.
D.v.s. analys av koden man kan göra utan att köra koden (analys som kräver att
koden körs kallas för dynamisk kodanalyas).

För att köra statisk kodanalys kör vi make-målet `static-code-analysis`. En
exempelkörning kan se ut såhär:

```
mattias@TRS-80:/tmp/dv1626-assignment2-media-manager-$ make static-code-analysis 
+---------------------------------------------------------------------
| Environment detected as Linux/WSL
| Description:  Ubuntu 20.04.1 LTS
| * compiler: clang-10
| * linker: clang-10
| * linter: clang-tidy
| * home: /home/mattias
| * fixtures: 
| * memcheck compile and link flags set to: "-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls"
| * asan flags set to: "symbolize=1 ASAN_SYMBOLIZER_PATH="
+---------------------------------------------------------------------
clang-tidy --header-filter=".*.hpp" --warnings-as-errors='*' --checks="cppcoreguidelines-*, bugprone*, diagnostic-*, -clang-diagnostic-c++20-extensions, analyzer-*, readability-*, -cppcoreguidelines-pro-bounds-pointer-arithmetic, -cppcoreguidelines-special-member-functions, -cppcoreguidelines-owning-memory" src/Ps2Game.cpp src/Time.cpp main.cpp --  -Iinclude  -Itest/include  -Iexternal/fmt/include
1973 warnings generated.
8868 warnings generated.
8868 warnings generated.
/mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/src/Ps2Game.cpp:15:7: error: implicit conversion 'const Ps2Game *' -> bool [readability-implicit-bool-conversion,-warnings-as-errors]
  if (dynamic_cast<const Ps2Game*>(&rhs)) {
      ^
                                         != nullptr
/mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/include/Ps2Game.hpp:13:8: error: annotate this function with 'override' or (rarely) 'final' [cppcoreguidelines-explicit-virtual-functions,-warnings-as-errors]
  bool operator==(const Media& rhs) const ;
       ^
                                          override
/mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/include/Ps2Game.hpp:14:8: error: annotate this function with 'override' or (rarely) 'final' [cppcoreguidelines-explicit-virtual-functions,-warnings-as-errors]
  bool operator!=(const Media& rhs) const ;
       ^
                                          override
/mnt/c/Users/Mattias/repos/dv1626-assignment2-media-manager-/include/Ps2Game.hpp:18:15: error: annotate this function with 'override' or (rarely) 'final' [cppcoreguidelines-explicit-virtual-functions,-warnings-as-errors]
  std::string prettyPrint() const ;
              ^
                                  override
Suppressed 8864 warnings (8864 in non-user code).
Use -header-filter=.* to display errors from all non-system headers. Use -system-headers to display errors from system headers as well.
4 warnings treated as errors
make: *** [makefile:90: static-code-analysis] Error 4
```

Här ser vi fyra varningar med förbättringar som kan göras på vår kod. I det här
fallet så ser vi att vi glömt `override` på de funktioner som overridear
funktioner i basklassen. Missar man `override` finns det en risk att man skapar
en överlagring istället för en override vilket gör att den inte kommer gå att
anropa via en pekare eller referens till basklassen. Den andra varningen är en
*best practice*. Om man inte har med `nullptr` i ifsatsen kan läsaren bli lurad
att det är något annat man jämför. Om man vill ha mer information om varför man
får varningen, vad som är problematiskt, och hur man kan åtgärda varningen så
finns det bra dokumentation för varje varning. Enklaste sättet är att googla på
"taggen" som varningen har. I vårt fall
`cppcoreguidelines-explicit-virtual-functions` och
`readability-implicit-bool-conversion`.

Med verktyg som `clang-tidy` hittas ofta många buggar som annars hade lett till
konstiga fel. Mycket av det man kan få komplettering på hittas vid den statiska
kodanalysen. Se därför till att output från den statiska kodanalysen är så ren
som möjligt. Åtgärda allt ni kan åtgärda.
