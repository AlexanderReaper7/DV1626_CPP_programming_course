// #include <Book.hpp>
// #include <MediaManager.hpp>
// #include <Ps2Game.hpp>
// #include <Vinyl.hpp>
//#include <catch.hpp>
//#include <iostream>

//// Assignment and copy/ctor are not part of this assignment
// GIVEN("Check assignment and copy-constructors") {
//   WHEN("MediaManager") {
//     MediaManager manager;
//     addBook(manager, 42);
//     WHEN("Copyconstructor") {
//       { MediaManager otherManager = manager; }
//       THEN(
//           "The book should be returned when calling getBooks(). Prettyprint
//           " "and other getters should not crash") {
//         manager.printMedia();
//         manager.getBooks();
//         REQUIRE(manager.getBooks().size() == 1);
//       }
//     }
//     WHEN("Assignment") {
//       {
//         MediaManager otherManager;
//         otherManager = manager;
//       }
//       THEN(
//           "The book should be returned when calling getBooks(). Prettyprint
//           " "and other getters should not crash") {
//         manager.printMedia();
//         manager.getBooks();
//         REQUIRE(manager.getBooks().size() == 1);
//       }
//     }
//   }
// }
//}