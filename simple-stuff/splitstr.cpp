//
//  main.cpp
//  Splitstr
//
//  Created by Francis Johny on 10/05/15.
//  Copyright (c) 2015 Vyfrankens. All rights reserved.
//

#include <iostream>
#include <string>
int main(int argc, char const *argv[])
{
    std::string s = "grep hello || hello ||| hi";
    std::string delimiter = "|";
    
    size_t pos = 0, pos1 = 0, flag = 0;
    std::string token, token1;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        pos1 = s.find(delimiter, pos + delimiter.length());
        while (pos1 == pos+1){
            pos = pos1;
            pos1 = s.find(delimiter, pos + delimiter.length());
            flag = 1;
        }
        if (flag) {
            token = s.substr(0, pos1);
            std::cout << token << std::endl;
            if (pos1 > s.length())
                exit(0);
            s.erase(0, pos1 + delimiter.length());
        }
        else{
            token = s.substr(0, pos);
            std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
        }
        
    }
    std::cout << s << std::endl;
    return 0;
}

