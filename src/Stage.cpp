#include "Stage.h"


/**********************************************
 *  StageInfo
 **********************************************/

StageInfo::StageInfo()
{
    /*
     * (0, 0, 0) -> a random generated stage
     */

    this->init_map();
}


StageInfo::~StageInfo()
{
    for (auto i=this->maps.begin(); i!=this->maps.end(); ++i)
        delete i->second;
}


void StageInfo::set(unsigned int series, unsigned int level,
                    unsigned int sub_level)
{
    this->series = series;
    this->level = level;
    this->sub_level = sub_level;
    this->changed = true;
}


bool StageInfo::check(unsigned int series, unsigned int level,
           unsigned int sub_level) const
{
    if (this->series != series)
        return false;
    else if (this->level != level)
        return false;
    else if (this->sub_level != sub_level)
        return false;
    return true;
}


bool StageInfo::is_random() const
{
    if (!(this->series || this->level || this-> sub_level))
        return true;
    return false;
}


StageMap* StageInfo::get_map()
{
    const auto key = std::make_tuple(this->series, this->level, this->sub_level);
    return this->get_map(key);
}


StageMap* StageInfo::get_map(std::tuple<int, int, int> key)
{
    auto val = this->maps.find(key);
    if (val == this->maps.end())
        return NULL;

    return val->second;
}


void StageInfo::init_map()
{
	this->maps[std::make_tuple(1, 1, 0)] = new StageMap("stage/1-1-0.json");
}


/**********************************************
 *  StageMap
 **********************************************/

StageMap::StageMap(std::string path)
{
    /*
     * path: file path to load
     */

    std::fstream f(path, std::ios::in);
    Json::Value root;

    f >> root;
    for (auto i=0; i<root["map"].size(); ++i)
    {
        for (auto j=0; j<root["map"][i].size(); ++j)
        {
            this->data[i][j] = root["map"][i][j].asInt();
        }
    }
}
