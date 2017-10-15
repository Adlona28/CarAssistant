#include <iostream>
#include <fstream>

int main() {
        std::string command = "";
        std::fstream myfile;
        myfile.open("input.txt", std::fstream::in);
        if (myfile.is_open()){
            std::string line;
            while ( getline (myfile,line)){
              command += line + "\n";
            }
            myfile.close();
            myfile.open("input.txt", std::fstream::out | std::fstream::trunc);
            myfile.close();
        }
        std::cout<< command << std::endl;
}
