#ifndef WINLUA_H_E_V1
#define WINLUA_H_E_V1
#include <string>
#include <vector>

class crypto {
private:
    std::string encryption_key = "WinLua is amazing ok";
    
    std::string randomize_key(std::string key) {
        std::string ret;
        
        for (int i = 0; i < key.size()) {
            int k = (int)key[i];
            ret += "\\";
            k << 3;
            ret += std::to_string(k);
        }
    }
public:
    std::string encrypt(std::string decrypted, std::string key) {
        
    }
    
    std::string decrypt(std::string encrypted, std::string key) {
        
    }
}
#endif
