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
 
void generate_text_file(const string& filename, int num_records) {      //Создание файла 
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
            student_id = 100000 + rand() % 900000; 
        } while (find(unique_ids.begin(), unique_ids.end(), student_id) != unique_ids.end()); 
 
        unique_ids.push_back(student_id); 
 
        int group_number = 100 + rand() % 900; // Номер группы от 100 до 999 
        string full_name = "Фамилия" + to_string(i + 1) + " Имя" + to_string(i + 1) + " Отчество" + to_string(i + 1); 
 
        text_file << student_id << " " << group_number << " " << full_name << endl; 
    } 
 
    text_file.close(); 
} 
 
void convert_to_binary_file(const string& text_filename, const string& binary_filename) {       //Преобразование в бинарный файл 
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
 
int main() { 
    setlocale(0, ""); 
    cout << ("\e[1;1H\e[2J");  // Очистка экрана с помощью escape-последовательности
    const string text_filename = "students.txt"; 
    const string binary_filename = "students.dat"; 
    const int num_records = 100; 
 
    auto start = chrono::high_resolution_clock::now(); 
 
    generate_text_file(text_filename, num_records); 
    convert_to_binary_file(text_filename, binary_filename); 
 
    auto end = chrono::high_resolution_clock::now(); 
 
    cout << "Данные успешно записаны в бинарный файл!" << endl; 
 
    chrono::duration<double, milli> duration = end - start; 
    cout << "Время работы алгоритма: " << duration.count() << " миллисекунд" << endl; 
 
    return 0; 
}