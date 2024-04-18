/* Code Description
* FILE: BlogDemoMain.cpp
* DESCRIPTON: demo main function for generic hashmap for blog post
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
	test_genhashmap["string_val"] = new StringEntry("Welcome to Vision Tech Insights!");
	test_genhashmap["vector_float_val"] = new VectorFloatEntry({ 0.1, 0.2, 0.3, 0.4, 0.5 });

	std::cout << "====== Initialize gen hashmap ======" << std::endl << std::endl;

	// print all the values in the generic hash map
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


	// save generic hash map into a text file
	std::cout << "====== Save gen hashmap to text file ======" << std::endl << std::endl;

	// save to txt configuration file
	test_io_txt.save_to_file(
		test_genhashmap,
		"test_config_file.txt",
		std::ios_base::out,
		"This is the test configuration file for Vision Tech Insights blog."
	);


	// save generic hash map into a text file
	std::cout << "====== Set values in gen hashmap ======" << std::endl << std::endl;
	// try to change some of the values
	((StringEntry*)test_genhashmap["string_val"])->set(std::string("Hello world!"));
	((VectorFloatEntry*)test_genhashmap["vector_float_val"])->set(std::vector<float>{-0.1, -0.2, -0.3});

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

	// try to get value from genhashmap
	std::cout << "====== Get values from gen hashmap ======" << std::endl << std::endl;
	std::string tmp_string;
	((StringEntry*)test_genhashmap["string_val"])->get(&tmp_string);
	std::vector<float> tmp_float_vec;
	((VectorFloatEntry*)test_genhashmap["vector_float_val"])->get(&tmp_float_vec);

	std::cout << "--- get values START ---" << std::endl;
	std::cout << "tmp_float_vec = {";
	for (int i_val = 0; i_val < tmp_float_vec.size(); i_val++) {
		std::cout << tmp_float_vec[i_val];
		if (i_val < tmp_float_vec.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "}" << std::endl;
	std::cout << "tmp_string = " << tmp_string << std::endl;
	std::cout << "--- get values END ---" << std::endl;
	std::cout << std::endl;


	// load generic hash map from the text file
	std::cout << "====== Load gen hashmap from text file ======" << std::endl << std::endl;

	// update values according to txt configuration file
	test_io_txt.update_from_file(
		test_genhashmap,
		"test_config_file.txt",
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
