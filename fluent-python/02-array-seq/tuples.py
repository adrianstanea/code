from enum import StrEnum
import os

lax_coordinates = (33.94, -118)
latitude, longitude = lax_coordinates

print(latitude)
print(longitude)


a = (10, "alpha", [1, 2])
b = (10, "alpha", [1, 2])

print("=" * 20)
print(a == b)
b[-1].append(3)
print(a == b)


def fixed(obj) -> bool:
    try:
        hash(obj)
    except TypeError:
        return False
    return True


tf = (10, "alpha", (1, 2))
tm = (10, "alpha", [1, 2])
print(fixed(tf))  # true - contains only imitable objects
print(fixed(tm))  # false - the list is mutable, so the tuple is not hashable

print("=" * 20)
for item in reversed(tf):
    print(item)

# Unpacking
# Swapping values
a = 1
b = 2
print("=" * 20)
print(a, b)
a, b = b, a
print(a, b)


def divmod(a, b):
    return a // b, a % b


print("=" * 20)
print(divmod(20, 8))
print(*divmod(20, 8))

print("=" * 20)

head, tail = os.path.split("home/user/.ssh/idrsa.pub")
print(head)
print(tail)

print("=" * 20)
a, b, *rest = range(2)
print(a)
print(b)
print(rest)

# Nested unpacking
metro_areas = [
    ("Tokyo", "JP", 36.933, (35.689722, 139.691667)),  # <1>
    ("Delhi NCR", "IN", 21.935, (28.613889, 77.208889)),
    ("Mexico City", "MX", 20.142, (19.433333, -99.133333)),
    ("New York-Newark", "US", 20.104, (40.808611, -74.020386)),
    ("São Paulo", "BR", 19.649, (-23.547778, -46.635833)),
]

for city, _, _, (lat, lon) in metro_areas:
    if lon <= 0:
        print(f"{city:15} | {lat:9.4f} | {lon:9.4f}")

print("=" * 20)


# Pattern matching
class Command(StrEnum):
    START = "start"
    STOP = "stop"
    PAUSE = "pause"


def handle(command: Command):
    match command:
        case Command.START:
            print("Starting")
        case Command.STOP:
            print("Stopping")
        case Command.PAUSE:
            print("Pausing")
        case _:
            raise ValueError(f"Unknown command: {command}")


try:
    handle(Command.START)
    handle(Command.STOP)
    handle(Command.PAUSE)
    handle("invalid_command")
except ValueError as e:
    print(e)
