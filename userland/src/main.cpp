#include <serialization.h>
#include <cassert>

using namespace ObjectModel;

namespace TestFrame
{
	void testPack()
	{
		std::string foo = "name";
		std::unique_ptr<Array> p = Array::createString("name", Type::I8, foo);

		Object Test("Foo");
		Test.addEntity(p.get());

		Core::Util::retriveNsave(&Test);
	}
}

int main(int argc, char** argv)
{
	assert(Core::Util::isLittleEndian());

	TestFrame::testPack();

	(void)argc;
	(void)argv;
	return 0;
}