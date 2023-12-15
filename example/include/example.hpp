#pragma once

#include <string>
#include <vector>
#include <map>

enum class Week
{
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

class Book
{
public:
    Book(int isbn, std::string title, bool in_stock = false) : isbn_(isbn), title_(title), in_stock_(in_stock) {}
    int get_isbn() const { return isbn_; }
    std::string get_title() const { return title_; }
    bool get_in_stock() const { return in_stock_; }

private:
    int isbn_;
    std::string title_;
    bool in_stock_;
};

class Library
{
public:
    Library() = default;
    std::vector<Book> get_books() const { return books_; }
    std::map<std::string, std::string> get_thesaurus() const { return thesaurus_; }
    void set_books(std::vector<Book> value) { books_ = value; }
    void set_thesaurus(std::map<std::string, std::string> value) { thesaurus_ = value; }

private:
    std::vector<Book> books_;
    std::map<std::string, std::string> thesaurus_;
};