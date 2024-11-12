#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10.3/Lab10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest103
{
	TEST_CLASS(UnitTest103)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::vector<Resident> residents = {
				{"Ivanov", "I.I.", 1, true},
				{"Petrov", "P.P.", 6, false}
			};

			// Redirect cout to a string stream
			std::stringstream buffer;
			std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

			// Call the function
			display_all_data(residents);

			// Restore cout
			std::cout.rdbuf(oldCout);

			// Expected output
			std::string expectedOutput =
				"\nСписок всіх записів:\n"
				"Запис 1:\n"
				"  Прізвище: Ivanov\n"
				"  Ініціали: I.I.\n"
				"  Номер кімнати: 1\n"
				"  Тип кімнати: Одномісна\n"
				"Запис 2:\n"
				"  Прізвище: Petrov\n"
				"  Ініціали: P.P.\n"
				"  Номер кімнати: 6\n"
				"  Тип кімнати: Двомісна\n\n";

			// Compare the output to the expected output
			Assert::AreEqual(expectedOutput, buffer.str());
		}
	};
}