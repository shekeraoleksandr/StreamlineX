#pragma once
#include <iostream>
#include "primitive.h"
#include "array.h"
#include "object.h"

namespace ObjectModel
{
	class Object : public Root
	{
	public:
		int16_t primitiveCount = 0, arrayCount = 0, stringCount = 0, objectCount = 0;
		std::vector<Primitive> primitives;
		std::vector<Array> arrays;
		std::vector<Array> strings;
		std::vector<Object> objects;
	public:
		Object(std::string name = "default");
		void addEntity(Root*);
		void pack(std::vector<uint8_t>&, int16_t&);
		static Object unpack(std::vector<uint8_t>&, int16_t&);
		inline int16_t getPrimitiveCount() { return primitiveCount; }
		inline int16_t getArrayCount() { return arrayCount; }
		inline int16_t getStringCount() { return stringCount; }
		inline int16_t getObjectCount() { return objectCount; }


		Primitive findPrimitiveByName(std::string name)
		{
			for (Primitive p : primitives)
			{
				if (p.getName() == name)
				{
					return p;
				}
			}
		}

        Array findStringByName(std::string name)
        {
            for (Array str : strings)
            {
                if (str.getName() == name)
                {
                    return  str;
                }
            }
        }

        Object findObjectByName(std::string name)
        {
            for (Object o : objects)
            {
                if (o.getName() == name)
                {
                    return o;
                }
            }
        }

        Array findArrayByName(std::string name)
        {
            for (Array arr : arrays)
            {
                if (arr.getName() == name)
                {
                    return arr;
                }
            }
        }
	};

}