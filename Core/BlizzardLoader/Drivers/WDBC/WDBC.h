#ifndef MELLIANCORE_WDBC_H
#define MELLIANCORE_WDBC_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "WDBC.h"
#include "Config.h"
#include "Log.h"

struct Header
{
    std::uint32_t magic;
    std::uint32_t record_count;
    std::uint32_t field_count;
    std::uint32_t record_size;
    std::uint32_t string_block_size;
};

template<typename T>
struct Achievement
{
    std::uint32_t id;
    std::int32_t required_faction;
    std::int32_t map_id;
    std::uint32_t parent_achievement;
    T name_1;
    T name_2;
    T name_3;
    T name_4;
    T name_5;
    T name_6;
    T name_7;
    T name_8;
    T name_9;
    T name_10;
    T name_11;
    T name_12;
    T name_13;
    T name_14;
    T name_15;
    T name_16;
    std::uint32_t name_flags;
    T description_1;
    T description_2;
    T description_3;
    T description_4;
    T description_5;
    T description_6;
    T description_7;
    T description_8;
    T description_9;
    T description_10;
    T description_11;
    T description_12;
    T description_13;
    T description_14;
    T description_15;
    T description_16;
    std::uint32_t description_flags;
    std::uint32_t category_id;
    std::uint32_t points;
    std::uint32_t order_in_category;
    std::uint32_t flags;
    std::uint32_t icon;
    T title_reward_1;
    T title_reward_2;
    T title_reward_3;
    T title_reward_4;
    T title_reward_5;
    T title_reward_6;
    T title_reward_7;
    T title_reward_8;
    T title_reward_9;
    T title_reward_10;
    T title_reward_11;
    T title_reward_12;
    T title_reward_13;
    T title_reward_14;
    T title_reward_15;
    T title_reward_16;
    std::uint32_t title_reward_flags;
    std::uint32_t count;
    std::uint32_t ref_achievement;
};

template<typename T>
struct AreaPOI
{
    std::uint32_t id;
    std::uint32_t importance;
    std::uint32_t normal_icon;
    std::uint32_t normal_icon_50;
    std::uint32_t normal_icon_0;
    std::uint32_t horde_icon;
    std::uint32_t horde_icon_50;
    std::uint32_t horde_icon_0;
    std::uint32_t alliance_icon;
    std::uint32_t alliance_icon_50;
    std::uint32_t alliance_icon_0;
    std::uint32_t faction_id;
    float x;
    float y;
    float z;
    std::uint32_t map_id;
    std::uint32_t flags;
    std::uint32_t area_table_id;
    T name_1;
    T name_2;
    T name_3;
    T name_4;
    T name_5;
    T name_6;
    T name_7;
    T name_8;
    T name_9;
    T name_10;
    T name_11;
    T name_12;
    T name_13;
    T name_14;
    T name_15;
    T name_16;
    std::uint32_t name_flags;
    T description_1;
    T description_2;
    T description_3;
    T description_4;
    T description_5;
    T description_6;
    T description_7;
    T description_8;
    T description_9;
    T description_10;
    T description_11;
    T description_12;
    T description_13;
    T description_14;
    T description_15;
    T description_16;
    std::uint32_t description_flags;
    std::uint32_t world_state_id;
    std::uint32_t world_map_link;
};

struct gtChanceToMeleeCritBase
{
    float value;
};

class WDBC
{
private:
    static bool loaded;
public:
    static std::vector<Achievement<std::string>> m_achievement;
    static std::vector<AreaPOI<std::string>> m_area_poi;
    static std::vector<gtChanceToMeleeCritBase> m_gt_chance_to_melee_crit_base;

    static void loadAll()
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
    static void load(const std::string &name, std::vector<T> &data)
    {
        MEL_INFO("loading {0}", name);

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
    static void loadWithStrings(const std::string &name, std::vector<TFinal> &data)
    {
        MEL_INFO("loading {0}", name);

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
    static void addStrings(
        const TRaw &raw,
        TWithStrings &with_strings,
        const std::map<std::uint32_t, std::string> &strings
    )
    {
        if constexpr (
            (std::is_same_v<TRaw, AreaPOI<std::uint32_t>> && std::is_same_v<TWithStrings, AreaPOI<std::string>>)
            ||
            (std::is_same_v<TRaw, Achievement<std::uint32_t>> && std::is_same_v<TWithStrings, Achievement<std::string>>)
            ) {
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
        }

        if constexpr (std::is_same_v<TRaw, AreaPOI<std::uint32_t>> &&
                      std::is_same_v<TWithStrings, AreaPOI<std::string>>) {
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
};

#endif //MELLIANCORE_WDBC_H
