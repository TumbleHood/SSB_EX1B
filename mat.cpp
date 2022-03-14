#include "mat.hpp"
#include <string>
#include <stdexcept>

using namespace ariel;
using namespace std;

const int MAX_ASCII = 126, MIN_ASCII = 33;

string alternate(char c1, char c2, int ctr){
    string s;
    char cur = c1;
    while (ctr > 0){
        s += cur;
        cur == c1 ? cur = c2 : cur = c1;
        ctr--;
    }
    return s;
}

string reverse(string s){
    for (int i = 0; i < s.length() / 2; i++){
        char temp = s[i];
        s[i] = s[s.length() - i - 1];
        s[s.length() - i - 1] = temp;
    }
    return s;
}

string matHelper(int width, int height, char c1, char c2, int i, int j){
    if (2 * j > width){
        j--;
    }
    string prefix = alternate(c1, c2, j);
    string suffix = reverse(prefix);
    char cur = j % 2 == 0 ? c1 : c2;
    string s = prefix + string(width - 2 * j, cur) + suffix + '\n';
    if (i == height){
        return s;
    }
    return s + matHelper(width, height, c1, c2, i + 2, j + 1) + s;
}

string ariel::mat(int width, int height, char c1, char c2){
    if (width % 2 == 0 || height % 2 == 0){
        throw invalid_argument("Mat size is always odd");
    }
    if (width <= 0 || height <= 0){
        throw invalid_argument("Mat scales are always positive");
    }
    if (c1 < MIN_ASCII || c1 > MAX_ASCII || c2 < MIN_ASCII || c2 > MAX_ASCII){
        throw invalid_argument("Invalid characters");
    }
    return matHelper(width, height, c1, c2, 1, 0);
}