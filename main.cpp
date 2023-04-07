/*
 * АиСД-2, 2023, задание 5
 * Кадыкова Татьяна Алексеевна
 * БПИ213
 * CLion
 * Сделаны изменения времени и количества операцией алгоритмов: наивный поиск вхождений в текст,
 * алгоритм КМП (стандартный), алгоритм КМП (с уточненными гранями)
 * для четырех текстов и размеров шаблонов 100-3000 с шагом 100
 * и запись результатов в таблицы
 */

#include <iostream>
#include <chrono>
#include <fstream>

#include "generate.cpp"
#include "utils.cpp"
#include "algorithms/naive.cpp"
#include "algorithms/KMP_SmartBrs.cpp"

std::vector<std::vector<int> (*)(std::string, std::string, uint64_t *)> algs({
    naive, standardKmp, smartKmp
});
std::vector<std::string> alg_names({
    "Naive Comparison", "Standard KMP", "Optimal KMP"
});

std::vector<std::string> texts({
    binaryText(10000), binaryText(100000),
    dnaText(10000), dnaText(100000)
});
std::vector<std::string> text_names({
    "Binary Small Text", "Binary Large Text",
    "DNA Small Text", "DNA Large Text"
});

std::vector<std::vector<std::string>> samples({
    getSamples(texts[0]), getSamples(texts[1]), getSamples(texts[2]), getSamples(texts[3])
});
std::vector<std::vector<int>> indexes_insert = genIndexes();

std::vector<uint64_t> computing_times(algs.size() * texts.size());
std::vector<uint64_t> operations_count(algs.size() * texts.size());

void calculateComputingTimes(int sample_num) {
    for (int k = 0; k < texts.size(); ++k) {
        std::string sample = samples[k][sample_num];
        for (int j = 0; j < algs.size(); ++j) {
            computing_times[k * algs.size() + j] = 0;
            int iterations = 10;
            for (int i = 0; i < iterations; ++i) {
                operations_count[k * algs.size() + j] = 0;
                auto start = std::chrono::high_resolution_clock::now();
                std::vector<int> entries = algs[j](sample, texts[k],
                                                   &operations_count[k * algs.size() + j]);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                if (!checker(entries, sample, texts[k])) {
                    std::cout << "failed to calculate entries of sample:\n" << sample <<
                        "\nof the text\n" << texts[k] <<
                        "\nusing " << alg_names[j] << "\nEntries:\n";
                    printArray(entries);
                }
                computing_times[k * algs.size() + j] +=
                    std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
            }
            computing_times[k * algs.size() + j] /= iterations;
        }
    }
}

std::string getNames() {
    std::string first_row = "Sample sizes";
    for (int k = 0; k < texts.size(); ++k) {
        for (int j = 0; j < algs.size(); ++j) {
            first_row.append(";" + text_names[k] + " & " + alg_names[j]);
        }
    }
    first_row.append("\n");
    return first_row;
}

void fillTableRow(std::ofstream *stream_time, std::ofstream *stream_oper, int sample_num) {
    calculateComputingTimes(sample_num);
    std::string table_row = std::to_string(100 + sample_num * 100);
    for (auto comp_time : computing_times) {
        table_row.append(";" + std::to_string(comp_time));
    }
    table_row.append("\n");
    *stream_time << table_row;

    table_row = std::to_string(100 + sample_num * 100);
    for (auto operations : operations_count) {
        table_row.append(";" + std::to_string(operations));
    }
    table_row.append("\n");
    *stream_oper << table_row;
}

void updateSamples(int num) {
    if (num == 0) {
        return;
    }
    for (int k = 0; k < samples.size(); ++k) {
        for (int j = 0; j < samples[k].size(); ++j) {
            for (int i = 0; i < num; ++i) {
                samples[k][j][indexes_insert[k][num]] = '?';
            }
        }
    }
}

void createTable(int num_of_q) {
    updateSamples(num_of_q);
    std::ofstream table_time("/mnt/c/Users/tanya/Documents/CLionProjects/HSE-HW2/tables/БПИ213_Кадыкова_"
                             + std::to_string(num_of_q)
                             + "AddsComputingTime.csv");
    std::ofstream table_oper("/mnt/c/Users/tanya/Documents/CLionProjects/HSE-HW2/tables/БПИ213_Кадыкова_"
                             + std::to_string(num_of_q)
                             + "AddsOperations.csv");
    table_time << getNames();
    table_oper << getNames();
    for (int sample_num = 0; sample_num < samples[0].size(); ++sample_num) {
        fillTableRow(&table_time, &table_oper, sample_num);
    }
    table_time.close();
    table_oper.close();
}

int main() {
    for (int i = 0; i <= 4; ++i) {
        createTable(i);
    }
    return 0;
}
