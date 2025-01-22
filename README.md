FACULTY PROJECT

## Project Overview
This README provides an overview of my implementations for Database Project.

## Introduction
Database looks like:
[STUDENTI]
0, Nicolescu Elena, 3, t
1, Pogoran Adrian, 4, b
2, Trandaf Denisa, 1, b
[MATERII]
0, USO, Roman Florentina
1, PCLP1, Pancila Daniela
[INROLARI]
0, 1, 3.37 2.00 3.35
0, 0, 2.65 2.00 2.07
1, 1, 2.34 0.39 0.11

where is memorised: id, name, overall notes, status(studenti), id, name, prof name(materii),
stud id, subject id, notes(inrolari)

## Files Descriptions
### `task1.c`
- **Description**: Implements basic operations like reading, adding and deleting of database Secretariat.
- **Key Functions**:
    - `citeste_secretariat()`: Takes every line of file, looks for title or instance, splits the line and adds to the database.
    - `adauga_student()`: Gets parameters of student, increases the number of array with one and adds student on the last position. 
    - `elibereaza_secretariat()`: Just deletes a secretariat`s array type. 

### `task2.c`
- **Description**: Provides useful commands just like SELECT, UPDATE, DELETE to modify database.
- **Key Functions**:
    - `select_fun()`: Extracts category of structure. Every field is associated with a number and memorises the order of fields into an int array. At every instanse , it`s crossing the array with codes and prints parameter associated with the number.
    - `update_fun()`: First extracts conditions and setting command. Condition: is splitting into field, operator, value, then field value from database is associated to a variable and depending of operator, it is compared to extracted value from command. Setting command is spliting like condition and extracted field from database is equalized with the value.
    - `delete_fun()`: First extracts conditions and verifies them for every line. If instance must deleted, then its index is noted into an array, then when the database is copied into another database, the indexes noted are ignored.

### `task3.c`
- **Description**: Provides complex operations of encrypting like Cipher Block Chaining.
- **Key Functions**:
    - `cripteaza_studenti()`: Encrypts the data with Cipher Block Chaining algorithm.
    - `split_into_blocks_and_pad()`: The function transforms all bytes of student data in 4 equals blocks, padding with null bytes if it s necessary.
    - `XOR()`: Makes XOR operation between a key and block, or block and block...
    - `P_BOX()`: With a bijective formula, rearranges the order of bytes.
