#pragma once
#include <type_traits>

template<class, template<class...> class>
struct IsTemplateOf : std::false_type {};

template<class... T, template<class...> class TTemplate>
struct IsTemplateOf<TTemplate<T...>, TTemplate> : std::true_type {};

template <class T>
constexpr bool IsMapOf(void)
{
	return (IsTemplateOf<T, std::map>::value);
}
