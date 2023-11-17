#include <iostream>
#include <fstream>
#include <json/json.h>

void writeToFile(const std::string &filename, const std::string &data)
{
    std::ofstream outputFile(filename);

    if (outputFile.is_open())
    {
        outputFile << data;

        outputFile.close();

        std::cout << "Data successfully written to " << filename << std::endl;
    }
    else
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

void createFiles(const Json::Value &root)
{
    for (unsigned int i = 0; i < root["Names"].size(); i++)
    {
        writeToFile(root["Names"][i].asString() + ".c", root[root["Names"][i].asString()].asString());
    }
}

void listprograms(const Json::Value &root)
{
    for (unsigned int i = 0; i < root.size(); i++)
    {
        std::cout << root[std::to_string(i)]["ID"].asString() << " : " << root[std::to_string(i)]["Name"].asString() << std::endl;
    }
    std::cout << "\n\n";
}

int main()
{
    const std::string filename = "data.json";

    std::ifstream fileStream(filename, std::ifstream::binary);
    if (!fileStream.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    JSONCPP_STRING errs;

    if (!Json::parseFromStream(readerBuilder, fileStream, &root, &errs))
    {
        std::cerr << "Error parsing JSON: " << errs << std::endl;
        return 1;
    }

    listprograms(root);

    int inchoice;
    std::cout << "Enter the program you require: ";
    std::cin >> inchoice;
    std::string choice = std::to_string(inchoice - 1);
    std::cout << "Creating: " << root[choice]["Name"].asString() << "\nConfirm? [y/n]";

    char ans;
    std::cin >> ans;

    if (ans == 'y')
    {
        createFiles(root[choice]);
        std::cout << "Completed!";
    }
    else
    {
        std::cout << "Cancelled!";
    }

    return 0;
}
