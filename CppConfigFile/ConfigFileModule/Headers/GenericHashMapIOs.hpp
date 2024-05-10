#pragma once

/* Code Description
* FILE: GenericHashMapIOs.h
* DESCRIPTON: input output functions for generic hash map
* NOTE:
*
* CREATE: 2024-04-07
* LAST UPDATE:
*/

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<assert.h>
#include<streambuf>

#include"GenericHashMapHelpers.hpp"
#include"GenericHashMap.hpp"

#ifndef GENERICHASHMAPIOS_H
#define GENERICHASHMAPIOS_H

// class for text IO of generic hash map
class GenHashMapIOTxt {
public:
	std::string type_name_dl = " ";
	std::string name_val_dl = "=";
	std::string entry_stop_str = ";";
	std::vector<std::string> default_message_enclousre = { "/*", "*/" };
	std::unordered_map<std::string, std::string> ignore_left_to_right_map = { {"//", "\n"}, {"/*", "*/"} };
	std::unordered_map<std::string, std::string> include_left_to_right_map = { {"\"", "\""} };
	std::unordered_set<char> rm_chars = { ' ', '\n', '\t' };

	// save generic hash map to file
	errflag_t save_to_file(
		const GenHashMap& gen_hashmap,
		const std::string& dst_file_path,
		std::ios_base::openmode dst_file_openmode = std::ios_base::out,
		const std::string& head_message = ""
	) {
		return save_genhashmap_to_txt(
			gen_hashmap,
			dst_file_path,
			dst_file_openmode,
			this->type_name_dl,
			//this->name_val_dl,
			" " + this->name_val_dl + " ",
			this->entry_stop_str,
			this->default_message_enclousre,
			head_message
		);
	}

	// load generic hash map 
	errflag_t update_from_file(
		GenHashMap& gen_hashmap,
		const std::string& src_file_path,
		std::ios_base::openmode src_file_openmode = std::ios_base::in
	) {
		return update_genhashmap_from_txt(
			gen_hashmap,
			src_file_path,
			src_file_openmode,
			this->type_name_dl,
			this->name_val_dl,
			this->entry_stop_str,
			this->ignore_left_to_right_map,
			this->include_left_to_right_map,
			this->rm_chars
		);
	}
};

#endif

