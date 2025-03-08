## Идиома RAII

>[!Note]
RAII (Resource Acquisition Is Initialization) — программная идиома, смысл которой заключается в том, что получение некоторого ресурса неразрывно совмещается с созданием объекта, а освобождение — с его уничтожением. 

Поскольку нам гарантировано, что вызов конструктора будет произведен строго в момент **создания** объекта, а вызов **деструктора** в момент его уничтожения, то мы можем привязать к этому свойству работу с ресурсами, например, выделение памяти.

Напишем пример простейшего умного указателя:
```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;#
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    PointerToInt p(5);
    std::cout << *p.m_ptr << std::endl;
}
```

Теперь нам не нужно явно вызывать `delete` для нашего поинтера — это будет сделано за нас в деструкторе. Таким образом, переживать об утечке памяти не стоит.

> [!Note]
> По идиоме RAII работают огромное количество классов стандартной библиотеки: практические все стандартные контейнеры, умные указатели, работа с файловыми и строковыми потоками, тредами и многим другим.

### Конструкторы копирования, операторы присваивания, правило 3-х, правило нуля
#### Конструкторы копирования
Давайте воспользуемся нашим классом умного указателя и дополним код
```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    PointerToInt p(5);
    std::cout << *p.m_ptr << std::endl;
    PointerToInt p1(p);
}
```

При вызове данного кода он падает с сообщением.
```
5
a.out(77885,0x1f931b840) malloc: Double free of object 0x142e05de0
a.out(77885,0x1f931b840) malloc: *** set a breakpoint in malloc_error_break to debug
fish: Job 1, './a.out' terminated by signal SIGABRT (Abort)
```

При создания объекта `p1` мы просто скопировали все поля из `p`. Таким образом указатель `m_ptr` в полях стал указывать на одну и ту же память. При разрушении объекта `delete` был вызван 2 раза для одного указателя, т. е. случилось UB.

Решить эту проблему можно разными способами, начнем с самого простого — запретим копировать наш объект. 
За копирования объектов класса отвечают конструкторы копирования и операторы копирующего присваивания. Начиная с С++11 мы можем пометить их `delete`, запретив копировать объект.
```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

	// Copy constructor
    PointerToInt(const PointerToInt&) = delete;
	// Copy assignment operator
	PointerToInt& operator=(const PointerToInt&) = delete;

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    PointerToInt p(5);
    std::cout << *p.m_ptr << std::endl;
    // CE, Copy constructor deleted
    // PointerToInt p1(p);
	PointerToInt p2;
	// CE, Copy assignment operator deleted
	// p2 = p;
}
```

> [!Note]
> Если в вашем классе в конструкторе вы делаете специфические операции, например, выделяете память в куче, то вам нужно переопределить деструктор, конструктор копирования и оператор копирующего присваивания. 
> Эту особенность называют «**Правило 3-х**»
> 
> В случае, когда в вашем конструкторе не происходит такой логики, реализовывать деструктор, конструктор копирования, оператор копирующего присваивания не нужно — за вас это сделает компилятор.
> Эту особенность называют «**Правило нуля**»

### Копирование объекта, продолжение
Вернемся к нашей проблеме, при дефолтной реализации конструктора копирования и оператора копирующего присваивания мы падали с `double free`
Одно решение для данной проблемы мы уже нашли: можно просто запретить копировать объект. Теперь обратимся к другим.
#### Копирование объекта с выделением новой сущности или глубокое копирование:

```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

    // Copy constructor
    PointerToInt(const PointerToInt& o) :
        m_ptr(new int(*o.m_ptr))
    {
    }

    // Copy assignment operator
    PointerToInt& operator=(const PointerToInt& o)
    {
        if (this != &o)
        {
            delete m_ptr;
            m_ptr = new int(*o.m_ptr);
        }
        return *this;
    }

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    // Copy Constructor
    {
        PointerToInt p(5);
        std::cout << "first pointer:" << *p.m_ptr << std::endl;
        PointerToInt p1(p);
        std::cout << "second pointer:" << *p1.m_ptr << std::endl;
    }
    // Copy Assignment Operator
    {
        PointerToInt p(5);
        std::cout << "first pointer:" << *p.m_ptr << std::endl;
        PointerToInt p1;
        p1 = p;
        std::cout << "second pointer:" << *p1.m_ptr << std::endl;
    }
}
```

Программа выведет:
```cpp
5
5
```

В такой реализации для каждого нового объекта `PointerToInt` будет выделен новый блок памяти в куче. Таким образом, при разрушении объекта и вызове деструктора не будет происходить `double free`.
Однако в этом коде остаётся одна существенная ошибка в реализации конструктора копирования. Мы рассмотрели случаи, когда исходный объект класса `PointerToInt` уже хранит созданный объект, а не `nullptr`. Что же будет, если мы напишем вот такой тест:

```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

    // Copy constructor
    PointerToInt(const PointerToInt& o) :
        m_ptr(new int(*o.m_ptr))
    {
    }

    // Copy assignment operator
    PointerToInt& operator=(const PointerToInt& o)
    {
        if (this != &o)
        {
            delete m_ptr;
            m_ptr = new int(*o.m_ptr);
        }
        return *this;
    }

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    // Default Pointer
    {
        PointerToInt p;
        PointerToInt p1(p);
        std::cout << (p.m_ptr == nullptr) << " " << (p1.m_ptr == nullptr) << std::endl;
    }
    {
        PointerToInt p;
        PointerToInt p1(5);
        p1 = p;
        std::cout << (p1.m_ptr == nullptr) << std::endl;
    }}

```

Программа аварийно завершится, с сообщением:
```
'./a.out' terminated by signal SIGSEGV (Address boundary error)
```

Фактически, в процессе копирования нашего объекта мы разыменовали `nullptr`, что является UB. Тоже самое произойдет и в операторе копирующего присваивания. Давайте исправим эту проблему, добавив проверку на нулевой указатель. Также в операторе присваивания обработаем ситуацию, когда мы присваиваем объект самому себе. В данном случае нам не нужно предпринимать никаких действий.

```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

    // Copy constructor
    PointerToInt(const PointerToInt& o) :
        m_ptr((o.m_ptr != nullptr) ? (new int(*o.m_ptr)) : (nullptr))
    {
    }

    // Copy assignment operator
    PointerToInt& operator=(const PointerToInt& o)
    {
        if (this == &o)
        {
            return *this;
        }

        delete m_ptr;
        m_ptr = (o.m_ptr != nullptr) ? (new int(*o.m_ptr)) : (nullptr);

        return *this;
    }

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    // Default Pointer
    {
        PointerToInt p;
        PointerToInt p1(p);
        std::cout << (p.m_ptr == nullptr) << " " << (p1.m_ptr == nullptr) << std::endl;
    }
    {
        PointerToInt p;
        PointerToInt p1(5);
        p1 = p;
        std::cout << (p1.m_ptr == nullptr) << std::endl;
    }
    {
		PointerToInt p;
		p = p;
	}
}
```

Такая реализация оператора копирующего присваивания выглядит не очень интуитивной и копирует часть кода из конструктора. При этом нам приходится в ручном режиме вызывать `delete` и `new`, что не является хорошей практикой и может потенциально сгенерировать новые ошибки. Здесь нам на помощь придёт еще одна идиома — **Copy and Swap**.
#### Идиома Copy and Swap
Мы уже реализовали конструктор копирования, поэтому в операторе копирующего присваивания можем выполнить следующие действия:
1. Создать копию объекта
2. Поменять значения у исходного объекта и копии
При такой реализации выделение и очистка памяти произойдёт автоматически в конструкторе и деструкторе объекта, мы лишь поменяем местами указатели у нашего и временного объекта.

```cpp
#include <iostream>

struct PointerToInt
{
    PointerToInt() = default;
    PointerToInt(const int num) :
        m_ptr(new int(num))
    {
    }

    // Copy constructor
    PointerToInt(const PointerToInt& o) :
        m_ptr((o.m_ptr != nullptr) ? (new int(*o.m_ptr)) : (nullptr))
    {
    }

    // Copy assignment operator
    PointerToInt& operator=(const PointerToInt& o)
    {
        if (this != &o)
        {
            PointerToInt copy(o);
            std::swap(m_ptr, copy.m_ptr);
        }

        return *this;
    }

    ~PointerToInt()
    {
        delete m_ptr;
    }

    int* m_ptr = nullptr;
};

int main()
{
    // Default Pointer
    {
        PointerToInt p;
        PointerToInt p1(p);
        std::cout << (p.m_ptr == nullptr) << " " << (p1.m_ptr == nullptr) << std::endl;
    }
    {
        PointerToInt p;
        PointerToInt p1(5);
        p1 = p;
        std::cout << (p1.m_ptr == nullptr) << std::endl;
    }
}
```

>[!Note]
>Идиома Copy and Swap базируется на принципе RAII. И помогает не просто улучшать читаемость кода, но и писать более безопасный код с точки зрения работы с ресурсами.
