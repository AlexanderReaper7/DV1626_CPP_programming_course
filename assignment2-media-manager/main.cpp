#include <iostream>
#include <string>
#include "MediaManager.hpp"

const int LIB_SIZE = 100;
const std::string SHOW_COMMANDS_KEY = "h";
const std::string PRINT_ALL_KEY = "1";
const std::string PRINT_BOOKS_KEY = "2";
const std::string PRINT_PS2GAMES_KEY = "3";
const std::string PRINT_VINYLS_KEY = "4";
const std::string ADD_BOOK_KEY = "5";
const std::string ADD_PS2GAME_KEY = "6";
const std::string ADD_VINYL_KEY = "7";
const std::string EXIT_KEY = "8";


void printChoises() {
    std::cout << "Välkommen till din mediehanterare! Vad vill du göra?\n"
    << PRINT_ALL_KEY << ". Lista samtliga media\n"
    << PRINT_BOOKS_KEY << ". Lista böcker\n"
    << PRINT_PS2GAMES_KEY << ". Lista ps2-spel\n"
    << PRINT_VINYLS_KEY << ". Lista vinyler\n"
    << ADD_BOOK_KEY << ". Lägg in en ny bok\n"
    << ADD_PS2GAME_KEY << ". Lägg in ett nytt ps2-spel\n"
    << ADD_VINYL_KEY << ". Lägg in en ny vinyl\n"
    << EXIT_KEY << ". Avsluta programmet\n";
}

std::string getCommand() {
    std::cout << "Vad vill du göra? (skriv '" << SHOW_COMMANDS_KEY << "' för att få upp alternativen igen)\n";
    std::string output;
    std::cin >> output;
    return output;
}

void printAllCommand(MediaManager& mmn) { // print media
    std::cout << mmn.printMedia() << "\n";
}
void printBooksCommand(MediaManager& mmn) { // print books
    auto v = mmn.getBooks();
    for (auto book: v) {
        std::cout << book.prettyPrint() << "\n";
    }
    std::cout << "\n";
}
void printGamesCommand(MediaManager& mmn) { // print games
    auto v = mmn.getPs2Games();
    for (auto game: v) {
        std::cout << game.prettyPrint() << "\n";
    }
    std::cout << "\n";
}
void printVinylsCommand(MediaManager& mmn) { // print vinyls
    auto v = mmn.getVinyls();
    for (auto vinyl: v) {
        std::cout << vinyl.prettyPrint() << "\n";
    }
    std::cout << "\n";
}
void AddBookCommand(MediaManager& mmn) { // add book
    std::string title;
    std::string author;
    std::string isbn;
    std::string pg;
    std::string ed;
    std::cout << "Titel?\n";
    std::cin >> title;
    std::cout << "Författare?\n";
    std::cin >> author;
    std::cout << "upplaga?\n";
    std::cin >> ed;
    int edition = std::stoi(ed);
    std::cout << "sidor?\n";
    std::cin >> pg;
    int pages = std::stoi(pg);
    std::cout << "ISBN?\n";
    std::cin >> isbn;
    mmn.addBook(Book(title, author, isbn, pages, edition));
}
void addGameCommand(MediaManager& mmn) { // add game
    std::string title;
    std::string studio;
    std::string yr;
    std::cout << "Titel?\n";
    std::cin >> title;
    std::cout << "Studio?\n";
    std::cin >> studio;
    std::cout << "År?\n";
    std::cin >> yr;
    int year = std::stoi(yr);
    mmn.addPs2Game(Ps2Game(title, studio, year));
}
void addVinylCommand(MediaManager& mmn) { // add vinyl
    std::string title;
    std::string tp;
    std::string artist;
    std::string yr;
    std::string rt;
    std::cout << "Titel?\n";
    std::cin >> title;
    std::cout << "Typ? '1' för LP, '2' för EP\n";
    std::cin >> tp;
    std::cout << "Artist?\n";
    std::cin >> artist;
    std::cout << "År?\n";
    std::cin >> yr;
    int year = std::stoi(yr);
    std::cout << "tid i sekunder?\n";
    std::cin >> rt;
    int runtime = std::stoi(rt);
    Vinyl v = Vinyl(title, static_cast<VinylTypes>(std::stoi(tp)), year, artist, Time(runtime));
    while (true) {
        std::cout << "vill du lägga till en låt? 'ja' eller 'nej'.\n";
        std::string in;
        std::string name;
        std::string time;
        std::cin >> in;
        if (in != "ja") { break; }
        std::cout << "Namn?\n";
        std::cin >> name;
        std::cout << "Tid i sekunder?\n";
        std::cin >> time;
        v.addTrack(Track(name, Time(std::stoi(time))));
    }
    mmn.addVinyl(v);
}

int main() {
    MediaManager mediaManager = MediaManager(LIB_SIZE);
    printChoises();    
    bool run = true;
    while (run) {
        std::string input = getCommand();

        //jag vet att detta inte är jätte bra men det funkar
        if (input == SHOW_COMMANDS_KEY) {printChoises();}
        else if (input == PRINT_ALL_KEY) {printAllCommand(mediaManager);}
        else if (input == PRINT_BOOKS_KEY) {printBooksCommand(mediaManager);}
        else if (input == PRINT_PS2GAMES_KEY) {printGamesCommand(mediaManager);}
        else if (input == PRINT_VINYLS_KEY) {printVinylsCommand(mediaManager);}
        else if (input == ADD_BOOK_KEY) {AddBookCommand(mediaManager);}
        else if (input == ADD_PS2GAME_KEY) {addGameCommand(mediaManager);}
        else if (input == ADD_VINYL_KEY) {addVinylCommand(mediaManager);}
        else if (input == EXIT_KEY) { run = false; }
    }
    return 0;
}
