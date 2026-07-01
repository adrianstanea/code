from abc import ABC, abstractmethod
from pathlib import Path


class DataSource(ABC):
    @abstractmethod
    def write(self, data: str) -> None:
        raise NotImplementedError("Subclasses must implement the write_data method")

    @abstractmethod
    def read(self) -> str:
        raise NotImplementedError("Subclasses must implement the read_data method")


class FileDataSource(DataSource):
    def __init__(self, filename: str) -> None:
        self._filename = filename

    @property
    def filename(self) -> str:
        return self._filename

    def write(self, data: str) -> None:
        Path(self.filename).write_text(data)

    def read(self) -> str:
        return Path(self.filename).read_text()


class DataSourceDecorator(DataSource, ABC):
    def __init__(self, data_source: DataSource) -> None:
        self._data_source = data_source

    @property
    def data_source(self) -> DataSource:
        return self._data_source


class EncryptionDecorator(DataSourceDecorator):
    def write(self, data: str) -> None:
        encrypted_data = self._encrypt(data)
        self.data_source.write(encrypted_data)

    def read(self) -> str:
        encrypted_data = self.data_source.read()
        return self._decrypt(encrypted_data)

    def _encrypt(self, data: str) -> str:
        # Simple encryption logic (for demonstration purposes)
        return "".join(reversed(data))

    def _decrypt(self, data: str) -> str:
        # Simple decryption logic (for demonstration purposes)
        return "".join(reversed(data))


class CompressionDecorator(DataSourceDecorator):
    def write(self, data: str) -> None:
        compressed_data = self._compress(data)
        self.data_source.write(compressed_data)

    def read(self) -> str:
        compressed_data = self.data_source.read()
        return self._decompress(compressed_data)

    def _compress(self, data: str) -> str:
        # Simple compression logic (for demonstration purposes) - LOSSY
        return data[::2]

    def _decompress(self, data: str) -> str:
        # Simple decompression logic (for demonstration purposes) - LOSSY
        return "".join([data[i // 2] if i % 2 == 0 else "" for i in range(len(data) * 2)])


def main() -> None:
    data_source: DataSource = FileDataSource("data.txt")
    data_source.write("Hello, World!")
    print("Simple data source:")
    print(data_source.read())

    data_source: DataSource = EncryptionDecorator(FileDataSource("data.txt"))
    data_source.write("Hello, World!")
    print("Data source (w/ Encryption):")
    print(data_source.read())

    data_source: DataSource = CompressionDecorator(FileDataSource("data.txt"))
    data_source.write("Hello, World!")
    print("Data source (w/ Compression):")
    print(data_source.read())

    data_source: DataSource = CompressionDecorator(EncryptionDecorator(FileDataSource("data.txt")))
    data_source.write("Hello, World!")
    print("Data source (w/ Compression & Encryption):")
    print(data_source.read())


if __name__ == "__main__":
    main()
