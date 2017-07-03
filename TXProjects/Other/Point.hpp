#ifndef Point_hpp

#define Point_hpp

#include <iostream>
#include <cmath>
#include <array>

#define Point_t Math::Point <Data_T, Measurements, Container_T>

//TODO: two constructs (TypeOfData, Iterators), std::swap

namespace Math
{
    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    class Point
    {
        public:
            Point ();
            Point (const Point_t& from);

            bool ok () const;
            void dump () const;

            Point_t& operator =  (const Point_t& from);

            Data_T& operator [] (const size_t place);
            const Data_T& operator [] (const size_t place) const;

            Container_T& coords ();
            Container_T& coords () const;

        protected:
            Container_T coords_;
    };

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    double_t Distance (const Point_t& from, const Point_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    bool operator == (const Point_t& from, const Point_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    bool operator != (const Point_t& from, const Point_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    std::istream& operator >> (std::istream& in, Point_t& value);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    std::ostream& operator << (std::ostream& out, const Point_t& value);

    typedef Point <   int, 2> PointI2;
    typedef Point < float, 2> PointF2;
    typedef Point <double, 2> PointD2;

    typedef Point <   int, 3> PointI3;
    typedef Point < float, 3> PointF3;
    typedef Point <double, 3> PointD3;

    typedef Point <   int, 4> PointI4;
    typedef Point < float, 4> PointF4;
    typedef Point <double, 4> PointD4;
}

template <typename Data_T, size_t Measurements, typename Container_T>
Point_t::Point ():
    coords_ ()
{
}

template <typename Data_T, size_t Measurements, typename Container_T>
Point_t::Point (const Point_t& from):
    coords_ ()
{
    (*this) = from;
}

template <typename Data_T, size_t Measurements, typename Container_T>
bool Point_t::ok () const
{
    return true;
}

template <typename Data_T, size_t Measurements, typename Container_T>
void Point_t::dump () const
{
}

template <typename Data_T, size_t Measurements, typename Container_T>
Point_t& Point_t::operator = (const Point_t& from)
{
    std::copy (from.coords_.cbegin (), from.coords_.cend (), coords_.begin ());

    return (*this);
}

template <typename Data_T, size_t Measurements, typename Container_T>
Data_T& Point_t::operator [] (const size_t place)
{
    return *(coords_.begin () + place);
}

template <typename Data_T, size_t Measurements, typename Container_T>
const Data_T& Point_t::operator [] (const size_t place) const
{
    return *(coords_.begin () + place);
}

template <typename Data_T, size_t Measurements, typename Container_T>
Container_T& Point_t::coords ()
{
    return coords_;
}

template <typename Data_T, size_t Measurements, typename Container_T>
Container_T& Point_t::coords () const
{
    return coords_;
}

template <typename Data_T, size_t Measurements, typename Container_T>
double_t Math::Distance (const Point_t& from, const Point_t& to)
{
    double_t result = 0;

    for (size_t i = 0; i < Measurements; i++)
        result += pow (from[i] - to[i], 2);

    return sqrt (result);
}

template <typename Data_T, size_t Measurements, typename Container_T>
bool Math::operator == (const Point_t& from, const Point_t& to)
{
    for (size_t i = 0; i < Measurements; i++)
    {
        if (from[i] != to[i])
            return false;
    }

    return true;
}

template <typename Data_T, size_t Measurements, typename Container_T>
bool Math::operator != (const Point_t& from, const Point_t& to)
{
    return !(from == to);
}

template <typename Data_T, size_t Measurements, typename Container_T>
std::istream& Math::operator >> (std::istream& in, Point_t& value)
{
    for (size_t i = 0; i < Measurements; i++)
        in >> value[i];

    return in;
}

template <typename Data_T, size_t Measurements, typename Container_T>
std::ostream& Math::operator << (std::ostream& out, const Point_t& value)
{
    for (size_t i = 0; i < Measurements; i++)
        out << value[i] << " ";

    return out;
}

#undef Point_t

#endif /* Point_hpp */
