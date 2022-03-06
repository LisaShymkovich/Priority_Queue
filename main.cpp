#include <iostream>
#include "priority_queue.hpp"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    PriorityQueue queue1;
    int size=0;
    int value;
    int pr;
    cout << "Введите кол-во элементов в очереди: ";
    cin >> size;
    while (size < 1)
    {
        cout << "Неверный ввод. Попробуйте снова: ";
        cin >> size;
    }
    
    for (int i = 0; i < size; i++)
    {
        cout << "Ввeдите значение: ";
        cin >> value;
        cout << "Выберите приоритет: \n";
        for (int i = 0; i < priorities_num - 1 ; i++)
        {
            cout << to_string(i+1) << "." << priorities_names[i] << "\n";
        }
        cin >> pr;
        
        while (pr < 1 || pr > priorities_num)
        {
            cout << "Неверный ввод. Попробуйте снова: ";
            cin >> pr;
        }
        try
        {
            queue1.Insert(value, Priority(pr));
        }
        catch (const runtime_error &ex)
        {
            cout << ex.what() << endl;
        }
        
    }
    
    cout << "Очередь: ";
    queue1.WriteToStream(cout);
    cout << endl;
    
    cout << "Первый элемент в очереди: " << queue1.GetHeadValue() << endl;
    cout << "Приоритет первого элемента в очереди: " << priorities_names[int(queue1.GetHeadPriority())-1]  << endl;
    cout << "\n";
    
    queue1.Pop();
    cout << "Очередь после удаления: ";
    queue1.WriteToStream(cout);
    cout << endl;
    try
    {
        cout << "Первый элемент в очереди после удаления: " << queue1.GetHeadValue() << endl;
        cout << "Приоритет первого элемента в очереди после удаления : " << priorities_names[int(queue1.GetHeadPriority())-1] << endl;
    }
    catch (const runtime_error &ex)
    {
        cout << ex.what() << endl;
    }
    
    cout << "Количество элементов в очереди после удаления: " << queue1.GetTotalSize() << endl;
    cout << "\n";
    int sizeOption;
    cout << "Информацию о каком приоритете вы хотите получить: " << endl;
    for (int i = 0; i < priorities_num - 1; i++)
    {
        cout << to_string(i+1) << "." << priorities_names[i] << "\n";
    }
    cin >> sizeOption;
    while (sizeOption < 1 || sizeOption > priorities_num )
    {
        cout << "Неверный ввод. Попробуйте снова: ";
        cin >> sizeOption;
    }
    cout << "Количество элементов заданного приоритета: " << queue1.GetCountOfPriority(Priority(sizeOption)) << endl;
    cout << "\n";
    
    cout << "Очередь пуста после удаления первого? " ;
    if (!queue1.IsEmpty()) cout << "Очередь не пуста!" << endl;
    else cout << "Очередь пуста!";
    cout << "\n";
    
    
    queue1.Erase();
    cout << "Очередь пуста после удаления всех? " ;
    if (!queue1.IsEmpty()) cout << "Очередь не пуста!" << endl;
    else cout << "Очередь пуста!" << endl;
    cout << "\n";
    return 0;
}
