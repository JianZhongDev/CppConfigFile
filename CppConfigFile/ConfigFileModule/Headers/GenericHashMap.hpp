#pragma once

/* Code Description
* FILE: GenericHashMap.h
* DESCRIPTON: generic hash map defintions
* NOTE:
*
* CREATE: 2024-04-07
* LAST UPDATE:
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>

#include "../Headers/GenericEntry.hpp"

#ifndef GENERICHASHMAP_H
#define GENERICHASHMAP_H

// #define ORDERED_MAP

#ifdef ORDERED_MAP
typedef std::map<std::string, GenericEntry*> GenHashMap;
#else
//typedef std::unordered_map<std::string, GenericEntry*> GenHashMap;
typedef std::unordered_map<std::string, GenericEntry*> GenHashMap;
#endif

#endif


