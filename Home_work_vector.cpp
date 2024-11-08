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

    void insert(unsigned int index, int element_value)
    {
        if (index > size)
        {
            PushBack(element_value);
        }
        else {
            EnsureCapacity();

            for (int i = size; i > index; --i)
            {
                data[i] = data[i - 1];
            }
            data[index] = element_value;
            size++;
        }
    }


    void remove_at(int index)
    {
        if (size == 0)
        {
            cout << "Vector is empty";
            return;
        }
        if (index > size)
        {
            size--;
            return;
        }
        else if (index < 0)
        {
            index = 0;
        }


        for (int i = index; i < size; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }

    void remove_by_value(int value) //
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == value)
            {
                for (int j = i; j< size; j++)
                {
                    data[j] = data[j + 1];
                }
                size--;
            }
        }
    }

    int pop_front()
    {   
        int a = data[0];
        for (int i = 0; i < size; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
        return a;
    }

    int pop_back()
    {
        int a = data[size - 1];
        size--;
        return a;
    }

    void trim_to_size()
    {
        int new_capacity = capacity - (capacity - size);
        int* temp = new int[new_capacity];
        for (int i = 0; i < size; ++i) 
        { 
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = new_capacity;
    }

    int index_of(unsigned int value)
    {
        int i = 0;
        while (i<size)
        {
            if (data[i] == value)
            {
                break;
            }
            i++;
        }
        if (i < size) return i;
        else return -1;
    }

    int last_index_of(int value)
    {
        int i = size;
        while (i >= 0)
        {
            if (data[i] == value)
            {
                break;
            }
            i--;
        }
        if (i < 0) return -1;
        else return i;
    }

    void reverse()
    {      
        
        for (int i = 0; i < size/2; ++i) 
        { 
            int temp = data[size - 1 - i];
            data[size - 1 - i] = data[i];
            data [i] = temp;
        }

    }

    Vector(const Vector& original)                      //конструктор копирования
    {
        size = original.size;

        if (this->data != nullptr) delete[] this->data;
        this->data = new int[size];

        for (int i = 0; i < size; i++)
        {
            data[i] = original.data[i];
        }
    }

    Vector& operator = (const Vector& original)
    {
        if (this == &original)
        {
            return *this;
        }

        size = original.size;

        if (this->data != nullptr) delete[] this->data;
        this->data = new int[size];

        for (int i = 0; i < size; i++)
        {
            data[i] = original.data[i];
        }      
    }



    friend ostream& operator << (ostream& os, const Vector& f);
    friend istream& operator >> (istream& is, Vector& f);

};

ostream& operator << (ostream& os, const Vector& f)
{
    for (int i = 0; i < f.GetSize(); i++)
    {
        os << f.data[i] << "\t";
    }
    os << "\n";
    return os;
}

//_______________________________________________________________
istream& operator >> (istream& is, Vector& f)
{
    int a;
       
    cout << "Введите размер массива: ";
    is >> a;

    int* b = new int[a];

    cout << "Введите массив из " << a << " элементов\n";
    for (int i = 0; i < a; i++)
    {
        cout << "Элемент " << i + 1 << ": ";
        is >> b[i];
    }
    f.size = a;

    for (int i = 0; i < a; i++)
    {
        f.data[i] = b[i];
    }

    delete[] b;

    return is;
}

int main()
{
    setlocale(0, "");

    Vector ar;
    ar.PushBack(1);
    ar.PushBack(2);
    ar.PushBack(3);
    ar.Print();
    ar.reverse();
    ar.Print();

    /*ar.remove_at(5);
    ar.Print();
    cout << "OK\n";*/


   /*Vector ar;

   cin >> ar;

   cout << ar;*/

   /*Vector ar_2(ar);
   cout << ar_2;*/

   /* Vector ar_2(4);
    ar_2.PushBack(7);
    cout << ar_2;

    ar_2 = ar;

    cout << ar_2;

    ar.Clear();

    ar.PushBack(1);
    ar.PushBack(2);
    ar.PushBack(3);
    ar.PushBack(4);
    ar.PushBack(5);
    ar.PushBack(4);

    ar.Print();
    ar.reverse();
    ar.Print();



    cout << ar.index_of(2) << "\n";
    cout << ar.index_of(7)<<"\n";

    cout << ar.last_index_of(2) << "\n";
    cout << ar.last_index_of(7) << "\n";

    ar.Print();
    ar.insert(1, 7);
    ar.Print();

    ar.remove_at(1);
    ar.Print();
    ar.remove_by_value(4);
    ar.Print();
    ar.pop_front();
    ar.Print();
    ar.pop_back();
    ar.Print();
    cout << "old capacity = " << ar.GetCapacity() << "\n";
    ar.trim_to_size();
    cout << "new capacity = " << ar.GetCapacity() << "\n";*/
}
