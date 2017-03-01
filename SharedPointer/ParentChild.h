#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <assert.h>

enum ID {
	eNoID = 0,
	e1,
	e2,
	e3
};

class Parent;

class Child {
public:
	explicit Child(ID id) : m_pParent(std::weak_ptr<Parent>()), m_id(id) {}
	~Child() noexcept {}
	const ID getID() const noexcept { return m_id; }
	void clearParent();
	friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Child>& pChild);
    friend Parent;
private:
    void setParent(std::weak_ptr<Parent>& pParent) noexcept { m_pParent = pParent; }
    std::weak_ptr<Parent> m_pParent;
	ID m_id;
};

bool operator==(const Child& lhs, const Child& rhs) noexcept {
	return lhs.getID() == rhs.getID();
}

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Child>& pChild) {
	if (pChild) {
		os << "parent = ";
		if (auto pParent = pChild->m_pParent.lock()) {
			os << pParent << ", id = " << pChild->m_id;
			os << ", use_count = " << pChild.use_count() << '\n';
		}
		else {
			os << "nullptr, id = " << pChild->m_id;
			os << ", use_count = " << pChild.use_count() << '\n';
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
	static void addChild(std::weak_ptr<Parent>& wParent, std::shared_ptr<Child>& pChild) {
        if (auto pParent = wParent.lock()) {
            pChild->setParent(wParent);
            pParent->m_children.push_back(pChild);
        }
	}
	std::shared_ptr<Child>  removeChild(ID id);
	std::shared_ptr<Child>  removeChild(std::shared_ptr<Child>& pChild) {
        return removeChild(pChild->getID());
    }
	auto findChild(ID id);

	friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Parent>& pParent);
private:
	std::vector<std::shared_ptr<Child>> m_children;
};

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Parent>& pParent) {
	if (pParent) {
		os << "Parent =" << pParent.get() << ":\n";
		for (const std::shared_ptr<Child>& pChild : pParent->m_children) {
			os << "Child: " << pChild;
		}
	}
	else {
		os << "Parent = nullptr\n";
	}
	return os;
}