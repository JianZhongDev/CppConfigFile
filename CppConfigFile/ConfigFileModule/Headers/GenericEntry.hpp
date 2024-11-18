#pragma once

/* Code Description
* FILE: GenericEntry.h
* DESCRIPTON: Entry class to save data with different data types
* NOTE:
*
* CREATE: 2024-04-06
* LAST UPDATE:
*/


#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>
#include<sstream>
#include<typeinfo>
#include<typeindex>
#include<type_traits>
#include<assert.h>

#include "StringHelpers.hpp"

#ifndef GENERICENTRY_H
#define GENERICENTRY_H

// Base type of generic entry
class GenericEntry {
protected:
	std::string type_name;
public:
	//TODO: could potentially change the return type from void to int and return error flag
	//TODO: could potentially use type_index instead of hardcoded string as the type identifier

	GenericEntry() {
		// set up the type_name in the constructor
		this->type_name = "generic_entry";
	}

	// NOTE: direct data access function to be implemented in the subclasses

	// Return string of the type name
	void get_typename(std::string* dst_string) {
		*dst_string = this->type_name;
	}

	// Write the value of the entry into string
	virtual void write_val_string(std::string* dst_string) = 0 {
		//Override this method in subclass 
	}

	// Read value of the entry from string
	virtual void read_val_string(const std::string& src_string) = 0{
		//Override this method in subclass 
	}
};


// Entry of generic type definition
template<typename data_t>
class TypedEntry : public GenericEntry {
protected:
	data_t data;
public:
	//Constructor without initial value
	TypedEntry() {
		this->type_name = "typed_entry";
	}
	//Constructor with initial value
	TypedEntry(data_t data) : TypedEntry() {
		this->data = data_t(data);
	}

	// Implemented set entry value method
	void set(const data_t& data) {
		this->data = data_t(data);
	}

	// Implemented get entry value method
	void get(data_t* data_p) {
		*data_p = data_t(this->data);
	}

};


// Entries with primitive type  
template<typename data_t>
class PrimitiveTypeEntry : public TypedEntry<data_t> {
	// NOTE: Only need to define contructor giving type_name in the subclasses
public:
	PrimitiveTypeEntry() {
		this->type_name = "primitivetype_entry";
	}
	PrimitiveTypeEntry(const data_t& data) : PrimitiveTypeEntry() {
		this->data = data_t(data);
	}
	virtual void write_val_string(std::string* dst_string) override {
		*dst_string = std::to_string(this->data);
	}
	virtual void read_val_string(const std::string& src_string) override {
		if (std::is_fundamental<data_t>::value) { // validate the data type is primitive data type
			std::stringstream(src_string) >> this->data; // use stringstream to convert value string to value
		}
	}
};


// Entries with int type
class IntEntry : public PrimitiveTypeEntry<int> {
public:
	IntEntry(int data = 0) {
		this->type_name = "int";
		this->data = data;
	}
};


// Entries with unsigned in type
class UintEntry : public PrimitiveTypeEntry<unsigned int> {
protected:
public:
	UintEntry(unsigned int data = 0) {
		this->type_name = "uint";
		this->data = data;
	}
};


// Entries with unsigned long long type
class ULongLongEntry : public PrimitiveTypeEntry<unsigned long long> {
protected:
public:
	ULongLongEntry(unsigned long long data = 0) {
		this->type_name = "ulonglong";
		this->data = data;
	}
};


// Entries with float type
class FloatEntry : public PrimitiveTypeEntry<float> {
public:
	FloatEntry(float data = 0.0) {
		this->type_name = "float";
		this->data = data;
	}
};


// Entries with double type
class DoubleEntry : public PrimitiveTypeEntry<double> {
public:
	DoubleEntry(double data = 0.0) {
		this->type_name = "float";
		this->data = data;
	}
};


// Entries with string type
class StringEntry : public TypedEntry<std::string> {
protected:
	// NOTE: value string format: "value_string"
	std::string str_enclosure[2] = { "\"", "\"" };
public:
	StringEntry(const std::string& data = "") {
		this->type_name = "string";
		this->data = data;
	}

	void write_val_string(std::string* dst_string) override {
		// Add " " to string
		*dst_string = str_enclosure[0] + std::string(this->data) + str_enclosure[1];
	}

	void read_val_string(const std::string& src_string) override {
		// Extract string between " "
		std::string tmp_str = helper_extract_string_between_enclosure(src_string, str_enclosure[0], str_enclosure[1]);
		this->data = std::string(tmp_str);
	}
};


// Vector class with primitive data type
template<typename data_t>
class VectorPrimitiveTypeEntry : public TypedEntry<std::vector<data_t>> {
	// NOTE: Only need to define contructor giving type_name in the subclasses
protected:
	//NOTE: data string format: {val0, val1, val2}
	std::string str_dl = ",";
	std::string str_enclosure[2] = { "{", "}" };
public:
	VectorPrimitiveTypeEntry() {
		this->type_name = "vector_primitivetype";
	}

	VectorPrimitiveTypeEntry(const std::vector<data_t>& data) : VectorPrimitiveTypeEntry() {
		this->data = std::vector<data_t>(data);
	}

	void write_val_string(std::string* dst_string) override {
		std::stringstream result_strstream;
		unsigned data_len = this->data.size();
		unsigned count = 0;

		// iterate through data vector
		result_strstream << this->str_enclosure[0];
		for (auto itr = this->data.begin(); itr != this->data.end(); ++itr) {
			result_strstream << std::to_string(*itr);
			count++;
			if (count < data_len) result_strstream << this->str_dl;
		}
		result_strstream << this->str_enclosure[1];

		*dst_string = result_strstream.str();
	}

	void read_val_string(const std::string& src_string) override {
		// remove '{', '}', and '_'
		std::string tmp_str = helper_extract_string_between_enclosure(src_string, str_enclosure[0], str_enclosure[1]);
		tmp_str = helper_clean_tailheadchars_string(tmp_str, std::unordered_set<char>{' '});
		// extract value string for each element
		std::vector<std::string> val_strs = helper_split_string_with_delimiter(tmp_str, this->str_dl);
		
		if (std::is_fundamental<data_t>::value) { // validate data type
			// iterate through value strings for each element
			this->data.clear();
			for (auto itr = val_strs.begin(); itr != val_strs.end(); ++itr) {
				data_t tmp_val;
				std::stringstream(*itr) >> tmp_val;
				this->data.push_back(tmp_val);
			}
		}
	}
};


// Entry with int vector
class VectorIntEntry : public VectorPrimitiveTypeEntry<int> {
public:
	VectorIntEntry(const std::vector<int>& data = { 0 }) {
		this->type_name = "vector_int";
		this->data = std::vector<int>(data);
	}
};


// Entry with unsigned int vector
class VectorUIntEntry : public VectorPrimitiveTypeEntry<unsigned int> {
public:
	VectorUIntEntry(const std::vector<unsigned int>& data = { 0 }) {
		this->type_name = "vector_int";
		this->data = std::vector<unsigned int>(data);
	}
};


// Entry with float vector
class VectorFloatEntry : public VectorPrimitiveTypeEntry<float> {
public:
	VectorFloatEntry(const std::vector<float>& data = { 0.0 }) {
		this->type_name = "vector_float";
		this->data = std::vector<float>(data);
	}
};

#endif