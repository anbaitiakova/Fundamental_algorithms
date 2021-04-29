#include "Monom.h"
#include <list>
#include <set>

class polynomial: public TeX_convertible
{
    std::list<monomial>poly_list;

public:
    polynomial() = default;

    polynomial(const char* polinom)
    {
        char* ptr = (char*)polinom;
        while(*ptr != '\0')
        {
            poly_list.push_back(ptr);
            if (*ptr == '+' || *ptr == '-')
                ptr += 2;
            while(*ptr != ' ')
            {
                if(*ptr == '\0')
                    break;
                ptr++;
            }
            if(*ptr == '\0')
                break;
            ptr++;
        }
    }

    polynomial(const polynomial& polinom)
    {
        for(auto& iter: polinom.poly_list)
        {
            poly_list.push_back(iter);
        }
    }

    polynomial& operator=(const polynomial& polinom)
    {
        if(!poly_list.empty())
            poly_list.clear();
        for(auto& iter: polinom.poly_list)
        {
            poly_list.push_back((iter));
        }
        return *this;
    }

    polynomial& operator+=(const monomial& monom)
    {
        bool flag = false;
        for(auto& iter: poly_list)
        {
            try
            {
                iter += monom;
                flag = true;
            }
            catch(const char* ex)
            {
                std::cerr << ex << '\n';
            }
        }
        if (!flag)
            poly_list.push_back(monom);
        return *this;
    }

    polynomial operator+(const monomial& monom) const
    {
        return polynomial(*this) += monom;
    }

    polynomial& operator+=(const polynomial& polinom)
    {
        for (auto& iter: polinom.poly_list)
        {
            *this += iter;
        }
        return *this;
    }

    polynomial operator+(const polynomial& polinom) const
    {
        return polynomial(*this) += polinom;
    }

    polynomial& operator-=(const monomial& monom)
    {
        bool flag = false;
        for(auto& iter: poly_list)
        {
            try
            {
                iter -= monom;
                flag = true;
            }
            catch(const char* ex)
            {
                std::cerr << ex << '\n';
            }
        }
        if (!flag)
        {
            monomial tmp = monom;
            tmp.change();
            (*this).poly_list.push_back(tmp);
        }
        return *this;
    }

    polynomial operator-(const monomial& monom) const
    {
        return polynomial(*this) -= monom;
    }

    polynomial& operator-=(const polynomial& polinom)
    {
        for (auto& iter: polinom.poly_list)
        {
            *this -= iter;
        }
        return *this;
    }

    polynomial operator-(const polynomial& polinom) const
    {
        return polynomial(*this) -= polinom;
    }

    polynomial& operator*=(const monomial& monom)
    {
        for(auto& iter: poly_list)
            iter *= monom;
        is_repeated(*this);
        return *this;
    }

    polynomial operator*(const monomial& monom) const
    {
        return polynomial(*this) *= monom;
    }

    polynomial& operator*=(const polynomial& polinom)
    {
        polynomial res;
        for(auto& iter: poly_list)
        {
            for(auto& iter2: polinom.poly_list)
                res.poly_list.push_back(iter * iter2);
        }
        is_repeated(res);
        *this = res;
        return *this;
    }

    polynomial operator*(const polynomial& polinom) const
    {
        return polynomial(*this) *= polinom;
    }

    polynomial& operator/=(const char& derivative)
    {
        for(auto& iter: poly_list)
        {
            iter /= derivative;
        }
        return *this;
    }

    polynomial operator/(const char& derivative) const
    {
        return polynomial(*this) /= derivative;
    }

    polynomial& operator/=(const char* mix_der)
    {
        char* ptr = (char*)mix_der;
        char derivative;
        while(*ptr != '\0')
        {
            derivative = *ptr;
            *this /= derivative;
            ptr++;
            if(*ptr == ' ')
                ptr++;
        }
        is_repeated(*this);
        return *this;
    }

    polynomial operator/(const char* mix_der) const
    {
        return polynomial(*this) /=  mix_der;
    }

    bool operator==(const polynomial& polinom) const
    {
        if (poly_list.size() != polinom.poly_list.size())
            return false;
        auto iter = poly_list.begin();
        auto it = polinom.poly_list.begin();
        while(iter != poly_list.end() || it != polinom.poly_list.end())
        {
            if ((*iter) != (*it))
                return false;
            iter++;
            it++;
        }
        return true;
    }

    bool operator!=(const polynomial& polinom) const
    {
        return !(*this == polinom);
    }

    polynomial& is_repeated(polynomial& polinom)
    {
        polynomial poly;
        monomial monom;
        for(auto iter = polinom.poly_list.begin(); iter != polinom.poly_list.end(); iter++)
        {
            auto it = iter;
            it++;
            try
            {
                monom = (*iter) + (*it);
                if(!monom.is_zero())
                    poly.poly_list.push_back(monom);
                iter++;
            }
            catch(const char* ex)
            {
                std::cerr << ex << '\n';
                monom = *iter;
                if(!monom.is_zero())
                    poly.poly_list.push_back(monom);
            }
        }
        polinom = poly;
        return polinom;
    }

    friend bool uniformity(const polynomial& polinom)
    {
        auto iter = polinom.poly_list.begin();
        auto it = iter++;
        while(iter != polinom.poly_list.end())
        {
            if(monomial(*iter).degree() != monomial(*it).degree())
                return false;
            iter++;
            it++;
        }
        return true;
    }

    friend bool harmonicity(polynomial& polinom)
    {
        polynomial poli;
        std::set<char>set_of_var;
        polynomial list_is_zero;
        for(monomial iter: polinom.poly_list)
        {
            for(auto it: iter.uniq_var())
                set_of_var.insert(it);
        }
        for(auto item: set_of_var)
        {
            polinom /= item;
            polinom /= item;
            poli += polinom;
        }
        list_is_zero.poly_list.push_back(monomial("0"));
        if(poli == list_is_zero)
            return true;
        return false;
    }

    friend std::ostream& operator<<(std::ostream &out, const polynomial& polinom)
    {
        for (monomial iter : polinom.poly_list)
            out << iter;
        return out;
    }

    friend std::istream& operator>>(std::istream &in, polynomial& polinom)
    {
        std::string string;
        getline(in, string, '\n');
        polinom = polynomial(string.c_str());
        return in;
    }

    ~polynomial()
    {
        poly_list.clear();
    }
    std::string convert() const override
    {
        std::string result;
        result += "(";
        for (monomial monom: poly_list)
            result += monom.convert();
        result += ")";
        return result;
    }
};