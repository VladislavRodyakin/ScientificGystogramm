#include "gtest/gtest.h"
#include "../ScientificGystogrammReal/Gyst.hpp"
#include "../ScientificGystogrammReal/Parser.hpp"

TEST(TestOfParser, EmptyStream) {
	std::stringstream iss;
	iss << "";
	std::vector<int> test_vector = Parser::parse(iss);
	EXPECT_EQ(0, test_vector.size());
}

TEST(TestOfParser, OneElementStream) {
	std::stringstream iss;
	iss << "2023";
	std::vector<int> test_vector = Parser::parse(iss);
	EXPECT_EQ(2023, test_vector[0]);
}

TEST(TestOfParser, ManyElementsStream) {
	std::stringstream iss;
	iss << "1 2 3 4 5 6 7 8 9 10";
	std::vector<int> test_vector = Parser::parse(iss);
	EXPECT_EQ(10, test_vector.size());
}

TEST(HistorgamTest, SingleConstructorsTest){
	EXPECT_ANY_THROW(Gyst test(1, 2, 10));
}

TEST(HistogrgamTest, AddData){
	Gyst test(1, 2, 2);
	std::vector<int> data1{ 1 };
	test.add_data(data1);
	EXPECT_EQ(test.at(0), 1);
	std::vector<int> data2{ 1, 1, 3, 3 };
	test.add_data(data2);
	EXPECT_EQ(test.at(0), 3);
	EXPECT_EQ(test.at(1), 2);
}

TEST(HistogrgamTest, AtFunction){
	Gyst test(1, 10, 9);
	std::vector<int> data{ 1, 1, 2, 3, 3, 4, 5 };
	test.add_data(data);
	EXPECT_EQ(test.at(0), 3);
	EXPECT_EQ(test.at(1), 2);
	EXPECT_EQ(test.at(2), 1);
	EXPECT_ANY_THROW(test.at(10));
}

TEST(HistogrgamTest, GetResult){
	Gyst test(1, 2, 2);
	std::vector<int> data{ 1, 1, 3, 3};
	test.add_data(data);
	std::string string{ "0 2\n1 2\n" };
	EXPECT_EQ(test.string_format(), string);
}

TEST(HistogrgamTest, PlusTest){
	Gyst hist1(1, 10, 9);
	std::vector<int> data1{ 1, 1 };
	hist1.add_data(data1);
	Gyst hist2(1, 10, 9);
	std::vector<int> data2{ 3, 3 };
	hist2.add_data(data2);
	Gyst result = hist1 + hist2;
	EXPECT_EQ(result.at(0), 2);
	EXPECT_EQ(result.at(1), 2);
}

TEST(HistorgamTest, MinusTest1){
	Gyst hist1(1, 10, 9);
	std::vector<int> data1{ 1, 1 };
	hist1.add_data(data1);
	Gyst hist2(1, 10, 9);
	std::vector<int> data2{ 3, 3 };
	hist2.add_data(data2);
	Gyst result = hist1 - hist2;
	EXPECT_EQ(result.at(0), 2);
	EXPECT_EQ(result.at(1), 0);
}

TEST(HistogrgamTest, MinusTest2){
	Gyst hist1(1, 10, 9);
	std::vector<int> data1{ 2, 2 };
	hist1.add_data(data1);
	Gyst hist2(1, 10, 9);
	std::vector<int> data2{ 2, 2 };
	hist2.add_data(data2);
	Gyst result = hist1 - hist2;
	EXPECT_EQ(result.at(1), 0);
	EXPECT_EQ(result.at(2), 0);
}

//TEST(HistogrgamTest, BeginEmpty){
//	Gyst test(1, 10, 9);
//	EXPECT_EQ(test.begin(), test.end());
//}
//
//TEST(HistogrgamTest, BeginEndTest){
//	Gyst test(1, 10, 9);
//	std::vector<int> data{ 1, 1 };
//	test.add_data(data);
//	auto test_begin = test.begin();
//	auto test_end = test.end();
//	EXPECT_EQ(test_begin->first, 1);
//	EXPECT_EQ(test_begin->second, 2);
//	EXPECT_EQ(++test_begin, test_end);
//}
