#ifndef WINLUA_H_E_V1
#define WINLUA_H_E_V1
#include <string>
#include <vector>
#include <sstream>


//encryption class, created by Cyberhound#5672

class crypto {
private:
    std::string encryption_key = "thisreally doesnt matteratall so its finewhat you setthisto";
    int encryption_seed = 9486048;
    
    /*
    i highly recommend you make your own encryption seed and encryption key.
    probably hide the string (or obfusticate it or something) and i highly
    recommend changing the seed. note: if your gonna use this encryption, pls
    credit me, and hint hint this would be amazing encryption if you randomized
    the seed. (you can use rand() to do so, but warning, decryption has to have
    the seed too clearly).
    */
    
    std::vector<std::string> split(const std::string s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
public:
    std::string encrypt(std::string decrypted, std::string key = "") {
        if (key == "") {
            key = encryption_key;
        }
        
        std::string ret;
        
        for (int i = 0; i < decrypted.size(); i++) {
            int mod = (int)decrypted[i]; //converts char to int
            ret += "\\"; //push back \ so we can tell what size each bit of info is in decryption
            mod ^= (mod * encryption_seed);
            
            for (int i = 0; i < key.size(); i++) {
                int enc_modk = (int)key[i];
                int enc_orig = enc_modk;
                enc_modk ^= encryption_seed;
                
                mod ^= enc_modk;
                mod += enc_orig;
            }
            
            ret += std::to_string(mod);
        }
        
        return ret;
    }
    
    std::string decrypt(std::string encrypted, std::string key = "") {
        if (key == "") {
            key = encryption_key;
        }
        //decryption will eventually be developed, im at school
        //so for now ill return nothing until i develop it, i need
        //time i dont have sorry
        return "";
    }
};
#endif
