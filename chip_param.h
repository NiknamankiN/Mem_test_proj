#ifndef CHIP_PARAM_H
#define CHIP_PARAM_H

#include <string>
using namespace std;

struct chip_param{
    void set_all(string name_1, int size_1, float S_1, float S_1_1, float S_2,
                 float S_2_2, float S_3, float S_3_3, float S_4, float S_4_4, float S_5, float S_5_5)
    {
        name = name_1;
        size = size_1;
        CR[0] = S_1;
        CR_dev[0] = S_1_1;
        CR[1] = S_2;
        CR_dev[1] = S_2_2;
        CR[2] = S_3;
        CR_dev[2] = S_3_3;
        CR[3] = S_4;
        CR_dev[3] = S_4_4;
        CR[4] = S_5;
        CR_dev[4] = S_5_5;
    }
    string name = "My_name";
    int size = 0;
    float CR[5] = {0,0,0,0,0};
    float CR_dev[5] = {4,4,4,3,3};
};

#endif // CHIP_PARAM_H
