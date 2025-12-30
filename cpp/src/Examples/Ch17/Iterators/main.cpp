import std;

// =================================================================================
// 1. Custom Iterator Implementation
// =================================================================================
// Implementing a custom iterator allows your own types to work with STL algorithms
// and range-based for loops.
//
// This example creates a simple range of integers.
class IntegerRange {
public:
    // The Iterator class
    class Iterator {
    public:
        // Iterator traits (required for std::iterator_traits compatibility before C++20)
        // In C++20, concepts often deduce these, but it's good practice to define them.
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int*;   // Not strictly used here but part of the interface
        using reference         = int&;   // Not strictly used here but part of the interface

        Iterator(int val) : m_value(val) {}

        // Dereference operator
        value_type operator*() const { return m_value; }

        // Prefix increment (++it)
        Iterator& operator++() {
            m_value++;
            return *this;
        }

        // Postfix increment (it++)
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality operators
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_value == b.m_value; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_value != b.m_value; }

    private:
        int m_value;
    };

    IntegerRange(int start, int end) : m_start(start), m_end(end) {}

    // begin() and end() are required for range-based for loops
    Iterator begin() const { return Iterator(m_start); }
    Iterator end() const   { return Iterator(m_end); }

private:
    int m_start;
    int m_end;
};

// =================================================================================
// 2. Sentinel Example (C++20)
// =================================================================================
// A sentinel denotes the end of a range but doesn't have to be the same type as the iterator.
struct NullTerminator {};

struct CStringIterator {
    const char* ptr;

    // Minimal interface for a C++20 input_iterator
    using difference_type = std::ptrdiff_t;
    using value_type = char;

    char operator*() const { return *ptr; }
    CStringIterator& operator++() { ptr++; return *this; }
    void operator++(int) { ++*this; }

    // Comparison with Sentinel
    bool operator==(NullTerminator) const { return *ptr == '\0'; }
};

// =================================================================================
// Helper for printing
// =================================================================================
void print_separator(std::string_view title) {
    std::println("\n{:=^60}", title);
}

// =================================================================================
// Main Demonstration
// =================================================================================
int main() {
    // -----------------------------------------------------------------------------
    // A. Iterator Categories & Standard Containers
    // -----------------------------------------------------------------------------
    print_separator(" Iterator Categories ");

    // 1. Random Access Iterator (std::vector)
    // Supports O(1) access, +, -, <, >, etc.
    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto it_ra = vec.begin();
    std::println("Random Access (Vector):");
    std::println("  *it_ra       = {}", *it_ra);
    std::println("  *(it_ra + 3) = {}", *(it_ra + 3)); // Jump arithmetic
    std::println("  it_ra[3]     = {}", it_ra[3]);     // Subscript operator

    // 2. Bidirectional Iterator (std::list)
    // Supports ++, --. No jump arithmetic.
    std::list<int> lst = {100, 200, 300};
    auto it_bi = lst.begin();
    std::println("Bidirectional (List):");
    std::println("  Current: {}", *it_bi);
    std::advance(it_bi, 2); // O(N) operation for bidirectional
    std::println("  After advance(2): {}", *it_bi);
    --it_bi;
    std::println("  After --: {}", *it_bi);

    // 3. Forward Iterator (std::forward_list)
    // Supports ++ only.
    std::forward_list<int> flst = {1, 2, 3};
    auto it_fw = flst.begin();
    std::println("Forward (Forward List):");
    std::println("  Current: {}", *it_fw);
    // --it_fw; // Compilation Error!

    // -----------------------------------------------------------------------------
    // B. Iterator Operations
    // -----------------------------------------------------------------------------
    print_separator(" Iterator Operations ");

    // std::advance, std::next, std::prev, std::distance
    // These functions dispatch to the most efficient implementation based on iterator tags.

    auto it = vec.begin();
    std::println("Start: {}", *it);

    std::advance(it, 2); // Moves iterator in place
    std::println("After advance(2): {}", *it);

    auto it_next = std::next(it, 2); // Returns new iterator, doesn't modify 'it'
    std::println("next(it, 2): {}", *it_next);

    auto it_prev = std::prev(it, 1); // Returns new iterator
    std::println("prev(it, 1): {}", *it_prev);

    auto dist = std::distance(vec.begin(), vec.end());
    std::println("distance(begin, end): {}", dist);

    // -----------------------------------------------------------------------------
    // C. Stream Iterators
    // -----------------------------------------------------------------------------
    print_separator(" Stream Iterators ");

    // Treat streams as sequences of data
    std::string data = "10 20 30";
    std::stringstream ss(data);

    // istream_iterator reads T from stream
    std::istream_iterator<int> input_begin(ss);
    std::istream_iterator<int> input_end; // Default constructor is end-of-stream

    std::vector<int> from_stream;
    // Copy from stream to vector
    std::copy(input_begin, input_end, std::back_inserter(from_stream));

    std::print("Read from stream: ");
    for(auto i : from_stream) std::print("{} ", i);
    std::println("");

    // ostream_iterator writes T to stream
    std::print("Write to cout: ");
    std::copy(from_stream.begin(), from_stream.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::println("");

    // -----------------------------------------------------------------------------
    // D. Insert Iterators
    // -----------------------------------------------------------------------------
    print_separator(" Insert Iterators ");

    std::vector<int> target;
    std::vector<int> source = {1, 2, 3};

    // std::back_inserter -> calls push_back()
    std::copy(source.begin(), source.end(), std::back_inserter(target));

    // std::front_inserter -> calls push_front() (e.g. for deque or list)
    std::deque<int> deq;
    std::copy(source.begin(), source.end(), std::front_inserter(deq));

    // std::inserter -> calls insert(pos, val)
    std::vector<int> mid_insert = {10, 40};
    std::vector<int> to_insert = {20, 30};
    std::copy(to_insert.begin(), to_insert.end(), std::inserter(mid_insert, mid_insert.begin() + 1));

    std::print("Inserted in middle: ");
    for(auto i : mid_insert) std::print("{} ", i);
    std::println("");

    // -----------------------------------------------------------------------------
    // E. Reverse Iterators
    // -----------------------------------------------------------------------------
    print_separator(" Reverse Iterators ");

    std::vector<int> v_rev = {1, 2, 3, 4, 5};
    std::print("Reverse iteration: ");
    // rbegin() returns a reverse_iterator pointing to the last element
    for(auto rit = v_rev.rbegin(); rit != v_rev.rend(); ++rit) {
        std::print("{} ", *rit);
    }
    std::println("");

    // Converting reverse_iterator to base iterator
    auto rit = v_rev.rbegin(); // Points to 5
    auto base_it = rit.base(); // Points to end() (one past 5)
    // This offset is necessary so that ranges [rbegin, rend) correspond to [begin, end)
    // &*rit == &*(rit.base() - 1)

    std::println("rit points to: {}", *rit);
    // std::println("base_it points to: {}", *base_it); // Undefined behavior (end iterator)
    std::println("*(base_it - 1) points to: {}", *(base_it - 1));

    // -----------------------------------------------------------------------------
    // F. Const Iterators
    // -----------------------------------------------------------------------------
    print_separator(" Const Iterators ");

    const std::vector<int> const_vec = {1, 2, 3};
    // begin() on const container returns const_iterator
    std::vector<int>::const_iterator cit = const_vec.begin();
    std::println("Read const iterator: {}", *cit);
    // *cit = 10; // Error: cannot assign to variable that is const

    // cbegin() / cend() explicitly request const iterators
    auto cit2 = vec.cbegin();
    // *cit2 = 99; // Error

    // -----------------------------------------------------------------------------
    // G. Custom Iterator Usage
    // -----------------------------------------------------------------------------
    print_separator(" Custom Iterator ");

    IntegerRange range(10, 15);
    std::print("IntegerRange(10, 15): ");
    for (int i : range) {
        std::print("{} ", i);
    }
    std::println("");

    // Using with STL algorithm
    auto max_el = std::max_element(range.begin(), range.end());
    std::println("Max element in custom range: {}", *max_el);

    // -----------------------------------------------------------------------------
    // H. Sentinels (C++20)
    // -----------------------------------------------------------------------------
    print_separator(" Sentinels ");

    const char* raw_str = "Hello Sentinel";
    CStringIterator c_begin{raw_str};
    NullTerminator c_end;

    std::print("Iterating with sentinel: ");
    // The loop continues as long as c_begin != c_end
    for (auto it = c_begin; it != c_end; ++it) {
        std::print("{}", *it);
    }
    std::println("");

    return 0;
}
