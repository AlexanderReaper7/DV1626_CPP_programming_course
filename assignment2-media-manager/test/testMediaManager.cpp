class Media;
#if __has_include("Media.hpp")
#include "Media.hpp"
#endif

class MediaManager;
#if __has_include("MediaManager.hpp")
#include "MediaManager.hpp"
#endif

class Book;
#if __has_include("Book.hpp")
#include "Book.hpp"
#endif

class Ps2Game;
#if __has_include("Ps2Game.hpp")
#include "Ps2Game.hpp"
#endif

class Vinyl;
class Track;
enum class VinylTypes;
#if __has_include("Vinyl.hpp")
#include "Vinyl.hpp"
#endif

#include <catch.hpp>

#include "functionCheckerGenerators.inc"
#include "printers.hpp"

using namespace std::chrono_literals;

static const int ITERATIONS = 99;

template <typename T_MediaManager, typename T_Book>
void addBookAsFunc(T_MediaManager &mediaManager, int i) {
  T_Book book("a", "b", "c", i, i);
  mediaManager.addMedia(&book);
}

template <typename T_MediaManager, typename T_Vinyl, typename Track_T,
          typename T_VinylTypes>
void addVinylAsFunc(T_MediaManager &mediaManager, int i) {
  T_Vinyl vinyl("b", T_VinylTypes::LONG_PLAY, i, "c", Time(46min));
  vinyl.addTrack(Track_T("aa", Time(3min + 3s)));
  vinyl.addTrack(Track_T("bb", Time(2min + 23s)));
  vinyl.addTrack(Track_T("cc", Time(3min + 14s)));
  mediaManager.addMedia(&vinyl);
}

template <typename T_MediaManager, typename T_Ps2Game>
void addGameAsFunc(T_MediaManager &mediaManager, int i) {
  T_Ps2Game game("c", "d", i);
  mediaManager.addMedia(&game);
}

template <typename T_MediaManager, typename T_Book, typename T_Vinyl,
          typename Track_T, typename T_VinylTypes, typename T_Ps2Game>
void addMediasAsFunc(T_MediaManager &mediaManager) {
  static int i = 0;
  addBookAsFunc<T_MediaManager, T_Book>(mediaManager, i);
  addGameAsFunc<T_MediaManager, T_Ps2Game>(mediaManager, i);
  addVinylAsFunc<T_MediaManager, T_Vinyl, Track_T, T_VinylTypes>(mediaManager,
                                                                 i);
  i++;
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addMedia)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addBook)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addVinyl)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addPs2Game)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(printMedia)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getBooks)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getVinyls)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getPs2Games)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getMedias)

TEMPLATE_TEST_CASE_SIG("Testing the MediaManager class", "",
                       ((int Dummy, typename T_MediaManager, typename T_Media,
                         typename T_Book, typename T_Ps2Game, typename T_Vinyl,
                         typename T_VinylTypes, typename T_Track),
                        Dummy, T_MediaManager, T_Media, T_Book, T_Ps2Game,
                        T_Vinyl, T_VinylTypes, T_Track),
                       (42, MediaManager, Media, Book, Ps2Game, Vinyl,
                        VinylTypes, Track)) {
  static constexpr bool vinylDefined = isDefined<T_Vinyl>::value;
  static constexpr bool vinylTypeDefined = isDefined<T_VinylTypes>::value;
  static constexpr bool trackDefined = isDefined<T_Track>::value;
  static constexpr bool bookDefined = isDefined<T_Book>::value;
  static constexpr bool ps2gameDefined = isDefined<T_Ps2Game>::value;
  static constexpr bool mediaManagerDefined = isDefined<T_MediaManager>::value;
  if constexpr (!vinylDefined || !vinylTypeDefined || !trackDefined ||
                !bookDefined || !ps2gameDefined || !mediaManagerDefined) {
    FAIL(
        "Could not find definition of Vinyl, VinylType, Track, Book, Ps2Game "
        "and/or MediaManager. Skipping the rest of the tests. Rerun the tests "
        "once you have implemented the above classes and enum classes.");
  } else {
    static constexpr bool isConstructible =
        std::is_constructible<T_MediaManager, size_t>::value;
    static constexpr bool hasOpEquals =
        has_const_equalsOp<T_MediaManager, bool, const T_MediaManager &>::value;
    static constexpr bool hasOpInEquals =
        has_const_inEqualsOp<T_MediaManager, bool,
                             const T_MediaManager &>::value;
    HAS_FN(addMedia, T_MediaManager, void, T_Media *);
    HAS_FN(addBook, T_MediaManager, void, const T_Book &);
    HAS_FN(addVinyl, T_MediaManager, void, const T_Vinyl &);
    HAS_FN(addPs2Game, T_MediaManager, void, const T_Ps2Game &);
    HAS_CONST_FN(printMedia, T_MediaManager, std::string);
    HAS_CONST_FN(getBooks, T_MediaManager, std::vector<T_Book>);
    HAS_CONST_FN(getVinyls, T_MediaManager, std::vector<T_Vinyl>);
    HAS_CONST_FN(getPs2Games, T_MediaManager, std::vector<T_Ps2Game>);
    HAS_CONST_FN(getMedias, T_MediaManager, T_Media **);
    static constexpr bool signaturesOk =
        hasOpEquals && hasOpInEquals && var_has_addMedia && var_has_addBook &&
        var_has_addVinyl && var_has_addPs2Game && var_has_printMedia &&
        var_has_getBooks && var_has_getVinyls && var_has_getPs2Games;
    WHEN("Running signature tests on the MediaManager class") {
      WHEN("Checking for correct constructors and destructors") {
        CHECKVAR(isConstructible, "Checking MediaManager constructor");
      }
      WHEN("Checking for correct getters") {
        CHECKVAR2(addMedia);
        CHECKVAR2(addBook);
        CHECKVAR2(addVinyl);
        CHECKVAR2(addPs2Game);
        CHECKVAR2(printMedia);
        CHECKVAR2(getBooks);
        CHECKVAR2(getVinyls);
        CHECKVAR2(getPs2Games);
        CHECKVAR2(getMedias);
      }
      CHECKVAR(hasOpEquals, "operator==");
      CHECKVAR(hasOpInEquals, "operator!=");
    }

    WHEN("Testing the MediaManager class implementation") {
      if constexpr (!signaturesOk) {
        FAIL(
            "Skipping this section as the class does not conform to the "
            "spec. Make sure you have implented all methods with the correct "
            "signatures. The tests above should guide you and show you what "
            "is actually missing or wrong ");
      } else {
        SECTION("Basic tests of member functions") {
          T_MediaManager mediaManager(100);
          GIVEN("Three books has been added to the media manager") {
            T_Book hitchickersGuide("Liftarens guide till galaxen",
                                    "Douglas Adams", "9789132212697", 42, 3);
            mediaManager.addBook(hitchickersGuide);
            T_Book yachtDesign("Principles of Yacht Design",
                               "Lars Larsson, Rolf Eliasson, Michal Orych",
                               "9781408187906", 352, 4);
            mediaManager.addBook(yachtDesign);
            T_Book revelationSpace("Revelation Space", "Alastair Reynolds",
                                   "9780575083097", 576, 1);
            mediaManager.addBook(revelationSpace);

            WHEN("getBooks() is called") {
              std::vector<T_Book> books = mediaManager.getBooks();
              THEN(
                  "There should be three books in the supplied vector after "
                  "the function call") {
                REQUIRE(books.size() == 3);
              }
              THEN(
                  "The first book should be \"Liftarens guide till galaxen\"") {
                REQUIRE(books[0] == hitchickersGuide);
                REQUIRE(books[0].getTitle() == "Liftarens guide till galaxen");
                REQUIRE(books[0].getAuthor() == "Douglas Adams");
                REQUIRE(books[0].getIsbn() == "9789132212697");
                REQUIRE(books[0].getPages() == 42);
                REQUIRE(books[0].getEdition() == 3);
              }
              THEN("The second book should be \"Principles of Yacht Design\"") {
                REQUIRE(books[1] == yachtDesign);
              }
              THEN("The third book should be \"Revelation Space\"") {
                REQUIRE(books[2] == revelationSpace);
              }
              THEN(
                  "The pointers returned by getMedias() point equal objects ") {
                REQUIRE(*mediaManager.getMedias()[0] == hitchickersGuide);
              }
            }
          }

          GIVEN("A Vikingarna LP has been added to the media library") {
            T_Vinyl kramgoaSeven("Kramgoa Låtar 7", T_VinylTypes::LONG_PLAY,
                                 1979, "Vikingarna", Time(46min));
            kramgoaSeven.addTrack(T_Track("Djinghis Khan", Time(3min + 3s)));
            kramgoaSeven.addTrack(T_Track("Hjärtats röst", Time(2min + 23s)));
            kramgoaSeven.addTrack(T_Track("Annie's Song", Time(3min + 14s)));
            kramgoaSeven.addTrack(
                T_Track("Om du lämnar mig så här", Time(3min + 14s)));
            kramgoaSeven.addTrack(
                T_Track("Så länge du älskar är du ung", Time(3min + 22s)));
            kramgoaSeven.addTrack(T_Track("Jag kommer hem", Time(2min + 27s)));
            kramgoaSeven.addTrack(T_Track("Jag var så kär", Time(2min + 55s)));
            kramgoaSeven.addTrack(T_Track("Such a Night", Time(2min + 57s)));
            mediaManager.addVinyl(kramgoaSeven);
            WHEN("The library is printed") {
              std::vector<T_Vinyl> vinyls = mediaManager.getVinyls();
              THEN(
                  "There should be one vinyl in the supplied vector after the "
                  "function call") {
                REQUIRE(vinyls.size() == 1);
              }
              THEN("The Vinyl should be \"Kramgoa Låtar 7\"") {
                REQUIRE(vinyls[0] == kramgoaSeven);
              }
              THEN(
                  "The pointers returned by getMedias() point equal objects ") {
                REQUIRE(*mediaManager.getMedias()[0] == kramgoaSeven);
              }
            }
          }
          GIVEN("Two games are added to the media manager") {
            mediaManager.addPs2Game(
                T_Ps2Game("Battlefield Bad Company 2", "DICE", 2010));
            mediaManager.addPs2Game(T_Ps2Game("Battlefield 4", "DICE", 2013));
            WHEN("The library is printed") {
              std::vector<T_Ps2Game> games = mediaManager.getPs2Games();
              THEN(
                  "There should be two games in the supplied vector after the "
                  "function call") {
                REQUIRE(games.size() == 2);
              }
              THEN("The first game should be \"Battlefield Bad Company 2\"") {
                REQUIRE(games[0] ==
                        T_Ps2Game("Battlefield Bad Company 2", "DICE", 2010));
              }
              THEN("The first game should be \"Battlefield 4\"") {
                REQUIRE(games[1] == T_Ps2Game("Battlefield 4", "DICE", 2013));
              }
              THEN(
                  "The pointers returned by getMedias() point equal objects ") {
                REQUIRE(*mediaManager.getMedias()[0] ==
                        T_Ps2Game("Battlefield Bad Company 2", "DICE", 2010));
              }
            }
          }
          GIVEN("Another media manager") {
            T_MediaManager secondManager(42);
            WHEN("Both media managers has the same contents added") {
              mediaManager.addBook(T_Book("a", "b", "c", 1, 1));
              secondManager.addBook(T_Book("a", "b", "c", 1, 1));

              mediaManager.addPs2Game(T_Ps2Game("b", "c", 1));
              secondManager.addPs2Game(T_Ps2Game("b", "c", 1));

              THEN("The media managers should be equal") {
                REQUIRE(mediaManager == secondManager);
              }
              WHEN("Different medias are added") {
                mediaManager.addBook(T_Book("x", "b", "c", 1, 1));
                secondManager.addPs2Game(T_Ps2Game("y", "b", 1));
                THEN("They should not be equal") {
                  REQUIRE(mediaManager != secondManager);
                }
              }
              WHEN("Different medias with the same title is added") {
                mediaManager.addBook(T_Book("a", "b", "c", 1, 1));
                secondManager.addPs2Game(T_Ps2Game("a", "b", 1));
                THEN("They should not be equal") {
                  REQUIRE(mediaManager != secondManager);
                }
              }
              WHEN("Different medias with the same media types are added") {
                mediaManager.addBook(T_Book("a", "b", "c", 1, 1));
                secondManager.addBook(T_Book("b", "c", "d", 2, 2));
                THEN("They should not be equal") {
                  REQUIRE(mediaManager != secondManager);
                }
              }
            }
          }
        }
        SECTION(
            "Detailed testing of polymorpic behaviour. I.e. addMedia() should "
            "function equiavalently compard to addBook, addVinyl etc") {
          T_MediaManager mediaManager(13);
          GIVEN("Two books") {
            T_Book book1("a", "b", "c", 1338, 43);
            T_Book book2("b", "d", "d", 1339, 44);
            WHEN("One book is added through addMedia()") {
              mediaManager.addMedia(&book1);
              THEN(
                  "The pointer returned by getMedias() should not point to the "
                  "same object") {
                REQUIRE(mediaManager.getMedias()[0] != &book1);
              }
              THEN(
                  "The book should be returned when calling getBooks(). "
                  "Prettyprint and other getters should not crash") {
                mediaManager.printMedia();
                mediaManager.getBooks();
                REQUIRE(mediaManager.getBooks().size() == 1);
                REQUIRE(mediaManager.getBooks()[0] == book1);
                REQUIRE(mediaManager.getBooks()[0] != book2);
              }
            }
            WHEN("One book is added through addBook()") {
              mediaManager.addBook(book1);
              THEN(
                  "The book should be returned when calling getBooks(). "
                  "Prettyprint and other getters should not crash") {
                mediaManager.printMedia();
                mediaManager.getBooks();
                REQUIRE(mediaManager.getBooks().size() == 1);
                REQUIRE(mediaManager.getBooks()[0] == book1);
                REQUIRE(mediaManager.getBooks()[0] != book2);
              }
            }
          }
          GIVEN("Two games") {
            T_Ps2Game game1("a", "b", 2);
            T_Ps2Game game2("b", "c", 3);
            WHEN("One game is added through addMedia()") {
              mediaManager.addMedia(&game1);
              THEN(
                  "The pointer returned by getMedias() should not point to the "
                  "same object") {
                REQUIRE(mediaManager.getMedias()[0] != &game1);
              }
              THEN(
                  "The game should be returned when calling getPs2Games(). "
                  "Prettyprint and other getters should not crash") {
                mediaManager.printMedia();
                mediaManager.getPs2Games();
                REQUIRE(mediaManager.getPs2Games().size() == 1);
                REQUIRE(mediaManager.getPs2Games()[0] == game1);
                REQUIRE(mediaManager.getPs2Games()[0] != game2);
              }
            }
            WHEN("One game is added through addGame()") {
              mediaManager.addPs2Game(game1);
              THEN(
                  "The game should be returned when calling getPs2Games(). "
                  "Prettyprint and other getters should not crash") {
                mediaManager.printMedia();
                mediaManager.getPs2Games();
                REQUIRE(mediaManager.getPs2Games().size() == 1);
                REQUIRE(mediaManager.getPs2Games()[0] == game1);
                REQUIRE(mediaManager.getPs2Games()[0] != game2);
              }
            }
          }
          GIVEN("Two vinyls") {
            T_Vinyl vinyl1("a", T_VinylTypes::LONG_PLAY, 3, "b", Time(46min));
            vinyl1.addTrack(T_Track("aa", Time(3min + 3s)));
            vinyl1.addTrack(T_Track("bb", Time(2min + 23s)));
            vinyl1.addTrack(T_Track("cc", Time(3min + 14s)));
            T_Vinyl vinyl2("b", T_VinylTypes::EXTENDED_PLAY, 3, "c",
                           Time(47min));
            WHEN("One vinyl is added through addMedia()") {
              mediaManager.addMedia(&vinyl1);
              THEN(
                  "The pointer returned by getMedias() should not point to the "
                  "same object") {
                REQUIRE(mediaManager.getMedias()[0] != &vinyl1);
              }
              THEN(
                  "The vinyl should be returned when calling getVinyls(). "
                  "Prettyprint and other getters should not crash") {
                mediaManager.printMedia();
                mediaManager.getVinyls();
                REQUIRE(mediaManager.getVinyls().size() == 1);
                REQUIRE(mediaManager.getVinyls()[0] == vinyl1);
                REQUIRE(mediaManager.getVinyls()[0] != vinyl2);
              }
            }
            WHEN("One vinyl is added through addVinyl()") {
              mediaManager.addMedia(&vinyl1);
              THEN(
                  "The vinyl should be returned when calling getVinyls(). "
                  "Prettyprint and other getters should not crash") {
                mediaManager.printMedia();
                mediaManager.getVinyls();
                REQUIRE(mediaManager.getVinyls().size() == 1);
                REQUIRE(mediaManager.getVinyls()[0] == vinyl1);
                REQUIRE(mediaManager.getVinyls()[0] != vinyl2);
              }
            }
          }
        }
        SECTION("Stress testing to trigger faults in memory management") {
          T_MediaManager mediaManager(1000);
          WHEN("Lots of Medias added allocated on the stack in a for-loop") {
            for (size_t i = 0; i < ITERATIONS; ++i) {
              T_Book book("a", "b", "c", i, i);
              mediaManager.addMedia(&book);

              T_Ps2Game game("a", "b", i);
              mediaManager.addMedia(&game);

              T_Vinyl vinyl("a", T_VinylTypes::LONG_PLAY, i, "b", Time(46min));
              vinyl.addTrack(T_Track("aa", Time(3min + 3s)));
              vinyl.addTrack(T_Track("bb", Time(2min + 23s)));
              vinyl.addTrack(T_Track("cc", Time(3min + 14s)));
              mediaManager.addMedia(&vinyl);
            }
            THEN("Prettyprint and other getters should not crash") {
              mediaManager.printMedia();
              mediaManager.getBooks();
              mediaManager.getPs2Games();
              mediaManager.getVinyls();
            }
          }
          WHEN("Lots of Medias added allocated on the stack in a function") {
            for (size_t i = 0; i < ITERATIONS; ++i) {
              addMediasAsFunc<T_MediaManager, T_Book, T_Vinyl, T_Track,
                              T_VinylTypes, T_Ps2Game>(mediaManager);
            }
            THEN("printMedia() and getters should not crash") {
              mediaManager.printMedia();
              mediaManager.getBooks();
              mediaManager.getPs2Games();
              mediaManager.getVinyls();
            }
          }
          WHEN(
              "Lots of Medias added allocated on the heap in a for-loop and "
              "then deleted") {
            for (size_t i = 0; i < ITERATIONS; ++i) {
              T_Book *book = new T_Book("a", "b", "c", i, i);
              mediaManager.addMedia(book);
              delete book;

              T_Ps2Game *game = new T_Ps2Game("a", "b", i);
              mediaManager.addMedia(game);
              delete game;

              T_Vinyl *vinyl =
                  new T_Vinyl("a", T_VinylTypes::LONG_PLAY, i, "b", Time(6s));
              vinyl->addTrack(T_Track("aa", Time(1s)));
              vinyl->addTrack(T_Track("bb", Time(2s)));
              vinyl->addTrack(T_Track("cc", Time(3s)));
              mediaManager.addMedia(vinyl);
              delete vinyl;
            }
            THEN("Prettyprint and other getters should not crash") {
              mediaManager.printMedia();
              mediaManager.getBooks();
              mediaManager.getPs2Games();
              mediaManager.getVinyls();
            }
          }
          WHEN("Items are added both via addBook, addVinyl etc and addMedia") {
            for (size_t i = 0; i < ITERATIONS; ++i) {
              T_Book book("a", "b", "c", i, i);
              mediaManager.addMedia(&book);
              mediaManager.addBook(T_Book("a", "b", "c", i, 42));

              T_Ps2Game game("a", "b", i);
              mediaManager.addMedia(&game);
              mediaManager.addPs2Game(T_Ps2Game("a", "b", ITERATIONS + i));

              T_Vinyl vinyl("a", T_VinylTypes::LONG_PLAY, i, "b", Time(46min));
              vinyl.addTrack(T_Track("aa", Time(3min + 3s)));
              vinyl.addTrack(T_Track("bb", Time(2min + 23s)));
              vinyl.addTrack(T_Track("cc", Time(3min + 14s)));
              mediaManager.addMedia(&vinyl);
              mediaManager.addVinyl(T_Vinyl("a", T_VinylTypes::LONG_PLAY,
                                            ITERATIONS + i, "b", Time(46min)));
            }
            THEN("Prettyprint and other getters should not crash") {
              mediaManager.printMedia();
              mediaManager.getBooks();
              mediaManager.getPs2Games();
              mediaManager.getVinyls();
            }
          }
        }
        SECTION("Testing comparison between different medias") {
          GIVEN("Harry Potter as a Vinyl, Book and as a Ps2game") {
            T_Vinyl vinyl("Sagan om Ringen", T_VinylTypes::LONG_PLAY, 1970,
                               "Bo Hansson", Time(47min + 32s));
            T_Book book("Sagan om Ringen", "J.R.R Tolkien", "0 00 717197", 535, 2);
            T_Ps2Game game("Sagan om Ringen", "Sophisticated Games Ltd", 2001);

            THEN("Check that they do not equal each other") {
              REQUIRE(book == book);
              REQUIRE(vinyl == vinyl);
              REQUIRE(game == game);
              REQUIRE(book != game);
              REQUIRE(book != vinyl);
              REQUIRE(vinyl != game);
            }

            WHEN("They are stored as Media") {
              T_Media *bookM = &book;
              T_Media *gameM = &game;
              T_Media *vinylM = &vinyl;
              THEN("The comparisons should still hold true") {
                REQUIRE(*bookM == *bookM);
                REQUIRE(*vinylM == *vinylM);
                REQUIRE(*gameM == *gameM);
                REQUIRE(*bookM != *gameM);
                REQUIRE(*bookM != *vinylM);
                REQUIRE(*vinylM != *gameM);
              }
            }
          }
        }
      }
    }
  }
}
