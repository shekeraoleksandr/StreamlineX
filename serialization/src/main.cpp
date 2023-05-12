#include "../include/serialization.h"
#include <cassert>
#include "../include/primitive.h"



using namespace ObjectModel;

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

namespace TestFrame
{
	void testPack()
	{
		int32_t foo = 231;
		std::unique_ptr<Primitive> p = Primitive::create("int32", Type::I32, foo);

        std::string string = "test";
        std::unique_ptr<Array> str = Array::createString("string", Type::I8, string);

        std::vector<uint8_t> v {15, 4, 6, 3, 24};
        std::unique_ptr<Array> arr = Array::createArray("array", Type::I8, v);

		Object Test("Foo");
        Test.addEntity(p.get());
        Test.addEntity(str.get());
        Test.addEntity(arr.get());


		Core::Util::retriveNsave(&Test);
	}

	void testUnpack()
	{
		std::vector<uint8_t> objectFromFile = Core::Util::load("Foo.abc");

		[[maybe_unused]] int16_t it = 0;
		Object toPrintObject = Object::unpack(objectFromFile, it);

		[[maybe_unused]] int16_t it2 = 0;
        int w = Core::decode<int32_t>(toPrintObject.findPrimitiveByName("int32").getData(), it2);
        std::cout << "Primitive: " << w << std::endl;

        it2 = 0;
        std::string str = Core::decode<std::string>(toPrintObject.findStringByName("string").getData(), it2);
        std::string res = str.substr(0, toPrintObject.findStringByName("string").getData().size());
        std::cout << "String: " << res << std::endl;

        it2 = 0;
        std::vector<uint8_t> v(toPrintObject.findArrayByName("array").getData().size());
        Core::decode(toPrintObject.findArrayByName("array").getData(), it2,  v);
        std::cout << "Array: " << v << std::endl;
	}
}

int main(int argc, char** argv)
{
	assert(Core::Util::isLittleEndian(5));

	TestFrame::testPack();
	TestFrame::testUnpack();

	(void)argc;
	(void)argv;
	return 0;
}