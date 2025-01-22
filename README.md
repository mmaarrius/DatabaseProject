FACULTY PROJECT

## Project Overview
This README provides an overview of my implementations for Database Project.

## Introduction
In database.txt is an example of database.In 'studenti' we memorise id, name, overall grade, status, in 'materii' subject id, name, prof name, in 'inrolari' student id, subject id, notes (3 notes).

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
