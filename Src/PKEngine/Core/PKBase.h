#ifndef PKENGINE_PKBASE_H
#define PKENGINE_PKBASE_H

#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <Core/PKMath.h>
#include <Core/PKTypes.h>

namespace pkengine
{
	namespace containers
	{
		template<typename K, typename V>
		using umap = std::unordered_map<K, V>;

		template<typename K, typename V>
		using map = std::map<K, V>;

		template<typename K>
		using uset = std::unordered_set<K>;

		template<typename K>
		using set = std::set<K>;

		template<typename T>
		using list = std::list<T>;

		template<typename T>
		using vector = std::vector<T>;
	}
}

#endif // !PKENGINE_PKBASE_H
