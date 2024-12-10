#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Структура для хранения данных о владельце телефона
struct PhoneOwner {
    string phoneNumber;   // ключ - номер телефона
    string ownerName;     // имя владельца
    string address;       // адрес

    // Конструктор по умолчанию
    PhoneOwner() : phoneNumber(""), ownerName(""), address("") {}

    // Параметризованный конструктор
    PhoneOwner(string phone, string name, string addr)
        : phoneNumber(phone), ownerName(name), address(addr) {}
};

// Класс для реализации хеш-таблицы с линейным пробированием
class HashTable {
private:
    vector<PhoneOwner> table;  // Таблица для хранения записей
    vector<bool> used;         // Флаги занятости ячеек
    int size;                  // Текущее количество элементов
    int capacity;              // Размер таблицы
    float loadFactor = 0.75;   // Коэффициент загрузки (максимальная заполненность)

    // Хеш-функция на основе модульного деления
    int hashFunction(string phoneNumber) {
        int hash = 0;
        for (char ch : phoneNumber) {
            hash = (hash * 31 + ch) % capacity;  // Хеширование с использованием простого умножения и деления
        }
        return hash;
    }

    // Функция для увеличения размера таблицы и перераспределения элементов
    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2;  // Увеличиваем размер таблицы вдвое
        vector<PhoneOwner> oldTable = table;

        table = vector<PhoneOwner>(capacity);   // Пересоздаем таблицу с новым размером
        used = vector<bool>(capacity, false);   // Обновляем флаги занятости
        size = 0;  // Обнуляем размер, так как при рехешировании элементы будут вставляться заново

        // Переносим старые элементы в новую таблицу
        for (int i = 0; i < oldCapacity; ++i) {
            if (used[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Конструктор с начальным размером таблицы
    HashTable(int cap = 7) : capacity(cap), size(0) {
        table.resize(capacity);    // Резервируем место в таблице
        used.resize(capacity, false);  // Изначально все ячейки свободны
    }

    // Вставка новой записи в таблицу
    void insert(PhoneOwner owner) {
        if ((float)size / capacity >= loadFactor) {
            rehash();  // Рехеширование при превышении коэффициента загрузки
        }

        int index = hashFunction(owner.phoneNumber);

        // Линейное пробирование для поиска свободной ячейки
        while (used[index]) {
            if (table[index].phoneNumber == owner.phoneNumber) {
                cout << "Ошибка: номер телефона уже существует!" << endl;
                return;
            }
            index = (index + 1) % capacity;  // Переход к следующей ячейке
        }

        table[index] = owner;    // Вставка нового элемента
        used[index] = true;      // Устанавливаем флаг занятости
        size++;                  // Увеличиваем размер таблицы
        cout << "Запись успешно добавлена: " << owner.phoneNumber << endl;
    }

    // Удаление записи по номеру телефона
    void remove(string phoneNumber) {
        int index = hashFunction(phoneNumber);

        // Поиск записи для удаления
        while (used[index]) {
            if (table[index].phoneNumber == phoneNumber) {
                used[index] = false;  // Удаление записи
                size--;
                cout << "Запись с номером " << phoneNumber << " удалена." << endl;
                return;
            }
            index = (index + 1) % capacity;
        }

        cout << "Запись с номером " << phoneNumber << " не найдена." << endl;
    }

    // Поиск записи по номеру телефона
    PhoneOwner* search(string phoneNumber) {
        int index = hashFunction(phoneNumber);

        // Поиск элемента в таблице
        while (used[index]) {
            if (table[index].phoneNumber == phoneNumber) {
                return &table[index];
            }
            index = (index + 1) % capacity;
        }

        return nullptr;  // Запись не найдена
    }

    // Вывод всех записей в таблице
    void display() {
        cout << left << setw(15) << "Номер          " << setw(20) << "Имя владельца      " << setw(30) << "Адрес" << endl;
        cout << string(65, '-') << endl;

        // Перебор всех ячеек таблицы
        for (int i = 0; i < capacity; ++i) {
            if (used[i]) {  // Печать только занятых ячеек
                cout << left << setw(15) << table[i].phoneNumber
                     << setw(20) << table[i].ownerName
                     << setw(30) << table[i].address << endl;
            }
        }
    }
};

// Автоматическое заполнение таблицы 5-7 записями для тестирования
void automaticFill(HashTable &table) {
    table.insert(PhoneOwner("1234567890", "Ivan Ivanov", "Moscow"));
    table.insert(PhoneOwner("0987654321", "Petr Petrov", "Saint Petersburg"));
    table.insert(PhoneOwner("1112223334", "Sergey Sergeev", "Kazan"));
    table.insert(PhoneOwner("5556667778", "Anna Smirnova", "Sochi"));
    table.insert(PhoneOwner("3334445556", "Olga Sokolova", "Novosibirsk"));
}

// Текстовое меню для взаимодействия с пользователем
void userInterface(HashTable &table) {
    int choice;
    do {
        cout << "\nМеню:\n"
             << "1. Добавить запись\n"
             << "2. Удалить запись\n"
             << "3. Найти запись\n"
             << "4. Показать все записи\n"
             << "5. Выйти\n"
             << "Введите номер операции: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string phone, name, address;
                cout << "Введите номер телефона (10 символов): ";
                cin >> phone;
                cout << "Введите имя владельца: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введите адрес: ";
                getline(cin, address);
                table.insert(PhoneOwner(phone, name, address));
                break;
            }
            case 2: {
                string phone;
                cout << "Введите номер телефона для удаления: ";
                cin >> phone;
                table.remove(phone);
                break;
            }
            case 3: {
                string phone;
                cout << "Введите номер телефона для поиска: ";
                cin >> phone;
                PhoneOwner* owner = table.search(phone);
                if (owner) {
                    cout << "Найдено: " << owner->phoneNumber << ", "
                         << owner->ownerName << ", " << owner->address << endl;
                } else {
                    cout << "Запись не найдена." << endl;
                }
                break;
            }
            case 4:
                table.display();
                break;
            case 5:
                cout << "Выход..." << endl;
                break;
            default:
                cout << "Неверный выбор, попробуйте снова." << endl;
        }
    } while (choice != 5);
}

// Главная функция программы
int main() {
    setlocale(0, ""); 
    cout << ("\e[1;1H\e[2J"); 

    HashTable table;  // Создаем хеш-таблицу
    
    cout << "Автоматическое заполнение таблицы 5 записями..." << endl;
    automaticFill(table);  // Заполняем таблицу тестовыми записями
    
    userInterface(table);  // Запуск меню для взаимодействия с пользователем
    
    return 0;
}


/*
Ниже приведен пример программы на языке C++, которая реализует хеш-таблицу с использованием метода линейного пробирования и выполняет операции вставки, удаления, поиска и вывода данных. Для тестирования предусмотрены 5-7 автоматических записей, а также предусмотрен командный интерфейс для взаимодействия с пользователем.

Структура данных
Каждый элемент в хеш-таблице представляет собой запись с полями:

Номер телефона (ключ) — строка длиной 10 символов.
Владелец телефона — строка с именем владельца.
Адрес — строка с адресом владельца.

Описание программы:
Класс HashTable реализует хеш-таблицу с методами вставки, удаления, поиска и вывода всех записей.
Линейное пробирование используется для разрешения коллизий, когда два разных ключа хешируются в одно и то же место.
Рехеширование выполняется автоматически, если таблица заполнена более чем на 75%.
Программа начинает с автоматической вставки 5 записей и предлагает текстовый интерфейс для взаимодействия с пользователем.
Тестирование
Автоматическое заполнение — в таблицу добавляются 5 записей.
Добавление — можно добавить новую запись вручную.
Удаление — можно удалить существующую запись.
Поиск — поиск записи по номеру телефона.
Вывод — вывод всех записей в таблице.
*/
