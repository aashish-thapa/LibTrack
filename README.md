# Library Management System

## Overview

The Library Management System is a console-based application that allows librarians to manage book and student records efficiently. This application supports adding, modifying, and deleting records for both books and students, as well as issuing and depositing books to and from students. It ensures smooth operation and management of the library by tracking issued books and preventing students from borrowing more than one book at a time.

## Features

- **Book Management:**
  - Add new book records.
  - Display all book records.
  - Display specific book records.
  - Modify existing book records.
  - Delete book records.

- **Student Management:**
  - Add new student records.
  - Display all student records.
  - Display specific student records.
  - Modify existing student records.
  - Delete student records.

- **Book Issue and Deposit:**
  - Issue a book to a student.
  - Deposit a book from a student.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++11 or later.

### Compilation and Execution

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/aashish-thapa/library-management-system.git
   cd library-management-system
   ```
   
2.Compile the Code:
  ```sh
  g++ -o library_management_system main.cpp
```
3.Run the Application:
```sh
./library_management_system
```

Usage
Upon running the application, you will be presented with a menu offering various options for managing books and students. The options are self-explanatory and guide you through the necessary steps for each action.

Code Structure
main.cpp: Contains the main function and the core logic of the application.
Book class: Manages book-related information and operations.
Student class: Manages student-related information and operations.
File Operations: Uses file streams to read and write book and student records from/to binary files.
Contributing
If you wish to contribute to this project, please fork the repository and create a pull request with your changes. We welcome all contributions!

License
This project is licensed under the MIT License. See the LICENSE file for more details.

Author
Aashish Thapa
Acknowledgements
This project is inspired by the need to manage library records efficiently.
Thanks to all contributors and users who have provided feedback and suggestions.
markdown
Copy code

---






