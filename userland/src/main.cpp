#include <serialization.h>
#include <cassert>

using namespace ObjectModel;

namespace TestFrame
{
	void testPack()
	{
		int32_t foo = 24;
		std::unique_ptr<Primitive> p = Primitive::create("int32", Type::I32, foo);

		std::string str = "name";
		std::unique_ptr<Array> s = Array::createString("name", Type::I8, str);

		std::vector<int64_t> v{ 1, 2, 3, 4 };
		std::unique_ptr<Array> arr = Array::createArray("array", Type::I64, v);

		Object Test1("Foo1");
		Object Test2("Foo2");
		Test1.addEntity(p.get());
		Test1.addEntity(s.get());
		Test1.addEntity(arr.get());

		Core::Util::retriveNsave(&Test1);

		Test2.addEntity(&Test1);
		Core::Util::retriveNsave(&Test2);
	}

	void testUnpack()
	{
		std::vector<uint8_t> objectFromFile = Core::Util::load("Foo1.abc");

		int16_t it = 0;
		Object toPrintObject = Object::unpack(objectFromFile, it);

		int16_t it2 = 0;
		int integer = Core::decode<int32_t>(toPrintObject.findPrimitiveByName("int32").getData(), it2);
		
		std::cout << integer << std::endl;


	}
}

int main(int argc, char** argv)
{
	assert(Core::Util::isLittleEndian());
	TestFrame::testPack();
	TestFrame::testUnpack();

	(void)argc;
	(void)argv;
	return 0;
}