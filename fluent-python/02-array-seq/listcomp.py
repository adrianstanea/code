import collections
import array

TShirt = collections.namedtuple("TShirt", ["color", "size"])

if __name__ == "__main__":
    symbols = "$¢£¥€"
    codes = [last := ord(symbol) for symbol in symbols]

    print(f"Last item from list comprehension: {last}")

    for code in codes:
        print(f"{code} {chr(code)}")

    # Cartesian product of two lists
    colors = ["black", "white"]
    sizes = ["S", "M", "L"]
    t_shirts: list[TShirt] = [TShirt(color, size) for color in colors for size in sizes]
    print(t_shirts)

    symbols_generator = (ord(symbol) for symbol in symbols)
    print("loop 1")
    for item in symbols_generator:
        print(item)
    # The generator is exhausted after the first loop, so this will not print anything
    for item in symbols_generator:
        print(item)

    tuples = tuple(ord(symbol) for symbol in symbols)
    print(tuples)
    print(isinstance(tuples, tuple))

    arr = array.array("I", tuples)
    print(arr)
