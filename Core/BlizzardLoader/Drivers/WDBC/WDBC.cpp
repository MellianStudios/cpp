#include <iostream>
#include <fstream>
#include "WDBC.h"
#include "Config/Config.h"

bool WDBC::loaded = false;
std::vector<Achievement<std::string>> WDBC::m_achievement = {};
std::vector<AreaPOI<std::string>> WDBC::m_area_poi = {};
std::vector<gtChanceToMeleeCritBase> WDBC::m_gt_chance_to_melee_crit_base = {};

void WDBC::loadAll()
{
    if (loaded) {
        return;
    }

    loadWithStrings<Achievement<std::uint32_t>, Achievement<std::string>>("Achievement", m_achievement);
    loadWithStrings<AreaPOI<std::uint32_t>, AreaPOI<std::string>>("AreaPOI", m_area_poi);
    load<gtChanceToMeleeCritBase>("gtChanceToMeleeCritBase", m_gt_chance_to_melee_crit_base);

    loaded = true;
}

template<typename T>
void WDBC::load(const std::string &name, std::vector<T> &data)
{
    if (Config::Global::debug) {
        std::cout << "loading " << name << std::endl;
    }

    std::fstream file;

    Header header{};

    file.open(Config::Global::data_path + "/dbc/" + name + ".dbc", std::fstream::in | std::fstream::binary);

    file.read(reinterpret_cast<char *>(&header), 20);

    for (int i = 0; i < header.record_count; i++) {
        T row{};

        file.read(reinterpret_cast<char *>(&row), header.record_size);

        data.emplace_back(row);
    }
}

template<typename TDefinition, typename TFinal>
void WDBC::loadWithStrings(const std::string &name, std::vector<TFinal> &data)
{
    if (Config::Global::debug) {
        std::cout << "loading " << name << std::endl;
    }

    std::fstream file;

    Header header{};

    file.open(Config::Global::data_path + "/dbc/" + name + ".dbc", std::fstream::in | std::fstream::binary);

    file.read(reinterpret_cast<char *>(&header), 20);

    std::vector<TDefinition> rows;

    for (int i = 0; i < header.record_count; i++) {
        TDefinition row{};

        file.read(reinterpret_cast<char *>(&row), header.record_size);

        rows.emplace_back(row);
    }

    std::map<std::uint32_t, std::string> strings;

    std::uint32_t offset = 0;

    while (offset < header.string_block_size) {
        std::string value;

        std::getline(file, value, '\0');

        strings.insert({offset, value});

        offset += value.size() + 1;
    }

    for (TDefinition &row: rows) {
        TFinal final{};

        if (!strings.empty()) {
            addStrings(row, final, strings);
        }

        data.emplace_back(final);
    }

    rows = {};
}

template<typename TRaw, typename TWithStrings>
void WDBC::addStrings(
    const TRaw &raw,
    TWithStrings &with_strings,
    const std::map<std::uint32_t, std::string> &strings
)
{
    if constexpr (std::is_same_v<TRaw, AreaPOI<std::uint32_t>> && std::is_same_v<TWithStrings, AreaPOI<std::string>>) {
        with_strings.id = raw.id;
        with_strings.importance = raw.importance;
        with_strings.normal_icon = raw.normal_icon;
        with_strings.normal_icon_50 = raw.normal_icon_50;
        with_strings.normal_icon_0 = raw.normal_icon_0;
        with_strings.horde_icon = raw.horde_icon;
        with_strings.horde_icon_50 = raw.horde_icon_50;
        with_strings.horde_icon_0 = raw.horde_icon_0;
        with_strings.alliance_icon = raw.alliance_icon;
        with_strings.alliance_icon_50 = raw.alliance_icon_50;
        with_strings.alliance_icon_0 = raw.alliance_icon_0;
        with_strings.faction_id = raw.faction_id;
        with_strings.x = raw.x;
        with_strings.y = raw.y;
        with_strings.z = raw.z;
        with_strings.map_id = raw.map_id;
        with_strings.flags = raw.flags;
        with_strings.area_table_id = raw.area_table_id;
        with_strings.name_1 = raw.name_1 > 0 ? strings.at(raw.name_1) : "";
        with_strings.name_2 = raw.name_2 > 0 ? strings.at(raw.name_2) : "";
        with_strings.name_3 = raw.name_3 > 0 ? strings.at(raw.name_3) : "";
        with_strings.name_4 = raw.name_4 > 0 ? strings.at(raw.name_4) : "";
        with_strings.name_5 = raw.name_5 > 0 ? strings.at(raw.name_5) : "";
        with_strings.name_6 = raw.name_6 > 0 ? strings.at(raw.name_6) : "";
        with_strings.name_7 = raw.name_7 > 0 ? strings.at(raw.name_7) : "";
        with_strings.name_8 = raw.name_8 > 0 ? strings.at(raw.name_8) : "";
        with_strings.name_9 = raw.name_9 > 0 ? strings.at(raw.name_9) : "";
        with_strings.name_10 = raw.name_10 > 0 ? strings.at(raw.name_10) : "";
        with_strings.name_11 = raw.name_11 > 0 ? strings.at(raw.name_11) : "";
        with_strings.name_12 = raw.name_12 > 0 ? strings.at(raw.name_12) : "";
        with_strings.name_13 = raw.name_13 > 0 ? strings.at(raw.name_13) : "";
        with_strings.name_14 = raw.name_14 > 0 ? strings.at(raw.name_14) : "";
        with_strings.name_15 = raw.name_15 > 0 ? strings.at(raw.name_15) : "";
        with_strings.name_16 = raw.name_16 > 0 ? strings.at(raw.name_16) : "";
        with_strings.name_flags = raw.name_flags;
        with_strings.description_1 = raw.description_1 > 0 ? strings.at(raw.description_1) : "";
        with_strings.description_2 = raw.description_2 > 0 ? strings.at(raw.description_2) : "";
        with_strings.description_3 = raw.description_3 > 0 ? strings.at(raw.description_3) : "";
        with_strings.description_4 = raw.description_4 > 0 ? strings.at(raw.description_4) : "";
        with_strings.description_5 = raw.description_5 > 0 ? strings.at(raw.description_5) : "";
        with_strings.description_6 = raw.description_6 > 0 ? strings.at(raw.description_6) : "";
        with_strings.description_7 = raw.description_7 > 0 ? strings.at(raw.description_7) : "";
        with_strings.description_8 = raw.description_8 > 0 ? strings.at(raw.description_8) : "";
        with_strings.description_9 = raw.description_9 > 0 ? strings.at(raw.description_9) : "";
        with_strings.description_10 = raw.description_10 > 0 ? strings.at(raw.description_10) : "";
        with_strings.description_11 = raw.description_11 > 0 ? strings.at(raw.description_11) : "";
        with_strings.description_12 = raw.description_12 > 0 ? strings.at(raw.description_12) : "";
        with_strings.description_13 = raw.description_13 > 0 ? strings.at(raw.description_13) : "";
        with_strings.description_14 = raw.description_14 > 0 ? strings.at(raw.description_14) : "";
        with_strings.description_15 = raw.description_15 > 0 ? strings.at(raw.description_15) : "";
        with_strings.description_16 = raw.description_16 > 0 ? strings.at(raw.description_16) : "";
        with_strings.description_flags = raw.description_flags;
        with_strings.world_state_id = raw.world_state_id;
        with_strings.world_map_link = raw.world_map_link;
    } else if constexpr (
        std::is_same_v<TRaw, Achievement<std::uint32_t>>
        &&
        std::is_same_v<TWithStrings, Achievement<std::string>>
        ) {
        with_strings.id = raw.id;
        with_strings.required_faction = raw.required_faction;
        with_strings.map_id = raw.map_id;
        with_strings.parent_achievement = raw.parent_achievement;
        with_strings.name_1 = raw.name_1 > 0 ? strings.at(raw.name_1) : "";
        with_strings.name_2 = raw.name_2 > 0 ? strings.at(raw.name_2) : "";
        with_strings.name_3 = raw.name_3 > 0 ? strings.at(raw.name_3) : "";
        with_strings.name_4 = raw.name_4 > 0 ? strings.at(raw.name_4) : "";
        with_strings.name_5 = raw.name_5 > 0 ? strings.at(raw.name_5) : "";
        with_strings.name_6 = raw.name_6 > 0 ? strings.at(raw.name_6) : "";
        with_strings.name_7 = raw.name_7 > 0 ? strings.at(raw.name_7) : "";
        with_strings.name_8 = raw.name_8 > 0 ? strings.at(raw.name_8) : "";
        with_strings.name_9 = raw.name_9 > 0 ? strings.at(raw.name_9) : "";
        with_strings.name_10 = raw.name_10 > 0 ? strings.at(raw.name_10) : "";
        with_strings.name_11 = raw.name_11 > 0 ? strings.at(raw.name_11) : "";
        with_strings.name_12 = raw.name_12 > 0 ? strings.at(raw.name_12) : "";
        with_strings.name_13 = raw.name_13 > 0 ? strings.at(raw.name_13) : "";
        with_strings.name_14 = raw.name_14 > 0 ? strings.at(raw.name_14) : "";
        with_strings.name_15 = raw.name_15 > 0 ? strings.at(raw.name_15) : "";
        with_strings.name_16 = raw.name_16 > 0 ? strings.at(raw.name_16) : "";
        with_strings.name_flags = raw.name_flags;
        with_strings.description_1 = raw.description_1 > 0 ? strings.at(raw.description_1) : "";
        with_strings.description_2 = raw.description_2 > 0 ? strings.at(raw.description_2) : "";
        with_strings.description_3 = raw.description_3 > 0 ? strings.at(raw.description_3) : "";
        with_strings.description_4 = raw.description_4 > 0 ? strings.at(raw.description_4) : "";
        with_strings.description_5 = raw.description_5 > 0 ? strings.at(raw.description_5) : "";
        with_strings.description_6 = raw.description_6 > 0 ? strings.at(raw.description_6) : "";
        with_strings.description_7 = raw.description_7 > 0 ? strings.at(raw.description_7) : "";
        with_strings.description_8 = raw.description_8 > 0 ? strings.at(raw.description_8) : "";
        with_strings.description_9 = raw.description_9 > 0 ? strings.at(raw.description_9) : "";
        with_strings.description_10 = raw.description_10 > 0 ? strings.at(raw.description_10) : "";
        with_strings.description_11 = raw.description_11 > 0 ? strings.at(raw.description_11) : "";
        with_strings.description_12 = raw.description_12 > 0 ? strings.at(raw.description_12) : "";
        with_strings.description_13 = raw.description_13 > 0 ? strings.at(raw.description_13) : "";
        with_strings.description_14 = raw.description_14 > 0 ? strings.at(raw.description_14) : "";
        with_strings.description_15 = raw.description_15 > 0 ? strings.at(raw.description_15) : "";
        with_strings.description_16 = raw.description_16 > 0 ? strings.at(raw.description_16) : "";
        with_strings.description_flags = raw.description_flags;
        with_strings.category_id = raw.category_id;
        with_strings.points = raw.points;
        with_strings.order_in_category = raw.order_in_category;
        with_strings.flags = raw.flags;
        with_strings.icon = raw.icon;
        with_strings.title_reward_1 = raw.title_reward_1 > 0 ? strings.at(raw.title_reward_1) : "";
        with_strings.title_reward_2 = raw.title_reward_2 > 0 ? strings.at(raw.title_reward_2) : "";
        with_strings.title_reward_3 = raw.title_reward_3 > 0 ? strings.at(raw.title_reward_3) : "";
        with_strings.title_reward_4 = raw.title_reward_4 > 0 ? strings.at(raw.title_reward_4) : "";
        with_strings.title_reward_5 = raw.title_reward_5 > 0 ? strings.at(raw.title_reward_5) : "";
        with_strings.title_reward_6 = raw.title_reward_6 > 0 ? strings.at(raw.title_reward_6) : "";
        with_strings.title_reward_7 = raw.title_reward_7 > 0 ? strings.at(raw.title_reward_7) : "";
        with_strings.title_reward_8 = raw.title_reward_8 > 0 ? strings.at(raw.title_reward_8) : "";
        with_strings.title_reward_9 = raw.title_reward_9 > 0 ? strings.at(raw.title_reward_9) : "";
        with_strings.title_reward_10 = raw.title_reward_10 > 0 ? strings.at(raw.title_reward_10) : "";
        with_strings.title_reward_11 = raw.title_reward_11 > 0 ? strings.at(raw.title_reward_11) : "";
        with_strings.title_reward_12 = raw.title_reward_12 > 0 ? strings.at(raw.title_reward_12) : "";
        with_strings.title_reward_13 = raw.title_reward_13 > 0 ? strings.at(raw.title_reward_13) : "";
        with_strings.title_reward_14 = raw.title_reward_14 > 0 ? strings.at(raw.title_reward_14) : "";
        with_strings.title_reward_15 = raw.title_reward_15 > 0 ? strings.at(raw.title_reward_15) : "";
        with_strings.title_reward_16 = raw.title_reward_16 > 0 ? strings.at(raw.title_reward_16) : "";
        with_strings.title_reward_flags = raw.title_reward_flags;
        with_strings.title_reward_flags = raw.title_reward_flags;
        with_strings.count = raw.count;
        with_strings.ref_achievement = raw.ref_achievement;
    }
}
