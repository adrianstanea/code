import std;

using namespace std;
class Person {
   public:
    explicit Person(string first, string last)
        : m_firstName{std::move(first)}, m_lastName{std::move(last)} {}
    [[nodiscard]] const string& getFirstName() const { return m_firstName; }
    [[nodiscard]] const string& getLastName() const { return m_lastName; }

   private:
    string m_firstName;
    string m_lastName;
};

void printRange(string_view msg, auto&& range) {
    println("{}: {:n}", msg, range);
}

int main() {
    std::vector data{33, 11, 22};

    std::print("Before:");
    for (const auto& value : data) {
        std::println("{}", value);
    }

    // =========================================================================
    // RANGES
    // =========================================================================

    namespace ranges = std::ranges;
    ranges::sort(data);

    std::println("Ascending:");
    for (const auto& value : data) {
        std::println("{}", value);
    }

    std::println("Descending:");
    ranges::sort(data, ranges::greater{});
    for (const auto& value : data) {
        std::println("{}", value);
    }

    // Sort using a custom lambda
    std::println("Using lambda:");
    ranges::sort(data, [](const auto& a, const auto& b) { return a > b; });
    for (const auto& value : data) {
        std::println("{}", value);
    }

    // =========================================================================
    // PROJECTIONS
    // =========================================================================

    vector persons{Person("John", "Doe"), Person("Jane", "Doe")};
    // This does not compile if Person does not support operator<
    // ranges::sort(persons);

    // Solution: sort using lambda
    ranges::sort(persons, [](const auto& a, const auto& b) {
        return a.getFirstName() < b.getFirstName();
    });
    // Solution: sort using projection: use a callback(proj argument) to
    // transform each parameter before applyin the comparison
    ranges::sort(persons, ranges::less{}, &Person::getFirstName);

    // =========================================================================
    // VIEWS
    // =========================================================================
    std::println("{:=^60}", "Views");
    std::vector values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printRange("Original sequence: ", values);

    // / Filter out all odd values, leaving only the even values.
    auto result1{values | std::views::filter([](const auto& value) {
                     return value % 2 == 0;
                 })};
    printRange("Only even values: ", result1);
    // Transform all values to their double value.
    auto result2{result1 | std::views::transform(
                               [](const auto& value) { return value * 2.0; })};
    printRange("Values doubled: ", result2);
    // Drop the first 2 elements.
    auto result3{result2 | std::views::drop(2)};
    printRange("First two dropped: ", result3);
    // Reverse the view.
    auto result4{result3 | std::views::reverse};
    printRange("Sequence reversed: ", result4);

    // Modifying elements through a view
    vector values2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printRange("Original sequence: ", values2);

    auto test_view{values2 | std::views::filter([](const auto& value) {
                       return value % 2 == 0;
                   }) |
                   std::views::drop(2) | std::views::reverse};
    // Modify within view changes underlying data
    for (auto& value : test_view) {
        value = value * 10;
    }
    printRange("Modified view", test_view);
    printRange("Modfied sequence: ", values2);

    println("Type integers, an integer >= 5 stops the program.");
    auto test{ranges::istream_view<int>{cin} |
              views::take_while([](const auto& v) { return v < 5; }) |
              views::transform([](const auto& v) { return v * 2; })};
    for (auto value : test) {
        println("> {}", value);
    }
    println("Terminating...");

    return 0;
}
