#include <rapidjson_macros/rapidjson_macros>
#include <example.hpp>
#include <iostream>

RAPIDJSON_ENUM_NAME_TRAITS(Week,
                           (MONDAY, "monday"),
                           (TUESDAY, "tuesday"),
                           (WEDNESDAY, "wednesday"),
                           (THURSDAY, "thursday"),
                           (FRIDAY, "friday"),
                           (SATURDAY, "saturday"),
                           (SUNDAY, "sunday"))
RAPIDJSON_N_CTOR_GETTER_NAME_TRAITS(Book, 2, (get_isbn, "isbn"), (get_title, "title"), (get_in_stock, "in stock"))
RAPIDJSON_ALL_GETTER_SETTER_TRAITS(Library, get_, set_, books, thesaurus)

int main()
{
    rapidjson_macros::to_stream<Week>(std::cout, Week::THURSDAY); // "thursday"
    std::cout << std::endl;

    Book book = rapidjson_macros::as<Book>(R"({"isbn":16, "title":"Codex Astartes"})", false);
    rapidjson_macros::to_stream<Book>(std::cout, book); // {"isbn":16,"title":"Codex Astartes","in stock":false}
    std::cout << std::endl;

    Library library;
    library.set_books({Book(11, "Loken")});
    library.set_thesaurus({{"lodge", "distrust"}, {"Horus", "traitor"}});
    rapidjson_macros::to_stream<Library>(std::cout, library); // {"books":[{"isbn":16,"title":"Codex Astartes","in stock":false}],"thesaurus":{"Horus":"traitor","lodge":"distrust"}}
    std::cout << std::endl;

    return 0;
}