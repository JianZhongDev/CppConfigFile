/* Code Description
* FILE: DemoMain.cpp
* DESCRIPTON: demo main function for generic hashmap
* NOTE:
*
* CREATE: 2024-04-06
* LAST UPDATE:
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

#define MAIN // enable or disable main method in this file

#ifdef MAIN

#include "../Headers/GenericEntry.h"
#include "../Headers/GenericHashMap.h"
#include "../Headers/GenericHashMapIOs.h"

void main() {
	GenHashMap test_genhashmap;
	GenHashMapIOTxt test_io_txt;

	// initialize generic hash map
	test_genhashmap["int01"] = new IntEntry(-1);
	test_genhashmap["int02"] = new IntEntry(-2);
	test_genhashmap["uint01"] = new UintEntry(1);
	test_genhashmap["uint02"] = new UintEntry(2);
	test_genhashmap["float01"] = new FloatEntry(0.1);
	test_genhashmap["float02"] = new FloatEntry(0.2);
	test_genhashmap["ulonglong01"] = new ULongLongEntry(1000);
	test_genhashmap["ulonglong02"] = new ULongLongEntry(2000);
	test_genhashmap["string01"] = new StringEntry("Hello world!");
	test_genhashmap["string02"] = new StringEntry("Welcome!");
	test_genhashmap["vector_float01"] = new VectorFloatEntry({ 0.1, 0.2, 0.3, 0.4, 0.5 });
	test_genhashmap["vector_float02"] = new VectorFloatEntry({ 0.6, 0.7, 0.8, 0.9, 1.0, 1.1});

	std::cout << "--- genhashmap values START ---" << std::endl;
	for (const auto& key_val_pair : test_genhashmap) {
		std::string cur_name_str = key_val_pair.first;
		std::string cur_type_str;
		std::string cur_val_str;
		key_val_pair.second->get_typename(&cur_type_str);
		key_val_pair.second->write_val_string(&cur_val_str);
		std::cout << cur_type_str << " " << cur_name_str << " = " << cur_val_str << std::endl;
	}
	std::cout << "--- genhashmap values END ---" << std::endl;
	std::cout << std::endl;
	
	// save to txt configuration file
	test_io_txt.save_to_file(
		test_genhashmap,
		"test.txt",
		std::ios_base::out,
		"This is a test configuration file."
	);


	// try to change some of the values
	((FloatEntry*)test_genhashmap["float01"])->set(-0.1);
	((ULongLongEntry*)test_genhashmap["ulonglong02"])->set(1500);
	((StringEntry*)test_genhashmap["string02"])->set(std::string("some random string"));

	std::cout << "--- genhashmap values START ---" << std::endl;
	for (const auto& key_val_pair : test_genhashmap) {
		std::string cur_name_str = key_val_pair.first;
		std::string cur_type_str;
		std::string cur_val_str;
		key_val_pair.second->get_typename(&cur_type_str);
		key_val_pair.second->write_val_string(&cur_val_str);
		std::cout << cur_type_str << " " << cur_name_str << " = " << cur_val_str << std::endl;
	}
	std::cout << "--- genhashmap values END ---" << std::endl;
	std::cout << std::endl;

	// try to get some of the values
	std::vector<float> tmp_float_vec;
	((VectorFloatEntry*)test_genhashmap["vector_float01"])->get(&tmp_float_vec);
	std::string tmp_string;
	((StringEntry*)test_genhashmap["string02"])->get(&tmp_string);
	unsigned long long tmp_ulonglong;
	((ULongLongEntry*)test_genhashmap["ulonglong01"])->get(&tmp_ulonglong);


	std::cout << "--- get values START ---" << std::endl;
	std::cout << "tmp_float_vec = {";
	for (const auto& val : tmp_float_vec) {
		std::cout << val << ", ";
	}
	std::cout << "}" << std::endl;
	std::cout << "tmp_string = " << tmp_string << std::endl;
	std::cout << "tmp_ulonglong = " << tmp_ulonglong << std::endl;
	std::cout << "--- get values END ---" << std::endl;
	std::cout << std::endl;

	// update values according to txt configuration file
	test_io_txt.update_from_file(
		test_genhashmap,
		"test.txt",
		std::ios_base::in
	);

	std::cout << "--- genhashmap values START ---" << std::endl;
	for (const auto& key_val_pair : test_genhashmap) {
		std::string cur_name_str = key_val_pair.first;
		std::string cur_type_str;
		std::string cur_val_str;
		key_val_pair.second->get_typename(&cur_type_str);
		key_val_pair.second->write_val_string(&cur_val_str);
		std::cout << cur_type_str << " " << cur_name_str << " = " << cur_val_str << std::endl;
	}
	std::cout << "--- genhashmap values END ---" << std::endl;
	std::cout << std::endl;

}

#endif
