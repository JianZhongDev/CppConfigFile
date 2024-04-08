#pragma once

/* Code Description
* FILE: GenericHashMapHelpers.h
* DESCRIPTON: helper functions for generic hashmap.
* NOTE:
*
* CREATE: 2024-04-06
* LAST UPDATE:
*/

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<assert.h>
#include<streambuf>

#include "GenericEntry.h"
#include "StringHelpers.h"

typedef int errflag_t;


// save generic hash map entries to configuration text file
errflag_t save_genhashmap_to_txt(
	const std::unordered_map<std::string, GenericEntry*>& gen_hashmap,
	const std::string& dst_file_path,
	std::ios_base::openmode dst_file_openmode = std::ios_base::out,
	const std::string& type_name_dl = " ",
	const std::string& name_val_dl = "=",
	const std::string& entry_stop_str = ";",
	const std::vector<std::string>& default_message_enclousre = {"/*", "*/"},
	const std::string& head_message = ""
) {
	errflag_t err_flag = 0;
	std::ofstream dst_file(dst_file_path, dst_file_openmode);
	if (dst_file.is_open()) {
		// save head message if given
		if (head_message.size() > 0) {
			dst_file << default_message_enclousre[0] + head_message + default_message_enclousre[1] + "\n";
		}
		// iterate though hash map and save all entries
		for (const auto& key_val_pair : gen_hashmap) {
			std::string cur_name_str = key_val_pair.first;
			std::string cur_type_str;
			std::string cur_val_str;
			key_val_pair.second->get_typename(&cur_type_str);
			key_val_pair.second->write_val_string(&cur_val_str);
			// convert type name value to entry string
			std::string cur_entry_str = helper_pack_type_name_val_string(
				cur_type_str,
				cur_name_str,
				cur_val_str,
				type_name_dl,
				name_val_dl
			);
			dst_file << cur_entry_str + entry_stop_str + "\n";
		}
		dst_file.close(); // close file
		err_flag = 1;
	}
	else {
		std::cout << "ERR:\t Unable to open file. File path = " + dst_file_path << std::endl;
		err_flag = -1;
	}
	return err_flag;
}


// update generic hash map entries according to configuration text file
errflag_t update_genhashmap_from_txt(
	std::unordered_map<std::string, GenericEntry*>& gen_hashmap,
	const std::string& src_file_path,
	std::ios_base::openmode src_file_openmode = std::ios_base::in,
	const std::string& type_name_dl = " ",
	const std::string& name_val_dl = "=",
	const std::string& entry_stop_str = ";",
	const std::unordered_map<std::string, std::string>& ignore_left_to_right_map = {{"//", "\n"}, {"/*", "*/"}},
	const std::unordered_map<std::string, std::string>& include_left_to_right_map = {{"\"", "\""}},
	const std::unordered_set<char>& rm_chars = {' ', '\n', '\t'}
) {
	errflag_t err_flag = 0;
	std::ifstream src_file(src_file_path, src_file_openmode);
	if (src_file.is_open()) {
		std::string src_string(
			(std::istreambuf_iterator<char>(src_file)),
			std::istreambuf_iterator<char>()
			);
		std::vector<std::string> entry_strings = helper_extract_entrystr(
			src_string,
			entry_stop_str,
			ignore_left_to_right_map,
			include_left_to_right_map
		);
		for (auto& cur_entry_str : entry_strings) {
			std::string tmp_str;
			std::size_t tmp_str_len = 0;
			//clean up entry string
			tmp_str = helper_bothside_clean_chars(
				cur_entry_str,
				rm_chars
			);
			// split entry string
			std::string type_string;
			std::string name_string;
			std::string value_string;
			helper_split_entrystr_into_type_name_val(
				tmp_str,
				type_name_dl,
				name_val_dl,
				&type_string,
				&name_string,
				&value_string
			);
			// clean up name string
			name_string = helper_bothside_clean_chars(
				name_string,
				rm_chars
			);
			// update entry if name exists
			if (gen_hashmap.find(name_string) != gen_hashmap.end()) {
				type_string = helper_bothside_clean_chars(
					type_string,
					rm_chars
				);
				// update entry if type match
				std::string hp_typename;
				gen_hashmap[name_string]->get_typename(&hp_typename);
				if (type_string == hp_typename) {
					value_string = helper_bothside_clean_chars(
						value_string,
						rm_chars
					);
					gen_hashmap[name_string]->read_val_string(value_string);
				}
				else {
					std::cout << "ERR:\tType mismatch! " + type_string + " <--> " + hp_typename + "\n";
				}
			}
			else {
				std::cout << "ERR:\tName not found! " + name_string + "\n";
			}
		}
		err_flag = 1;
	}
	else {
		std::cout << "ERR:\t Unable to open file. File path = " + src_file_path << std::endl;
		err_flag = -1;
	}

	return err_flag;
}


// delete all the elements in a generic hash map
errflag_t clear_genhashmap(
	std::unordered_map<std::string, GenericEntry*>& gen_hashmap
) {
	// iterate through the hash map to release all the entries
	for (auto key_val_pair : gen_hashmap) {
		delete key_val_pair.second;
	}
	gen_hashmap.clear();

	return 1;
}






