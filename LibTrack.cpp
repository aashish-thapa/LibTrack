#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdio>

class Book {
    std::string bookNumber;
    std::string bookName;
    std::string authorName;

public:
    void createBook() {
        std::cout << "\nNEW BOOK ENTRY...\n";
        std::cout << "Enter Book Number: ";
        std::cin >> bookNumber;
        std::cin.ignore();
        std::cout << "Enter Book Name: ";
        std::getline(std::cin, bookName);
        std::cout << "Enter Author Name: ";
        std::getline(std::cin, authorName);
        std::cout << "\nBook Created.\n";
    }

    void showBook() const {
        std::cout << "\nBook Number: " << bookNumber;
        std::cout << "\nBook Name: " << bookName;
        std::cout << "\nAuthor Name: " << authorName << "\n";
    }

    void modifyBook() {
        std::cout << "Book Number: " << bookNumber;
        std::cout << "\nModify Book Name: ";
        std::cin.ignore();
        std::getline(std::cin, bookName);
        std::cout << "Modify Author's Name: ";
        std::getline(std::cin, authorName);
    }

    const std::string& retBookNumber() const {
        return bookNumber;
    }

    void report() const {
        std::cout << bookNumber << std::setw(30) << bookName << std::setw(30) << authorName << "\n";
    }
};

class Student {
    std::string admissionNumber;
    std::string name;
    std::string bookNumber;
    int token = 0;

public:
    void createStudent() {
        std::cout << "\nNEW STUDENT ENTRY...\n";
        std::cout << "Enter Admission Number: ";
        std::cin >> admissionNumber;
        std::cin.ignore();
        std::cout << "Enter Student Name: ";
        std::getline(std::cin, name);
        token = 0;
        bookNumber.clear();
        std::cout << "\nStudent Record Created.\n";
    }

    void showStudent() const {
        std::cout << "\nAdmission Number: " << admissionNumber;
        std::cout << "\nStudent Name: " << name;
        std::cout << "\nNumber of Books Issued: " << token;
        if (token == 1) {
            std::cout << "\nBook Number: " << bookNumber << "\n";
        }
    }

    void modifyStudent() {
        std::cout << "Admission Number: " << admissionNumber;
        std::cout << "\nModify Student Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
    }

    const std::string& retAdmissionNumber() const {
        return admissionNumber;
    }

    const std::string& retBookNumber() const {
        return bookNumber;
    }

    int retToken() const {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void setBookNumber(const std::string& bookNo) {
        bookNumber = bookNo;
    }

    void report() const {
        std::cout << "\t" << admissionNumber << std::setw(20) << name << std::setw(10) << token << "\n";
    }
};

void writeBook() {
    std::ofstream outFile("book.dat", std::ios::binary | std::ios::app);
    char choice;
    Book book;

    do {
        book.createBook();
        outFile.write(reinterpret_cast<const char*>(&book), sizeof(Book));
        std::cout << "\nDo you want to add more records? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void writeStudent() {
    std::ofstream outFile("student.dat", std::ios::binary | std::ios::app);
    char choice;
    Student student;

    do {
        student.createStudent();
        outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        std::cout << "\nDo you want to add more records? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void displaySpecificBook(const std::string& bookNumber) {
    std::ifstream inFile("book.dat", std::ios::binary);
    Book book;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.retBookNumber() == bookNumber) {
            book.showBook();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "\nBook does not exist.\n";
    }
}

void displaySpecificStudent(const std::string& admissionNumber) {
    std::ifstream inFile("student.dat", std::ios::binary);
    Student student;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.retAdmissionNumber() == admissionNumber) {
            student.showStudent();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "\nStudent does not exist.\n";
    }
}

void modifyBook() {
    std::fstream file("book.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::string bookNumber;
    bool found = false;
    Book book;

    std::cout << "\nMODIFY BOOK RECORD...\n";
    std::cout << "Enter Book Number: ";
    std::cin >> bookNumber;

    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.retBookNumber() == bookNumber) {
            book.showBook();
            std::cout << "\nEnter new details of the book.\n";
            book.modifyBook();
            file.seekp(-static_cast<int>(sizeof(Book)), std::ios::cur);
            file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
            std::cout << "\nRecord Updated.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "\nRecord Not Found.\n";
    }
}

void modifyStudent() {
    std::fstream file("student.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::string admissionNumber;
    bool found = false;
    Student student;

    std::cout << "\nMODIFY STUDENT RECORD...\n";
    std::cout << "Enter Admission Number: ";
    std::cin >> admissionNumber;

    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.retAdmissionNumber() == admissionNumber) {
            student.showStudent();
            std::cout << "\nEnter new details of the student.\n";
            student.modifyStudent();
            file.seekp(-static_cast<int>(sizeof(Student)), std::ios::cur);
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
            std::cout << "\nRecord Updated.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "\nRecord Not Found.\n";
    }
}

void deleteStudent() {
    std::ifstream inFile("student.dat", std::ios::binary);
    std::ofstream outFile("temp.dat", std::ios::binary);
    std::string admissionNumber;
    bool found = false;
    Student student;

    std::cout << "\nDELETE STUDENT RECORD...\n";
    std::cout << "Enter Admission Number: ";
    std::cin >> admissionNumber;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.retAdmissionNumber() != admissionNumber) {
            outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();
    std::remove("student.dat");
    std::rename("temp.dat", "student.dat");

    if (found) {
        std::cout << "\nRecord Deleted.\n";
    } else {
        std::cout << "\nRecord Not Found.\n";
    }
}

void deleteBook() {
    std::ifstream inFile("book.dat", std::ios::binary);
    std::ofstream outFile("temp.dat", std::ios::binary);
    std::string bookNumber;
    bool found = false;
    Book book;

    std::cout << "\nDELETE BOOK RECORD...\n";
    std::cout << "Enter Book Number: ";
    std::cin >> bookNumber;

    while (inFile.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.retBookNumber() != bookNumber) {
            outFile.write(reinterpret_cast<const char*>(&book), sizeof(Book));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();
    std::remove("book.dat");
    std::rename("temp.dat", "book.dat");

    if (found) {
        std::cout << "\nRecord Deleted.\n";
    } else {
        std::cout << "\nRecord Not Found.\n";
    }
}

void displayAllBooks() {
    std::ifstream inFile("book.dat", std::ios::binary);
    Book book;

    std::cout << "\n\n\t\tBook List\n";
    std::cout << "====================================================\n";
    std::cout << "Book Number      Book Name                Author\n";
    std::cout << "====================================================\n";

    while (inFile.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        book.report();
    }

    inFile.close();
}

void displayAllStudents() {
    std::ifstream inFile("student.dat", std::ios::binary);
    Student student;

    std::cout << "\n\n\t\tStudent List\n";
    std::cout << "====================================================\n";
    std::cout << "Admission No.    Name                    Books Issued\n";
    std::cout << "====================================================\n";

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        student.report();
    }

    inFile.close();
}

void bookIssue() {
    std::fstream bookFile("book.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::fstream studentFile("student.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::string admissionNumber, bookNumber;
    bool foundStudent = false, foundBook = false;
    Student student;
    Book book;

    std::cout << "\n\nBOOK ISSUE...\n";
    std::cout << "\nEnter Student Admission Number: ";
    std::cin >> admissionNumber;
    std::cout << "Enter Book Number: ";
    std::cin >> bookNumber;

    while (studentFile.read(reinterpret_cast<char*>(&student), sizeof(Student)) && !foundStudent) {
        if (student.retAdmissionNumber() == admissionNumber) {
            foundStudent = true;
            if (student.retToken() == 0) {
                while (bookFile.read(reinterpret_cast<char*>(&book), sizeof(Book)) && !foundBook) {
                    if (book.retBookNumber() == bookNumber) {
                        foundBook = true;
                        student.addToken();
                        student.setBookNumber(bookNumber);
                        studentFile.seekp(-static_cast<int>(sizeof(Student)), std::ios::cur);
                        studentFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
                        std::cout << "\nBook issued successfully.\n";
                    }
                }
                if (!foundBook) {
                    std::cout << "Book number does not exist.\n";
                }
            } else {
                std::cout << "Student already has a book issued.\n";
            }
        }
    }
    if (!foundStudent) {
        std::cout << "Student record not found.\n";
    }
}

void bookDeposit() {
    std::fstream bookFile("book.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::fstream studentFile("student.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::string admissionNumber;
    bool foundStudent = false, foundBook = false;
    Student student;

    std::cout << "\n\nBOOK DEPOSIT...\n";
    std::cout << "\nEnter Student Admission Number: ";
    std::cin >> admissionNumber;

    while (studentFile.read(reinterpret_cast<char*>(&student), sizeof(Student)) && !foundStudent) {
        if (student.retAdmissionNumber() == admissionNumber) {
            foundStudent = true;
            if (student.retToken() == 1) {
                std::cout << "Book Deposited Successfully.\n";
                student.resetToken();
                studentFile.seekp(-static_cast<int>(sizeof(Student)), std::ios::cur);
                studentFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
            } else {
                std::cout << "No book is issued to this student.\n";
            }
        }
    }
    if (!foundStudent) {
        std::cout << "Student record not found.\n";
    }
}

void intro() {
    std::cout << "\n\n\n\tLIBRARY MANAGEMENT SYSTEM";
    std::cout << "\n\n\tMADE BY: Aashish Thapa\n\n";
    std::cout << "\n\n\nPress any key to continue...";
    std::cin.get();
}

int main() {
    char choice;
    intro();

    do {
        std::cout << "\n\n\n\tMAIN MENU";
        std::cout << "\n\n\t01. CREATE STUDENT RECORD";
        std::cout << "\n\n\t02. DISPLAY ALL STUDENTS RECORD";
        std::cout << "\n\n\t03. DISPLAY SPECIFIC STUDENT RECORD";
        std::cout << "\n\n\t04. MODIFY STUDENT RECORD";
        std::cout << "\n\n\t05. DELETE STUDENT RECORD";
        std::cout << "\n\n\t06. CREATE BOOK RECORD";
        std::cout << "\n\n\t07. DISPLAY ALL BOOKS";
        std::cout << "\n\n\t08. DISPLAY SPECIFIC BOOK";
        std::cout << "\n\n\t09. MODIFY BOOK RECORD";
        std::cout << "\n\n\t10. DELETE BOOK RECORD";
        std::cout << "\n\n\t11. ISSUE BOOK";
        std::cout << "\n\n\t12. DEPOSIT BOOK";
        std::cout << "\n\n\t13. EXIT";
        std::cout << "\n\n\tPlease select your option (1-13): ";
        std::cin >> choice;

        switch (choice) {
        case '1':
            writeStudent();
            break;
        case '2':
            displayAllStudents();
            break;
        case '3': {
            std::string admissionNumber;
            std::cout << "\n\nEnter The Admission Number: ";
            std::cin >> admissionNumber;
            displaySpecificStudent(admissionNumber);
            break;
        }
        case '4':
            modifyStudent();
            break;
        case '5':
            deleteStudent();
            break;
        case '6':
            writeBook();
            break;
        case '7':
            displayAllBooks();
            break;
        case '8': {
            std::string bookNumber;
            std::cout << "\n\nEnter The Book Number: ";
            std::cin >> bookNumber;
            displaySpecificBook(bookNumber);
            break;
        }
        case '9':
            modifyBook();
            break;
        case '10':
            deleteBook();
            break;
        case '11':
            bookIssue();
            break;
        case '12':
            bookDeposit();
            break;
        case '13':
            exit(0);
        default:
            std::cout << "\a";
        }
    } while (choice != '13');

    return 0;
}
