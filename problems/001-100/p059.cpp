#include "lib/utility.hh"

std::vector<std::string> all_possible_keys() {
    std::vector<std::string> possible_keys;
    for (char a = 'a'; a <= 'z'; ++a) {
        for (char b = 'a'; b <= 'z'; ++b) {
            for (char c = 'a'; c <= 'z'; ++c) {
                std::string key(1, a);
                key += b;
                key += c;
                possible_keys.push_back(key);
            }
        }
    }
    return possible_keys;
}

std::string decrypt(const std::string& encrypted, const std::string& key) {
    std::string decrypted = "";
    for (size_t i = 0; i < encrypted.size(); ++i) {
        decrypted += char(encrypted[i] ^ key[i % key.size()]);
    }
    return decrypted;
}

bool makes_sense(const std::string& msg) {
    const static std::vector<std::string> common_words = {
        "the", "and", "but", "or", "him", "her"
    };

    int count = 0;
    for (const auto& w : common_words) {
        if (msg.find(w) != std::string::npos) {
            count += 1;
        }
    }

    return count > 3;
}

int main(void) {
    start_time();

    std::string encrypted_msg;
    std::ifstream file("files/p059_cipher.txt");
    std::string token;
    while (std::getline(file, token, ',')) {
        encrypted_msg += char(stoi(token));
    }

    for (const auto key : all_possible_keys()) {
        std::string decrpyted_msg = decrypt(encrypted_msg, key);

        if (makes_sense(decrpyted_msg)) {
            std::cout << "Key: " << key << std::endl;
            std::cout << "Decrypted Message: " << decrpyted_msg << std::endl;
            int tot = 0;
            for (char c : decrpyted_msg) {
                tot += c;
            }
            printf("Solution: %d\n", tot);
            break;
        }
    }

    end_time();
}
