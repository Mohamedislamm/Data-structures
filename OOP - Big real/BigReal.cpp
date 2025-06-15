#include "BigReal.h"
#include <regex>

//default constructor
BigReal::BigReal() { //makes default +0.0
    sign = '+';
    integer = "0";
    fraction = "0";
}
BigReal::BigReal(string real) {
    if (regex_match(real, regex("[+-]?\\d*\\.?\\d*"))) { //check if valid input by matching regex
        if (real[0] == '-'|| real[0] == '+'){
            sign = real[0];
            real = real.substr(1);  // Remove the negative sign from the beginning
        }

        int dotPos = real.find('.');
        if (dotPos != string::npos) {
            integer = real.substr(0, dotPos);
            fraction = real.substr(dotPos + 1);
        } else {
            integer = real;
            fraction = "0";  // Set fraction to "0" when there's no dot
        }
    } else {
        cout << "Invalid Input" << endl;
    }
}


bool BigReal::isValid(const string& real) {
    return regex_match(real, regex("[+-]?\\d*.?\\d+")); //check if valid input by matching regex
}

void BigReal::padding(BigReal &other) {
    int diff = abs((int)integer.size() - (int)other.integer.size()); //to find difference in size in integer part
    if (integer.size() > other.integer.size()) {  //add zeros to the smaller number
        for (int i = 0; i < diff; i++) {
            other.integer = "0" + other.integer;
        }
    } else if (integer.size() < other.integer.size()) {
        for (int i = 0; i < diff; i++) {
            integer = "0" + integer;
        }
    }
    diff = abs((int)fraction.size() -(int) other.fraction.size()); //to find difference in size in fraction part
    if (fraction.size() > other.fraction.size()) {
        for (int i = 0; i < diff; i++) {
            other.fraction += "0";
        }
    } else if (fraction.size() < other.fraction.size()) {
        for (int i = 0; i < diff; i++) {
            fraction += "0";
        }
    }

}


BigReal BigReal::operator+(BigReal &other) {    //reference to not waste storage
    BigReal result("");
    int carry = 0;
    padding(other); //to make both numbers the same size
    if (sign == other.sign) { //if both numbers have the same sign
        result.sign = sign;


        // Adding the fraction part
        for (int i = fraction.size() - 1; i >= 0; i--) {
            int sum = (fraction[i] - '0') + (other.fraction[i] - '0') + carry; //adds both digits and the carry
            result.fraction = to_string(sum % 10) + result.fraction; //to add the remainder to the result
            carry = sum / 10;
        }

        // Adding the integer part
        for (int i = integer.size() - 1; i >= 0; i--) {
            int sum = (integer[i] - '0') + (other.integer[i] - '0') + carry;
            result.integer = to_string(sum % 10) + result.integer;
            carry = sum / 10;
        }
        if (carry != 0) {
            result.integer = to_string(carry) + result.integer;

        }

    } else { //if both numbers have different signs
        if (sign == '-') { //if the first number is negative
            result = other + *this; // Addition since first number is negative
        } else { //if the second number is negative
            other.sign = '+';
            result = *this - other;
        }
    }

    return result;
}

BigReal BigReal::operator-(BigReal &other) {
    BigReal result("");
    int borrow = 0;
    padding(other); //to make both numbers the same size
    if (*this > other || *this == other) {
        if (sign == other.sign) {
            result.sign = sign;
            // Subtracting the fraction part
            for (int i = fraction.size() - 1; i >= 0; i--) {
                int diff = (fraction[i] - '0') - (other.fraction[i] - '0') - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.fraction = to_string(diff) + result.fraction;
            }

            // Subtracting the integer part
            for (int i = integer.size() - 1; i >= 0; i--) {
                int diff = (integer[i] - '0') - (other.integer[i] - '0') - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.integer = to_string(diff) + result.integer;
            }
        }
        else{
            if(sign == '+'){
                other.sign = '+';
                result = *this + other;
            }
            else{
                sign= '+';

                result =  *this + other;
                result.sign='-';
            }
        }
    }
    else{
        if (sign == other.sign){
            if (sign == '+') {
                swap(other, *this);
                for (int i = fraction.size() - 1; i >= 0; i--) {
                    int diff = (fraction[i] - '0') - (other.fraction[i] - '0') - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.fraction = to_string(diff) + result.fraction;
                }

                // Subtracting the integer part
                for (int i = integer.size() - 1; i >= 0; i--) {
                    int diff = (integer[i] - '0') - (other.integer[i] - '0') - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.integer = to_string(diff) + result.integer;
                }
                result.sign='-';
            }
            else{
                result = other - *this;
            }
        }
        else{
            if(sign == '+'){
                other.sign = '+';
                result = *this + other;
            }
            else{
                sign='+';
                result = *this + other;
                result.sign = '-';

            }
        }


    }

    return result;
}

bool BigReal::operator<(BigReal& nextReal) {
    if (integer.size() > nextReal.integer.size()) return false; //if the first number is bigger than the second one
    else if (integer.size() < nextReal.integer.size()) return true;

    else if (integer.size() == nextReal.integer.size())
    {
        for (int i = 0; i < integer.size(); i++)
        {
            if (integer[i] > nextReal.integer[i])  return false; //if both numbers are equal in size , start comparing each digit
            else if (integer[i] < nextReal.integer[i]) return true;
        }
    }
    if (fraction.size() > nextReal.fraction.size()) return false; //if integers are the same , check decimal
    else if (fraction.size() < nextReal.fraction.size()) return true;

    else if (fraction.size() == nextReal.fraction.size())
    {
        for (int i = 0; i < fraction.size(); i++)
        {
            if (fraction[i] > nextReal.fraction[i])  return false;
            else if (fraction[i] < nextReal.fraction[i]) return true;
        }
    }
    return false;
}

bool BigReal::operator>(BigReal& nextReal){
    if (integer.size() > nextReal.integer.size()) return true; //if the first number is bigger than the second one
    else if (integer.size() < nextReal.integer.size()) return false;

    else if (integer.size() == nextReal.integer.size())
    {
        for (int i = 0; i < integer.size(); i++)
        {
            if (integer[i] > nextReal.integer[i])  return true; //if both numbers are equal in size , start comparing each digit
            else if (integer[i] < nextReal.integer[i]) return false;
        }
    }
    if (fraction.size() > nextReal.fraction.size()) return true; //if integers are the same , check decimal
    else if (fraction.size() < nextReal.fraction.size()) return false;

    else if (fraction.size() == nextReal.fraction.size())
    {
        for (int i = 0; i < fraction.size(); i++)
        {
            if (fraction[i] > nextReal.fraction[i])  return true;
            else if (fraction[i] < nextReal.fraction[i]) return false;
        }
    }
    return true;
}

bool BigReal::operator==(BigReal& nextReal) {
    if (sign == nextReal.sign && integer == nextReal.integer && fraction == nextReal.fraction) return true;
    else return false;
}

ostream &operator<<(ostream &COUT, const BigReal & num) { //overloading << operator in cout
    if (num.sign == '-') COUT << num.sign; //to avoid printing + sign
    COUT << num.integer<< "." << num.fraction;
    return COUT;

}

istream &operator>>(istream &in, BigReal &num) {
    string real;
    in >> real;
    num = BigReal(real);
    return in;

}



