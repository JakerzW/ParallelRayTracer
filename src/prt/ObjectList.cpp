#include "Object.h"
#include "ObjectList.h"

ObjectList::ObjectList()
{
}

ObjectList::ObjectList(std::vector<std::shared_ptr<Object>> l)
{
	list = l;
}

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

std::vector<std::shared_ptr<Object>> ObjectList::GetList()
{
	return list;
}
