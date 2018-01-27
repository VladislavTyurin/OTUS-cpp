#pragma once

template<typename T>
class is_container
{
private:
    is_container() = delete;
    is_container(const is_container&) = delete;

    template<typename C>
    static constexpr char has_iterator(typename C::iterator*)
    {
        return char();
    }
    template<typename C>
    static constexpr int has_iterator(...)
    {
        return int();
    }
public:
    static constexpr auto value = has_iterator<T>(nullptr);
};
