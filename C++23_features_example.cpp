export module MyLib;

#include <expected>
#include <string>
#include <cctype>
#include <algorithm>
#include <ranges>

// Ten moduł eksportuje funkcję parseNumber, która zwraca wartość lub błąd w std::expected.
export std::expected<int, std::string> parseNumber(const std::string& s) {
    // Sprawdzamy, czy łańcuch zawiera tylko cyfry (ew. znak '-')
    bool negative = false;
    std::string::size_type startPos = 0;
    if (!s.empty() && s[0] == '-') {
        negative = true;
        startPos = 1;
    }

    // Używamy ranges, by sprawdzić pozostałe znaki
    auto substrView = s.substr(startPos);
    bool allDigits = std::ranges::all_of(substrView, [](unsigned char c) {
        return std::isdigit(c);
    });

    if (!allDigits || s.size() == startPos) {
        return std::unexpected("Invalid number format: '" + s + "'");
    }

    try {
        int val = std::stoi(s);
        return val;
    } catch (...) {
        return std::unexpected("stoi error: unable to parse '" + s + "'");
    }
}
