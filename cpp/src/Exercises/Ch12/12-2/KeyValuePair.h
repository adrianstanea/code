
#pragma once
#include <algorithm>
#include <string>
#include <utility>

template <typename K, typename V>
class KeyValuePair {
   public:
    KeyValuePair() = default;
    explicit KeyValuePair(K key, V value)
        : m_key(std::move(key)), m_value(std::move(value)) {}

    const K& getKey() const { return m_key; }
    const K&& getKey() { return std::move(m_key); }
    void setKey(K key) { m_key = std::move(key); }

    const V& getValue() const { return m_value; }
    const V&& getValue() { return std::move(m_value); }
    void setValue(V value) { m_value = std::move(value); }

   private:
    K m_key;
    V m_value;
};

template <>
class KeyValuePair<const char*, const char*> {
   public:
    KeyValuePair() = default;
    explicit KeyValuePair(const char* key, const char* value)
        : m_key(key), m_value(value) {}

    const std::string& getKey() const { return m_key; }
    const std::string&& getKey() { return std::move(m_key); }
    void setKey(std::string key) { m_key = std::move(key); }

    const std::string& getValue() const { return m_value; }
    const std::string&& getValue() { return std::move(m_value); }
    void setValue(std::string value) { m_value = std::move(value); }

   private:
    std::string m_key;
    std::string m_value;
};