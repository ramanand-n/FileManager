#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <windows.h>
using  namespace std;
namespace fs = filesystem;

class CopyException
{
public:
    const char* what()
    {
        return "Error in  file copying";
    }
};

class MoveException
{
public:
    const char* what()
    {
        return " move operation failed.";
    }
};

bool IsDirectory(string source)
{
    fs::path sourceFile(source);
    if (fs::is_directory(sourceFile))
        return true;
    return false;
}

int main()
{
    int choice, result;
    bool IsValidDirectory=false;
    string Currentpath = "D:\\";
    string NextDirectory,Source,Target,copyCommand, moveCommand,deleteCommand,  temperoryPath;
    string SubDirectory;
    fs::path sourceFile{};
    fs::path targetParent{}, target{}, DeleteLocation{};
        
    cout << "1. List Files\n2. Change Directory\n3. Copy Files\n4. Move Files\n5. Delete Files";
    cout << "\n6. Go to previous Directory\n7.Exit";
   
    do
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "current Path: " << Currentpath << endl;
            for (const auto& entry : fs::directory_iterator(Currentpath))
            {
                string StringPath = entry.path().generic_string();
               cout << StringPath.substr(StringPath.find_last_of("/") + 1) << '\n';
            }
            break;

        case 2:
            cout << "\nNext directory to change to: ";
            cin>>NextDirectory;
                        
            for (const auto& entry : fs::directory_iterator(Currentpath))
            {
                string StringPath = entry.path().generic_string();
                SubDirectory= StringPath.substr(StringPath.find_last_of("/") + 1);
                if (SubDirectory == NextDirectory)
                {
                    IsValidDirectory = true;
                    break;
                }
                else
                    IsValidDirectory = false;
            }

            /*if (IsVaalidDirectory(temperoryPath))
            {
                Currentpath = temperoryPath;
                cout << Currentpath;
            }*/
            if(!IsValidDirectory)
                cout<<"directory did not exist";
            else
            {
                Currentpath += "\\" + NextDirectory;
                cout << endl << Currentpath;
            }

            break;

        case 3:
            cout << "Enter Source file";
            cin >> Source;
            cout << "Enter Target Directory";
            cin >> Target;
                        
            Source =  string("\"") + Source +  string("\"");
            Target =  string("\"") + Target +  string("\"");

            try
            {
                copyCommand = string("xcopy") +  string(" ") + Source +  string(" ") + Target;


                result = system(copyCommand.c_str());

                if (result == 0) {
                     cout << "Copy completed successfully." <<  endl;
                }
                else 
                {
                    CopyException e;
                     throw  e;
                }
            }
            catch( CopyException e)
            {
                cerr << "Error: " << e.what() << endl;
            }

        break;

        case 4:

            cout << "Enter Source file eg: drive:\\folder\filename : ";
            cin >> Source;
            cout << "Enter Target Directory eg: drive:\\folder\filename : ";
            cin >> Target;

            Source =  string("\"") + Source +  string("\"");
            Target =  string("\"") + Target +  string("\"");

            try
            {
                moveCommand = string("move") + string(" ") + Source +  string(" ") + Target;

                result = system(moveCommand.c_str());

                if (result == 0)
                {
                    cout << "move completed successfully." << endl;
                }
                else
                {
                    MoveException e;
                    throw  e;
                }
            }
            catch(MoveException ex)
            {
                cerr << "Error: " << ex.what() << endl;
            }
        break;

        case 5:
            cout << "Enter location of file to delete eg: drive:\\folder\filename : ";
            cin >> Source;
            
            if (IsDirectory(Source))
            {
                deleteCommand = string("rmdir") +  string(" ") + Source +  string(" ");
                system(deleteCommand.c_str());
            }
            
            else
            {
                if (Source[0] == 'D')
                {
                    deleteCommand = string("cd D:");
                    system(deleteCommand.c_str());

                    Source.erase(0, 3);
                    deleteCommand = string("del") + string(" ") + Source + string(" ");
                    result=system(deleteCommand.c_str());

                    if (result == 0)
                    {
                        cout << "Directory Deletion completed." << endl;
                    }
                    else
                    {
                       cerr<<"deletion failed";
                    }
                    
                }
                else if (Source[0] == 'C')
                {
                    deleteCommand = string("cd C:");
                    system(deleteCommand.c_str());

                    Source.erase(0, 3);
                    deleteCommand = string("del") +  string(" ") + Source +  string(" ");
                    result=system(deleteCommand.c_str());
                }
               
            }
            break;

        case 6:
            Currentpath = Currentpath.substr(0, Currentpath.find_last_of("\\"));
            cout << Currentpath;
        break;

        case 7:
            break;

        default:
            cout << "invalid choice";
            break;
        }

    } while (choice != 7);

    return 0;
}