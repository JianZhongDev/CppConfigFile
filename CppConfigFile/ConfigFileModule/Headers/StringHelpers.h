#pragma once

/* Code Description
* FILE: StringHelpers.h
* DESCRIPTON: helper functions for string processing.
* NOTE:
*
* CREATE: 2024-04-06
* LAST UPDATE:
*/


#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<assert.h>

#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

// function used to extract strings between string between left and right enclosures
// src_string = "some string" + "start_enclosure" + "result_string" + "end_enclosure" + "some_string"
std::string helper_extract_string_between_enclosure(
	const std::string& src_string,
	const std::string& start_enclosure,
	const std::string& end_enclosure
) {

	std::size_t start_idx = 0;
	std::size_t end_idx = 0;

	std::size_t cur_enclosure_len = 0;
	std::size_t src_str_len = src_string.size();

	// Search for end index of start_enclosure in src_string
	cur_enclosure_len = start_enclosure.size();
	for (start_idx = 0; start_idx < src_str_len - cur_enclosure_len; ++start_idx) {
		if (src_string.substr(start_idx, cur_enclosure_len) == start_enclosure) break;
	}
	start_idx += cur_enclosure_len;

	// Search for start index of end_enclosure in src_string
	cur_enclosure_len = end_enclosure.size();
	for (end_idx = src_str_len > cur_enclosure_len ? src_str_len - cur_enclosure_len : 0; end_idx > 0; --end_idx) {
		if (src_string.substr(end_idx, cur_enclosure_len) == end_enclosure) break;
	}

	// Deal with case where start_enclosure or end_enclourse not found
	if (end_idx < start_idx) {
		return "";
	}

	// return result string
	return src_string.substr(start_idx, end_idx - start_idx);
}


// Remove chars in rm_chars set from the head(left end) and tail(right end) src_string  
std::string helper_clean_tailheadchars_string(const std::string& src_string, const std::unordered_set<char>& rm_chars) {
	std::size_t srcstr_len = src_string.size();
	std::size_t start_idx = 0;
	std::size_t end_idx = 0;

	// Remove chars in the head(left end)
	for (start_idx = 0; start_idx < srcstr_len; ++start_idx) {
		if (rm_chars.find(src_string[start_idx]) == rm_chars.end()) break;
	}

	// Remove chars in the tail(right end)
	for (end_idx = srcstr_len; end_idx > 0; --end_idx) {
		if (rm_chars.find(src_string[end_idx - 1]) == rm_chars.end()) break;
	}

	// Case where all the chars of the string are in rm_chars set  
	if (end_idx < start_idx) return "";

	return src_string.substr(start_idx, end_idx - start_idx);
}


// Split string according to delimiter
// src_string = "substr_0" + "delimiter" + "substr_1" + "delimiter" + ... + "substr_n"
std::vector<std::string> helper_split_string_with_delimiter(const std::string& src_string, const std::string& del_string) {
	std::size_t substr_start_idx = 0;
	std::size_t substr_end_idx = 0;

	std::size_t srcstr_len = src_string.size();
	std::size_t delstr_len = del_string.size();

	// calculate search range
	std::size_t search_len = srcstr_len > delstr_len ? srcstr_len - delstr_len : 0;

	std::vector<std::string> result;

	// traverse through string to find delimiters
	while (substr_end_idx < search_len) {
		if (src_string.substr(substr_end_idx, delstr_len) == del_string) {
			// CASE: delimiter found
			if (substr_end_idx > substr_start_idx) {
				// add subtring to result
				result.push_back(src_string.substr(substr_start_idx, substr_end_idx - substr_start_idx));
			}
			substr_end_idx += delstr_len;
			substr_start_idx = substr_end_idx;
		}
		else {
			// CASE: delimiter not found
			++substr_end_idx;
		}
	}
	// Add the last subtring to result if any
	if (substr_end_idx > substr_start_idx) {
		result.push_back(src_string.substr(substr_start_idx, substr_end_idx - substr_start_idx));
	}
	return result;
}


// split entry string into type name and values
void helper_split_entrystr_into_type_name_val(
	const std::string& src_string,
	const std::string& type_name_dl,
	const std::string& name_val_dl,
	std::string* type_str_p,
	std::string* name_str_p,
	std::string* val_str_p
) {
	// NOTE: assuming string format: {type}{type_name_dl}{name}{name_val_dl}{val}
	// NOTE: assuming string directly start with type
	size_t substr_start_idx = 0;
	size_t substr_end_idx = 0;

	// find type string
	substr_end_idx = src_string.find(type_name_dl, substr_start_idx);
	if (substr_end_idx != std::string::npos) {
		*type_str_p = std::string(src_string.substr(substr_start_idx, substr_end_idx - substr_start_idx));
		substr_start_idx = substr_end_idx + type_name_dl.size();
		substr_end_idx = substr_start_idx;
	}
	else {
		*type_str_p = "";
		substr_end_idx = substr_start_idx;
	}

	// find name string
	substr_end_idx = src_string.find(name_val_dl, substr_start_idx);
	if (substr_end_idx != std::string::npos) {
		*name_str_p = std::string(src_string.substr(substr_start_idx, substr_end_idx - substr_start_idx));
		substr_start_idx = substr_end_idx + type_name_dl.size();
		substr_end_idx = substr_start_idx;
	}
	else {
		*name_str_p = "";
		substr_end_idx = substr_start_idx;
	}

	//copy value string
	substr_end_idx = src_string.size();
	if (substr_end_idx > substr_start_idx) {
		*val_str_p = std::string(src_string.substr(substr_start_idx, substr_end_idx - substr_start_idx));
	}
	else {
		*val_str_p = "";
	}
}


// pack type name value string into one string
std::string helper_pack_type_name_val_string(
	const std::string& type_string,
	const std::string& name_string,
	const std::string& val_string,
	const std::string& type_name_dl = " ",
	const std::string& name_val_dl = "="
) {
	return type_string + type_name_dl + name_string + name_val_dl + val_string;
}


// clean chars in rm_char from start_idx, moving left to right
std::string helper_forward_oneway_clean_chars(
	const std::string& src_string,
	const std::unordered_set<char>& rm_chars,
	std::size_t start_idx
) {
	std::size_t srcstr_len = src_string.length();
	for (; start_idx < srcstr_len; ++start_idx) {
		if (rm_chars.find(src_string[start_idx]) == rm_chars.end()) break;
	}
	return src_string.substr(start_idx, srcstr_len - start_idx);
}


// clean chars in rm_char from start_idx, moving right to left
std::string helper_backward_oneway_clean_chars(
	const std::string& src_string,
	const std::unordered_set<char>& rm_chars,
	std::size_t start_idx
) {
	for (; start_idx > 0; --start_idx) {
		if (rm_chars.find(src_string[start_idx - 1]) == rm_chars.end()) break;
	}
	return src_string.substr(0, start_idx - 0);
}


// clean chars in rm_char at two ends of the string
std::string helper_bothside_clean_chars(
	const std::string& src_string,
	const std::unordered_set<char>& rm_chars
) {
	std::size_t srcstr_len = src_string.size();
	std::size_t start_idx = 0;
	std::size_t end_idx = srcstr_len;

	for (start_idx = 0; start_idx < srcstr_len; ++start_idx) {
		if (rm_chars.find(src_string[start_idx]) == rm_chars.end()) break;
	}
	for (end_idx = srcstr_len; end_idx > 0; --end_idx) {
		if (rm_chars.find(src_string[end_idx - 1]) == rm_chars.end()) break;
	}
	if (end_idx < start_idx) {
		return "";
	}
	return src_string.substr(start_idx, end_idx - start_idx);
}


// extract entry strings from complicated strings
std::vector<std::string> helper_extract_entrystr(
	const std::string& src_string,
	const std::string& entry_stop_str = ";", //string indicates the end of an entry string
	std::unordered_map<std::string, std::string> ignore_left_to_right_map = { {"//", "\n"}, {"/*", "*/"} }, //string parts between "left" and "right" to ignore
	std::unordered_map<std::string, std::string> include_left_to_right_map = { {"\"", "\""} } //string parts between "left" and "right" to include
) {
	std::size_t slow_idx = 0;
	std::size_t fast_idx = 0;
	std::size_t srcstr_len = src_string.size();
	std::size_t entry_stop_str_len = entry_stop_str.size();

	// count string lengths in the left_to_right map keys
	std::unordered_set<std::size_t> ignore_left_lens;
	for (const auto& itr : ignore_left_to_right_map) {
		ignore_left_lens.insert(itr.first.size());
	}

	// count string lengths in the left_to_right map keys
	std::unordered_set<std::size_t> include_left_lens;
	for (const auto& itr : include_left_to_right_map) {
		include_left_lens.insert(itr.first.size());
	}

	// itrate through src_string to find all entry strings
	std::vector<std::string> entry_strs;
	while (fast_idx < srcstr_len) {
		// check string between "left" and "right" to include
		for (auto cur_left_len : include_left_lens) {
			if (fast_idx + cur_left_len > srcstr_len) continue;
			std::string cur_left_str = src_string.substr(fast_idx, cur_left_len);
			if (include_left_to_right_map.find(cur_left_str) != include_left_to_right_map.end()) {
				std::string cur_right_str = include_left_to_right_map[cur_left_str];
				std::size_t cur_right_len = cur_right_str.size();
				for (fast_idx += cur_left_len; fast_idx + cur_right_len < srcstr_len; ++fast_idx) {
					if (src_string.substr(fast_idx, cur_right_len) == cur_right_str) break;
				}
				fast_idx += cur_right_len;
				//break;
			}
		}
		// check string between "left" and "right" to exclude
		for (auto cur_left_len : ignore_left_lens) {
			if (fast_idx + cur_left_len > srcstr_len) continue;
			std::string cur_left_str = src_string.substr(fast_idx, cur_left_len);
			if (ignore_left_to_right_map.find(cur_left_str) != ignore_left_to_right_map.end()) {
				std::string cur_right_str = ignore_left_to_right_map[cur_left_str];
				std::size_t cur_right_len = cur_right_str.size();
				for (fast_idx += cur_left_len; fast_idx + cur_right_len < srcstr_len; ++fast_idx) {
					if (src_string.substr(fast_idx, cur_right_len) == cur_right_str) break;
				}
				fast_idx += cur_right_len;
				slow_idx = fast_idx;
				//break;
			}
		}
		if (fast_idx + entry_stop_str_len > srcstr_len) break; // reach the end of src_string
		// Found complete entry string
		if (src_string.substr(fast_idx, entry_stop_str_len) == entry_stop_str) {
			entry_strs.push_back(src_string.substr(slow_idx, fast_idx - slow_idx));
			slow_idx = fast_idx + 1;
		}
		++fast_idx;
	}

	return entry_strs;
}

#endif