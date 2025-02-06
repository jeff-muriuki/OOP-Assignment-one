#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string bookNumber;
    bool isAvailable;

public:
    Book(string title, string author, string bookNumber)
        : title(title), author(author), bookNumber(bookNumber), isAvailable(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getBookNumber() const { return bookNumber; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool availability) { isAvailable = availability; }

    void display() const
    {
        cout << "Title: " << title << ", Author: " << author
             << ", bookNumber: " << bookNumber << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class User
{
private:
    string Id;
    string name;
    vector<Book *> booksBorrowed;

public:
    User(string Id, string name) : Id(Id), name(name) {}

    string getId() const { return Id; }
    string getName() const { return name; }

    void borrowBook(Book *book)
    {
        if (book->getAvailability())
        {
            booksBorrowed.push_back(book);
            book->setAvailability(false);
            cout << "Book borrowed by " << name << endl;
        }
        else
        {
            cout << "Book not available for borrowing." << endl;
        }
    }

    void returnBook(Book *book)
    {
        auto it = find(booksBorrowed.begin(), booksBorrowed.end(), book);
        if (it != booksBorrowed.end())
        {
            booksBorrowed.erase(it);
            book->setAvailability(true);
            cout << "Book returned by " << name << endl;
        }
        else
        {
            cout << "This book was not borrowed by " << name << endl;
        }
    }

    void displayBooksBorrowed() const
    {
        cout << name << "'s borrowed books :" << endl;
        for (const auto &book : booksBorrowed)
        {
            book->display();
        }
    }
};

class Library
{
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(const Book &book)
    {
        books.push_back(book);
        cout << "Book added to library." << endl;
    }

    void removeBook(const string &bookNumber)
    {
        auto it = remove_if(books.begin(), books.end(),
                            [&bookNumber](const Book &book)
                            { return book.getBookNumber() == bookNumber; });
        if (it != books.end())
        {
            books.erase(it, books.end());
            cout << "Book removed from the library." << endl;
        }
        else
        {
            cout << "Book not found in the library." << endl;
        }
    }

    void addUser(const User &user)
    {
        users.push_back(user);
        cout << "User added to the system." << endl;
    }

    Book *searchBookByTitle(const string &title)
    {
        for (auto &book : books)
        {
            if (book.getTitle() == title)
            {
                return &book;
            }
        }
        return nullptr;
    }

    Book *searchBookByAuthor(const string &author)
    {
        for (auto &book : books)
        {
            if (book.getAuthor() == author)
            {
                return &book;
            }
        }
        return nullptr;
    }

    Book *searchBookByBookNumber(const string &bookNumber)
    {
        for (auto &book : books)
        {
            if (book.getBookNumber() == bookNumber)
            {
                return &book;
            }
        }
        return nullptr;
    }

    User *findUserByID(const string &Id)
    {
        for (auto &user : users)
        {
            if (user.getId() == Id)
            {
                return &user;
            }
        }
        return nullptr;
    }

    void displayAllBooks() const
    {
        cout << "Library Books:" << endl;
        for (const auto &book : books)
        {
            book.display();
        }
    }
};

int main()
{
    Library library;

    // Adding books
    library.addBook(Book("The River and the Source", "Margaret A. Ogola", "1527304"));
    library.addBook(Book("Gifted Hands", "Ben Carson", "3388410"));

    // Adding users
    library.addUser(User("USER1", "Kasongo"));
    library.addUser(User("USER2", "Zakayo"));

    // Searching for books
    Book *book1 = library.searchBookByTitle("The River and the Source");
    Book *book2 = library.searchBookByBookNumber("3388410");

    // Borrowing & returning books
    User *user1 = library.findUserByID("USER1");
    if (user1 && book1)
    {
        user1->borrowBook(book1);
        user1->displayBooksBorrowed();
        user1->returnBook(book1);
    }

    // Display all books
    library.displayAllBooks();

    return 0;
}