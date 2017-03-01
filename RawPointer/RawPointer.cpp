// RawPointer.cpp : Defines the entry point for the console application.
//

#include "ParentChild.h"

Child::Child(Parent* parent, ID id) : m_parent(parent), m_id(id) {
	if (parent != nullptr) {
		parent->addChild(this);
	}
}

Child::~Child() noexcept {
	if (m_parent != nullptr) {
		m_parent->removeChild(this);
	}
}

Child* addChild3(Parent* parent)
{
	Child* pChild = new Child(parent, e3);
	return pChild;
}

int main()
{
	Parent* pParent = new Parent();
	Child* pChild1 = new Child(pParent, e1);
	std::cout << "child1: " << pChild1;
	Child* pChild2 = new Child(e2);
	std::cout << "child2 before addChild call: " << pChild2;
	pParent->addChild(pChild2);
	std::cout << "child2 after addChild call: " << pChild2;
	Child* pChild3 = addChild3(pParent);
	std::cout << "child3: " << pChild3;
	std::cout << "Parent after three children added:\n" << *pParent << '\n';
	Child* pChild4 = pParent->findChild(e2);  // return pointer to child2
	std::cout << "Parent after findChild call:\n" << *pParent << '\n';
	std::cout << "child4: " << pChild4;
	Child* pChild5 = pParent->removeChild(e1);
	std::cout << "child5: " << pChild5;
	std::cout << "Parent after removeChild(e1) call:\n" << *pParent << '\n';
    Child* pChild6 = pParent->removeChild(pChild4);
    std::cout << "child6: " << pChild6;
    std::cout << "Parent after removeChild(pChild4) call:\n" << *pParent << '\n';
    Child* pChild7 = pParent->removeChild(e1);
    std::cout << "pChild7: " << pChild7;
    Child* pChild8 = pParent->removeChild(pChild4);
    std::cout << "pChild8: " << pChild8;

	delete pParent;
    delete pChild5;
    delete pChild6;

	std::cout << "Press any non-whitespace character key and then the Enter key to terminate:" << std::endl;
	char c;
	std::cin >> c;
}
