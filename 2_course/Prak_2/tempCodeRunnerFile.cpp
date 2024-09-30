#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Структура для записи студента
struct StudentRecord {
    int student_id;       // Номер зачетной книжки (ключ)
    int group_number;     // Номер группы
    string full_name;     // ФИО
};

// Генерация текстового файла с уникальными записями студентов
void generate_text_file(const string& filename, int num_records) {
    ofstream text_file(filename);
    if (!text_file.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        exit(0);
    }

    srand((time(0)));
    vector<int> unique_ids;

    for (int i = 0; i < num_records; ++i) {
        int student_id;
        do {
            student_id = 100000 + rand() % 900000; // Уникальные номера зачетных книжек
        } while (find(unique_ids.begin(), unique_ids.end(), student_id) != unique_ids.end());

        unique_ids.push_back(student_id);

        int group_number = 100 + rand() % 900; // Номер группы от 100 до 999
        string full_name = "Фамилия" + to_string(i + 1) + " Имя" + to_string(i + 1) + " Отчество" + to_string(i + 1);

        text_file << student_id << " " << group_number << " " << full_name << endl;
    }

    text_file.close();
}

// Преобразование текстового файла в бинарный файл
void convert_to_binary_file(const string& text_filename, const string& binary_filename) {
    ifstream text_file(text_filename);
    ofstream binary_file(binary_filename, ios::binary);

    if (!text_file.is_open() || !binary_file.is_open()) {
        cerr << "Не удалось открыть файл." << endl;
        exit(0);
    }

    StudentRecord record;
    while (text_file >> record.student_id >> record.group_number) {
        text_file.ignore(); // Игнорируем пробел перед ФИО
        getline(text_file, record.full_name); // Читаем ФИО

        binary_file.write(reinterpret_cast<const char*>(&record.student_id), sizeof(record.student_id));
        binary_file.write(reinterpret_cast<const char*>(&record.group_number), sizeof(record.group_number));

        size_t name_length = record.full_name.size();
        binary_file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
        binary_file.write(record.full_name.c_str(), name_length);
    }

    text_file.close();
    binary_file.close();
}

// Поиск в бинарном файле
StudentRecord linear_search(const string& binary_filename, int key) {
    ifstream binary_file(binary_filename, ios::binary);
    if (!binary_file.is_open()) {
        cerr << "Не удалось открыть бинарный файл." << endl;
        exit(0);
    }

    StudentRecord record;
    while (binary_file.read(reinterpret_cast<char*>(&record.student_id), sizeof(record.student_id))) {
        binary_file.read(reinterpret_cast<char*>(&record.group_number), sizeof(record.group_number));

        size_t name_length;
        binary_file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
        record.full_name.resize(name_length);
        binary_file.read(&record.full_name[0], name_length);

        if (record.student_id == key) {  // Если найден нужный ключ
            binary_file.close();
            return record;  // Возвращаем найденную запись
        }
    }

    binary_file.close();
    return {};  // Возвращаем пустую структуру, если не найдено
}

// Функция для замера времени выполнения поиска
void perform_search_and_measure_time(const string& binary_filename, int key) {
    auto start = chrono::high_resolution_clock::now();  // Начало замера времени

    StudentRecord result = linear_search(binary_filename, key);  // Выполняем линейный поиск

    auto end = chrono::high_resolution_clock::now();  // Конец замера времени

    chrono::duration<double, milli> duration = end - start;  // Расчет времени поиска

    // Вывод результатов
    if (result.student_id != 0) {
        cout << "Запись найдена: " << result.student_id << ", Группа: " << result.group_number
             << ", ФИО: " << result.full_name << endl;
    } else {
        cout << "Запись с номером зачётки " << key << " не найдена." << endl;
    }

    // Вывод времени поиска
    cout << "Время поиска: " << duration.count() << " миллисекунд\n";
}

int main() {
    setlocale(0, "");  // Для корректного вывода русских символов

    const string text_filename = "students.txt";
    const string binary_filename = "students.bin";
    const vector<int> record_counts = { 100, 1000, 10000 };  // Количество записей для замеров

    for (int num_records : record_counts) {
        // Генерация текстового файла и преобразование его в бинарный файл
        generate_text_file(text_filename, num_records);
        convert_to_binary_file(text_filename, binary_filename);

        cout << "Данные записаны в бинарный файл для " << num_records << " записей." << endl;

        // Выполнение поиска для ключа (номер зачётки)
        int key_to_find = 100001;  // Пример ключа для поиска
        cout << "Поиск в файле с " << num_records << " записями:" << endl;
        perform_search_and_measure_time(binary_filename, key_to_find);
        cout << endl;
    }

    return 0;
}
