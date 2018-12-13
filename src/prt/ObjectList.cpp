#include "Object.h"
#include "ObjectList.h"

ObjectList::ObjectList()
{
}

//Initialise the object list
ObjectList::ObjectList(std::vector<std::shared_ptr<Object>> l)
{
	list = l;
}

//Calculate if the ray hits any object and carry out the hit function for that object
bool ObjectList::DidHit(std::shared_ptr<Ray> ray, float tMin, float tMax, HitRecord &hitRec) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	float currentClosest = tMax;
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list.at(i)->DidHit(ray, tMin, currentClosest, tempRec))
		{
			hitAnything = true;
			currentClosest = tempRec.t;
			hitRec = tempRec;
		}
	}
	return hitAnything;
}

//Return the object list
std::vector<std::shared_ptr<Object>> ObjectList::GetList()
{
	return list;
}
