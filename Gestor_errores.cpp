#include <iostream>
#include <array>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
#include <fstream>

using namespace std;

int error(int cod_error, std::ifstream& file, std::streampos position){
    std::streampos oldpos = file.tellg();
    file.seekg(position);
    cout << file.peek() << endl;
    file.seekg(oldpos);

    return 0;
}