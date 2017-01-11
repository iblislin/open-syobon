#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

#include "json/json.h"

#ifndef STAGE_H
#define STAGE_H

#define STAGE_MAP_X 1001
#define STAGE_MAP_Y 17


class StageMap
{
public:
    StageMap(std::string path);

    std::array<std::array<unsigned int, STAGE_MAP_X>, STAGE_MAP_Y> data;
};


class StageInfo
{
public:
    unsigned int series    = 1;
    unsigned int level     = 1;
    unsigned int sub_level = 0;
    std::map<std::tuple<int, int, int>, StageMap*> maps;

    bool changed = false;

    StageInfo();
    ~StageInfo();

    void set(unsigned int series, unsigned int level, unsigned int sub_level);
    bool check(unsigned int series, unsigned int level,
               unsigned int sub_level) const;

    bool is_random() const;

    StageMap* get_map();
    StageMap* get_map(std::tuple<int, int, int>);

private:
    void init_map();
};

#endif  /* ifndef STAGE_H */
