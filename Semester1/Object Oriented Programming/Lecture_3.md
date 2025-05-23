# Динамический полиморфизм C++
## Виртаульные функции
Проблема: при вызове метода у ссылки на базовый класс, вызывается метод базового класса
```cpp
struct Base
{
    void Foo() const
    {
        std::cout << "Base" << std::endl;
    }
};

struct Derived : Base
{
    void Foo() const
    {
        std::cout << "Derived" << std::endl;
    }
};

int main()
{
    Derived d;
    const Base& ref = d;
    ref.Foo(); // output: "Base"
}
```
Решение: виртуальные функции
```cpp
struct Base
{
    virtual void Foo() const // <- Функцию нужно объявить виртуальной только базовом классе
    {
        std::cout << "Base" << std::endl;
    }
};

struct Derived : Base
{
    void Foo() const override // <- override нужен для того, чтобы точно переопределить метод базового класса и не ошибиться в сигнатуре
    {
        std::cout << "Derived" << std::endl;
    }
};

int main()
{
    Derived d;
    const Base& ref = d;
    ref.Foo(); // output: "Derived"
    Base b = d;
    b.Foo();   // output: "Base" <-- Не сработает, если вызвать от копии
}
```
* 💡 **Важное определение:** класс называется полиморфным, если у него есть хоть одна виртуальная функция
* ! Виртуальные функции работают **только при вызове через ссылку** на базовый класс. Если сделать копию,
#### Плюсы минусы виртуальных функций
`++` При вызове по ссылке на базовый класс, вызываются методы наследников\
`--` Использование виртуальных функций более затратно, так как решение, какой метод вызвать, принимается в рантайме
#### Ключевые слова override и final
Ключевое слово `override` говорит компилятору о том, что мы переопределяем **виртуальный** метод базового класса. Если сигнатура метода в дочернем классе не совпадает с методом базового класса, будет CE\
Ключевое слово `final` говорит компилятору то же, что и `override`, но кроме этого запрещает переопределять этот метод в наследниках ниже по иерархии
## Чистые виртуальные функции
Можно объявить виртуальную функцию без определения
Синтаксис:
```cpp
struct Base
{
    virtual void Foo() const = 0; // Foo - чистая виртуальная функция (Pure virtual function)
};

struct Derived : Base
{
    void Foo() const override
    {
        std::cout << "Derived" << std::endl;
    }
};

int main()
{
    Derived d;
    const Base& ref = d;
    ref.Foo(); // output: "Derived"
}
```
💡 **Важное определение:** Класс, в котором есть **хотя бы одна** виртуальная функция, называется **абстрактным**

* Абстрактный класс **не может** быть инстанцирован! Иными словами, нельзя создать объект абстрактного класса
* При этом можно создавать ссылки на абстрактный класс, как в примере выше

## Хранение и передача полиморфных объектов
Часто нужно сохранить полиморфность объектов, но нет возможности передать их по ссылке (например возврат из функции). Ссылки не сгодятся, так как нельзя вернуть ссылку на локальный объект. А копировать не выйдет, так как тогда исчезнут свойства полиморфности. Выход есть!\
#### std::shared_ptr из \<memory\>
Клас
```cpp
#include <memory>

class AbstractWidget
{
public:
    virtual void Draw() const = 0;
    virtual ~AbstractWidget() = default; // Если вам нечего написать в деструкторе, то напиши = default
};

class Widget1 : public AbstractWidget
{
public:
    ~Widget1()
    {
        std::cout << "~Widget1()" << std::endl;
    }

    virtual void Draw() const override
    {
        std::cout << 1 << std::endl;
    }
};

class Widget2 : public AbstractWidget
{
public:
    ~Widget2()
    {
        std::cout << "~Widget2()" << std::endl;
    }
    virtual void Draw() const override
    {
        std::cout << 2 << std::endl;
    }
};

std::shared_ptr<AbstractWidget> BuildWidget(int id)
{
    if (id % 2 == 0)
    {
        return std::make_shared<Widget1>();
    }
    else
    {
        return std::make_shared<Widget2>();
    }
}

int main()
{
    auto widget = BuildWidget(5);
    widget->Draw(); // output: 2
} // <--- Только здесь разрушится объект Widget2 (output: ~Widget2)
```
Как видим из примера, сперва объект был создан в BuildWidget, а умер только по выходе из main. При этом вызвалась нужная нам реализация из Widget2
## Виртуальный деструктор
#### 📢❗🚨 Золотое правило: если в классе объявлена **хотя бы одна** виртуальная функция, то необходимо объявить и виртуальный деструктор. Если он тривиальный, напишите `= default`
Объяснение:\
В примере выше в случае использования shared_ptr будет всё хорошо. Однако если использовать какой-нибудь другой класс управления объектами (например, unique_ptr), то деструкторы классов наследников не вызовутся. Это критично, так как порой в деструкторах выполняются очень-очень важные действия

