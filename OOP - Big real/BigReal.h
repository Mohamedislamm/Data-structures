#ifndef JIMMY_BIGREAL_H
#define JIMMY_BIGREAL_H
#include <string>

using namespace std;

class BigReal{
private:
    bool dot;
    char sign = '+';
    string integer ,fraction;

public:
    static bool isValid(const string& real);
    BigReal();
    explicit BigReal(string real);
    bool operator< (BigReal& nextReal);
    bool operator> (BigReal& anotherReal);
    bool operator== (BigReal& nextReal);
    BigReal operator+ (BigReal& other);
    void padding(BigReal& other);
    BigReal operator- (BigReal& other);
    friend ostream& operator << (ostream& out, const BigReal& num);
    friend istream& operator >> (istream& in, BigReal& num);



};

#endif //JIMMY_BIGREAL_H
