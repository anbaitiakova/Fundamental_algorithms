#include <iostream>
#include <map>
#include <set>

class TeX_convertible
{
public:
    virtual std::string convert() const = 0;
};

class polynomial;
class monomial: public TeX_convertible
{
    int coeff;
    std::map<char, size_t> variables;

public:
    monomial()
    {
        coeff = 0;
    }

    monomial(const char* str)
    {
        char* ptr = (char*)str;
        bool minus = false;
        coeff = 0;
        char var;
        size_t pow = 0;
        while(*ptr != '\0')
        {
            if (*ptr == ' ')
                break;
            if (*ptr == '-')
                minus = true;
            if (*ptr == '+' || *ptr == '-')
                ptr += 2;
            while(isdigit(*ptr))
            {
                coeff *= 10;
                coeff += *ptr - '0';
                ptr++;
            }

            if(coeff == 0)
            {
                if(minus)
                {
                    coeff = -1;
                    minus = false;
                }
                else
                    coeff = 1;
            }

            if(minus)
            {
                coeff *= -1;
                minus = false;
            }
            if (*ptr == ' ' || *ptr == '\0')
                break;
            var = *ptr;
            ptr++;
            if (*ptr == '^')
            {
                pow = 0;
                ptr++;
                while (isdigit(*ptr)) {
                    pow *= 10;
                    pow += *ptr - '0';
                    ptr++;
                }
                if (pow != 0)
                    variables.insert(std::make_pair(var, pow));
            }
            else
                variables.insert(std::make_pair(var, 1));
        }
    }

    monomial(const monomial& monom)
    {
        coeff = monom.coeff;
        variables = monom.variables;
    }

    monomial& operator=(const monomial& monom)
    {
        coeff = monom.coeff;
        variables = monom.variables;
        return *this;
    }

    bool operator==(const monomial& monom) const
    {
        if(coeff != monom.coeff)
            return false;
        if(variables == monom.variables)
            return true;
        return false;
    }

    bool operator!=(const monomial& monom) const
    {
        return !(*this == monom);
    }

    monomial& operator+=(const monomial& monom)
    {
        if (variables != monom.variables)
            throw "Different variables!";
        coeff += monom.coeff;
        if (coeff == 0)
            variables.clear();
        return *this;
    }

    monomial operator+(const monomial& monom) const
    {
        return monomial(*this) += monom;
    }

    monomial& operator-=(const monomial& monom)
    {
        if (variables != monom.variables)
            throw "Different variables!";
        coeff -= monom.coeff;
        if (coeff == 0)
            variables.clear();
        return *this;
    }

    monomial operator-(const monomial& monom) const
    {
        return monomial(*this) -= monom;
    }

    monomial& operator*=(const monomial& monom)
    {
        monomial result;
        result.coeff = coeff * monom.coeff;
        auto iter = variables.begin();
        auto iter2 = monom.variables.begin();
        while (iter != variables.end() && iter2 != monom.variables.end() )
        {
            if ((*iter).first == (*iter2).first)
                result.variables.insert(std::make_pair((*iter).first, (*iter).second + (*iter2).second));
            else
            {
                result.variables.insert(std::make_pair((*iter).first, (*iter).second));
                result.variables.insert(std::make_pair((*iter2).first, (*iter2).second));
            }
            ++iter;
            ++iter2;
        }
        if (iter != variables.end())
        {
            while (iter != variables.end())
            {
                result.variables.insert(std::make_pair((*iter).first, (*iter).second));
                iter++;
            }
        }
        if (iter2 != monom.variables.end())
        {
            while (iter2 != monom.variables.end())
            {
                result.variables.insert(std::make_pair((*iter2).first, (*iter2).second));
                iter2++;
            }
        }
        *this = result;
        return *this;
    }

    monomial operator*(const monomial& monom) const
    {
        return monomial(*this) *= monom;
    }

    monomial& operator/=(const char& derivative)
    {
        for(auto& iter: variables)
        {
            if(iter.first == derivative)
            {
                coeff *= iter.second;
                iter.second -= 1;
                if(iter.second == 0)
                    variables.erase(derivative);
                return *this;
            }
        }
        coeff = 0;
        variables.clear();
        return *this;
    }

    monomial operator/(const char& derivative) const
    {
        return monomial(*this) /= derivative;
    }

    monomial& change()
    {
        coeff *= -1;
        return *this;
    }

    int degree()
    {
        int sum = 0;
        for (auto iter: variables)
            sum += iter.second;
        return sum;
    }
    friend std::ostream& operator<<(std::ostream &out, const monomial& monom)
    {
        if(monom.coeff > 0)
        {
            out << "+" << monom.coeff;
        }
        else
            out << monom.coeff;
        for (auto iter : monom.variables)
        {
            out << iter.first;
        if(iter.second != 1)
            out  << "^" << iter.second;
        }
        //out << std::endl;
        return out;
    }

    friend std::istream& operator>>(std::istream &in, monomial& monom)
    {
        std::string str;
        in >> str;
        monom = monomial(str.c_str());
        return in;
    }

    std::set<char> uniq_var()
    {
        std::set<char>result;
        for(auto iter: variables)
        {
            result.insert(iter.first);
        }
        return result;
    }

    bool is_zero()
    {
        if (coeff == 0)
            return true;
        else return false;
    }

    ~monomial()
    {
        variables.clear();
    }

    std::string convert() const override
    {
        std:: string result;
        if(coeff == 0)
            return result += "0";

        if(coeff > 0)
        {
            result = "+" + std::to_string(coeff);
        }
        else
            result = std::to_string(coeff);
        for(auto iter: variables)
        {
            result += iter.first;
            if(iter.second > 1)
            {
                result += "^{" + std::to_string(iter.second) + "}";
            }
        }
        return result;
    }
};