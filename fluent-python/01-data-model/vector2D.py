import math


class Vector(object):
    def __init__(self, x: float = 0, y: float = 0) -> None:
        self.x = x
        self.y = y

    def __repr__(self) -> str:
        return f"Vector({self.x!r}, {self.y!r})"

    def __abs__(self):
        return math.hypot(self.x, self.y)

    def __bool__(self):
        return bool(abs(self))

    def __add__(self, other):
        x = self.x + other.x
        y = self.y + other.y
        return Vector(x, y)

    def __mul__(self, scalar: float):
        x = self.x * scalar
        y = self.y * scalar
        return Vector(x, y)


if __name__ == "__main__":
    v1 = Vector(3, 4)
    v2 = Vector(2, 1)
    print(v1 + v2)
    print(v1 * 3)
    print(abs(v1))
    print(bool(v1), bool(Vector(0, 0)))

    print(issubclass(Vector, object))
