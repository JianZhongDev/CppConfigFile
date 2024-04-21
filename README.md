# Configuration File Parser using C++

CppConfigFile is a configuration file parser built using C++. It enables the storage of C++ variables with different data types and their retrieval from human-readable configuration files.

The functionality of the implemented configuration file parser can be summarized as follows:

* Storing multiple setting variables with various data types.
* Saving setting variables to configuration files and loading them from these files.
* Supporting configuration files with comments.

## Software Support

The module was created and tested using Visual Studio 2022 Community with the `Default (ISO C++14 Standard)` settings.

## How to Use the Configuration File Parser

This code block provides a quick demonstration of how to utilize the configuration file parser:

``` C++
#include "GenericEntry.hpp"
#include "GenericHashMap.hpp"
#include "GenericHashMapIOs.hpp"
#include "GenericHashMapHelpers.hpp"

GenHashMap test_genhashmap;
// add new entry
test_genhashmap["int_val"] = new IntEntry(1);
// set value of the entry
((IntEntry*)test_genhashmap["int_val"])->set(-1);
// get value from the entry
int tmp_int;
((IntEntry*)test_genhashmap["int_val"])->get(&tmp_int);

GenHashMapIOTxt test_io_txt;
// save settings to configuration file
test_io_txt.save_to_file(
	test_genhashmap,
	"test_config_file.txt",
	std::ios_base::out,
	"This is the test configuration file for Vision Tech Insights blog."
);
// load settings from configuration file
test_io_txt.update_from_file(
	test_genhashmap,
	"test_config_file.txt",
	std::ios_base::in
);

// release generic entries and clear gen hashmap
clear_genhashmap(test_genhashmap);
```

More comprehensive working examples of the configuration file parser are included in the ["BlogDemoMain.cpp"](./CppConfigFile/ConfigFileModule/Tests/BlogDemoMain.cpp) and ["DemoMain.cpp"](./CppConfigFile/ConfigFileModule/Tests/DemoMain.cpp) files.


## How to Add Entries with a Newly Defined Data Type

TThe base classes for the entries are defined in the ["GenericEntry.hpp"](./CppConfigFile/ConfigFileModule/Headers/GenericEntry.hpp) header file.

For primitive types, simply create a subclass inheriting the `PrimitiveTypeEntry` class, define the constructor, and provide the `type_name` string as follows:

```C++
class IntEntry : public PrimitiveTypeEntry<int> {
public:
	IntEntry(int data = 0) {
		this->type_name = "int";
		this->data = data;
	}
};
```

For vectors with primitive types, simply create a subclass inheriting the `VectorPrimitiveTypeEntry` class, define the constructor, and provide the `type_name` string as follows:

```C++
// Entry with int vector
class VectorIntEntry : public VectorPrimitiveTypeEntry<int> {
public:
	VectorIntEntry(const std::vector<int>& data = { 0 }) {
		this->type_name = "vector_int";
		this->data = std::vector<int>(data);
	}
};
```

For a customized type, you will need to create a subclass inheriting either the `TypedEntry` or `GenericEntry` base class and implement the virtual methods.

## Tutorial

A comprehensive tutorial for this module can be found in [my blog post](https://jianzhongdev.github.io/VisionTechInsights/posts/building_a_configuration_file_parser_with_cpp/) (URL: https://jianzhongdev.github.io/VisionTechInsights/posts/building_a_configuration_file_parser_with_cpp/)

## License

Licensed under the [GPL-3.0 license](./LICENSE)



