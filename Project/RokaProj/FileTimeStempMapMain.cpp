#include "pch.h"

typedef rokaStl::RBT<char*, char*,PCharEqual, PCharGreater, PCharLess>  rokaMap;

std::string FileLastTimeStemp(std::string _spath)
{
	const file_time_type last_update = last_write_time(_spath);
	std::time_t last_timestemp_t = decltype(last_update)::clock::to_time_t(last_update);
	std::string sTimeStemp = std::asctime(std::localtime(&last_timestemp_t));

	return sTimeStemp;
}
void ReadFileTimeStemp(rokaMap& _map,std::string _spath)
{
	for (const auto& entry : directory_iterator(_spath))
	{
		if (is_regular_file(entry.path()))
		{
			string entryPath = entry.path().string();
			string sextension = entry.path().filename().extension().string();

			if (sextension.compare(".cpp") == false 
				|| sextension.compare(".h") == false)
			{
				string sFileName = entry.path().filename().string();
				string sTimeStemp = FileLastTimeStemp(entryPath);
				char* pcFileName = str2pchar(sFileName);
				char* pcTimeStemp = str2pchar(sTimeStemp);
				_map.insert(std::make_pair(pcFileName, pcTimeStemp));
			}
		}
	}
}
bool ReWriteTimeStempCheck(rokaMap& _map)
{
	
}
rokaMap TimeStempMap;
int main()
{
	rokaMap map;
	ReadFileTimeStemp(map, "..\\Script\\");         
	ReWriteTimeStempCheck(map);
	char* TimeStemp = map[(char*)"CTestScript.h"];
}