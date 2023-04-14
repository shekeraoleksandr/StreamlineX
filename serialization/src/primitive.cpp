#include "primitive.h"
#include "core.h"
#include <stdint.h>

namespace ObjectModel
{

	Primitive::Primitive()
	{
		size += sizeof type;
	}

	template<typename T>
	static std::unique_ptr<Primitive> Primitive::create(std::string name, Type type, T value)
	{
		std::unique_ptr<Primitive> p(new Primitive());
		p->setName(name);
		p->wrapper = static_cast<uint8_t>(Wrapper::PRIMITIVE);
		p->type = static_cast<uint8_t>(type);
		p->data = new std::vector<uint8_t>(sizeof value);
		p->size += (int32_t)p->data->size();
		int16_t iterator = 0;
		Core::template encode<T>(*p->data, iterator, value);


		return p;
	}

	void Primitive::pack(std::vector<uint8_t>& buffer, int16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);

	}

	std::vector<uint8_t> Primitive::getData()
	{
		return *data;
	}
}