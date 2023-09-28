#pragma once
#include <iostream>
#include <vector>
class HunPolynomial
{
public:
    HunPolynomial();
    HunPolynomial(const std::vector<int> &coef); // short for coefficients
    void Set(const std::vector<int> &coef);
    HunPolynomial operator+(const HunPolynomial &A);
    HunPolynomial operator-(const HunPolynomial &A);
    HunPolynomial operator*(const HunPolynomial &A);
    friend std::ostream &operator<<(std::ostream &outputStream, const HunPolynomial &A);
    float operator()(const float &x);

private:
    std::vector<int> polynomial = {};
};