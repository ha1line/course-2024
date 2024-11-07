# Lecture 1

## Структуры. Синтаксис, объявление, инициализация
```cpp
struct Person
{
    std::string name; // поле структуры
    int age = 0;      // значение поля по умолчанию
}; // <-- !!! не забывайте эту точку с запятой. Компиляторы часто пишут непонятные ошибки из-за её отсутсвия

int main()
{
    Person p; // p - объект класса Person
    p.name = "Boris"; // обращение к полям структуры
    
    // Аггрегатная инициализация структуры (поля указываеются в порядке их объявления)
    Person p2 = {"Boris", 18};
    // C++20: Аггрегатная инициализация с явным указанием полей
    // (предпочтительно использовать именно её, так как в примере выше не очень понятно, что значит 18)
    Person p3 = {.name = "Boris", .age = 18};
    return 0;
}
```
## Методы классов
```cpp
struct S
{
    void Foo() // Метод класса
    {
        std::cout << "Non const" << std::endl;
    }

    void Foo(int x) // Перегрузка методов
    {
        std::cout << "Non const Foo(int). x = " << x << std::endl;
    }

    void FooConst() const // Константный метод класса (может быть вызван )
    {
        std::cout << "Const" << std::endl;
    }

    std::string someData;
};

int main()
{
    S s;
    s.Foo(); // Ok, output "Non const"
    s.Foo(5); // Ok, output "Non const Foo(int). x = 5"
    s.FooConst(); // Ok, output "Const"
    
    const S s2;
    s2.FooConst(); // Ok, output "Const"
    s2.Foo(); // CE - нельзя вызвать неконстантный метод у константного объекта
    return 0;
}
```
# Конструкторы классов
```cpp
struct S
{
    S() = default; // Конструктор по умолчанию

    S(std::string str, int y) // Конструктор от строки и числа
        : message(str), y(y)  // список инициализации
    {
        // Тело конструктора. !!! Используйте его только для нетривиальных действий
    }
    // слово explicit надо ставить, если конструктор от одного аргумента
    explicit S(double x) // Перегрузка конструктора по double
    {
    }

    std::string message;
    int y = 0;
};
```
# Модификаторы доступа `public` и `private`
```cpp
class C
{
public:
    void publicFoo()
    {
    }
    std::string somePublicData;

private:
    void secretFoo()
    {
    }
    std::string someImportantData;
};

int main()
{
    C c;
    c.publicFoo(); // Ok
    c.somePublicData = "Hello"; // Ok
    c.secretFoo(); // CE: secretFoo is private member of C
    c.someImportantData = "world"; // CE: someImportantData is private member of C
    return 0;
}

```
!!! Первое (из двух) отличие классов и структур. У структур по умолчанию все поля public, а у классов private
