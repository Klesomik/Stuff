#include <iostream>
#include <cmath>

//TODO: more constructors, double_t -> Type_T, variadic templates

namespace Math
{
    template <typename Data_T, size_t Measurements>
    class Vector
    {
        private:
            using Vector_t = Vector <Data_T, Measurements>;

        public:
            Vector ();
            Vector (const Data_T from[]);
            Vector (const Vector <Data_T, Measurements>& from);
            Vector (const std::initializer_list <Data_T>& from);
            Vector (const Vector& start, const Vector& finish);

            double_t lenght ();

            Vector& rotate (const double_t angle);

            bool ok   ();
            void dump ();

            Data_T& operator [] (const size_t place);
            Vector& operator +  ();
            Vector& operator -  ();
            Vector& operator !  ();
            Vector& operator *= (const double_t k);
            Vector& operator /= (const double_t k);
            Vector& operator =  (const Vector <Data_T, Measurements>& from);
            Vector& operator += (const Vector <Data_T, Measurements>& from);
            Vector& operator -= (const Vector <Data_T, Measurements>& from);

            Data_T* coords ();

        protected:
            Data_T coords_[Measurements];
    };

    template <typename Data_T, size_t Measurements>
    bool operator == (const Vector <Data_T, Measurements>& from, const Vector <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements>
    bool operator != (const Vector <Data_T, Measurements>& from, const Vector <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements>
    Math::Vector <Data_T, Measurements> operator * (const Vector <Data_T, Measurements>& from, const size_t k);

    template <typename Data_T, size_t Measurements>
    Math::Vector <Data_T, Measurements> operator * (const size_t k, const Vector <Data_T, Measurements>& from);

    template <typename Data_T, size_t Measurements>
    Math::Vector <Data_T, Measurements> operator / (const Vector <Data_T, Measurements>& from, const size_t k);

    template <typename Data_T, size_t Measurements>
    Math::Vector <Data_T, Measurements> operator + (const Vector <Data_T, Measurements>& from, const Vector <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements>
    Math::Vector <Data_T, Measurements> operator - (const Vector <Data_T, Measurements>& from, const Vector <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements>
    Data_T operator & (const Vector <Data_T, Measurements>& from, const Vector <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements>
    Data_T operator ^ (const Vector <Data_T, Measurements>& from, const Vector <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements>
    std::istream& operator >> (std::istream& in, Math::Vector <Data_T, Measurements>& value);

    template <typename Data_T, size_t Measurements>
    std::ostream& operator << (std::ostream& out, Math::Vector <Data_T, Measurements>& value);

    template <typename Data_T, size_t Measurements>
    double Distance (Math::Vector <Data_T, Measurements>& first, Math::Vector <Data_T, Measurements>& second);

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

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>::Vector ():
    coords_ ()
{
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>::Vector (const Data_T from[]):
    coords_ ()
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] = from[i];
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>::Vector (const Vector <Data_T, Measurements>& from):
    coords_ ()
{
    (*this) = from;
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>::Vector (const std::initializer_list <Data_T>& from):
    coords_ ()
{
    std::copy (from.begin (), from.begin () + Measurements, coords_);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>::Vector (const Vector& start, const Vector& finish):
    coords_ ()
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] = finish.coords_[i] - start.coords_[i];
}

template <typename Data_T, size_t Measurements>
double_t Math::Vector <Data_T, Measurements>::lenght ()
{
    double_t result = 0;

    for (size_t i = 0; i < Measurements; i++)
        result += coords_[i] * coords_[i];

    return sqrt (result);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::rotate (const double_t angle)
{
    return (*this);
}

template <typename Data_T, size_t Measurements>
bool Math::Vector <Data_T, Measurements>::ok ()
{
    return true;
}

template <typename Data_T, size_t Measurements>
void Math::Vector <Data_T, Measurements>::dump ()
{
}

template <typename Data_T, size_t Measurements>
Data_T& Math::Vector <Data_T, Measurements>::operator [] (const size_t place)
{
    return coords_[place];
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator + ()
{
    return (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator - ()
{
    Vector <Data_T, Measurements> zero;

    return zero -= (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator ! ()
{
    double_t dist = lenght ();

    for (size_t i = 0; i < Measurements; i++)
        coords_[i] /= dist;

    return (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator *= (const double_t k)
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] *= k;

    return (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator /= (const double_t k)
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] /= k;

    return (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator = (const Vector <Data_T, Measurements>& from)
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] = from.coords_[i];

    return (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator += (const Vector <Data_T, Measurements>& from)
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] += from.coords_[i];

    return (*this);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements>& Math::Vector <Data_T, Measurements>::operator -= (const Vector <Data_T, Measurements>& from)
{
    for (size_t i = 0; i < Measurements; i++)
        coords_[i] -= from.coords_[i];

    return (*this);
}

template <typename Data_T, size_t Measurements>
Data_T* Math::Vector <Data_T, Measurements>::coords ()
{
    return coords_;
}

template <typename Data_T, size_t Measurements>
bool operator == (const Math::Vector <Data_T, Measurements>& from, const Math::Vector <Data_T, Measurements>& to)
{
    for (size_t i = 0; i < Measurements; i++)
    {
        if (from.coords_[i] != to.coords_[i])
            return false;
    }

    return true;
}

template <typename Data_T, size_t Measurements>
bool operator != (const Math::Vector <Data_T, Measurements>& from, const Math::Vector <Data_T, Measurements>& to)
{
    return !(from == to);
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements> operator * (const Math::Vector <Data_T, Measurements>& from, const double_t k)
{
    Math::Vector <Data_T, Measurements> copy (from);

    copy *= k;

    return copy;
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements> operator * (const double_t k, const Math::Vector <Data_T, Measurements>& from)
{
    Math::Vector <Data_T, Measurements> copy (from);

    copy *= k;

    return copy;
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements> operator / (const Math::Vector <Data_T, Measurements>& from, const double_t k)
{
    Math::Vector <Data_T, Measurements> copy (from);

    copy /= k;

    return copy;
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements> operator + (const Math::Vector <Data_T, Measurements>& from, const Math::Vector <Data_T, Measurements>& to)
{
    Math::Vector <Data_T, Measurements> copy (from);

    copy += to;

    return copy;
}

template <typename Data_T, size_t Measurements>
Math::Vector <Data_T, Measurements> operator - (const Math::Vector <Data_T, Measurements>& from, const Math::Vector <Data_T, Measurements>& to)
{
    Math::Vector <Data_T, Measurements> copy = (from);

    copy -= to;

    return copy;
}

template <typename Data_T, size_t Measurements>
Data_T operator & (const Math::Vector <Data_T, Measurements>& from, const Math::Vector <Data_T, Measurements>& to)
{
    Data_T result = 0;

    for (size_t i = 0; i < Measurements; i++)
        result += from[i] * to[i];

    return result; // |a| * |b| * cos (alpha)
}

template <typename Data_T, size_t Measurements>
Data_T operator ^ (const Math::Vector <Data_T, Measurements>& from, const Math::Vector <Data_T, Measurements>& to)
{
    Data_T result = 0;

    return result; // |a| * |b| * sin (alpha)
}

template <typename Data_T, size_t Measurements>
std::istream& Math::operator >> (std::istream& in, Math::Vector <Data_T, Measurements>& value)
{
    for (size_t i = 0; i < Measurements; i++)
        in >> value[i];

    return in;
}

template <typename Data_T, size_t Measurements>
std::ostream& Math::operator << (std::ostream& out, Math::Vector <Data_T, Measurements>& value)
{
    for (size_t i = 0; i < Measurements; i++)
        out << value[i] << " ";

    return out;
}

template <typename Data_T, size_t Measurements>
double Math::Distance (Math::Vector <Data_T, Measurements>& first, Math::Vector <Data_T, Measurements>& second)
{
    double value = 0;

    for (int i = 0; i < Measurements; i++)
        value += (first[i] - second[i]) * (first[i] - second[i]);

    return sqrt (value);
}
