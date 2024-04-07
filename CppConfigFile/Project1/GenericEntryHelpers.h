#pragma once

/* Code Description
* FILE: GenericEntryHelpers.h
* DESCRIPTON: helper functions for generic entry class.
* NOTE:
*
* CREATE: 2024-04-04
* LAST UPDATE:
*/


#include<iostream>
#include<string>
#include<unordered_set>

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

