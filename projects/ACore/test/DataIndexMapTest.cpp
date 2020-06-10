// Copyright 2020 Michael Vlach
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "pch.hpp"

#include <catch2/catch.hpp>

namespace acore
{
auto operator==(const DataIndexMap &map, const std::vector<std::pair<size_type, DataIndexMapElement>> &values) -> bool
{
    if (values.size() != static_cast<size_t>(map.count()))
    {
        return false;
    }

    for (size_type e = 0; e < map.size(); ++e)
    {
        for (const DataIndexMapElement &data : map.values(e))
        {
            if (std::find(values.begin(), values.end(), std::pair<size_type, DataIndexMapElement>{e, data}) == values.end())
            {
                return false;
            }
        }
    }

    return true;
}
}

namespace Catch
{
template<>
struct StringMaker<acore::DataIndexMap>
{
    [[nodiscard]] static std::string convert(const acore::DataIndexMap &map)
    {
        std::stringstream os;
        os << '{';
        for (acore::size_type e = 0; e < map.size(); ++e)
        {
            for (const acore::DataIndexMapElement &data : map.values(e))
            {
                os << " {" << e << '|' << data.key << ", " << data.value << "} ";
            }
        }
        os << '}';
        return os.str();
    }
};

template<>
struct StringMaker<std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>>
{
    [[nodiscard]] static std::string convert(const std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>> &values)
    {
        std::stringstream os;
        os << '{';
        for (auto keyValue : values)
        {
            os << " {" << keyValue.first << '|' << keyValue.second.key << ',' << keyValue.second.value << "} ";
        }
        os << '}';
        return os.str();
    }
};
}

namespace dataindexmaptest
{
TEST_CASE("[acore::DataIndexMap]")
{
    REQUIRE(std::is_default_constructible_v<acore::DataIndexMap>);
    REQUIRE(std::is_copy_constructible_v<acore::DataIndexMap>);
    REQUIRE(std::is_copy_assignable_v<acore::DataIndexMap>);
    REQUIRE(std::is_nothrow_move_assignable_v<acore::DataIndexMap>);
    REQUIRE(std::is_nothrow_destructible_v<acore::DataIndexMap>);
}

TEST_CASE("DataIndexMap() [acore::DataIndexMap]")
{
    const acore::DataIndexMap map;
    REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{});
}

TEST_CASE("DataIndexMap(const Vector<std::pair<size_type, DataIndexMapElement>> &data) [acore::DataIndexMap]")
{
    const std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>> data{{1, {2, 3}}, {5, {6, 7}}, {10, {4, 3}}, {1, {4, 9}}, {1, {0, 2}}};
    const acore::DataIndexMap map{data};
    REQUIRE(map == data);
}

TEST_CASE("clear() -> void [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        acore::DataIndexMap map;
        map.clear();
        REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{});
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{1, {10, 11}}, {1, {-2, -3}}, {5, {55, 555}}, {69, {42, 1}}}};
        map.clear();
        REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{});
    }
}

TEST_CASE("count() const noexcept -> size_type [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(noexcept(map.count()));
        REQUIRE(map.count() == 0);
    }

    SECTION("[data]")
    {
        const acore::DataIndexMap map{{{51, {1, 2}}, {49, {3, 45}}, {42, {65, 7}}, {1, {-1, -1}}, {5, {2, 3}}}};
        REQUIRE(map.count() == 5);
    }
}

TEST_CASE("count(size_type element) const [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(map.count(5) == 0);
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{1, {2, 3}}, {1, {4, 5}}, {5, {6, 7}}, {10, {11, 12}}, {1, {6, 7}}}};

        SECTION("[existing]")
        {
            REQUIRE(std::as_const(map).count(1) == 3);
        }

        SECTION("[missing]")
        {
            REQUIRE(std::as_const(map).count(100) == 0);
        }

        SECTION("[removed]")
        {
            map.remove(5);
            REQUIRE(std::as_const(map).count(5) == 0);
        }
    }
}

TEST_CASE("insert(size_type element, size_type key, size_type value) -> void [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        acore::DataIndexMap map;
        map.insert(1, 2, 3);
        REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{{1, {2, 3}}});
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{100, {99, 98}}, {99, {98, 97}}, {6, {7, 8}}, {9, {10, 11}}}};

        SECTION("[existing]")
        {
            map.insert(99, 98, 100);
            REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{{100, {99, 98}}, {99, {98, 100}}, {6, {7, 8}}, {9, {10, 11}}});
        }

        SECTION("[missing]")
        {
            map.insert(69, 42, 0);
            REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{{69, {42, 0}}, {100, {99, 98}}, {99, {98, 97}}, {6, {7, 8}}, {9, {10, 11}}});
        }
    }
}

TEST_CASE("isEmpty() const noexcept -> bool [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(noexcept(map.isEmpty()));
        REQUIRE(map.isEmpty());
    }

    SECTION("[data]")
    {
        const acore::DataIndexMap map{{{3, {30, 33}}}};
        REQUIRE_FALSE(map.isEmpty());
    }
}

TEST_CASE("keys() const -> Vector<size_type> [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(map.keys(1) == std::vector<acore::size_type>{}); //NOLINT(readability-container-size-empty)
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{1, {2, 3}}, {5, {6, 7}}, {10, {15, 16}}, {5, {16, 17}}, {18, {19, 20}}, {5, {1, 0}}}};

        SECTION("[existing]")
        {
            std::vector<acore::size_type> actual = std::as_const(map).keys(5);
            std::sort(actual.begin(), actual.end());
            REQUIRE(actual == std::vector<acore::size_type>{1, 6, 16});
        };

        SECTION("[missing]")
        {
            REQUIRE(std::as_const(map).keys(100) == std::vector<acore::size_type>{}); //NOLINT(readability-container-size-empty)
        }

        SECTION("[removed]")
        {
            map.remove(18);
            REQUIRE(std::as_const(map).keys(18) == std::vector<acore::size_type>{}); //NOLINT(readability-container-size-empty)
        }
    }
}

TEST_CASE("remove(size_type element) -> void [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        acore::DataIndexMap map;
        map.remove(10);
        REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{});
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{1, {2, 3}}, {10, {2, 3}}, {100, {3, 5}}, {10, {3, 4}}}};

        SECTION("[existing]")
        {
            map.remove(1);
            REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{{10, {2, 3}}, {100, {3, 5}}, {10, {3, 4}}});
        }

        SECTION("[multiple]")
        {
            map.remove(10);
            REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{{1, {2, 3}}, {100, {3, 5}}});
        }
    }
}

TEST_CASE("remove(size_type element, size_type key) -> void [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        acore::DataIndexMap map;
        map.remove(5, 10);
        REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{});
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{100, {-101, -102}}, {200, {15, 20}}, {0, {1, 2}}, {200, {-300, -1}}, {5, {17, 58}}, {69, {42, 0}}}};
        map.remove(200, -300);
        REQUIRE(map == std::vector<std::pair<acore::size_type, acore::DataIndexMapElement>>{{100, {-101, -102}}, {200, {15, 20}}, {0, {1, 2}}, {5, {17, 58}}, {69, {42, 0}}});
    }
}

TEST_CASE("size() const noexcept -> acore::size_type [acore::DataIndexMap")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(noexcept(map.size()));
        REQUIRE(map.size() == 0);
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map;
        map.insert(1, 2, 3);
        map.insert(3, 1, 2);
        map.insert(5, 4, 4);
        REQUIRE(map.size() == 6);
    }

    SECTION("[multiple data per element]")
    {
        acore::DataIndexMap map;
        map.insert(1, 2, 3);
        map.insert(3, 1, 2);
        map.insert(3, 2, 2);
        map.insert(3, 3, 3);
        REQUIRE(map.size() == 4);
    }
}

TEST_CASE("storage() noexcept -> Data * [acore::DataIndexMap]")
{
    acore::DataIndexMap map;
    REQUIRE(noexcept(map.storage()));
    REQUIRE(map.storage() != nullptr);
}

TEST_CASE("storage() const noexcept -> const Data * [acore::DataIndexMap]")
{
    const acore::DataIndexMap map;
    REQUIRE(noexcept(map.storage()));
    REQUIRE(map.storage() != nullptr);
}

TEST_CASE("value(size_type element) -> size_type [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(map.value(1, 2) == acore::INVALID_INDEX);
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{2, {4, 8}}, {32, {64, 128}}, {2, {10, 11}}, {256, {512, 1024}}, {2048, {4096, 8192}}}};

        SECTION("[existing]")
        {
            REQUIRE(std::as_const(map).value(2, 10) == 11);
        }

        SECTION("[missing]")
        {
            REQUIRE(std::as_const(map).value(1, 10) == acore::INVALID_INDEX);
        }

        SECTION("[removed]")
        {
            map.remove(256);
            REQUIRE(std::as_const(map).value(256, 512) == acore::INVALID_INDEX);
        }
    }
}

TEST_CASE("values(size_type element) const -> Vector<DataIndexMapElement> [acore::DataIndexMap]")
{
    SECTION("[empty]")
    {
        const acore::DataIndexMap map;
        REQUIRE(map.values(3) == std::vector<acore::DataIndexMapElement>{}); //NOLINT(readability-container-size-empty)
    }

    SECTION("[data]")
    {
        acore::DataIndexMap map{{{10, {20, 30}}, {11, {21, 31}}, {12, {21, 31}}, {11, {13, 14}}, {52, {65, 67}}, {11, {87, 89}}}};

        SECTION("[existing]")
        {
            REQUIRE(std::as_const(map).values(52) == std::vector<acore::DataIndexMapElement>{{65, 67}});
        }

        SECTION("[multiple]")
        {
            std::vector<acore::DataIndexMapElement> actual = std::as_const(map).values(11);
            std::sort(actual.begin(), actual.end());
            REQUIRE(actual == std::vector<acore::DataIndexMapElement>{{13, 14}, {21, 31}, {87, 89}});
        }

        SECTION("[missing]")
        {
            REQUIRE(std::as_const(map).values(100) == std::vector<acore::DataIndexMapElement>{}); //NOLINT(readability-container-size-empty)
        }

        SECTION("[removed]")
        {
            map.remove(12);
            REQUIRE(std::as_const(map).values(12) == std::vector<acore::DataIndexMapElement>{}); //NOLINT(readability-container-size-empty)
        }
    }
}

TEST_CASE("acore::DataIndexMap [examples]")
{
    SECTION("[usage]")
    {
        // clang-format off
        //! [[Usage]]
acore::DataIndexMap map;

map.insert(1, 2, 3);
map.insert(1, 3, 4);
map.insert(2, 3, 4);

map.remove(1, 3);

const acore::size_type value1 = map.value(1, 2); //== 3
const acore::size_type value2 = map.value(1, 3); //== acore::INVALID_INDEX since the value was removed
        //! [[Usage]]
        // clang-format on;
        REQUIRE(value1 == 3);
        REQUIRE(value2 == acore::INVALID_INDEX);
    }
}
}
