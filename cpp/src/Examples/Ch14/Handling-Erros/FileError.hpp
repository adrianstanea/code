#pragma once

#include <cstddef>
#include <exception>
#include <format>
#include <string>
#include <utility>

class FileError : public std::exception {
   public:
    explicit FileError(std::string file_name)
        : m_file_name(std::move(file_name)) {}

    [[nodiscard]] virtual const std::string& getFileName() const noexcept {
        return m_file_name;
    }

    [[nodiscard]] const char* what() const noexcept override {
        return m_message.c_str();
    }

   protected:
    void setMessage(std::string message) { m_message = std::move(message); }

   private:
    std::string m_file_name;
    std::string m_message;
};

class FileOpenError : public FileError {
   public:
    explicit FileOpenError(std::string file_name)
        : FileError(std::move(file_name)) {
        setMessage(std::format("Failed to open file: {}", getFileName()));
    }
};

class FileReadError : public FileError {
   public:
    explicit FileReadError(std::string file_name, std::size_t line_number)
        : FileError(std::move(file_name)), m_line_number(line_number) {
        setMessage(std::format("Failed to read from file: {} at line {}",
                               getFileName(), m_line_number));
    };

    [[nodiscard]] virtual std::size_t getLineNumber() const noexcept {
        return m_line_number;
    }

   private:
    std::size_t m_line_number{0};
};