#ifndef MELLIANCORE_WDBC_H
#define MELLIANCORE_WDBC_H

#include <string>
#include <vector>
#include <map>

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

    static void loadAll();

    template<typename T>
    static void load(const std::string &name, std::vector<T> &data);

    template<typename TDefinition, typename TFinal>
    static void loadWithStrings(const std::string &name, std::vector<TFinal> &data);

    template<typename TRaw, typename TWithStrings>
    static void addStrings(
        const TRaw &raw,
        TWithStrings &with_strings,
        const std::map<std::uint32_t, std::string> &strings
    );
};

#endif //MELLIANCORE_WDBC_H
