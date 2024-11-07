#include <iostream>
#include <windows.h>
using namespace std;

class Vector {
    unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
    unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
    int* data = nullptr; // указатель на динамический массив целых чисел

    // метод приватный, потому что это внутрення логика класса, о которой клиент думать не должен
    void EnsureCapacity() {
        // если весь резерв памяти исчерпан
        if (size == capacity) {
            capacity *= 2; // собираемся увеличить резерв памяти в 2 раза
            int* temp = new int[capacity];
            for (int i = 0; i < size; ++i) { // memcpy_s
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
    }

public:
    Vector() : Vector(10) {
        // cout << "C-TOR WITHOUT PARAMS!\n";
    }

    Vector(unsigned int capacity) {
        if (capacity < 10)
            capacity = 10;

        this->capacity = capacity;
        data = new int[capacity];
        // cout << "C-TOR WITH PARAMS!\n";
    }

    ~Vector() {
        // cout << "DESTRUCTOR!\n";
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    unsigned int GetSize() const {
        return size;
    }

    unsigned int GetCapacity() const {
        return capacity;
    }

    // TODO:
    // перегрузка = 
    // КК

    void PushBack(int value) {
        EnsureCapacity(); // проверка, хватит ли места для нового элемента
        data[size++] = value;
    }

    void PushFront(int value) {
        EnsureCapacity();
        for (int i = size; i > 0; --i) // i = 1
            data[i] = data[i - 1]; // data[1] = data[0]

        data[0] = value;
        size++;
    }

    void Clear() {
        // if (data != nullptr) delete[] data;
        // capacity = 0;
        size = 0;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void Print() const {
        if (IsEmpty()) {
            cout << "Vector is empty.\n";
            return;
        }

        for (int i = 0; i < size; ++i)
            cout << data[i] << " ";

        cout << "\n";
    }

    // ...остальные методы...

    void Insert(int index, int element_value)
    {
        if (index > size)
        {
            EnsureCapacity();
            data[size++] = element_value;
        }

        EnsureCapacity();

        for (int i = size; i > index; --i)
        {
            data[i] = data[i - 1];
        }
        data[index] = element_value;
        size++;
    }


    void RemoveAt(int index)
    {
        if (index > size)
        {
            size--;
        }
        else if (index < 0)
        {
            index == 0;
        }


        for (int i = index; i < size; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }



};

int main()
{
    Vector ar;
    ar.PushBack(1);
    ar.PushBack(2);
    ar.PushBack(3);
    ar.Print();
    ar.Insert(1, 7);
    ar.Print();

    ar.RemoveAt(1);
    ar.Print();



}
