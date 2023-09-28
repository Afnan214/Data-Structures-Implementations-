#include "HunPolynomial.h"
#include <cmath>
#include <math.h>
HunPolynomial::HunPolynomial() {}
HunPolynomial::HunPolynomial(const std::vector<int> &coef) : polynomial{coef} {}
void HunPolynomial::Set(const std::vector<int> &coef)
{
    polynomial = coef;
}
HunPolynomial HunPolynomial::operator+(const HunPolynomial &A)
{
    HunPolynomial newPolynomial;
    std::vector<int> newPoly = {};
    int a = this->polynomial.size() - 1;
    int b = A.polynomial.size() - 1;
    if (a == 0)
    {
        newPoly = A.polynomial;
        newPolynomial.Set(newPoly);
        return newPolynomial;
    }
    else if (b == 0)
    {
        newPoly = this->polynomial;
        newPolynomial.Set(newPoly);
        return newPolynomial;
    }

    int sum = 0;
    while (a != -1 && b != -1)
    {
        sum = this->polynomial[a] + A.polynomial[b];
        newPoly.insert(newPoly.begin(), sum);
        a--;
        b--;
    }
    if (a == b)
    {
    }
    else if (a < b)
    {
        while (b != -1)
        {
            newPoly.insert(newPoly.begin(), A.polynomial[b]);
            b--;
        }
    }
    else
    {
        while (a != -1)
        {
            newPoly.insert(newPoly.begin(), this->polynomial[a]);
            a--;
        }
    }
    newPolynomial.Set(newPoly);
    return newPolynomial;
}
HunPolynomial HunPolynomial::operator-(const HunPolynomial &A)
{
    HunPolynomial newPolynomial;
    std::vector<int> newPoly = {};
    int a = this->polynomial.size() - 1;
    int b = A.polynomial.size() - 1;
    if (this->polynomial.empty())
    {
        for (int i : A.polynomial)
        {
            newPoly.push_back(i * (-1));
        }
        newPolynomial.Set(newPoly);
        return newPolynomial;
    }
    else if (b == 0)
    {

        newPoly = this->polynomial;
        newPolynomial.Set(newPoly);
        return newPolynomial;
    }
    int diff = 0;
    while (a != -1 && b != -1)
    {
        diff = this->polynomial[a] - A.polynomial[b];
        newPoly.insert(newPoly.begin(), diff);
        a--;
        b--;
    }
    if (a == b)
    {
    }
    else if (a < b)
    {
        while (b != -1)
        {
            newPoly.insert(newPoly.begin(), (-1) * A.polynomial[b]);
            b--;
        }
    }
    else
    {
        while (a != -1)
        {
            newPoly.insert(newPoly.begin(), this->polynomial[a]);
            a--;
        }
    }
    newPolynomial.Set(newPoly);
    return newPolynomial;
}
HunPolynomial HunPolynomial::operator*(const HunPolynomial &A)
{
    HunPolynomial newPolynomial;
    std::vector<int> newPoly = {};
    int a = this->polynomial.size();
    int b = A.polynomial.size();
    for (size_t i = 0; i < (a + b) - 1; i++)
    {
        newPoly.push_back(0);
    }
    if (a == 0 || b == 0)
    {
        return newPolynomial;
    }

    for (size_t i = 0; i < a; i++)
    {
        for (size_t j = 0; j < b; j++)
        {
            newPoly[i + j] += this->polynomial[i] * A.polynomial[j];
        }
    }
    newPolynomial.Set(newPoly);
    return newPolynomial;
}
std::ostream &operator<<(std::ostream &outputStream, const HunPolynomial &A)
{
    int poly = A.polynomial.size() - 1;
    short counter = 0;
    for (int i : A.polynomial)
    {
        if (i < 0)
        {
            outputStream << "- ";
        }
        else if (i > 0 && counter != 0)
        {
            outputStream << "+ ";
        }
        if (poly != 0 && poly != 1)
        {
            if (i == -1 || i == 1)
            {
                outputStream << "x^" << poly << " ";
            }
            else if (i == 0)
            {
            }
            else
            {
                outputStream << abs(i) << "*x^" << poly << " ";
            }
        }
        else if (poly == 1)
        {
            if (i == -1 || i == 1)
            {
                outputStream << "x"
                             << " ";
            }
            else if (i == 0)
            {
            }
            else
            {
                outputStream << abs(i) << "*x"
                             << " ";
            }
        }
        else if (poly == 0)
        {
            if (i != 0)
            {
                outputStream << abs(i);
            }
        }
        poly--;
        counter++;
    }
    return outputStream;
}
float HunPolynomial::operator()(const float &x)
{
    float result = 0.0;
    int poly = polynomial.size() - 1;
    for (int i : polynomial)
    {
        result += i * (pow(x, poly));
        poly--;
    }
    return result;
}