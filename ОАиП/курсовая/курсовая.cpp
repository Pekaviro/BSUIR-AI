#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <vector>

using namespace std;

struct Participant 
{
    string name;
    string nomination;
    int age;
    int quantity;
} list;

// Функция для считывания данных из файла
vector<Participant> inputData(const string& filename)
{
    int number_of_lines = 0;
    string line;
    ifstream file(filename);
    while (getline(file, line))
        ++number_of_lines;
    ifstream inputFile(filename);
    vector<Participant> list(number_of_lines); // Объявление массива структур
    if (inputFile.is_open()) 
    {
        int count = 0; // Количество считанных записей
        while (count<number_of_lines) 
        {
            inputFile >> list[count].name >> list[count].nomination >> list[count].age >> list[count].quantity;
            ++count;
        }
    }
    else 
        cout << "Файл для чтения не открыт" << endl;
    inputFile.close();
    return list;
}

// Функция для добавления данных в файл
void addDataToFile(const string& filename) 
{
    Participant stru;
    cout << "Введите название танцевального коллектива: ";
    cin >> stru.name;
    cout << "Введите номинацию: ";
    cin >> stru.nomination;
    cout << "Введите возрастную категорию: ";
    while (true)
    {
        cin >> stru.age;
        if (stru.age != 1 && stru.age != 2 && stru.age != 3)
        {
            cin.clear();
            cin.ignore();
            cout << "Пожалуйста, введите корректное значение." << endl;
        }
        else
            break;
    }
    cout << "Введите количество участников: ";
    while (true)
    {
        cin >> stru.quantity;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Пожалуйста, введите корректное значение." << endl;
        }
        else
            break;
    }
    ofstream file(filename, ios::app);
    if (file.is_open()) 
    {
        file << setw(25) << left << stru.name << setw(20) << stru.nomination << setw(25) << stru.age << setw(10) << stru.quantity << endl;
        file.close();
        cout << endl << "Данные успешно добавлены в файл." << endl;
    }
    else 
    {
        cout << "Ошибка при добавлении данных в файл." << endl;
    }
    cout << endl;
}

// Функция для удаления данных в файле
void deleteDataInFile(const string& filename) {
    string targetName;
    cout << "Введите название коллектива для удаления: ";
    cin >> targetName;
    cout << endl;
    vector<Participant> list = inputData(filename);
    // Выполнить линейный поиск по названию
    bool found = false;
    ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].name != targetName)
            {
                outputFile << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
            }
            else
                found = true;
        }
        if (!found)
        {
            cout << "Коллектив с названием " << targetName << " не найден." << endl;
        }
        else
            cout << "Данные успешно удалены." << endl;
    }
    else
    {
        cout << "Ошибка при удалении данных из файла." << endl;
    }
    cout << endl;
}

// Функция для просмотра содержимого файла
void viewFile(const string& filename) 
{
    ifstream file(filename);
    string line;
    cout << endl;
    cout << setw(25) << left << "Название коллектива" << setw(20) << "Номинация" << setw(25) << "Возрастная категория" << setw(10) << "Количество участников" << endl;
    cout << "........................................................................................................" << endl;
    if (file) 
    { 
        while(getline(file, line))
        cout << line << endl;
    }
    else 
    {
        cout << "Ошибка при просмотре файла" << endl;
    }
    cout << endl;
}

// Функция для сортировки методом прямого обмена по количеству участников в порядке возрастания 
void bubbleSortAsc(const string& filename) 
{
    vector<Participant> list = inputData(filename);
    // Сортировка
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < list.size() - 1; ++i) 
        {
            if (list[i].quantity > list[i + 1].quantity) 
            {
                swap(list[i], list[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
    // Запись отсортированных данных в файл
    ofstream outputFile(filename);
    for (int i = 0; i < list.size(); ++i) 
    {
        outputFile << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
    }
}

// Функция для сортировки методом прямого обмена по количеству участников в порядке убывания
void bubbleSortDesc(const string& filename) 
{
    vector<Participant> list = inputData(filename);
    // Сортировка
    bool swapped;
    do 
    {
        swapped = false;
        for (int i = 0; i < list.size() - 1; ++i)
        {
            if (list[i].quantity < list[i + 1].quantity) 
            {
                swap(list[i], list[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
    // Запись отсортированных данных в файл
    ofstream outputFile(filename);
    for (int i = 0; i < list.size(); ++i)
    {
        outputFile << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
    }
    viewFile(filename);
    cout << "Данные успешно отсортированы и записаны в файл." << endl << endl << endl;
}

// Функция для обмена элементов массива
void swap(Participant& a, Participant& b) 
{
    Participant temp = a;
    a = b;
    b = temp;
}

// Функции для разделения массива и возврата индекса опорного элемента
int partitionAsc(vector<Participant>& arr, int low, int high) 
{
    int i = low - 1;
    for (int j = low; j < high; j++) 
    {
        if (arr[j].age < arr[high].age)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int partitionDesc(vector<Participant>& arr, int low, int high) 
{
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j].age > arr[high].age)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Функции для реализации QuickSort
void QuickSortAsc(vector<Participant>& arr, int low, int high)
{
    if (low < high) 
    {
        int index = partitionAsc(arr, low, high);
        QuickSortAsc(arr, low, index - 1);
        QuickSortAsc(arr, index + 1, high);
    }
}

void QuickSortDesc(vector<Participant>& arr, int low, int high) 
{
    if (low < high)
    {
        int index = partitionDesc(arr, low, high);
        QuickSortDesc(arr, low, index - 1);
        QuickSortDesc(arr, index + 1, high);
    }
}

// Функция для сортировки методом QuickSort по возрасту в порядке возрастания
void sortbyQuantityAsc(const string& filename) 
{
    vector<Participant> list = inputData(filename);
    // Сортировка
    QuickSortAsc(list, 0, list.size() - 1);
    // Запись отсортированных данных в файл
    ofstream outputFile(filename);
    for (int i = 0; i < list.size(); ++i) 
    {
        outputFile << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
    }
    viewFile(filename);
    cout << "Данные успешно отсортированы и записаны в файл." << endl << endl << endl;
}

// Функция для сортировки методом QuickSort по возрасту в порядке убывания
void sortbyQuantityDesc(const string& filename) 
{
    vector<Participant> list = inputData(filename);
    // Сортировка
    QuickSortDesc(list, 0, list.size() - 1);
    // Запись отсортированных данных в файл
    ofstream outputFile(filename);
    for (int i = 0; i < list.size(); ++i) 
    {
        outputFile << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
    }
    viewFile(filename);
    cout << "Данные успешно отсортированы и записаны в файл." << endl << endl << endl;
}

// Функция для бинарного поиска по количеству участников 
void binarySearch(const string& filename)
{
    cout << "Введите количество участников: ";
    int targetQuantity;
    while (true)
    {
        cin >> targetQuantity;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Пожалуйста, введите корректное значение." << endl;
        }
        else
            break;
    }
    cout << endl << endl;
    bubbleSortAsc(filename);
    vector<Participant> list = inputData(filename);
    // Выполнить бинарный поиск по количеству участников
    int low = 0;
    int high = list.size() - 1;
    bool found = false;
    while (low <= high) 
    {
        int mid = low + (high - low) / 2;
        if (list[mid].quantity == targetQuantity)
        {
            // Вывести информацию о найденном коллективе 
            cout << "Найден(ы) коллектив(ы) с количеством участников " << targetQuantity << ":" << endl << endl;
            cout << setw(25) << left << "Название коллектива" << setw(20) << "Номинация" << setw(25) << "Возрастная категория" << setw(10) << "Количество участников" << endl;
            cout << "........................................................................................................" << endl;
            cout << setw(25) << left << list[mid].name << setw(20) << list[mid].nomination << setw(25) << list[mid].age << setw(10) << list[mid].quantity << endl;
            found = true;
            for (int i = mid-1; list[i].quantity == targetQuantity; i--)
            {
                cout << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
            }
            for (int i = mid+1; list[i].quantity == targetQuantity; i++)
            {
                cout << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
            }
            break;
        }
        else if (list[mid].quantity < targetQuantity) 
        {
            low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
    }
    if (!found)
    {
        cout << "Коллектив с количеством участников " << targetQuantity << " не найден." << endl << endl;
    }
    cout << endl << endl;
}

// Функция для линейного поиска по возрастной категории
void linearSearch(const string& filename) 
{
    cout << "Введите возрастную категорию: ";
    int targetAge;
    while (true) {
        cin >> targetAge;
        if (targetAge != 1 && targetAge != 2 && targetAge != 3)
        {
            cin.clear();
            cin.ignore();
            cout << "Пожалуйста, введите корректное значение." << endl;
        }
        else
            break;
    }
    cout << endl << endl;
    vector<Participant> list = inputData(filename);
    // Выполнить линейный поиск по возрасту
    bool found = false;
    for (int i = 0; i < list.size(); i++) 
    {
        if (list[i].age == targetAge) 
        {
            cout << "Найден(ы) коллектив(ы) с возрастной категорией " << targetAge << ":" << endl << endl;
            cout << setw(25) << left << "Название коллектива" << setw(20) << "Номинация" << setw(25) << "Возрастная категория" << setw(10) << "Количество участников" << endl;
            cout << "........................................................................................................" << endl;
            found = true;
            break;
        }
    }
    for (int i = 0; i < list.size(); i++) 
    {
        if (list[i].age == targetAge)
        {
            // Вывести информацию о найденном коллективе
            cout << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
        }
    }
    cout << endl << endl;
    if (!found) 
    {
        cout << "Коллектив в возрастной категории " << targetAge << " не найден." << endl;
    }
}

//Функция выполнения задания
void resultTask(const string& filename)
{
    cout << "Введите номинацию: ";
    string targetNomination;
    cin >> targetNomination;
    cout << endl;
    vector<Participant> list = inputData(filename);
    ofstream outputFile("result.txt");
    // Выполнить линейный поиск по номинации
    bool found = false;
    for (int i = 0; i < list.size(); i++) 
    {
        if (list[i].nomination == targetNomination) 
        {
            cout << "Найден(ы) коллектив(ы) в номинации " << targetNomination << ":" << endl << endl;
            found = true;
            break;
        }
    }
    for (int i = 0; i < list.size(); i++) 
    {
        if (list[i].nomination == targetNomination)
        {
            outputFile << setw(25) << left << list[i].name << setw(20) << list[i].nomination << setw(25) << list[i].age << setw(10) << list[i].quantity << endl;
        }
    }
    if (!found) 
    {
        cout << "Коллектив в номинации " << targetNomination << " не найден." << endl;
    }
    else
    {
        sortbyQuantityAsc("result.txt");
    }
    cout << endl;
}

int main() 
{
    string filename = "list.txt";
    int a;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do 
    {
        cout << "Меню:" << endl;
        cout << "1. Добавить данные в файл" << endl;
        cout << "2. Удалить данные в файле" << endl;
        cout << "3. Просмотреть файл" << endl;
        cout << "4. Отсортировать файл методом прямого обмена по количеству участников в порядке возрастания" << endl;
        cout << "5. Отсортировать файл методом прямого обмена по количеству участников в порядке убывания" << endl;
        cout << "6. Отсортировать файл методом QuickSort по возрастной категории в порядке возрастания" << endl;
        cout << "7. Отсортировать файл методом QuickSort по возрастной категории в порядке убывания" << endl;
        cout << "8. Бинарный поиск танцевального коллектива по количеству участников" << endl;
        cout << "9. Линейный поиск танцевального коллектива по возрастной категории" << endl;
        cout << "10. Вывести в порядке возрастания возрастной категории список коллективов, участвующих в определённой номинации, и сохранить список в файл result.txt" << endl;
        cout << "0. Выйти" << endl;
        cout << "Выберите действие: ";
        while (true) 
        {
            cin >> a;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "Пожалуйста, введите корректное значение." << endl;
            }
            else
                break;
        }
        cout << endl;
            switch (a) 
            {
            case 1: 
            {
                addDataToFile(filename);
                break;
            }
            case 2: 
            {
                deleteDataInFile(filename);
                break;
            }
            case 3: 
            {
                viewFile(filename);
                break;
            }
            case 4:
            {
                bubbleSortAsc(filename);
                viewFile(filename);
                cout << "Данные успешно отсортированы и записаны в файл." << endl << endl << endl;
                break;
            }
            case 5: 
            {
                bubbleSortDesc(filename);
                break;
            }
            case 6: 
            {
                sortbyQuantityAsc(filename);
                break;
            }
            case 7: 
            {
                sortbyQuantityDesc(filename);
                break;
            }
            case 8:
            {
                binarySearch(filename);
                break;
            }
            case 9: 
            {
                linearSearch(filename);
                break;
            }
            case 10: 
            {
                resultTask(filename);
                break;
            }
            }
    } while (a != 0);
    return 0;
}