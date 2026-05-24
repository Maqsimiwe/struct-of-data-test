#include <iostream>
#include <stdexcept>
#include <functional>
using namespace std;


// Определение узла

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    explicit Node(int value) : data(value), next(nullptr), prev(nullptr) {}

    Node() : data(0), next(nullptr), prev(nullptr) {}
};


// Основной класс списка

class DoublyLinkedListWithSentinel {
private:
    Node* sentinel;
    size_t count;

public:

    DoublyLinkedListWithSentinel() : count(0) {
        sentinel = new Node();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;

    ~DoublyLinkedListWithSentinel() {
        clear();
        delete sentinel;
    }

    DoublyLinkedListWithSentinel(const DoublyLinkedListWithSentinel&) = delete;
    DoublyLinkedListWithSentinel& operator=(const DoublyLinkedListWithSentinel&) = delete;

    // ОПЕРАЦИЯ 1: ВСТАВКА

    // Вставить элемент в начало списка
    void push_front(int value) {
        Node* new_node = new Node(value);
        insert_node_after(sentinel, new_node);
        count++;
    }

    // Вставить элемент в конец списка
    void push_back(int value) {
        Node* new_node = new Node(value);
        insert_node_before(sentinel, new_node);
        count++;
    }

    // ОПЕРАЦИЯ 2: УДАЛЕНИЕ

    // Удалить узел с заданным значением
    // Возвращает true если узел найден и удалён, false иначе
    bool remove_value(int value) {
        Node* node = find_node(value);
        if (node == nullptr) {
            return false;
        }
        remove_node(node);
        return true;
    }

    // Удалить узел с начала списка
    int pop_front() {
        Node* node = sentinel->next;
        int value = node->data;
        remove_node(node);
        return value;
    }

    // Удалить узел с конца списка
    int pop_back() {
        Node* node = sentinel->prev;
        int value = node->data;
        remove_node(node);
        return value;
    }

    // Очистить весь список
    void clear() {
        Node* current = sentinel->next;
        while (current != sentinel) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        count = 0;
    }

    // ОПЕРАЦИЯ 3: ПОИСК

    // Найти узел по значению
    Node* find_node(int value) {
        Node* current = sentinel->next;
        while (current != sentinel && current->data != value) {
            current = current->next;
        }
        return (current == sentinel) ? nullptr : current;
    }

    // Проверить наличие элемента в списке
    bool contains(int value) const {
        Node* current = sentinel->next;
        while (current != sentinel && current->data != value) {
            current = current->next;
        }
        return current != sentinel;
    }

    // Найти элемент и вернуть его позицию (индекс)
    // Возвращает -1 если элемент не найден
    int index_of(int value) const {
        int index = 0;
        Node* current = sentinel->next;
        while (current != sentinel) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    // Получить элемент по индексу
    // Выбрасывает исключение если индекс выходит за границы
    int& at(size_t index) {
        Node* current = sentinel->next;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // ОПЕРАЦИЯ 4: ОБХОД

    // Обход в прямом направлении с функцией обратного вызова
    void traverse_forward(function<void(int)> callback) const {
        Node* current = sentinel->next;
        while (current != sentinel) {
            callback(current->data);
            current = current->next;
        }
    }

    // Обход в обратном направлении с функцией обратного вызова
    void traverse_backward(function<void(int)> callback) const {
        Node* current = sentinel->prev;
        while (current != sentinel) {
            callback(current->data);
            current = current->prev;
        }
    }

    // Вывести список в прямом направлении
    void display_forward(const string& separator = " ") const {
        cout << "[ ";
        Node* current = sentinel->next;
        bool first = true;
        while (current != sentinel) {
            if (!first) cout << separator;
            cout << current->data;
            first = false;
            current = current->next;
        }
        cout << " ]\n";
    }

    // Вывести список в обратном направлении
    void display_backward(const string& separator = " ") const {
        cout << "[ ";
        Node* current = sentinel->prev;
        bool first = true;
        while (current != sentinel) {
            if (!first) cout << separator;
            cout << current->data;
            first = false;
            current = current->prev;
        }
        cout << " ]\n";
    }
};
