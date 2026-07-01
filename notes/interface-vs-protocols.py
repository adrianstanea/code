import abc


class Animal(abc.ABC):
    @abc.abstractmethod
    def eat(self, food: str) -> None:
        print(f"{self.__class__.__name__} is eating {food}")
