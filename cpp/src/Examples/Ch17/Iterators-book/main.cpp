import std;

template <std::input_iterator Iter>
decltype(auto) myPrint(Iter begin, Iter end) {
    for (auto iter{begin}; iter != end; iter++) {
        std::print(std::cout, "{}, ", *iter);
    }
    std::println("");
}

template <std::input_iterator Iter>
decltype(auto) myFind(
    Iter begin, Iter end,
    const typename std::iterator_traits<Iter>::value_type& value) {
    for (auto iter{begin}; iter != end; iter++) {
        if (*iter == value) {
            return iter;
        }
    }
    return end;
}

template <std::input_iterator Iter>
decltype(auto) sum(Iter begin, Iter end) {
    auto result{*begin};
    begin++;
    for (; begin != end; begin++) {
        result += *begin;
    }
    return result;
}

int main() {
    std::println("\n{:=^60}", "Without function");
    std::vector values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto iter{std::cbegin(values)}; iter != std::cend(values); iter++) {
        std::print(std::cout, "{}, ", *iter);
    }

    std::println("\n{:=^60}", "With myPrint");
    myPrint(std::cbegin(values), std::cend(values));

    const auto result{myFind(std::begin(values), std::end(values), 5)};
    if (result != std::end(values)) {
        auto distance{std::distance(std::begin(values), result)};
        std::println("Found value {} at distance {}", *result, distance);
    } else {
        std::println("Value not found");
    }

    // std::println("");
    // std::println(
    //     "Enter number separated by whitespace (press Ctrl+D to stop - "
    //     "LINUX): ");
    // std::istream_iterator<int> input_iterator{std::cin};
    // std::istream_iterator<int> end_iterator;

    // auto result2{sum(input_iterator, end_iterator)};
    // std::println("Sum of input elements is: {}", result2);

    // Add new values to the vector, copy
    values.push_back(1);
    values.push_back(1);
    values.push_back(1);
    std::set<int> setOne{};
    // std::copy(std::cbegin(values), std::cend(values),
    //           std::insert_iterator<std::set<int>>(setOne,
    //           std::cbegin(setOne)));
    std::println("{:=^60}", "Inserter");
    std::copy(std::cbegin(values), std::cend(values),
              std::inserter(setOne, std::cbegin(setOne)));
    myPrint(std::cbegin(values), std::cend(values));
    std::println("{:=^60}", "");
    myPrint(std::cbegin(setOne), std::cend(setOne));

    auto ostream_iterator{std::ostream_iterator<int>(std::cout, ", ")};
    std::copy(std::cbegin(values), std::cend(values), ostream_iterator);

    return 0;
}
