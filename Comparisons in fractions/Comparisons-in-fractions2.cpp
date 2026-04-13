#include <iostream>
#include <numeric>
#include <string>
#include <windows.h>

class Fraction
{
private:
	int numerator_;
	int denominator_;
	void reduce()
	{
		int gcd = std::gcd(numerator_, denominator_);
		numerator_ /= gcd;
		denominator_ /= gcd;
	}

public:

	Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) 
	{
		if (denominator == 0) {
			throw "Знаменатель не может быть равен нулю";

		}
		reduce();  
	}
	void lcm(const Fraction& other, int& new_numerator_,
	int& other_new_numerator_) const
	{
		if (denominator_ != other.denominator_)
		{
			int lcm = std::lcm(denominator_, other.denominator_); // общий знаменатель, наименьшее общее кратное
			new_numerator_ = lcm / denominator_ * numerator_;
			other_new_numerator_ = lcm / other.denominator_ * other.numerator_;
		};
	}
	bool operator == (const Fraction& other) const
	{
		int new_num_;
		int other_new_num_;
		lcm(other, new_num_, other_new_num_);
		return (new_num_ == other_new_num_);
	}
	bool operator != (const Fraction& other) const
	{
		return !(*this == other);
	}
	bool operator > (const Fraction& other) const
	{
		int new_num_;
		int other_new_num_;
		lcm(other, new_num_, other_new_num_);
		return (new_num_ > other_new_num_);
	}
	bool operator < (const Fraction& other) const
	{
		return (!(*this > other) && !(*this == other));
	}
	bool operator >= (const Fraction& other) const
	{
		return ((*this > other) && (*this == other));
	}
	bool operator <= (const Fraction& other) const
	{
		return ((*this < other) && (*this == other));
	}
};

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Fraction f1(4, 3);
	Fraction f2(6, 11);

	std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
	std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
	std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
	std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
	std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
	std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
	return 0;
}
