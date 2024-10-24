#include <iostream>
#include <unordered_map>

template <typename T>
class Deque
{
    struct Node
    {
        Node *next;
        Node *prev;
        T data;
        Node() : next(nullptr), prev(nullptr), data(0) {}
        Node(T a) : next(nullptr), prev(nullptr), data(a) {}
    };

    Node *front;
    Node *back;
    size_t totalSize;
    int frontIndex, backIndex;
    std::unordered_map<int, Node *> mp;

public:
    Deque() : front(nullptr), back(nullptr), totalSize(0), frontIndex(-1), backIndex(0) {}
    void push_back(T element);
    void push_front(T element);
    T Getfront();
    T Getback();
    void print();
    T &operator[](int index);
    bool isEmpty();
    int GetSize();
    void pop_front();
    void pop_back();
};

template <typename T>
void Deque<T>::pop_back()
{
    if (!back)
        return;

    mp.erase(--backIndex);
    Node *nodeToDelete = back;
    back = back->prev;
    back->next = nullptr;
    delete nodeToDelete;
    totalSize--;
}

template <typename T>
void Deque<T>::pop_front()
{
    if (!front)
        return;

    mp.erase(++frontIndex);
    Node *nodeToDelete = front;
    front = front->next;
    front->prev = nullptr;
    delete nodeToDelete;
    totalSize--;
}

template <typename T>
void Deque<T>::push_front(T element)
{
    Node *temp = new Node(element);
    if (!front && !back)
    {
        front = back = temp;
    }
    else
    {
        front->prev = temp;
        temp->next = front;
        front = temp;
    }
    mp.insert({frontIndex--, front});
    totalSize++;
}

template <typename T>
void Deque<T>::push_back(T element)
{
    Node *temp = new Node(element);
    if (!front && !back)
    {
        front = back = temp;
    }
    else
    {
        back->next = temp;
        temp->prev = back;
        back = temp;
    }
    mp.insert({backIndex++, back});
    totalSize++;
}

template <typename T>
T Deque<T>::Getfront()
{
    if(isEmpty()) throw std::out_of_range("deque is empty");
    if (front)
    {
        return front->data;
    }
    return back->data;
}

template <typename T>
T Deque<T>::Getback()
{
    if(isEmpty()) throw std::out_of_range("deque is empty");
    if (back)
    {
        return back->data;
    }
    return front->data;
}

template <typename T>
void Deque<T>::print()
{
    Node *start = front;
    while (start != nullptr)
    {
        std::cout << start->data << " ";
        start = start->next;
    }
    std::cout << std::endl;
}

template <typename T>
bool Deque<T>::isEmpty()
{
    return totalSize == 0;
}

template <typename T>
T &Deque<T>::operator[](int index)
{
    if (index < 0 || index >= totalSize)
    {
        throw std::out_of_range("Index out of range");
    }
    return mp[index + frontIndex + 1]->data;
}

template <typename T>
int Deque<T>::GetSize()
{
    return totalSize;
}

int main()
{
    Deque<int> dq;
    dq.print();
    dq.push_back(10);
    dq.print();
    std::cout << dq.Getback() << " " << dq.Getfront() << std::endl;
    dq.push_back(100);
    dq.push_front(20);
    dq.push_front(150);
    dq.push_back(250);
    dq.print();
    std::cout << "\n"
              << dq.Getback() << " " << dq.Getfront() << std::endl;
    dq.pop_front();
    dq.print();
    std::cout << "\n"
              << dq.Getback() << " " << dq.Getfront() << std::endl;
    dq.pop_back();
    dq.print();
    std::cout << "\n"
              << dq.Getback() << " " << dq.Getfront() << std::endl;
    std::cout << dq.GetSize();
}
