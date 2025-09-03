#include <iostream>
#include <string>
#include <assert.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

struct BigInt {
    u8* data;
    u64 bit_count;
    u64 bit_capacity;
};

struct BigIntStr {
    std::string str;
    BigIntStr(u64 n) {
        str = std::to_string(n);
    }
    BigIntStr(const char* input) {
        assert(is_number(input) && "input is not a number");
        str = input;
    }
    BigIntStr(const std::string& input) {
        assert(is_number(input));
        str = input;
    }

    void add(u64 n) {
        std::string number = std::to_string(n); 
    }

    void add(const char* n) {
        std::string sn = n;
        add(sn);
    }

    void add(const std::string& n) {
        u64 carry = 0;
        int i = str.length() - 1;
        for (int j = n.length() - 1; j >= 0; j--) {
            char str_digit = '0';
            bool in_range =  i >= 0;
            char c = n[j];

            if (in_range) str_digit = str[i];

            char digit_sum = c - '0' + str_digit + carry;
            carry = 0;

            if (digit_sum > '9') {
                digit_sum -= 10;
                carry = 1;
            }
            if (in_range) {
                str[i] = digit_sum;
            } 
            else {
                str = digit_sum + str; 
            }

            i--;
        }
    }

    void add(const BigIntStr& n) {
        add(n.str);
    }

    void halve() {
        u64 additive = 0;
        u64 next_additive = 0;
        for (char& c : str) {
            additive = next_additive;
            if ((c - '0') % 2 == 1) next_additive = 5; 
            else next_additive = 0;
            c = (c - '0') / 2 + additive + '0';
        }
        for (const char& c : str) {
            if (c == '0') str = str.substr(1, str.size() - 1);
        }
    }

    std::string to_binary() {
        std::string bin = "";
        BigIntStr copy = str;
        while (true) {
            char c = copy.str[copy.str.size() - 1];
            c = (c - '0') % 2 + '0'; 
            bin = c + bin;
            copy.halve(); 
            if (copy.str.size() == 0 || 
                copy.str.size() == 1 && copy.str[0] == '0') break;
        }
        return bin;
    }

    static bool is_number(const std::string& str) {
        for (const char& c : str) {
            if (c < '0' || c > '9') return false;
        }
        return true;
    }

};

int main() {
    //BigInt n = 100;
    BigIntStr s = 100;
    BigIntStr s2 = "10";
    s2.add("234");

    std::cout << "s = " << s.str << "\n";
    std::cout << "s2 = " << s2.str << "\n";

    std::string bin = s2.to_binary(); 
    std::cout << "s2 in binary = " << bin << "\n";


    return 0;
}
