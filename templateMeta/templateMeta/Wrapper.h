#pragma once
#include <type_traits>
#include <shared_mutex>

template <class, template<class...> class>
struct IsTemplateOf : std::false_type {};

template <class... T, template<class...> class TTemplate>
struct IsTemplateOf<TTemplate<T...>, TTemplate> : std::true_type {};
//
//template<class Container>
//using Value = typename Container::value_name;
//
//template<>
//using Value<int> = int;

template <class T, class = void>
struct RefType
{
	using type = typename std::add_pointer<T>::type;
};
template <class T>
struct RefType<T,
	typename std::enable_if<IsTemplateOf<T, std::shared_ptr>::value>::type
>
{
	using type = T;
};

//template <class T, class = void>
//struct ValueType {};

//template <class T>
//struct ValueType
//{
//	using type = typename T::value_type;
//};
//template <class T>
//struct ValueType
//{
//	using type = typename T::mapped_type;
//};


template <class T>
using ref_type = typename RefType<T>::type;
//template <class T>
//using value_type = typename ValueType<T>::type;

template<class T>
class ContainerWrapper
{
	//struct CValue;
public:
	decltype(auto) test(void);
	//typename T::key_type Find() {}
	//typename T::value_type Find() {}
private:
	std::shared_mutex mutex_;
	T container_;
};

template<class T>
inline decltype(auto) ContainerWrapper<T>::test(void)
{
	return false;
}
