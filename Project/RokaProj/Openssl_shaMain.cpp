#include "pch.h"

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
size_t GetHash()
{
	return 0;
}
struct tFileTimeStemp
{

};
vector<std::string> FileNames;
rokaStl::RBT<unsigned char*, char*> ScriptTimeStemps;
char* testchar;

int main()
{
    {
        std::string str = "hello";
        size_t lenth = str.length();
        testchar = new char[lenth+1];
        memset(testchar, '\0', lenth+1);
        str.copy(testchar, lenth+1);
    }
    std::cout << testchar << std::endl;
    const path directory_path = "..\\Script\\";
    
    // Iterate over the files in the directory
    for (const auto& entry : directory_iterator(directory_path))
    {
        if (is_regular_file(entry.path()))
        {
            string filename = entry.path().filename().string();
            string extension = entry.path().filename().extension().string();
            if (extension.compare(".cpp") == false || extension.compare(".h")==false)
            {
                std::string hashKey = sha256(filename);
                char* cKey = str2pchar(hashKey);
                const file_time_type last_update = last_write_time(entry.path());
                // Convert to a time_t (if needed)
                std::time_t lastWriteTimeT = decltype(last_update)::clock::to_time_t(last_update);
                // Convert to a local time string
                std::string lastWriteTimeString = std::asctime(std::localtime(&lastWriteTimeT));
                size_t tslenth = lastWriteTimeString.size();
                char* cValue = str2pchar(lastWriteTimeString);

                FileNames.push_back(filename);
                ScriptTimeStemps.insert(std::make_pair((unsigned char*)cKey, cValue));
            }
        }
    }
    //map에 저장한 key : hash , value : timestemp 출력해보며 Test
    for (auto itr = ScriptTimeStemps.begin(); itr != ScriptTimeStemps.end(); itr++)
    {
        std::cout << "Key: ";
        unsigned char* key = itr.GetKey();
        size_t len = strlen((const char*)key);
        std::cout <<itr.GetKey() << " Value: " << itr.GetData();
    }

    //filename 으로 map
 
	SHA256_CTX shaContext;
	SHA256_Init(&shaContext);
	const char* txt = "test";
	size_t len = strlen(txt);
	SHA256_Update(&shaContext, txt, len);

	unsigned char result[SHA256_DIGEST_LENGTH] = {};
	SHA256_Final(result,&shaContext);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        std::cout << hex << setw(2) << setfill('0') << (int)result[i];
    }
}