#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <assert.h>

enum ID {
	e1 = 1,
	e2,
	e3
};

class Parent;

class Child {
public:
    explicit Child(ID id) : m_id(id) {}
	~Child() noexcept {}
    const ID getID() const noexcept { return m_id; }
	friend std::ostream& operator<<(std::ostream& os, const Child* pChild);
    friend Parent;
private:
    void setParent(std::shared_ptr<Parent>& pParent)
    {
        m_pParent = pParent;
    }

    std::shared_ptr<Parent> m_pParent;
	ID m_id;
};

bool operator==(const Child& lhs, const Child& rhs) noexcept {
	return lhs.getID() == rhs.getID();
}

std::ostream& operator<<(std::ostream& os, const Child* pChild) {
    if (pChild) {
        os << "parent = ";
        if (pChild->m_pParent) {
            os << pChild->m_pParent << ", id = " << pChild->m_id << '\n';
        }
        else {
            os << "nullptr, id = " << pChild->m_id << '\n';
        }
    }
    else {
        os << "nullptr\n";
    }
	return os;
}


class Parent {
public:
	Parent() {}
	~Parent() noexcept {}
	static void addChild(std::shared_ptr<Parent>& pParent, std::unique_ptr<Child>& pChild) {
		pChild->setParent(pParent);
		pParent->m_children.push_back(std::forward<std::unique_ptr<Child>>(pChild));
	}
	std::unique_ptr<Child>  removeChild(ID id);
	std::unique_ptr<Child>  removeChild(Child* pChild) {
        return removeChild(pChild->getID());
    }
	Child* findChild(ID id);
	friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Parent>& pParent);
private:
	std::vector<std::unique_ptr<Child>> m_children;
};

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Parent>& pParent) {
	if (pParent) {
		os << "Parent =" << pParent.get() << ":\n";
		for (const std::unique_ptr<Child>& pChild : pParent->m_children) {
			os << "Child: " << pChild.get();
		}
	}
	else {
		os << "Parent = nullptr\n";
	}
	return os;
}