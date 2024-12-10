#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Структура элемента множества
struct Record {
    string phone_number; // Ключ - номер телефона (10 символов)
    string owner;        // Владелец телефона
    string address;      // Адрес

    Record() : phone_number(""), owner(""), address("") {}
    Record(string phone, string own, string addr)
        : phone_number(phone), owner(own), address(addr) {}
};

// Класс хеш-таблицы
class HashTable {
private:
    vector<Record> table;      // Массив записей
    vector<bool> occupied;     // Занятые ячейки
    int size;                  // Текущий размер таблицы
    int count;                 // Количество элементов

    // Хеш-функция для строки (по номеру телефона)
    int hash(string key) {
        int hash_value = 0;
        for (char c : key) {
            hash_value = (hash_value * 31 + c) % size;
        }
        return hash_value;
    }

    // Рехеширование при увеличении размера
    void rehash() {
        int old_size = size;
        size *= 2;  // Увеличиваем размер таблицы вдвое
        vector<Record> old_table = table;
        vector<bool> old_occupied = occupied;

        // Создаем новые пустые таблицы
        table = vector<Record>(size);
        occupied = vector<bool>(size, false);
        count = 0;

        // Перемещаем старые данные в новую таблицу
        for (int i = 0; i < old_size; ++i) {
            if (old_occupied[i]) {
                insert(old_table[i].phone_number, old_table[i].owner, old_table[i].address);
            }
        }
    }

public:
    // Конструктор
    HashTable(int initial_size = 7) : size(initial_size), count(0) {
        table = vector<Record>(size);
        occupied = vector<bool>(size, false);
    }

    // Вставка записи
    void insert(string phone_number, string owner, string address) {
        if (count >= size / 2) {
            rehash(); // Рехеширование, если таблица заполнена более чем на 50%
        }

        int index = hash(phone_number);
        int start_index = index;
        while (occupied[index]) {  // Линейное пробирование
            index = (index + 1) % size;
            if (index == start_index) {
                cout << "Таблица заполнена." << endl;
                return;
            }
        }
        table[index] = Record(phone_number, owner, address);
        occupied[index] = true;
        count++;
    }

    // Удаление записи по номеру телефона
    void remove(string phone_number) {
        int index = hash(phone_number);
        int start_index = index;
        while (occupied[index]) {
            if (table[index].phone_number == phone_number) {
                occupied[index] = false; // Помечаем как пустую ячейку
                count--;
                cout << "Запись удалена." << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start_index) {
                cout << "Запись не найдена." << endl;
                return;
            }
        }
        cout << "Запись не найдена." << endl;
    }

    // Поиск записи по номеру телефона
    void search(string phone_number) {
        int index = hash(phone_number);
        int start_index = index;
        while (occupied[index]) {
            if (table[index].phone_number == phone_number) {
                cout << "Найдено: " << table[index].owner << ", Адрес: " << table[index].address << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start_index) {
                cout << "Запись не найдена." << endl;
                return;
            }
        }
        cout << "Запись не найдена." << endl;
    }

    // Вывод всех записей
    void display() {
        cout << "Текущие записи в хеш-таблице:" << endl;
        for (int i = 0; i < size; ++i) {
            if (occupied[i]) {
                cout << "Номер телефона: " << table[i].phone_number
                     << ", Владелец: " << table[i].owner
                     << ", Адрес: " << table[i].address << endl;
            }
        }
    }
};

// Тестирование программы
int main() {
    HashTable hashTable;

    // Вставка записей
    hashTable.insert("1234567890", "Alice", "Street 1");
    hashTable.insert("0987654321", "Bob", "Street 2");
    hashTable.insert("1112223334", "Charlie", "Street 3");
    hashTable.insert("5556667778", "Dave", "Street 4");
    hashTable.insert("9998887776", "Eve", "Street 5");

    // Вывод всех записей
    hashTable.display();

    // Поиск записей
    cout << "Поиск записи по номеру 1234567890:" << endl;
    hashTable.search("1234567890");

    // Удаление записи
    cout << "Удаление записи с номером 0987654321:" << endl;
    hashTable.remove("0987654321");

    // Повторный вывод всех записей
    hashTable.display();

    // Вставка дополнительных записей для проверки рехеширования
    hashTable.insert("2223334445", "Frank", "Street 6");
    hashTable.insert("3334445556", "Grace", "Street 7");

    // Вывод после рехеширования
    hashTable.display();

    return 0;
}


/*
Для разработки приложения на C++, которое использует хеш-таблицу с методами вставки, удаления, поиска и вывода элементов множества, а также поддерживает операции расширения таблицы и рехеширования при необходимости, будем использовать структуру данных с элементами множества, состоящими из следующих полей:

Ключ (номер телефона) — строка из 10 символов.
Владелец телефона — строка.
Адрес — строка.
Хеш-таблица будет реализована с использованием метода открытой адресации и линейного пробирования для разрешения коллизий. Мы также реализуем механизмы для динамического расширения таблицы и повторного хеширования при необходимости.

Структура программы
Класс HashTable: Этот класс будет содержать методы для работы с хеш-таблицей, такие как вставка, удаление, поиск, вывод данных, расширение таблицы и рехеширование.
Класс Record: Этот класс будет представлять запись в хеш-таблице, содержащую ключ и дополнительные данные.
Основные методы класса HashTable:
Вставка элемента.
Удаление элемента.
Поиск элемента по ключу.
Рехеширование при переполнении.

Объяснение программы:
Хеш-функция: Мы используем простую хеш-функцию, которая вычисляет значение по строке (номер телефона) и возвращает индекс для размещения элемента в таблице.
Линейное пробирование: Если возникает коллизия (ячейка уже занята), используется линейное пробирование, при котором продолжается поиск следующей свободной ячейки.
Рехеширование: Когда таблица заполнена более чем на 50%, ее размер увеличивается вдвое, и все записи переносятся в новую таблицу.
Командный интерфейс: Пользователь может выполнять операции вставки, удаления, поиска и вывода элементов.
Тестирование:
Программа вставляет несколько элементов и выводит таблицу.
Проверяются операции поиска, удаления, и рехеширование.
*/