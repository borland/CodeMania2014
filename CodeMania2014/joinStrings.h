#include <string>
#include <list>
#include <tuple>

namespace detail 
{
	template <typename T>
	class has_empty
	{
	private:
		template <typename U, U> class check { };
	
		template <typename C> static char f(check<bool (C::*)(void) const, &C::empty>*);
	
		template <typename C> static char f(check<bool (C::*)(void), &C::empty>*);

		template <typename C> static long f(...);
	
	public:
		static const bool value = (sizeof(f<T>(nullptr)) == sizeof(char));
	};
}

// Joins all the elements in a collection into a string.
// The collection can contain anything that is compatible with std::stringstream operator <<
template<typename InputIterator, typename CharType>
typename std::enable_if<!detail::has_empty<typename std::iterator_traits<InputIterator>::value_type>::value, std::basic_string<CharType>>::type
joinString( const InputIterator& begin, const InputIterator& end, const CharType * const glue)
{
	std::basic_stringstream<CharType> result;

	bool hasAppended = false;
	InputIterator iter = begin;
	for(; iter != end; ++iter)
	{
		if( hasAppended )
			result << glue;

		result << *iter;
		hasAppended = true;
	}

	return result.str();
}

// overload which allows you to optionally skip empty entries. Uses std::enable_if to only be available for collections of std::basic_string<>
template<typename InputIterator, typename CharType>
typename std::enable_if<detail::has_empty<typename std::iterator_traits<InputIterator>::value_type>::value, std::basic_string<CharType>>::type
joinString( const InputIterator& begin, const InputIterator& end, const CharType * const glue, bool skipEmpty = true)
{
	std::basic_stringstream<CharType> result;

	bool hasAppended = false;
	InputIterator iter = begin;
	for(; iter != end; ++iter)
	{
		if( skipEmpty && iter->empty() )
			continue;

		if( hasAppended )
			result << glue;

		result << *iter;
		hasAppended = true;
	}

	return result.str();
}

// Joins all the elements in a collection into a string.
// The collection can contain anything that is compatible with std::basic_stringstream operator <<
template<typename CollectionType, typename CharType>
typename std::enable_if<!detail::has_empty<typename CollectionType::value_type>::value, std::basic_string<CharType>>::type
joinString( const CollectionType &collection, const CharType * const glue )
{
	return joinString(collection.begin(), collection.end(), glue);
}

template<typename CollectionType, typename CharType>
typename std::enable_if<detail::has_empty<typename CollectionType::value_type>::value, std::basic_string<CharType>>::type
joinString( const CollectionType &collection, const CharType * const glue, bool skipEmpty = true )
{
	return joinString(collection.begin(), collection.end(), glue, skipEmpty);
}
