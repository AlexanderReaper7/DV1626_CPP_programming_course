class Media;
class Book;
#if __has_include("Book.hpp")
#include "Book.hpp"
#endif

#include "catch.hpp"
#include "functionCheckerGenerators.inc"
#include "printers.hpp"

TEMPLATE_TEST_CASE_SIG("Testing the Book class", "",                     //
                       ((int Dummy, typename T_Media, typename T_Book),  //
                        Dummy, T_Media, T_Book),                         //
                       (42, Media, Book)) {
  if constexpr (!isDefined<T_Book>::value) {
    FAIL(
        "Could not find definition of Book. Skipping the rest of the tests. "
        "Rerun the tests once you have implemented the Book class.");
  } else {
    static constexpr bool isBaseOfMedia =
        std::is_base_of<T_Media, T_Book>::value;
    static constexpr bool isPolymorphic = std::is_polymorphic<T_Book>::value;
    static constexpr bool isConstructible =
        std::is_constructible<T_Book, const std::string&, const std::string&,
                              const std::string&, int, int>::value;

    static constexpr bool hasOpEquals = has_const_equalsOp<T_Book, bool, const T_Book&>::value;
    static constexpr bool hasOpInEquals =
        has_const_inEqualsOp<T_Book, bool, const T_Book&>::value;

    HAS_CONST_FN(getAuthor, T_Book, const std::string&);
    HAS_CONST_FN(getIsbn, T_Book, const std::string&);
    HAS_CONST_FN(getPages, T_Book, int);
    HAS_CONST_FN(getEdition, T_Book, int);
    HAS_CONST_FN(prettyPrint, T_Book, std::string);
    static constexpr bool signaturesOk =
        hasOpEquals && hasOpInEquals && var_has_getIsbn && var_has_getPages &&
        var_has_getEdition && var_has_prettyPrint && isBaseOfMedia &&
        isPolymorphic && isConstructible;

    WHEN("Running signature tests on the Book class") {
      WHEN("Checking for polymorphism and correct base class") {
        CHECKVAR(isBaseOfMedia, "Baseclass should be Media");
        CHECKVAR(isPolymorphic, "Polymorphism");
      }
      WHEN("Checking for correct constructors and destructors") {
        CHECKVAR(isConstructible, "Checking Book constructor");
      }
      WHEN("Checking for correct getters") {
        CHECKVAR2(getAuthor);
        CHECKVAR2(getIsbn);
        CHECKVAR2(getPages);
        CHECKVAR2(getEdition);
      }
      CHECKVAR(hasOpEquals, "operator==");
      CHECKVAR(hasOpInEquals, "operator!=");
      CHECKVAR2(prettyPrint);
    }

    WHEN("Testing the Book class implementation") {
      if constexpr (!signaturesOk) {
        FAIL(
            "Skipping this section as the class does not conform to the "
            "spec. "
            "Make sure you have implented all methods with the correct "
            "signatures. The tests above should guide you and show you what "
            "is actually missing or wrong ");
      } else {
        GIVEN("A fantastic science fiction novel") {
          T_Book reveleationSpace("Revelation Space", "Alastair Reynolds",
                                  "9780575083097", 576, 1);
          THEN("Getters should return expected values") {
            REQUIRE(reveleationSpace.getTitle() == "Revelation Space");
            REQUIRE(reveleationSpace.getAuthor() == "Alastair Reynolds");
            REQUIRE(reveleationSpace.getIsbn() == "9780575083097");
            REQUIRE(reveleationSpace.getPages() == 576);
            REQUIRE(reveleationSpace.getEdition() == 1);
          }
          WHEN("Creating a copy") {
            T_Book tmp(reveleationSpace);
            THEN("The copy constructor should produce a identical copy") {
              REQUIRE(tmp.getTitle() == reveleationSpace.getTitle());
              REQUIRE(tmp.getPages() == reveleationSpace.getPages());
            }
            THEN("The == operator should work") {
              REQUIRE(tmp == reveleationSpace);
              AND_THEN("And so should the != operator") {
                T_Book fake("Fake", "FakePerson", "NaN", 43, 1338);
                REQUIRE(tmp != fake);
              }
            }
          }
        }
      }
      // Move to media? or another testfile?
      WHEN("Testing equals and non-equals with polymorphism") {
        GIVEN("Three books, original, a copy, and an another") {
          T_Book orig("a", "b", "c", 1, 2);
          T_Book copy("a", "b", "c", 1, 2);
          T_Book another("d", "e", "f", 3, 4);
          THEN("Check that orig can be compared to itself") {
            REQUIRE(orig == orig);
          }
          THEN("Check that orig and copy are equal") { REQUIRE(orig == copy); }
          THEN("Check that orig and copy does not equals 'another'") {
            REQUIRE(orig != another);
            REQUIRE(copy != another);
          }
          WHEN("They are stored as Media") {
            T_Media* origM = &orig;
            T_Media* copyM = &copy;
            T_Media* anotherM = &another;
            THEN("The comparisons should still hold true") {
              REQUIRE(*origM == *origM);
              REQUIRE(*origM == *copyM);
              REQUIRE(*origM != *anotherM);
              REQUIRE(*copyM != *anotherM);
            }
          }
        }
      }
    }
  }
}