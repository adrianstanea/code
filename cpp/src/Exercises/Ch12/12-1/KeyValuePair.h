
#pragma once
#include <algorithm>
#include <utility>

template <typename K, typename V>
class KeyValuePair {
   public:
    KeyValuePair() = default;
    explicit KeyValuePair(K key, V value);

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

template <typename K, typename V>
KeyValuePair<K, V>::KeyValuePair(K key, V value)
    : m_key(std::move(key)), m_value(std::move(value)) {}