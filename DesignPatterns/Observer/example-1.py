import enum
from abc import ABC, abstractmethod
from enum import StrEnum
from random import sample
from time import sleep
from typing import Any

from pydantic import BaseModel, PrivateAttr


class Events(StrEnum):
    TEMPERATURE_CHANGE = "temperature_change"
    HUMIDITY_CHANGE = "humidity_change"


class Observer(ABC):
    @abstractmethod
    def update(self, event: Events, context: "Subject") -> None:
        raise NotImplementedError("Subclasses must implement the update method")


class Subject(ABC):
    @abstractmethod
    def attach(self, observer: Observer) -> None:
        """Attach an observer to the subject."""

    @abstractmethod
    def detach(self, observer: Observer) -> None:
        """Detach an observer from the subject."""

    @abstractmethod
    def notify(self, event: Events) -> None:
        """Notify all observers about an event."""


# Concrete Subject
class TemperatureSensor(Subject, BaseModel):
    temperature: float = 0.0

    _observers: list[Observer] = PrivateAttr(default_factory=list)

    def attach(self, observer: Observer) -> None:
        if observer not in self._observers:
            self._observers.append(observer)

    def detach(self, observer: Observer) -> None:
        if observer in self._observers:
            self._observers.remove(observer)

    def notify(self, event: Events) -> None:
        for observer in sample(self._observers, k=len(self._observers)):
            observer.update(event=event, context=self)

    def __setattr__(self, name: str, value: Any) -> None:  # noqa: ANN401
        # validation and assignment logic
        super().__setattr__(name, value)

        # notify when temperature changes
        if name == "temperature":
            self.notify(Events.TEMPERATURE_CHANGE)


class HumiditySensor(Subject, BaseModel):
    humidity: float = 0.0

    _observers: list[Observer] = PrivateAttr(default_factory=list)

    def attach(self, observer: Observer) -> None:
        if observer not in self._observers:
            self._observers.append(observer)

    def detach(self, observer: Observer) -> None:
        if observer in self._observers:
            self._observers.remove(observer)

    def notify(self, event: Events) -> None:
        for observer in sample(self._observers, k=len(self._observers)):
            observer.update(event=event, context=self)

    def __setattr__(self, name: str, value: Any) -> None:  # noqa: ANN401
        # validation and assignment logic
        super().__setattr__(name, value)

        # notify when humidity changes
        if name == "humidity":
            self.notify(Events.HUMIDITY_CHANGE)


# Concrete Observer
class Thermostat(Observer, BaseModel):
    class Threshold(enum.Enum):
        HOT = 28.0
        COLD = 18.0

    def update(self, event: Events, context: Subject) -> None:
        match event:
            case Events.TEMPERATURE_CHANGE:
                if not isinstance(context, TemperatureSensor):
                    raise TypeError("Thermostat: Invalid data provider")
                temperature = context.temperature
                if temperature > self.Threshold.HOT.value:
                    print("Thermostat: It's too hot! Turning on the AC.")
                elif temperature < self.Threshold.COLD.value:
                    print("Thermostat: It's too cold! Turning on the heater.")
            case _:
                print("Thermostat: Received unknown event")


class Display(Observer, BaseModel):
    temperature: float | None = 0.0
    humidity: float | None = 0.0

    def display(self) -> None:
        print("Display: Rendering updated data...")
        print(f"{self.temperature}C, {self.humidity}%")

    def update(self, event: Events, context: Subject) -> None:
        match event:
            case Events.TEMPERATURE_CHANGE:
                if not isinstance(context, TemperatureSensor):
                    raise TypeError("Display: Invalid data provider")
                self.temperature = context.temperature
            case Events.HUMIDITY_CHANGE:
                if not isinstance(context, HumiditySensor):
                    raise TypeError("Display: Invalid data provider")
                self.humidity = context.humidity
            case _:
                raise ValueError("Display: Received unknown event")
        self.display()


if __name__ == "__main__":
    sensor_temp = TemperatureSensor()
    sensor_humidity = HumiditySensor()

    thermostat = Thermostat()
    display = Display()

    sensor_temp.attach(thermostat)
    sensor_temp.attach(display)

    sensor_humidity.attach(display)

    # Example usage: change temperature to trigger notifications
    sensor_temp.temperature = 25.0
    sensor_temp.temperature = 30.0

    for i in range(3):
        # Each time the subject changes state, all the attached observers are notified
        # to react accordingly.
        sensor_temp.temperature = 20.0 + i * 5
        sensor_humidity.humidity = 60.0 + i
        sleep(1)
