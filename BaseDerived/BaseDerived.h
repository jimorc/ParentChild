#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <typeinfo>

enum ID {
    e1 = 1,
    e2, 
    e3,
    e4,
    e5
};

class Base {
public:
    explicit Base(ID id) : m_id(id) {}
    virtual ~Base() {}
    static void addChild(std::weak_ptr<Base> parent, std::shared_ptr<Base> child);
    std::shared_ptr<Base>  Base::removeChild(ID id);
    std::shared_ptr<Base> removeChild(std::shared_ptr<Base>& pChild)
    {
        return removeChild(pChild->getID());
    }
    std::shared_ptr<Base> findChild(ID id);
    ID getID() { return m_id; }
    friend bool operator==(const Base& lhs, const Base& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Base& base);
private:
    void setParent(std::weak_ptr<Base>& wParent) { m_pParent = wParent; }
    void clearParent();

    std::weak_ptr<Base> m_pParent;
    std::vector < std::shared_ptr<Base>> m_children;
    ID m_id;
};

bool operator==(const Base& lhs, const Base& rhs)
{
    return lhs.m_id == rhs.m_id;
}

std::ostream& operator<<(std::ostream& os, const Base& base)
{
    os << typeid(base).name() << ": id = " << base.m_id << "\n";
    for (auto& pChild : base.m_children) {
        auto wB = pChild->m_pParent;
        while (wB.lock()) {
            os << "\t";
            std::shared_ptr<Base> pB = wB.lock();
            wB = pB->m_pParent;
        }
        os << *pChild;
    }
    return os;
}

class A : public Base
{
public:
    explicit A(ID id) : Base(id) {}
};

class B : public Base 
{
public:
    explicit B(ID id) : Base(id) {}
};

class C : public Base
{
public:
    explicit C(ID id) : Base(id) {}
};
