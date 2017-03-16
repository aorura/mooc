#include <iostream>
#include <cstring>

//#define DEBUG 0

using namespace std;

class Str
{
public:
    char *str;
    int size;
    int *ref;

    Str(char *ca) {
        size = strlen(ca);
        str = new char[strlen(ca)+1];
        strcpy(str,ca);
        ref = new int;
        *ref = 1;
    }

    void incRef() {
        (*ref)++;
    }
 
    void decRef() {
        (*ref)--;
    }

    void release() {
		if (str != nullptr && ref != nullptr) {
			if (--(*ref) <= 0) {
				delete[] str;
				delete ref;
			}
		}
    }

    char* getStr() {
        return str;
    }
};
    
class String
{
private :
    Str *str;

public :
    String() : str(nullptr) { }
    String(char *ca) {
        str = new Str(ca);
    }

    String(const String& s) : str(s.str) {
        if (str != nullptr) 
            str->incRef();
    }

    ~String() {
        if (str != nullptr)
        	str->release();
    }

    String& operator=(const String& right) {
        // Increment a right operand reference count.
         right.str->incRef();

		str->release();

        str = right.str;
    }

    friend ostream& operator<<(ostream& os, const String& s);
};

ostream& operator<<(ostream& os, const String& s)
{
    if (s.str == nullptr) {
        cout << "String is null" << endl;
    } else {
        os << s.str->getStr() << endl;
    }

    return os;
}

int main()
{
    // 1단계. 생성자, 소멸자, 화면 출력
    String s1 = "hello";
    cout << s1 << endl;
    // 2단계. 복사 생성자
    String s2 = s1;
    cout << s2 << endl;
    // 3단계. 대입연산자
    String s3 = "student";
    s3 = s1;
    cout << s3 << endl;
    // 4단계. 자신과의 대입
    s1 = s1;
    cout << s1 << endl;
    // 5단계. 디폴트 생성자
    String s4;
    cout << s4 << endl;
}


