import MyLib;   // Importujemy nasz moduł
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    // Przyklad uzycia parseNumber
    auto result = parseNumber("-1234");
    if (result) {
        std::cout << "Parsed number: " << *result << std::endl;
    } else {
        std::cout << "Error: " << result.error() << std::endl;
    }

    // Drugi przykład z niepoprawnym łańcuchem
    auto badResult = parseNumber("12a34");
    if (!badResult) {
        std::cout << "Error: " << badResult.error() << std::endl;
    }

    // Użycie rozszerzonych Ranges, np. std::views::chunk
    std::vector<int> data {1, 2, 3, 4, 5, 6, 7};
    // Dzielimy wektor na podzakresy (chunk) o rozmiarze 3
    auto chunked = data | std::views::chunk(3);

    std::cout << "Chunked data:\n";
    for (auto group : chunked) {
        for (int val : group) {
            std::cout << val << " ";
        }
        std::cout << "| ";
    }
    std::cout << std::endl;

    return 0;
}
