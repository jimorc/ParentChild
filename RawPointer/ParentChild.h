#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

enum ID {
	e1 = 1,
	e2,
	e3
};

class Parent;

class Child {
public:
    explicit Child(ID id) : Child(nullptr, id) {}
	Child(Parent* parent, ID id);
	~Child() noexcept;
	const ID getID() const noexcept { return m_id; }
	friend std::ostream& operator<<(std::ostream& os, const Child* pChild);
    friend Parent;
private:
    void setParent(Parent* pParent) noexcept { m_parent = pParent; }
    Parent* m_parent;
	ID m_id;
};

bool operator==(const Child& lhs, const Child& rhs) noexcept {
	return lhs.getID() == rhs.getID();
}

std::ostream& operator<<(std::ostream& os, const Child* pChild) {
	if (pChild) {
		os << "parent = " << pChild->m_parent << ", id = " << pChild->m_id << '\n';
	}
	else {
		os << "nullptr\n";
	}
	return os;
}

class Parent {
public:
	Parent() {}
	~Parent() noexcept {
        while (m_children.size() > 0) {
            auto pChild = removeChild(m_children[0]->getID());
            delete pChild;
        }
	}
	void addChild(Child* child) {
		child->setParent(this);
		m_children.push_back(child);
	}
	Child* removeChild(ID id) {
		Child child(nullptr, id);
		auto iter = std::find_if(m_children.begin(), m_children.end(),
			[&child](const auto& ch) ->bool { return child == *ch; });
		if (iter != m_children.end()) {
			Child* rChild = *iter;
			m_children.erase(iter);
			rChild->setParent(nullptr);
			return rChild;
		}
		else {
			return nullptr;
		}
	}
	Child* removeChild(Child* pChild) {
        return removeChild(pChild->getID());
	}
	Child* findChild(ID id) {
		Child child(nullptr, id);
		auto iter = std::find_if(m_children.begin(), m_children.end(),
			[&child](const auto& ch) ->bool { return child == *ch; });
		if (iter != m_children.end()) {
			return *iter;
		}
		else {
			return nullptr;
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const Parent& parent);
private:
	std::vector<Child*> m_children;
};

std::ostream& operator<<(std::ostream& os, const Parent& parent) {
	os << "Parent =" << &parent << ":\n";
	for (const auto& pChild : parent.m_children) {
		os << "Child: " << pChild;
	}
	return os;
}