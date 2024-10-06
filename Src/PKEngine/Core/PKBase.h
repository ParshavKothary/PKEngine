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
	class PKNamedObject
	{
	private:
		static const unsigned int s_len = 32;

	public:
		void SetName(const std::string& name) { strncpy_s(Name, name.c_str(), s_len); }
		const char* GetName() const { return Name; }

	protected:
		char Name[32];
	};

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
