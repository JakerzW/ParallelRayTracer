#ifndef _OBJECTLIST_H
#define _OBJECTLIST_H

#include "Object.h"

#include <glm.hpp>

#include <memory>
#include <vector>

//Any object within the world must inherit from this
//All objects will require certain functions that are assigned in this class

class ObjectList : public Object
{
	private:
	std::vector<std::shared_ptr<Object>> list;

	public:
		ObjectList();
		ObjectList(std::vector<std::shared_ptr<Object>> l);
		virtual bool DidHit(std::shared_ptr<Ray> ray, float tMin, float tMax, HitRecord &hitRec) const;
		std::vector<std::shared_ptr<Object>> GetList();

};


#endif // !_OBJECT_H
