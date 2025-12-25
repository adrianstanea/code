#include <memory>
#include <print>
#include <vector>

#include "DoubleSpreadSHeetCell.hpp"
#include "SpreadSheetCell.hpp"
#include "StringSpreadSheetCell.hpp"

using namespace std;

int main(int argc, const char** argv) {
    vector<unique_ptr<SpreadSheetCell>> cells;

    cells.push_back(make_unique<StringSpreadSheetCell>());
    cells.push_back(make_unique<StringSpreadSheetCell>());
    cells.push_back(make_unique<DoubleSpreadSheetCell>());

    auto values = vector<string>{"hello", "world", "1.8"};

    for (size_t i = 0; i < cells.size(); ++i) {
        cells.at(i)->set(values.at(i));
    }

    for (const auto& cell : cells) {
        println("{}", cell->getString());
    }

    println("");
    {
        DoubleSpreadSheetCell doubleCell;
        doubleCell.set("8.4");
        DoubleSpreadSheetCell result{doubleCell + doubleCell};
        println("{}", result.getString());
    }

    {
        DoubleSpreadSheetCell doubleCell;
        doubleCell.set(8.4);
        StringSpreadSheetCell stringCell;
        stringCell.set(" Hello ");
        StringSpreadSheetCell result{doubleCell + stringCell + doubleCell};
        println("{}", result.getString());  // Prints Hello 8.400000
    }

    return 0;
}