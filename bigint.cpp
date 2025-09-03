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
        assert(is_number(input));
        str = input;
    }
    BigIntStr(const std::string& input) {
        assert(is_number(input));
        str = input;
    }
    void add(u64 n) {

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
            std::cout << "c = " << c << "\n";
            c = (c - '0') % 2 + '0'; 
            std::cout << "c mod 2 = " << c << "\n";
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

    std::cout << "s = " << s.str << "\n";
    std::cout << "s2 = " << s2.str << "\n";

    std::string bin = s2.to_binary(); 
    std::cout << "s2 in binary = " << bin << "\n";


    return 0;
}
