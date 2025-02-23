#ifndef USER_ID_H
#define USER_ID_H

#include <iostream>

class UserId
{
public:
    static UserId& instance()
    {
        static UserId id;
        return id;
    }

    ~UserId()
    {
        std::cout << "Destroy UserId with ID = " << m_id << std::endl;
    }

    int Get() const
    {
        return m_id;
    }
private:
    UserId();
private:
    int m_id = 0;
};

#endif // !USER_ID_H
