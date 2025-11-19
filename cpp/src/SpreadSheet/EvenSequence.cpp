#include "EvenSequence.hpp"
#include <stdexcept>
#include <print>

using namespace std;

EvenSequence::EvenSequence(std::initializer_list<double> values)
{
    if(values.size() % 2 != 0) {
        throw invalid_argument{"EvenSequence requires an even number of values."};
    }

    m_sequence.reserve(values.size());
    for(const auto& value: values) {
        m_sequence.push_back(value);
    }
}

void EvenSequence::print() const
{
    for(const auto& value: m_sequence) {
        std::print("{}, ", value);
    }
    std::print("");
}
