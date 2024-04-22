#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject()
{
	myClasses.push_back("GameObject");
	objID = nextID++;
}

GameObject::GameObject(int l)
{
	myClasses.push_back("GameObject");
	layer = l;
	objID = nextID++;
}

bool GameObject::isInClass(std::string classname) const
{
	for (const auto& name: myClasses)
	{
		if (name == classname)
			return true;
	}
	return false;
}
