#include "Stage.h"


/**********************************************
 *  StageInfo
 **********************************************/

StageInfo::StageInfo()
{
    /*
     * (0, 0, 0) -> a random generated stage
     */

    this->init_maps();
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


void StageInfo::init_maps()
{
    std::vector<std::tuple<int, int, int>> stage_list =
    {
        std::make_tuple(1, 1, 0),

        std::make_tuple(1, 2, 0),
        std::make_tuple(1, 2, 1),
        std::make_tuple(1, 2, 2),

        std::make_tuple(1, 3, 0),
        std::make_tuple(1, 3, 1),
        std::make_tuple(1, 3, 5),

        std::make_tuple(1, 4, 0),

        std::make_tuple(2, 1, 0),

        std::make_tuple(2, 2, 0),
        std::make_tuple(2, 2, 1),
        std::make_tuple(2, 2, 2),

        std::make_tuple(2, 3, 0),

        std::make_tuple(2, 4, 0),
        std::make_tuple(2, 4, 1),
        std::make_tuple(2, 4, 2),

        std::make_tuple(3, 1, 0),
    };

    auto get_path = [](std::tuple<int, int, int> tuple) -> std::string
    {
        return "stage/" +
            std::to_string(std::get<0>(tuple)) + "-" +
            std::to_string(std::get<1>(tuple)) + "-" +
            std::to_string(std::get<2>(tuple)) + ".json";
    };

    Json::Value json;
    for (auto i=stage_list.begin(); i!=stage_list.end(); ++i)
    {
        load_stage_metadata(get_path(*i), &json);
        this->maps[*i] = new StageMap(&json);
    }
}


void StageInfo::load_stage_metadata(std::string path, Json::Value *ret)
{
    std::ifstream f(path);
    if (!f.is_open())
        throw std::ios::failure("Unable to read stage file: " + path);

    f >> *ret;
    f.close();
}


unsigned int StageInfo::theme_offset() const
{
    return this->theme * 30;
}


/**********************************************
 *  StageMap
 **********************************************/

StageMap::StageMap(Json::Value *json)
{
    /* init the 2d std::array */
    for (auto i=this->data.begin(); i!=this->data.end(); ++i)
        for (auto j=i->begin(); j<i->end(); ++j)
            *j = 0;

    for (auto i=0; i<(*json)["map"].size(); ++i)
        for (auto j=0; j<(*json)["map"][i].size(); ++j)
            this->data[i][j] = (*json)["map"][i][j].asInt();
}
