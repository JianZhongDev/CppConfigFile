/* Code Description
* FILE: Test.cpp
* DESCRIPTON: include unit test codes
* NOTE:
*
* CREATE: 2024-04-06
* LAST UPDATE:
*/

#include<iostream>
#include<string>
#include <vector>
#include<unordered_map>

#include "../Headers/StringHelpers.h"
#include"../Headers/GenericEntry.h"
#include "../Headers/GenericHashMapHelpers.h"


#define MAIN // enable or disable main method in this file


// Quick test for string extraction function
static void test_string_extract_func() {
	std::string test_string = "  type01 name01 = \"val01 //  \n \"; /*comment 00 */ type02 name02 = \"val02 /* */ \"; //comment 01 \n type03 name03 = val03;";

	std::unordered_map<std::string, std::string> ignore_left_to_right_map;
	ignore_left_to_right_map["//"] = "\n";
	ignore_left_to_right_map["/*"] = "*/";

	std::unordered_map<std::string, std::string> include_left_to_right_map;
	include_left_to_right_map["\""] = "\"";

	std::vector<std::string> result = helper_extract_entrystr(
		test_string,
		";",
		ignore_left_to_right_map,
		include_left_to_right_map
	);

	for (const auto& val : result) {
		std::cout << val << std::endl;
	}
}


static void test_generic_entries() {
	std::unordered_map<std::string, GenericEntry*> test_map; // It is important to use GenericEntry* instead of GenericEntry otherwise the val would be cast into the base class

	IntEntry test_int01(-1);
	IntEntry test_int02(-2);
	UintEntry test_uint01(1);
	UintEntry test_uint02(2);
	FloatEntry test_float01(1.0);
	FloatEntry test_float02(2.0);
	StringEntry test_str01("hello world");
	StringEntry test_str02("this is test string");
	VectorFloatEntry test_vecfloat01(std::vector<float>{0.1, 0.2, 0.3, 0.4, 0.5});
	VectorFloatEntry test_vecfloat02(std::vector<float>{0.6, 0.7, 0.8, 0.9, 1.0});

	test_map["test_int01"] = &test_int01;
	test_map["test_int02"] = &test_int02;
	test_map["test_uint01"] = &test_uint01;
	test_map["test_uint02"] = &test_uint02;
	test_map["test_float01"] = &test_float01;
	test_map["test_float02"] = &test_float02;
	test_map["test_str01"] = &test_str01;
	test_map["test_str02"] = &test_str02;
	test_map["test_vecfloat01"] = &test_vecfloat01;
	test_map["test_vecfloat02"] = &test_vecfloat02;

	test_map["test_uint02"]->read_val_string("4");
	test_map["test_str02"]->read_val_string("\"some random text\"");
	test_map["test_vecfloat02"]->read_val_string("{  -0.1,-0.2, -0.3, -0.4, -0.5}");


	save_genhashmap_to_txt(
		test_map,
		"./test.txt",
		std::ios_base::out,
		" ",
		" = ",
		";",
		{"/*", "*/"},
		"This is a test config file.\n Hello.\n"
	);

	test_map["test_uint01"]->read_val_string("3");
	test_map["test_str01"]->read_val_string("\"alala\"");
	test_map["test_vecfloat01"]->read_val_string("{  1.1,1.2, 1.3, 1.4, 1.5,  }");

	update_genhashmap_from_txt(
		test_map,
		"./test.txt",
		std::ios_base::in,
		" ",
		"=",
		";"
	);

	for (const auto itr : test_map) {
		std::string tmp_typename;
		std::string tmp_valstr;
		itr.second->get_typename(&tmp_typename);
		itr.second->write_val_string(&tmp_valstr);
		std::cout << tmp_typename << " " << itr.first << " = " << tmp_valstr << std::endl;
	}

	((VectorFloatEntry*)test_map["test_vecfloat01"])->set(std::vector<float>{2.1, 2.2, 2.3, 2.4, 2.5, 2.6, });

	std::vector<float> test_vector_float;
	((VectorFloatEntry*)test_map["test_vecfloat01"])->get(&test_vector_float);

	std::cout << "test_vector_float = {";
	for (auto itr : test_vector_float) {
		std::cout << itr << ", ";
	}
	std::cout << "}" << std::endl;

}


#ifdef MAIN
// main method for test
void main() {
	test_string_extract_func();

	std::cout << "--- --- --- --- ---" << std::endl;

	test_generic_entries();
}
#endif