// Przykładowy kod prezentujący funkcje C++17 (takie jak if constexpr, fold expressions, structured 
// bindings itp.) stanowi autorskie opracowanie będące zbiorem inspiracji z różnych źródeł, m.in. 
// dokumentacji cppreference.com i artykułu ‘Features of C++17 with examples’ z serwisu GeeksforGeeks.
// Nie jest to wprost kopia z jednego źródła – kod został zmodyfikowany i scalony w taki sposób, aby w 
// jednej przykładowej aplikacji omówić kilka kluczowych funkcjonalności jednocześnie.


#include <iostream>
#include <tuple>
#include <type_traits>

// Nested namespaces (zamiast: namespace MyApp { namespace Utils { ... }})
namespace MyApp::Utils {
    
    // Direct List Initialization (dla typu wyliczeniowego)
    enum class Color { Red = 1, Green, Blue };

    // Fold Expressions
    template<typename... Args>
    auto sum(Args... args) {
        // Wykonujemy dodawanie wszystkich argumentów w zwięzłej formie:
        return (args + ... + 0);
    }
}

// if constexpr – przydatne w kodzie szablonowym
template<typename T>
void printTypeInfo(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integral: " << value << std::endl;
    } else {
        std::cout << "Not integral: " << value << std::endl;
    }
}

int main() {
    using namespace MyApp::Utils;

    // Direct list init dla Color
    Color c {2}; 
    std::cout << "Color c numeric value = " << static_cast<int>(c) << std::endl;

    // Structured bindings – rozpakowanie krotki
    auto getPoint = []() {
        return std::make_tuple(3, 4);
    };
    auto [x, y] = getPoint();
    std::cout << "Point: x=" << x << ", y=" << y << std::endl;

    // Inicjalizacja zmiennej w if
    if (int result = sum(1, 2, 3); result > 5) {
        std::cout << "Sum(1, 2, 3) = " << result << " is > 5\n";
    } else {
        std::cout << "Sum(1, 2, 3) = " << result << " is <= 5\n";
    }

    // Użycie fold expressions wprost
    std::cout << "Fold expression sum of (1, 2, 3, 4) = "
              << sum(1, 2, 3, 4) << std::endl;

    // if constexpr – wywołanie naszej funkcji dla różnych typów
    printTypeInfo(x);       // T = int
    printTypeInfo(3.14);    // T = double

    // Inicjalizacja zmiennej w switch
    switch (int combined = x + y; combined) {
        case 7:
            std::cout << "combined = 7\n";
            break;
        default:
            std::cout << "combined = " << combined << " (not 7)\n";
    }

    return 0;
}
