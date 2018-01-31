#pragma once

template<typename T>
class is_container
{
private:
    is_container() = delete;
    is_container(const is_container&) = delete;

    template<typename C>
    static constexpr bool has_iterator(typename C::iterator*)
    {
        return true;
    }
    template<typename C>
    static constexpr bool has_iterator(...)
    {
        return false;
    }
public:
    static constexpr bool value = has_iterator<T>(nullptr);
};
