#include <iostream> 
#include <fstream> 
#include <vector> 
#include <chrono> 
#include <string> 
#include <cstdlib> 
#include <ctime> 
#include <algorithm> 
 
using namespace std; 
 
struct StudentRecord { 
    int student_id;       // Номер зачетной книжки (ключ) 
    int group_number;     // Номер группы 
    string full_name;     // ФИО 
}; 
 
// Структура для хранения и смещения ID зачетки 
struct IndexEntry { 
    int student_id; 
    streampos offset; 
}; 
 
// Генерация текстового файла 
void generate_text_file(const string& filename, int num_records) { 
    ofstream text_file(filename); 
    if (!text_file.is_open()) { 
        cerr << "Не удалось открыть файл: " << filename << endl; 
        exit(0); 
    } 
 
    srand(static_cast<unsigned>(time(0))); 
    vector<int> unique_ids; 
 
    for (int i = 0; i < num_records; ++i) { 
        int student_id; 
        do { 
            student_id = 100000 + rand() % 900000; 
        } while (find(unique_ids.begin(), unique_ids.end(), student_id) != unique_ids.end()); 
 
        unique_ids.push_back(student_id); 
 
        int group_number = 100 + rand() % 900; // Номер группы от 100 до 999 
        string full_name = "Фамилия" + to_string(i + 1) + " Имя" + to_string(i + 1) + " Отчество" + to_string(i + 1); 
 
        text_file << student_id << " " << group_number << " " << full_name << endl; 
    } 
 
    text_file.close(); 
} 
 
// Преобразование текстового файла в бинарный файл 
void convert_to_binary_file(const string& text_filename, const string& binary_filename, vector<IndexEntry>& index_table) { 
    ifstream text_file(text_filename); 
    ofstream binary_file(binary_filename, ios::binary); 
 
    if (!text_file.is_open() || !binary_file.is_open()) { 
        cerr << "Не удалось открыть файл." << endl; 
        exit(0); 
    } 
 
    StudentRecord record; 
    while (text_file >> record.student_id >> record.group_number) { 
        text_file.ignore(); // Игнорируем пробел перед ФИО 
        getline(text_file, record.full_name); 
 
        streampos offset = binary_file.tellp(); // Запоминаем текущее смещение 
 
        binary_file.write(reinterpret_cast<const char*>(&record.student_id), sizeof(record.student_id)); 
        binary_file.write(reinterpret_cast<const char*>(&record.group_number), sizeof(record.group_number)); 
 
        size_t name_length = record.full_name.size(); 
        binary_file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length)); 
        binary_file.write(record.full_name.c_str(), name_length); 
 
        // Добавляем запись в индекс 
        index_table.push_back({ record.student_id, offset }); 
    } 
 
    text_file.close(); 
    binary_file.close(); 
 
    // Сортируем индекс по student_id 
    sort(index_table.begin(), index_table.end(), [](const IndexEntry& a, const IndexEntry& b) { 
        return a.student_id < b.student_id; 
        }); 
} 
 
// Бинарный поиск по индексу для получения смещения 
streampos binary_search(const vector<IndexEntry>& index_table, int key) { 
    int left = 0; 
    int right = index_table.size() - 1; 
 
    while (left <= right) { 
        int mid = left + (right - left) / 2; 
        if (index_table[mid].student_id == key) { 
            return index_table[mid].offset; // Возвращаем смещение записи 
        } 
        else if (index_table[mid].student_id < key) { 
            left = mid + 1; 
        } 
        else { 
            right = mid - 1; 
        } 
    } 
 
    return -1; // Не найдено 
} 
 
// Чтение записи по смещению 
StudentRecord read_record_from_file(const string& binary_filename, streampos offset) { 
    ifstream binary_file(binary_filename, ios::binary); 
    if (!binary_file.is_open()) { 
 
        cerr << "Не удалось открыть бинарный файл." << endl; 
        exit(0); 
    } 
 
    binary_file.seekg(offset); // Переходим к смещению 
    StudentRecord record; 
 
    binary_file.read(reinterpret_cast<char*>(&record.student_id), sizeof(record.student_id)); 
    binary_file.read(reinterpret_cast<char*>(&record.group_number), sizeof(record.group_number)); 
 
    size_t name_length; 
    binary_file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length)); 
    record.full_name.resize(name_length); 
    binary_file.read(&record.full_name[0], name_length); 
 
    binary_file.close(); 
    return record; // Возвращаем найденную запись 
} 
 
int main() { 
    
    setlocale(0, "");
    cout << ("\e[1;1H\e[2J");  // Очистка экрана с помощью escape-последовательности 
 
    // Генерируем файлы 
    int num_records = 10000; 
    string text_filename = "students.txt"; 
    string binary_filename = "students.bin"; 
 
    generate_text_file(text_filename, num_records); 
 
    vector<IndexEntry> index_table; 
    convert_to_binary_file(text_filename, binary_filename, index_table); 
 
    // Проверка времени выполнения поиска 
    int key_to_find; 
    cout << "Введите номер зачётки: "; 
 cin >> key_to_find;  
    cout << endl; 
    auto start = chrono::high_resolution_clock::now(); 
 
    streampos offset = binary_search(index_table, key_to_find); 
 
    if (offset != -1) { 
        StudentRecord found_record = read_record_from_file(binary_filename, offset); 
        cout << "Найден студент с номером зачетки " << found_record.student_id << ": Группа: " << found_record.group_number << " | ФИО: " << found_record.full_name << endl; 
    } 
    else { 
        cout << "Студент с номером зачетки " << key_to_find << " не найден." << endl; 
    } 
 
    auto end = chrono::high_resolution_clock::now(); 
    chrono::duration<double, milli> duration = end - start; 
    cout << "Время выполнения поиска: " << duration.count() << " миллисекунд." << endl; 
 
    return 0; 
}