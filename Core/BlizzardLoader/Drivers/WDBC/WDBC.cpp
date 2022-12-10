#include <string>
#include "WDBC.h"

bool WDBC::loaded = false;
std::vector<Achievement<std::string>> WDBC::m_achievement = {};
std::vector<AreaPOI<std::string>> WDBC::m_area_poi = {};
std::vector<gtChanceToMeleeCritBase> WDBC::m_gt_chance_to_melee_crit_base = {};
