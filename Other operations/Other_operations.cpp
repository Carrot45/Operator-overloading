#include <iostream>
#include <windows.h>
#include <string> 
#include <cstdlib> 
#include <stdexcept>


class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			throw std::invalid_argument("Знаменатель не может быть равен 0!");
		}
		numerator_ = numerator;
		denominator_ = denominator;
		reduction();  
	}
	int get_numer() const
	{
		return numerator_;
	}
	int get_denom() const
	{
		return denominator_;
	}
	int find_max_divider(int a, int b) const
	{
		a = abs(a);
		b = abs(b);
		while (a != 0 && b != 0)
		{
			if (a > b)
				a %= b;
			else
				b %= a;
		}
		return a + b;
	}
	void reduction()
	{
		int max_divider = find_max_divider(numerator_, denominator_);
		numerator_ /= max_divider;
		denominator_ /= max_divider;
		if (denominator_ < 0)
		{
			denominator_ = -denominator_;
			numerator_ = -numerator_;
		}
	}

	Fraction operator + (const Fraction& other) const
	{
		int common_denominator = denominator_ * other.denominator_;
		int new_numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
		Fraction result(new_numerator, common_denominator);
		result.reduction();
		return result;
	}
	Fraction operator - (const Fraction& other) const
	{
		int common_denominator = denominator_ * other.denominator_;
		int new_numerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
		Fraction result(new_numerator, common_denominator);
		result.reduction();
		return result;
	}
	Fraction operator * (const Fraction& other) const
	{
		int common_denominator = denominator_ * other.denominator_;
		int new_numerator = numerator_ * other.numerator_;
		Fraction result(new_numerator, common_denominator);
		result.reduction();
		return result;
	}
	Fraction operator / (const Fraction& other) const
	{
		int common_denominator = denominator_ * other.numerator_;
		int new_numerator = numerator_ * other.denominator_;
		Fraction result(new_numerator, common_denominator);
		result.reduction();
		return result;
	}
	Fraction& operator ++ ()
	{
		numerator_ += denominator_;
		reduction();
		return *this;
	}
	Fraction& operator -- ()
	{
		numerator_ -= denominator_;
		reduction();
		return *this;
	}
	Fraction operator ++ (int)
	{
		Fraction copy = *this;
		numerator_ += denominator_;
		reduction();
		return copy;
	}
	Fraction operator -- (int)
	{
		Fraction copy = *this;
		numerator_ -= denominator_;
		reduction();
		return copy;
	}
};

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int numerator1{}, numerator2{}, denominator1{}, denominator2{};
	std::cout << "Введите числитель первой дроби: ";
	std::cin >> numerator1;
	std::cout << "Введите знаменатель первой дроби: ";
	std::cin >> denominator1;
	std::cout << "Введите числитель второй дроби: ";
	std::cin >> numerator2;
	std::cout << "Введите знаменатель второй дроби: ";
	std::cin >> denominator2;

	Fraction f1(numerator1, denominator1);
	Fraction f2(numerator2, denominator2);

	Fraction f3 = f1 + f2;	
	std::cout << f1.get_numer() << "/" << f1.get_denom() << " + " << f2.get_numer() << "/" << f2.get_denom() << " = " << f3.get_numer() << "/" << f3.get_denom() << std::endl;
	Fraction f4 = f1 - f2;
	std::cout << f1.get_numer() << "/" << f1.get_denom() << " - " << f2.get_numer() << "/" << f2.get_denom() << " = " << f4.get_numer() << "/" << f4.get_denom() << std::endl;
	Fraction f5 = f1 * f2;
	std::cout << f1.get_numer() << "/" << f1.get_denom() << " * " << f2.get_numer() << "/" << f2.get_denom() << " = " << f5.get_numer() << "/" << f5.get_denom() << std::endl;
	Fraction f6 = f1 / f2;
	std::cout << f1.get_numer() << "/" << f1.get_denom() << " / " << f2.get_numer() << "/" << f2.get_denom() << " = " << f6.get_numer() << "/" << f6.get_denom() << std::endl;
	Fraction f7 = (++f1) * f2;
	std::cout << "++" << f1.get_numer() << "/" << f1.get_denom() << " * " << f2.get_numer() << "/" << f2.get_denom() << " = " << f7.get_numer() << "/" << f7.get_denom() << std::endl;
	
	std::cout << "Значение дроби 1 = " << f1.get_numer() << "/" << f1.get_denom() << std::endl;
	Fraction f8 = (f1--) * f2;

	std::cout << f1.get_numer() << "/" << f1.get_denom() << "-- * " << f2.get_numer() << "/" << f2.get_denom() << " = " << f8.get_numer() << "/" << f8.get_denom() << std::endl;
	
	std::cout << "Значение дроби 1 = " << f1.get_numer() << "/" << f1.get_denom() << std::endl;
	return 0;
}
