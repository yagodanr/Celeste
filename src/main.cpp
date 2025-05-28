#include <iostream>
#include "logger.h"


using namespace std;


int main() {
    cout << "Message2" << endl;

    SM_ERROR("Real error");

    return 0;
}


