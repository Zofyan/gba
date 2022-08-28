//
// Created by Sofyan on 25/08/2022.
//


#include "doctest/doctest.h"

int main(int argc, char** argv){
    doctest::Context context(argc, argv);
    int res = context.run();
    if(context.shouldExit()){
        return res;
    }

    int client_stuff_return_code = 0;

    return res + client_stuff_return_code;
}
