#include <iostream>
#include <vector>
#include <map>
#include <ranges>
#include <compare>
#include <concepts>  // Dla std::integral, std::floating_point, itd.
#include <string>

//
// 1. Concept "Arithmetic" – ogranicza typy do liczb całkowitych lub zmiennoprzecinkowych
//
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

//
// 2. Struktura z operatorem trójargumentowego porównania (<=>)
//
struct Person {
    std::string name;
    int age;

    // "default" mówi kompilatorowi, by sam wygenerował reguły porównania
    auto operator<=>(const Person&) const = default;
};

//
// 3. Funkcja add wykorzystująca concept
//
Arithmetic auto add(Arithmetic auto a, Arithmetic auto b) {
    return a + b;
}

int main() {
    //
    // Przykład użycia concept – wywołanie "add" dla typów arytmetycznych
    //
    std::cout << "add(2, 3) = " << add(2, 3) << std::endl;
    // Poniższe rzuciłoby błąd kompilacji, bo string nie pasuje do "Arithmetic":
    // std::cout << add(2, std::string("3")) << std::endl;

    //
    // Użycie operatora trójargumentowego porównania w strukturze Person
    //
    Person p1{"Alice", 30}, p2{"Bob", 25};
    if (p1 < p2) {
        std::cout << p1.name << " is 'less' than " << p2.name
                  << " according to <=>\n";
    }

    //
    // 4. Ranges – filtrowanie i transformacja wektora
    //
    std::vector<int> data = {1, 2, 3, 4, 5, 6};
    auto result = data
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 2; });

    std::cout << "After Ranges filter & transform: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    //
    // 5. map::contains – proste sprawdzenie czy klucz istnieje w mapie
    //
    std::map<std::string, int> fruit = {{"apple", 10}, {"banana", 20}};
    if (fruit.contains("banana")) {
        std::cout << "Found 'banana' in the map!\n";
    }

    //
    // 6. Nowe metody w std::string: starts_with, ends_with
    //
    std::string text = "HelloWorld";
    if (text.starts_with("Hello")) {
        std::cout << text << " starts with 'Hello'\n";
    }

    return 0;
}
