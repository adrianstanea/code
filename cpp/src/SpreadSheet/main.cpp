#include <print>
#include "SpreadSheetCell.hpp"
#include "EvenSequence.hpp"
#include <memory>

using namespace std;

int main()
{

    //     auto cell = SpreadSheetCell{5.2};
    //     println("Initial cell value: {:.2f}", cell.getValue());

    //     cell.setValue(42.0);
    //     println("Updated cell value: {:.2f}", cell.getValue());
    //     println("Updated cell value: {}", cell.getString());

    //     cell.setString("3.14159");
    //     println("Updated cell value: {:.2f}", cell.getValue());
    //     println("Updated cell value: {}", cell.getString());

    //     println();
    //     auto another_cell = SpreadSheetCell{"3.14"};
    //     another_cell.setString("58.0");
    //     println("Another cell value: {:.2f}", another_cell.getValue());

    //     println();
    //     SpreadSheetCell *p_cell{new SpreadSheetCell{1234.56}};
    //     p_cell->setString("123.456");
    //     println("Pointer cell value: {:.2f}", p_cell->getValue());
    //     println("Pointer cell values: {} \t {}", p_cell->getValue(), p_cell->getString());
    //     delete p_cell;
    //     p_cell = nullptr;

    //     println();
    //     auto p_another_cell{make_unique<SpreadSheetCell>(123)};
    //     println("Another unique pointer cell value: {} \t {}", p_another_cell->getString(), p_another_cell->getValue());
    //     p_another_cell->setValue(987.654);
    //     println("Another unique pointer cell value: {} \t {}", p_another_cell->getString(), p_another_cell->getValue());

    //     auto test_cell{make_unique<SpreadSheetCell>("test")};
    //     println("Test cell value: {} \t {}", test_cell->getString(), test_cell->getValue());

    //     SpreadSheetCell cells[3];
    //     // SpreadSheetCell cells[3] {
    //     //     SpreadSheetCell{10.0},
    //     //     SpreadSheetCell{"20.0"},
    //     //     SpreadSheetCell{30.0}
    //     // };
    //     for (const auto &cell : cells)
    //     {
    //         println("Cell value: {} \t {}", cell.getString(), cell.getValue());
    //     }

    //     auto smart_cell_ptr{make_shared<SpreadSheetCell>()};
    //     println("Smart cell pointer value: {} \t {}", smart_cell_ptr->getString(), smart_cell_ptr->getValue());

    //     SpreadSheetCell cell1{200.0};
    //     auto cell2{cell1};
    //     println("Cell1 value: {} \t {}", cell1.getString(), cell1.getValue());
    //     println("Cell2 value: {} \t {}", cell2.getString(), cell2.getValue());

    //     try
    //     {
    //         EvenSequence seq{ 2.0, 4.0, 6.0, 8.0};
    //         println("Even sequence values:");
    //         seq.print();
    //     } catch (const invalid_argument& e) {
    //         println("Error creating EvenSequence: {}", e.what());
    //     }

    //     return 0;

    // {
    //     SpreadSheetCell *cellPtr1{new SpreadSheetCell{5}};
    //     SpreadSheetCell *cellPtr2{new SpreadSheetCell{6}};

    //     println("cellPtr1: {}", cellPtr1->getValue());

    //     delete cellPtr1; // destroys cellPtr1
    //     cellPtr1 = nullptr;
    // }

    {
        auto cell1{make_unique<SpreadSheetCell>(5.0)};
        auto cell2{make_shared<SpreadSheetCell>(6.0)};
        auto cell3 = cell2;

        println("cell1: {}", cell1->getValue());
        println("cell2: {}", cell2->getValue());
        println("cell3: {}", cell3->getValue());
    }
}