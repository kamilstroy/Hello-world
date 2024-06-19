#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <fstream> 
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
using namespace std;



/*
class worki
{
private:   
public:

virtual int work(void) = 0;

};


class comandante
{private:
s1(string) command;

};
*/

/*int main(void){

std::string stroka;
system("gdb --help");
std::getline(std::cin, stroka);
//system("gdb --help");
system("cls");
std::cout<<stroka<<std::endl;
    return 0;
}*/


typedef struct koy_{
    
    string device;
    string speed;
    string interfaceHard;
    string programElf;
}koy;

vector<string> Commands;

void initial(const koy *SettingHard){
string Speed = SettingHard->speed;
string Device = SettingHard->device;
string InterFace = SettingHard->interfaceHard;
string ProgramElf = SettingHard->programElf;

Commands.push_back(" JLinkGDBServer -device " + Device + " -if " +  InterFace  + " -speed " + Speed);
Commands.push_back("arm-none-eabi-gdb " + ProgramElf);
Commands.push_back("target remote localhost:2331");
Commands.push_back("monitor reset halt");
Commands.push_back("load");
Commands.push_back("break main");
Commands.push_back("continue");

for(const auto& command : Commands){
    cout<<"Executing: " << command <<endl;
    int resuilt = system(command.c_str());
    if(resuilt != 0){
        cerr<< "Command failed" << resuilt << endl;
    }
    }
}



std::string Commandante(const char* cmd) {
    std::array<char, 10> buffer; //создаем контейнер массив на чары 128 штук
    std::string result;//строка для результирущего
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose); //смрат указатель который сам удалём динамическую память
    if (!pipe) {//если поток не открыт
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    /*try {
        std::string command = "gdb --help";
        std::string output = Commandante(command.c_str());

        std::ofstream outFile("output.txt");
        if (outFile.is_open()) {
            outFile << output;
            outFile.close();
            std::cout << "Output successfully written to output.txt" << std::endl;
        } else {
            std::cerr << "Failed to open output.txt for writing" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }*/

    koy koylar;
    koylar.device = "GD32F103VB";
    koylar.interfaceHard = "JTAG";
    koylar.programElf = " \"C:/Users/k.alyautdinov/Desktop/gd32f103_super_project/build/GD32F103_SUPER_PROJECT.elf\"";
    koylar.speed = "4000";

    initial(&koylar);

    return 0;
}
