# Наследование и время жизни объектов
## Наследование структур
При наследовании наследуются все поля и методы базового класса
```cpp
struct Base
{
    void Foo() const
    {
        std::cout << "Foo" << std::endl;
    }
    int a = 5;
};

struct Derived : Base
{
    void Bar() const
    {
        std::cout << "Bar" << std::endl;
    }
    int b = 10;
};

int main()
{
    Derived der;
    std::cout << der.b << std::endl; // Обращение к полю класса. output: 10
    der.Bar();                       // Вызов метода класса
    std::cout << der.a << std::endl; // Обращение к полю базового класса. output: 5
    der.Foo();                       // Вызов методы базового класса
}
```
## Публичное и приватное наследование
Структуры по умолчанию наследуются **публично**\
Классы по умолчанию наследуются **приватно**\
\* **Приватное** наследование создаёт для пользователя видимость, что производный класс не является наследником базового
```cpp
struct Base
{
    void Foo() const
    {
        std::cout << "Foo" << std::endl;
    }
    int a = 5;
};

struct PublishedExample : public Base // Пример публичного наследования
{
    void BarPub() const
    {
        std::cout << a << std::endl; // Обращение к полю базового класса
    }
 
};

struct PrivatedExample : private Base // Пример приватного наследования
{
    void BarPriv() const
    {
        // При приватном наследовании к полям базового класса можно обращаться только из методов производного
        // Нельзя обратиться из вне
        std::cout << a << std::endl; // Обращение к полю базового класса
    }
};

int main()
{
    PublishedExample pub;
    pub.Foo(); // Ok
    pub.a;     // Ok
    pub.BarPub(); // Ok. output: 5
    const Base& baseRef = pub; // Ok: на дочерний класс можно смотреть как на базовый
    Base base = pub;           // Ok: Можно скопировать ту часть pub, которая является base

    // Для внешнего наблюдателя класс PrivatedExample не является наследником Base
    // это его секрет :)
    PrivatedExample priv;
    priv.Foo(); // CE
    priv.a;     // CE
    const Base& baseRef2 = priv; // CE
    Base base2 = priv; // CE
    priv.BarPriv(); // Ok. output: 5
}
```
## Поведение модификаторов доступа при наследовании
**public, private, protected**
```cpp
class Base
{
    void Bar() const
    {
        std::cout << pub << std::endl;  // Ok
        std::cout << prot << std::endl; // Ok
        std::cout << priv << std::endl; // Ok
    }
public:
    int pub = 1;
protected:
    int prot = 2;
private:
    int priv = 3;
};

class Derived : public Base
{
    void Foo() const
    {
        std::cout << pub << std::endl;  // Ok. public поля доступны наследникам и внешним пользователям
        std::cout << prot << std::endl; // Ok. protected поля доступны только наследникам
        std::cout << priv << std::endl; // CE. private поля доступны только классу, в котором они объявлены
    }
};

int main()
{
    Derived der;
    der.pub; // Ok. public поля доступны внешним пользователям
    der.prot; // CE
    der.priv; // CE
}
```

## Время жизни объектов. Порядок конструирования и разрушения
У создании объектов любого класса всегда вызывается **конструктор**, а при разрушении - **деструктор**. Если вы не написали конструктор/деструктор явно, то компилятор сгенерирует его за вас.
```cpp
struct A
{
    A()
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;    
    }
};

int main()
{
    A a;
    // output:
    // A()
    // ~A()
}
```
Время разрушения объекта в C++ (в отличие от большинства языков) **детерменированно** (мы всегда чётко знаем, когда объект перестанет существовать).
Правила конструирования и разрушения объектов можно описать следующими утверждениями:
1. Объекты на стеке создаются в момент их объявления и разрушаются при выходе из скоупа
2. Объекты разрушаются в порядке, обратном их объявлению
3. При создании объекта, сначала вызываются конструкторы его полей в порядке их объявления. Деструкторы вызываются в обратном порядке (см. п. 2)
4. При наследовании сначала конструируется базовый класс, а потом уже дочерний. Деструкторы, как всегда, вызываются обратном порядке (см. п. 2)

Пример, где собраны все эти правила:
```cpp
struct A
{
    A()
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;    
    }
};

struct B
{
    B()
    {
        std::cout << "B()" << std::endl;
    }
    ~B()
    {
        std::cout << "~B()" << std::endl;    
    }
};

struct C
{
    C()
    {
        std::cout << "C()" << std::endl;
    }
    ~C()
    {
        std::cout << "~C()" << std::endl;    
    }
};

struct Base
{
    Base()
    {
        std::cout << "Base()" << std::endl;
    }

    A a;
    B b;

    ~Base()
    {
        std::cout << "~Base()" << std::endl;
    }
};

struct Derived : public Base
{
    Derived()
    {
        std::cout << "Derived()" << std::endl;
    }
    
    C c;
    
    ~Derived()
    {
        std::cout << "~Derived()" << std::endl;
    }
};

int main()
{
    {
        A a; // A()
        B b; // B()
    } // <-- конец скоупа: ~B(), ~A()
    std::cout << std::endl;
    {
        Base base; // A(), B(), Base()
    } // <--      ~Base(), ~B(), ~A()
    std::cout << std::endl;
    {
        Derived d; // A(), B(), Base(), C(), Derived()
    } // <--          ~Derived(), ~C(), ~Base(), ~B(), ~A()
}
```
Output:
```
A()
B()
~B()
~A()

A()
B()
Base()
~Base()
~B()
~A()

A()
B()
Base()
C()
Derived()
~Derived()
~C()
~Base()
~B()
~A()
```

