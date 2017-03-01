// UniquePointer.cpp : Defines the entry point for the console application.
//

#include "ParentChild.h"

std::unique_ptr<Child>  Parent::removeChild(ID id) {
    std::unique_ptr<Child> pChild = std::make_unique<Child>(id);
	auto iter = std::find_if(m_children.begin(), m_children.end(),
		[&pChild](const auto& ch) ->bool { return *pChild == *ch; });
	if (iter != m_children.end()) {
		m_children.erase(iter);
		return pChild;
	}
	else {
		return std::unique_ptr<Child>(nullptr);
	}
}

Child* Parent::findChild(ID id) {
    std::unique_ptr<Child> pChild = std::make_unique<Child>(id);
    auto iter = std::find_if(m_children.begin(), m_children.end(),
        [&pChild](const auto& ch) ->bool { return *pChild == *ch; });
    if (iter != m_children.end()) {
        return iter->get();
    }
    else {
        return nullptr;
    }
}

int main()
{
	std::shared_ptr<Parent> pParent = std::make_shared<Parent>();
    std::unique_ptr<Child> pChild1 = std::make_unique<Child>(e1);
	std::cout << "pChild1 after create: " << pChild1.get();
    std::cout << "pParent after pChild1 created: " << pParent;
    Parent::addChild(pParent, pChild1);
	std::cout << "pParent after pChild1 added: " << pParent;
    std::cout << "pChild1 after addChild: " << pChild1.get();
    std::unique_ptr<Child> pChild2 = std::make_unique<Child>(e2);
    std::unique_ptr<Child> pChild3 = std::make_unique<Child>(e3);
    Parent::addChild(pParent, pChild3);
    std::cout << "pParent after pChild3 added: " << pParent;
    Child* pChild4 = pParent->findChild(e1);
    std::cout << "pChild4: " << pChild4;
    std::cout << "pParent after findChild call: " << pParent;
    auto pChild5 = pParent->removeChild(e3);
    std::cout << "pChild5: " << pChild5.get();
    std::cout << "pParent after removeChild(e3): " << pParent;
    std::unique_ptr<Child> pChild6 = pParent->removeChild(pChild4);
    std::cout << "pChild6: " << pChild6.get();
    std::cout << "pParent after removeChild(pChild6): " << pParent;
    auto pChild7 = pParent->removeChild(e1);
    std::cout << "pChild7: " << pChild7.get();
    auto pChild8 = pParent->removeChild(pChild4);
    std::cout << "pChild8: " << pChild8.get();

	std::cout << "Press any non-whitespace character key and then the Enter key to terminate:" << std::endl;
	char c;
	std::cin >> c;
}

