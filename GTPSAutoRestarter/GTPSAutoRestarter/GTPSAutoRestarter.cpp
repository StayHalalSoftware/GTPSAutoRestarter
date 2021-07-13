/**********************************************************************************
*

    Simple Growtopia Private Server Auto Restarter Project
    Copyright (C) 2021 StayHalal Software

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


**********************************************************************************/

#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
string exename = "";

inline void SendConsole(const string text, const string type)
{
    cout << "[" << type << "]: " << text << endl;
}

inline bool isExists(const string name) {
    ifstream f(name.c_str());
    return f.good();
}

inline void autoRestarter(const string exe_name)
{
    system(("start /w " + exe_name).c_str());
    autoRestarter(exe_name);
}

int main()
{
    SendConsole("Simple GTPS Auto Restarter by StayHalal#8705", "INFO");
    SendConsole("Reading configuration file", "WARN");
    json j;
    ifstream read("config.json");
    if (read.is_open())
    {
        read >> j;
        exename = j["exe_name"].get<string>();
        SendConsole("Configuration file loaded, the current file target is file target is " + exename, "INFO");
        if (isExists(exename))
        {
            autoRestarter(exename);
        }
        else
        {
            SendConsole("The target file is not found, make sure the file is exist", "ERROR");
            system("pause");
            exit(0);
        }
    }
    else
    {
        SendConsole("Unable to load configuration file, press any key to exit", "ERROR");
        system("pause>nul");
        exit(0);
    }
    return 0;
}