#include <iostream>
using namespace std;

class MyList {                                       //Список MyList
    int x, count_;
    MyList* Head, * Tail, * Next, * Prev;
public:
    MyList() :count_(0), Head(NULL), Tail(NULL) {};     //Инициализация с помощью конструктора по умолчанию
    void Add(int);
    void Show();
    void Del(int);                                  //Функция принимает целочисленный параметр, обозначающий номер удаляемого элемента
    ~MyList();
};

/*ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СПИСОК*/
void MyList::Add(int x) {
    MyList* temp = new MyList;
    temp->x = x;
    temp->Next = NULL;
    count_++;
    if (!Head) {
        temp->Prev = NULL;
        Head = temp;
        Tail = Head;
    }
    else {
        temp->Prev = Tail;                  
        Tail->Next = temp;                
        Tail = temp;                        
    }
}

/*ПОКАЗЫВАЕТ СПИСОК НА ЭКРАНЕ*/
void MyList::Show() {
    MyList* t = Head;
    while (t) {
        cout << t->x << " ";
        t = t->Next;
    }
    cout << "\n\n";
}


/*ФУНКЦИЯ УДАЛЕНИЯ  ЭЛЕМЕНТА ДВУСВЯЗНОГО СПИСКА*/
void MyList::Del(int x) {
    //удаляем первый элемент
   
    if ((x == 1) and (Head->Next)) {                     
        MyList* temp = Head;	                        //Указываем, что нам нужно начало списка
        Head = Head->Next;	                            
        Head->Prev = NULL;	                            //Делаем так, чтоб предыдущий началу элемент был пустым
        delete temp;		                            //Удаляем удаляемое начало
        count_--;		                                //Обязательно уменьшаем счетчик
        return;		                                //И выходим из функции
    }
    else if ((x == 1) and (Head == Tail)) {           

        Head->Next = NULL;	                            //обнуляем все что нужно
        Head = NULL;
        delete Head;		                            //Удаляем указатель на начало
        count_ = 0;		                                //обозначаем, что в списке ноль элементов
        return;			                                //выходим из функции
    }

    // удаляемый элемент является последним элементом списка
   if (x == count_) {
        MyList* temp = Tail;	                            //Указываем, что нам нужен конец
        Tail = Tail->Prev;	                                
        Tail->Next = NULL;	                                //Обозначаем, что впереди  пусто
        delete temp;	                                    //Очищаем память 
        count_--;		                                    //Обязательно уменьшаем счетчик элементов
        return;		                                    //И выходим из функции
    }

    //удаляемый элемент лежит где-то в середине списка

    MyList* temp = Head, * temp2;                        //temp-Удаляемый элемент, temp2 нужен, чтобы не потерять данные

    cout<<count_<<"\n";
    for (int i = 0; i < x - 1; i++) temp = temp->Next;  //Идем к адресу удаляемого элемента

    temp2 = temp;	                                //Временно запоминаем адрес удаляемого элемента
    temp2->Prev->Next = temp->Next;	            //Записываем данные, что следующий за перед сейчас удаляемым элементом - это следующий от удаляемого
    temp2->Next->Prev = temp->Prev;               //а предыдущий для следующего - это предыдущий для удаляемого
    delete temp;                               //теперь смело можно освободить память, удалив адрес на начало удаляемого элемента
    count_--;                                         //Обязательно уменьшаем число элементов в списке.
    }


/*ДЕСТРУКТОР ДЛЯ КОРРЕКТНОГО ВЫСВОБОЖДЕНИЯ ПАМЯТИ*/
MyList::~MyList() {
    while (Head) {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }
}



int main() {
    MyList List1;
    List1.Add(10);
    List1.Add(20);
    List1.Add(30);
    List1.Add(40);
    List1.Add(50);
    List1.Show();
    List1.Del(1);//обозначаем какой элемент удаляем
    List1.Show();
    List1.Add(1000);// обозначаем какой элемент добавляем в конец
    List1.Show();
 
    
}