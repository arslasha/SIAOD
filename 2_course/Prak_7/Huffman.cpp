#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

// Узел дерева Хаффмана
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// Сравнение для очереди с приоритетами
struct Compare {
    bool operator()(Node *a, Node *b) {
        return a->freq > b->freq;
    }
};

// Рекурсивная функция для построения кодов
void buildHuffmanCodes(Node *root, string code, unordered_map<char, string> &codeMap) {
    if (!root) return;
    if (root->ch != '\0') {
        codeMap[root->ch] = code;
    }
    buildHuffmanCodes(root->left, code + "0", codeMap);
    buildHuffmanCodes(root->right, code + "1", codeMap);
}

// Функция для сжатия текста
string compressHuffman(const string &text, unordered_map<char, string> &codeMap) {
    string compressed = "";
    for (char ch : text) {
        compressed += codeMap[ch];
    }
    return compressed;
}

// Функция для декодирования текста
string decompressHuffman(const string &compressed, Node *root) {
    string decompressed = "";
    Node *current = root;
    for (char bit : compressed) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            decompressed += current->ch;
            current = root;
        }
    }
    return decompressed;
}

int main() {
    string text = "Прибавь к ослиной голове Еще одну, получишь две. Но сколько б ни было ослов, Они и двух не свяжут слов.";

    // Подсчет частот символов
    unordered_map<char, int> frequencyMap;
    for (char ch : text) {
        frequencyMap[ch]++;
    }

    // Построение дерева Хаффмана
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto &pair : frequencyMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node *root = pq.top();

    // Построение кодов Хаффмана
    unordered_map<char, string> codeMap;
    buildHuffmanCodes(root, "", codeMap);

    // Сжатие текста
    string compressed = compressHuffman(text, codeMap);
    cout << "Compressed: " << compressed << endl;

    // Восстановление текста
    string decompressed = decompressHuffman(compressed, root);
    cout << "Decompressed: " << decompressed << endl;

    return 0;
}
