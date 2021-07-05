#pragma once
#include <iostream>
#include <numeric>
#include <cstdint>
#include <cstdlib>

using namespace std;

using ll = int64_t;

class Fraction{
private:
	ll num, den;
public:
	Fraction(ll n, ll d = 1){
		if(d == 0){
			throw "Division By Zero Not Possible, Denominator Cannot Be 0";
		}
		if(d < 0){
			n = -n;
		}
		ll g = gcd(llabs(n), llabs(d));
		num = n / g;
		den = d / g;
	}
	ll numerator() const{
		return num;
	}
	ll denominator() const{
		return den;
	}
	Fraction operator+(Fraction const &f) const{
		return Fraction(num * f.den + den * f.num, den * f.den);
	}
	Fraction operator-() const{
		return Fraction(-num, den);
	}
	Fraction operator-(Fraction const &f) const{
		return Fraction(num * f.den - den * f.num, den * f.den);
	}
	Fraction operator*(Fraction const &f) const{
		ll g1 = gcd(num, f.den);
		ll g2 = gcd(den, f.num);
		return Fraction((num / g1) * (f.num / g2), (den / g2) * (f.den / g1));
	}
	Fraction operator*(ll n) const{
		ll g = gcd(n, den);
		return Fraction((n / g) * num, den / g);
	}
	Fraction operator*(int n) const{
		return *this * (ll)n;
	}
	Fraction reciprocal(Fraction const &f) const{
		ll sgn = (f.num < 0) ? -1 : 1;
		return Fraction(sgn * f.den, abs(f.num));
	}
	Fraction operator/(Fraction const &f){
		return *this * reciprocal(f);
	}
	bool operator==(Fraction const &f) const{
		return (num == f.num && den == f.den);
	}
	bool operator!=(Fraction const &f) const{
		return (num != f.num || den != f.den);
	}
	bool operator<(Fraction const &f) const{
		__int128 x = (__int128)llabs(num) * (__int128)f.den;
		__int128 y = (__int128)llabs(f.num) * (__int128)den;
		return x < y;
	}
	bool operator>(Fraction const &f) const{
		__int128 x = (__int128)llabs(num) * (__int128)f.den;
		__int128 y = (__int128)llabs(f.num) * (__int128)den;
		return x > y;
	}
	bool operator<=(Fraction const &f) const{
		return (*this == f || *this < f);
	}
	bool operator>=(Fraction const &f) const{
		return (*this == f || *this > f);
	}
	void operator+=(Fraction const &f){
		num = num * f.den + den * f.num;
		den = den * f.den;
	}
	void operator-=(Fraction const &f){
		num = num * f.den - den * f.num;
		den = den * f.den;
	}
	void operator*=(Fraction const &f){
		ll g1 = gcd(num, f.den);
		ll g2 = gcd(den, f.num);
		num = (num / g1) * (f.num / g2);
		den = (den / g2) * (f.den / g1);
	}
	void operator/=(Fraction const &f){
		auto fr = reciprocal(f);
		*this *= fr;
	}
	double to_double(){
		return (double)num / den;
	}
};

ostream& operator<<(ostream& os, const Fraction& f){
	os << f.numerator() << '/' << f.denominator();
	return os;
}
