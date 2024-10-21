#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

// Константы для ПСП
const int size1 = 17;
const int size2 = 111;


// Функция генерации ПСП
void generate_psp(std::vector<int>& psp, int num_bits) {
    int Array1[size1];
    int Array2[size2];

    srand(time(nullptr));

    // Инициализация регистров случайными числами (0 или 1)
    for (int i = 0; i < size1; ++i) {
        Array1[i] = rand() % 2;
    }
    for (int i = 0; i < size2; ++i) {
        Array2[i] = rand() % 2;
    }

    int p0 = 0, p14 = 14, p17 = 17;
    int p101 = 101, p111 = 111;

    // Генерация ПСП длиной num_bits
    for (int i = 0; i < num_bits; ++i) {
        int bit1 = Array1[(p14 - 1 + size1) % size1] ^ Array1[(p17 - 1 + size1) % size1];
        int bit2 = Array2[(p101 - 1 + size2) % size2] ^ Array2[(p111 - 1 + size2) % size2];

        psp.push_back(bit1 ^ bit2);  // XOR двух ПСП для получения итогового бита

        // Обновление указателей для регистра 1
        p0 = (p0 + size1 - 1) % size1;
        p14 = (p14 + size1 - 1) % size1;
        p17 = (p17 + size1 - 1) % size1;
        Array1[p0] = bit1;

        // Обновление указателей для регистра 2
        p0 = (p0 + size2 - 1) % size2;
        p101 = (p101 + size2 - 1) % size2;
        p111 = (p111 + size2 - 1) % size2;
        Array2[p0] = bit2;
    }
}

// Функция для маскирования и обратного маскирования файла
void process_file(const std::string& input_file, const std::string& output_file, bool mask_header, size_t header_size = 0, bool reverse = false) {
    // Открываем входной файл для чтения
    std::ifstream infile(input_file, std::ios::binary);
    if (!infile) {
        std::cerr << "Ошибка при открытии входного файла: " << input_file << std::endl;
        return;
    }

    // Считываем данные из файла
    std::vector<char> data((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    size_t file_size = data.size();

    // Генерация ПСП для маскирования или восстановления
    std::vector<int> psp;
    size_t psp_size = mask_header ? file_size : (file_size - header_size);
    generate_psp(psp, psp_size);

    // Маскирование или восстановление данных
    for (size_t i = (mask_header ? 0 : header_size); i < file_size; ++i) {
        data[i] ^= psp[i - (mask_header ? 0 : header_size)];  // XOR с ПСП
    }

    // Открываем выходной файл для записи
    std::ofstream outfile(output_file, std::ios::binary);
    if (!outfile) {
        std::cerr << "Ошибка при открытии выходного файла: " << output_file << std::endl;
        return;
    }

    // Записываем обработанные данные
    outfile.write(data.data(), data.size());
    outfile.close();

    std::cout << (reverse ? "Восстановление завершено: " : "Маскирование завершено: ") << output_file << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "russian");
    std::string input_file = "input.txt";     // Имя входного файла для маскирования
    std::string masked_file = "masked.txt";   // Имя зашифрованного файла
    std::string restored_file = "restored.txt"; // Имя восстановленного файла
    bool mask_header = true;  // Установите true для полного маскирования или false для маскирования без заголовка
    size_t header_size = 100;  // Размер заголовка, если есть, в байтах

    // Маскирование файла
    process_file(input_file, masked_file, mask_header, header_size);

    // Восстановление исходного файла
    process_file(masked_file, restored_file, mask_header, header_size, true);

    return 0;
}
