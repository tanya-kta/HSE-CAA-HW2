#include <iostream>
#include <chrono>
#include <fstream>

#include "generate.cpp"
#include "utils.cpp"
#include "algorithms/naive.cpp"
#include "algorithms/KMP_SmartBrs.cpp"

std::vector<std::vector<int> (*)(std::string, std::string)> algs({
    naive, standardKmp, smartKmp
});
std::vector<std::string> alg_names({
    "Naive Comparison", "Standard KMP", "Optimal KMP"
});

std::vector<std::string> texts({
    binaryText(10000), binaryText(100000),
    dnaText(10000), dnaText(100000)
});
std::vector<std::vector<std::string>> samples({
    getSamples(texts[0]), getSamples(texts[1]), getSamples(texts[2]), getSamples(texts[3])
});
std::vector<std::string> text_names({
    "Binary Small Text", "Binary Large Text",
    "DNA Small Text", "DNA Large Text"
});

std::vector<uint64_t> computing_times(algs.size() * texts.size());

void calculateComputingTimes(int sample_num) {
    for (int k = 0; k < texts.size(); ++k) {
        std::string sample = samples[k][sample_num];
        for (int j = 0; j < algs.size(); ++j) {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> entries = algs[j](sample, texts[k]);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            if (!checker(entries, sample, texts[k])) {
                std::cout << "failed to calculate entries of sample:\n" << sample <<
                    "\nof the text\n" << texts[k] <<
                    "\nusing " << alg_names[j] << "\nEntries:\n";
                printArray(entries);
            }
            computing_times[k * algs.size() + j] =
                std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
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

void fillTableRow(std::ofstream *stream, int sample_num) {
    calculateComputingTimes(sample_num);
    std::string table_row = std::to_string(100 + sample_num * 100);
    for (auto comp_time : computing_times) {
        table_row.append(";" + std::to_string(comp_time));
    }
    table_row.append("\n");
    *stream << table_row;
}

void getTableUpdateSamples() {
    std::ofstream table("/mnt/c/Users/tanya/Documents/CLionProjects/HSE-HW2/zeroAdds.csv");
    table << getNames();
    for (int sample_num = 0; sample_num <= samples[0].size(); ++sample_num) {
        fillTableRow(&table, sample_num);
    }
    table.close();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
