#include <iostream>
#include <windows.h>
#include <string> 
#include <cstdlib> 
#include <stdexcept>
#include <numeric>


class Fraction
{
private:
	int numerator_;
	int denominator_;

	void reduction()
	{
		int a = abs(numerator_);
		int b = abs(denominator_);
		while (a != 0 && b != 0)
		{
			if (a > b)
			{
				a %= b;
			}
			else
			{
				b %= a;
			}
		};
		int gcd = a + b;
		numerator_ /= gcd;
		denominator_ /= gcd;
		if (denominator_ < 0) {
			numerator_ = -numerator_;
			denominator_ = -denominator_;
		}
	};
public:
	Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
	{
		if (denominator == 0)
		{
			throw std::invalid_argument("Знаменатель не может быть равен 0!");
		}
		reduction();
	};

	void lcm(const Fraction& other, int& new_numerator_,
		int& other_new_numerator_, int& new_denominator_) const
	{
		new_denominator_ = std::lcm(denominator_, other.denominator_); // общий знаменатель, наименьшее общее кратное
		new_numerator_ = new_denominator_ / denominator_ * numerator_;
		other_new_numerator_ = new_denominator_ / other.denominator_ * other.numerator_;
	}

	int get_numer() const
	{
		return numerator_;
	}
	int get_denom() const
	{
		return denominator_;
	}

	Fraction operator + (const Fraction& other) const
	{		
		int new_num_{};
		int other_new_num_{};
		int new_denom_{};
		lcm(other, new_num_, other_new_num_, new_denom_);
		int result = new_num_ + other_new_num_;
		return Fraction(result, new_denom_);
	}
	Fraction operator - (const Fraction& other) const
	{
		int new_num_{};
		int other_new_num_{};
		int new_denom_{};
		lcm(other, new_num_, other_new_num_, new_denom_);
		int result = new_num_ - other_new_num_;
		return Fraction(result, new_denom_);
	}
	Fraction operator * (const Fraction& other) const
	{
		int common_denominator = denominator_ * other.denominator_;
		int new_numerator = numerator_ * other.numerator_;
		return Fraction(new_numerator, common_denominator);
	}
	Fraction operator / (const Fraction& other) const
	{
		if (other.numerator_ == 0) {
			throw std::invalid_argument("Деление на ноль!");
		}
		int common_denominator = denominator_ * other.numerator_;
		int new_numerator = numerator_ * other.denominator_;
		return Fraction(new_numerator, common_denominator);
	}
	Fraction& operator ++ ()
	{
		numerator_ += denominator_;
		return *this;
	}
	Fraction& operator -- ()
	{
		numerator_ -= denominator_;
		return *this;
	}
	Fraction operator ++ (int)
	{
		Fraction copy = *this;
		numerator_ += denominator_;
		return copy;
	}
	Fraction operator -- (int)
	{
		Fraction copy = *this;
		numerator_ -= denominator_;
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
