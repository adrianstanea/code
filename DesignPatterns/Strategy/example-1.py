import abc
from collections.abc import Sequence


class SortingStrategy(abc.ABC):
    """
    The strategy interface declares operations common to all supported versions
    of some algorithm.

    The context uses this interface to call the algorithm defined by some
    Concrete Strategy.
    """

    @abc.abstractmethod
    def do_algorithm(self, data: Sequence) -> Sequence:
        pass


class SortAscending(SortingStrategy):
    def do_algorithm(self, data: Sequence) -> Sequence:
        print("Default Strategy")
        return sorted(data)


class SortDescending(SortingStrategy):
    def do_algorithm(self, data: Sequence) -> Sequence:
        return sorted(data, reverse=True)


class Context:
    def __init__(self, strategy: SortingStrategy | None = None) -> None:
        self._strategy = strategy or SortAscending()  # defaults to ascending sort

    @property
    def strategy(self) -> SortingStrategy:
        return self._strategy

    @strategy.setter
    def strategy(self, strategy: SortingStrategy) -> None:
        self._strategy = strategy

    def do_business_logic(self) -> None:
        print(f"Context: Sorting data using: {self._strategy.__class__.__name__}")
        data = ["a", "b", "c", "d", "e"]
        result = self.strategy.do_algorithm(data)
        print(",".join(result))


if __name__ == "__main__":
    context = Context()
    print("Client is set to default strategy")
    context.do_business_logic()

    print("Client set to different strategy")
    context.strategy = SortDescending()

    context.do_business_logic()
