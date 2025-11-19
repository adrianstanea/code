#include <vector>
#include <initializer_list>

class EvenSequence
{
public:
    EvenSequence(std::initializer_list<double> values);

    void print() const;

private:
    std::vector<double> m_sequence;
};
