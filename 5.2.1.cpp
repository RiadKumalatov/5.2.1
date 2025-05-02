#include <iostream>
#include <stdexcept>
#include <algorithm>

class smart_array {
private:
    int* data;
    size_t size;
    size_t capacity;

public:
    smart_array(size_t initial_size) : size(0), capacity(initial_size) {
        data = new int[capacity];
    }

    ~smart_array() {
        delete[] data;
    }

    smart_array(const smart_array& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }

    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);

        return *this;
    }

    void add_element(int value) {
        if (size >= capacity) {
            size_t new_capacity = capacity * 2;
            int* new_data = new int[new_capacity];
            std::copy(data, data + size, new_data);
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << arr.get_element(0) << std::endl;
        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}