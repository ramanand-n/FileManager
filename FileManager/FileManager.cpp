#include <string>
#include <string_view>
#include <cstddef>
#include <iostream>
#include <filesystem>
using  namespace std;
namespace fs = filesystem;

int main()
{
    int choice;
    string Currentpath = "D:\\";

    cout << "1. List Files\n2. Change Directory\n3. Copy Files\n4. Move Files\n5. Delete Files";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        for (const auto& entry : fs::directory_iterator(Currentpath))
        {
           string StringPath = entry.path().generic_string();
            //std::string stringpath = entry.path();
           // stringpath.substr(stringpath.find("/") + 1);
            cout << StringPath << endl;
           
        }
        break;
    }
}