// SharedPointer.cpp : Defines the entry point for the console application.
//

#include "ParentChild.h"

void Child::clearParent() 
{
    if (auto pParent = m_pParent.lock()) {
        pParent->removeChild(m_id);
    }
    setParent(std::weak_ptr<Parent>());
}

std::shared_ptr<Child>  Parent::removeChild(ID id) {
	Child child(id);
	auto iter = std::find_if(m_children.begin(), m_children.end(),
		[&child](const auto& ch) ->bool { return child == *ch; });
	if (iter != m_children.end()) {
		auto rChild = *iter;
		m_children.erase(iter);
		rChild->clearParent();
		return rChild;
	}
	else {
        return std::shared_ptr<Child>(nullptr);
	}
}

auto Parent::findChild(ID id) {
	Child child(id);
	auto iter = std::find_if(m_children.begin(), m_children.end(),
		[&child](const auto& ch) ->bool { return child == *ch; });
	if (iter != m_children.end()) {
		return *iter;
	}
	else {
		return std::shared_ptr<Child>(nullptr);
	}
}

int main()
{
	std::shared_ptr<Parent> pParent = std::make_shared<Parent>();
    std::weak_ptr<Parent> wParent = pParent;
	std::shared_ptr<Child> pChild1 = std::make_shared<Child>(e1);
    Parent::addChild(wParent, pChild1);
	std::cout << "pChild1: " << pChild1;
	std::cout << "pParent after creating pChild1: " << pParent;
	std::shared_ptr<Child> pChild2 = std::make_shared<Child>(e2);
	std::cout << "pChild2 before addChild call: " << pChild2;
    Parent::addChild(wParent, pChild2);
	std::cout << "pParent after addChild call: " << pParent;
	std::shared_ptr<Child> pChild3 = std::make_shared<Child>(e3);
    Parent::addChild(wParent, pChild3);
	std::cout << "pParent after three children added:\n" << pParent;
	std::shared_ptr<Child> pChild4 = pParent->findChild(e2);
	std::cout << "pChild4: " << pChild4;
	std::cout << "pParent after findChild call: " << pParent;
	std::shared_ptr<Child> pChild5 = pParent->removeChild(e1);
	std::cout << "pChild5: " << pChild5;
	std::cout << "pParent after removeChild(e1): " << pParent;
    std::shared_ptr<Child> pChild6 = pParent->removeChild(pChild4);
    std::cout << "pChild6: " << pChild6;
    std::cout << "pParent after removeChild(pChild4): " << pParent;
    std::shared_ptr<Child> pChild7 = pParent->removeChild(e1);
    std::cout << "pChild7: " << pChild7;
    std::shared_ptr<Child> pChild8 = pParent->removeChild(pChild4);
    std::cout << "pChild8: " << pChild8;

    pParent.reset();
	std::cout << "pParent after reset: " << pParent;

	std::cout << "\nPress any non-whitespace character key and then the Enter key to terminate:" << std::endl;
	char c;
	std::cin >> c;
}

