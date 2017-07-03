#ifndef VectorNew_hpp

#define VectorNew_hpp

#include <iostream>
#include <cmath>
#include <array>
#include "Point.hpp"

//TODO: more constructors, double_t -> Type_T

#define Point_t Math::Point <Data_T, Measurements, Container_T>
#define Vector_t Math::Vector <Data_T, Measurements, Container_T>

#define Template template <typename Data_T, size_t Measurements, typename Container_T>

namespace Math
{
    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    class Vector //: public Math::Point <Data_T, Measurements, Container_T>
    {
        private:
            //typedef Math::Point <Data_T, Measurements, Container_T> Point_t;
            //typedef Math::Point <Data_T, Measurements, Container_T> Vector_t;

        public:
            Vector ();
            Vector (const Vector_t& from);
            Vector (const Vector_t& start, const Vector_t& finish);

            double_t length () const;

            Vector& rotate (const double_t angle);

            bool ok   () const;
            void dump () const;

            Vector_t& operator =  (const Vector_t& from);

            Data_T& operator [] (const size_t place);
            const Data_T& operator [] (const size_t place) const;

            Vector_t& operator +  () const;

            Vector_t& operator -  ();
            Vector_t& operator !  ();
            Vector_t  operator ~  ();
            Vector_t& operator *= (const double_t k);
            Vector_t& operator /= (const double_t k);
            Vector_t& operator += (Vector_t& from);
            Vector_t& operator -= (const Vector_t& from);

            Container_T& coords ();
            Container_T& coords () const;

        protected:
            Container_T coords_;
    };

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    bool operator == (const Vector_t& from, const Vector_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    bool operator != (const Vector_t& from, const Vector_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    Vector_t operator * (const Vector_t& from, const double_t k);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    Vector_t operator / (const Vector_t& from, const double k);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    Vector_t operator + (const Vector_t& from, const Vector_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    Vector_t operator - (const Vector_t& from, const Vector_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    Data_T operator & (const Vector_t& from, const Vector_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    Vector_t operator ^ (const Vector_t& from, const Vector_t& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    std::istream& operator >> (std::istream& in, Vector_t& value);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    std::ostream& operator << (std::ostream& out, const Vector_t& value);

    typedef Vector <   int, 2> VectorI2;
    typedef Vector < float, 2> VectorF2;
    typedef Vector <double, 2> VectorD2;

    typedef Vector <   int, 3> VectorI3;
    typedef Vector < float, 3> VectorF3;
    typedef Vector <double, 3> VectorD3;

    typedef Vector <   int, 4> VectorI4;
    typedef Vector < float, 4> VectorF4;
    typedef Vector <double, 4> VectorD4;
}

Template
Vector_t::Vector ():
    coords_ ()
{
}

Template
Vector_t::Vector (const Vector_t& from):
    coords_ ()
{
    (*this) = from;
}

Template
Vector_t::Vector (const Vector_t& start, const Vector_t& finish):
    coords_ ()
{
    (*this) = finish - start;
}

Template
double_t Vector_t::length () const
{
    return sqrt ((*this) & (*this));
}

Template
Vector_t& Vector_t::rotate (const double_t angle)
{
    return (*this); //To all measurements
}

Template
bool Vector_t::ok () const
{
    return true;
}

Template
void Vector_t::dump () const
{
}

Template
Vector_t& Vector_t::operator = (const Vector_t& from)
{
    std::copy (from.coords_.cbegin (), from.coords_.cend (), coords_.begin ());

    return (*this);
}

Template
Data_T& Vector_t::operator [] (const size_t place)
{
    return *(coords_.begin () + place);
}

Template
const Data_T& Vector_t::operator [] (const size_t place) const
{
    return *(coords_.begin () + place);
}

Template
Vector_t& Vector_t::operator + () const
{
    return (*this);
}

Template
Vector_t& Vector_t::operator - ()
{
    Vector_t zero;

    return zero -= (*this);
}

Template
Vector_t& Vector_t::operator ! ()
{
    (*this) /= length ();

    return (*this);
}

Template
Vector_t Vector_t::operator ~ ()
{
    Vector_t zero; //To all measurements

    zero[0] = +(*this)[1];
    zero[1] = -(*this)[0];

    return zero;
}

Template
Vector_t& Vector_t::operator *= (const double_t k)
{
    for (size_t i = 0; i < Measurements; i++)
        (*this)[i] *= k;

    return (*this);
}

Template
Vector_t& Vector_t::operator /= (const double_t k)
{
    if (k < 1e-8) return (*this) = Vector_t (); //k can't be less than 0. It's not right\

    for (size_t i = 0; i < Measurements; i++)
        (*this)[i] /= k;

    return (*this);
}

Template
Vector_t& Vector_t::operator += (Vector_t& from)
{
    for (size_t i = 0; i < Measurements; i++)
        (*this)[i] += from[i];

    return (*this);
}

Template
Vector_t& Vector_t::operator -= (const Vector_t& from)
{
    for (size_t i = 0; i < Measurements; i++)
        (*this)[i] -= from[i];

    return (*this);
}

Template
Container_T& Vector_t::coords ()
{
    return coords_;
}

Template
Container_T& Vector_t::coords () const
{
    return coords_;
}

Template
bool Math::operator == (const Vector_t& from, const Vector_t& to)
{
    for (size_t i = 0; i < Measurements; i++)
    {
        if (from[i] != to[i]) //from[i] and to[i] can't be double because '!='
            return false;
    }

    return true;
}

Template
bool Math::operator != (const Vector_t& from, const Vector_t& to)
{
    return !(from == to);
}

Template
Vector_t Math::operator * (const Vector_t& from, const double_t k)
{
    Vector_t copy (from);

    return (copy *= k);
}

Template
Vector_t Math::operator / (const Vector_t& from, const double k)
{
    Vector_t copy (from);

    return (copy /= k);
}

Template
Vector_t Math::operator + (const Vector_t& from, const Vector_t& to)
{
    Vector_t copy (from);

    return (copy += to);
}

Template
Vector_t Math::operator - (const Vector_t& from, const Vector_t& to)
{
    Vector_t copy (from);

    return (copy -= to);
}

Template
Data_T Math::operator & (const Vector_t& from, const Vector_t& to)
{
    Data_T result = 0; //Construct

    for (size_t i = 0; i < Measurements; i++)
        result += from[i] * to[i];

    return result; // |a| * |b| * cos (alpha)
}

Template
Vector_t Math::operator ^ (const Vector_t& from, const Vector_t& to)
{
    Vector_t result; //To all measurements

    return result; // |a| * |b| * sin (alpha)
}

Template
std::istream& Math::operator >> (std::istream& in, Vector_t& value)
{
    for (size_t i = 0; i < Measurements; i++)
        in >> value[i];

    return in;
}

Template
std::ostream& Math::operator << (std::ostream& out, const Vector_t& value)
{
    for (size_t i = 0; i < Measurements; i++)
        out << value[i] << " ";

    return out;
}

#undef Point_t
#undef Vector_t

#undef Template

#endif /* VectorNew_hpp */
