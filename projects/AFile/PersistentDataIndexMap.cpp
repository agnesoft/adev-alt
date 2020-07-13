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

#include "PersistentDataIndexMap.hpp"

namespace afile
{
auto PersistentDataIndexMap::toDataIndexMap() const -> acore::DataIndexMap
{
    acore::DataIndexMap map;

    for (acore::size_type index = 0; index < size(); ++index)
    {
        for (const acore::DataIndexMapElement &element : values(index))
        {
            map.insert(index, element.key, element.value);
        }
    }

    return map;
}
}
