#include <iostream>

std::string center(std::string str, int padding);
void draw_line(int place, int padding, int height);

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "usage: arch <height>";
        return 1;
    }
    int height = std::stoi(argv[1]);

    for (int i = 1; i < height + 1; i++) {
        draw_line(i, height-i, height);
    }

    return 0;
}
/*
 *      *         1 - place
 *      ***       2 - place
 *      *****     3 - place
 *      *******   4 - place
 *
 */
void draw_line(int place, int padding, int height) {
    if (place < 1) throw std::runtime_error("place less than 1");

    if (place == 1) {
        std::cout << center("*", padding) << std::endl;
        return;
    }
    //    *
    //   ***     -> 3 - 2 = 1
    //  ** **   -> 5 - 4 = 1
    // **   ** -> 7 - 4 = 3
    // 0123456
    //  ^^^^^
    // 
    //
    std::string result = "";
    int len = place + (place - 1);

    for (int i = 0; i < len; i++) {
                            //     7 / 2 = 4 <
        if (height / 2.5  < place) {   
    
            if (len < 3) {
                result += "*";
                continue;
            }

            int from = (len - 1) / 3;
            if (from <= i && i < len - from) {
                result+=" ";
                continue;
            }

            result += "*";
            continue;
        }
        result += "*";
    }

    std::cout << center(result, padding) << std::endl;
}

/* 
 *  [*]        -> [  *  ]
 *  [***]      -> [  ***  ]
 *  [*****]    -> [  *****  ]
*/
std::string center(std::string str, int padding) {
    std::string result = "";

    for (int i = 0; i < padding; i++) {
        result+=" ";
    }

    result+=str;

    for (int i = 0; i < padding; i++) {
        result+=" ";
    }

    return result;
}

