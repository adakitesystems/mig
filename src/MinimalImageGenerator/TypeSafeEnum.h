#ifndef __TYPE_SAFE_ENUM_H__2D826C6201FF8A2E598ACCDF318FB984____
#define __TYPE_SAFE_ENUM_H__2D826C6201FF8A2E598ACCDF318FB984____
#pragma once

/**
* More C++ Idioms/Type Safe Enum
* https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Safe_Enum
*/

namespace MIG {
	template<typename def, typename inner = typename def::type>
	class TypeSafeEnum : public def
	{
	public:
		TypeSafeEnum() : _val() {}
		TypeSafeEnum(inner v) : _val(v) {}

		inner underlying() const { return _val; }

		friend bool operator==(const TypeSafeEnum &lhs, const TypeSafeEnum &rhs) { return lhs._val == rhs._val; }
		friend bool operator!=(const TypeSafeEnum &lhs, const TypeSafeEnum &rhs) { return lhs._val != rhs._val; }
		friend bool operator<(const TypeSafeEnum &lhs, const TypeSafeEnum &rhs) { return lhs._val < rhs._val; }
		friend bool operator<=(const TypeSafeEnum &lhs, const TypeSafeEnum &rhs) { return lhs._val <= rhs._val; }
		friend bool operator>(const TypeSafeEnum &lhs, const TypeSafeEnum &rhs) { return lhs._val > rhs._val; }
		friend bool operator>=(const TypeSafeEnum &lhs, const TypeSafeEnum &rhs) { return lhs._val >= rhs._val; }

	private:
		inner _val;
	};
}

#endif
