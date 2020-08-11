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

#ifndef ADB_INSERTQUERY_HPP
#define ADB_INSERTQUERY_HPP

#include "ADbModule.hpp"
#include "KeyValue.hpp"
#include "Placeholders.hpp"
#include "QueryData.hpp"
#include "SubQuery.hpp"

#include <string>
#include <vector>

namespace adb
{
class CountQuery;
class Query;
class IdsQuery;
class InsertEdgeQuery;
class ValuesQuery;

//! The InsertQuery class helps constructing an
//! insert query. Its public methods can only be
//! called on an r-value (temporary) object.
class InsertQuery
{
public:
    //! Inserts a single edge without any data from
    //! the origin \a from to the end \a to. Both
    //! \a from and \a to must be existing nodes in
    //! the database.
    [[nodiscard]] auto edge() && -> InsertEdgeQuery;

    //! Insert a single node without any values.
    [[nodiscard]] auto node() && -> IdsQuery;

    //! Insert a single node with \a values.
    [[nodiscard]] auto node(std::vector<adb::KeyValue> values) && -> IdsQuery;

    //! Insert a single node with values being
    //! bound later in place of \a placeholder.
    [[nodiscard]] auto node(PlaceholderValues placeholder) && -> IdsQuery;

    //! Insert a single node with value being
    //! obtained as a result of executing the
    //! \a subQuery.
    [[nodiscard]] auto node(ValuesQuery subQuery) && -> IdsQuery;

    //! Insert \a count nodes without any values.
    [[nodiscard]] auto nodes(acore::size_type count) && -> IdsQuery;

    //! Insert nodes without any values. Number of
    //! inserted nodes will be bound later in place
    //! of \a placeholder.
    [[nodiscard]] auto nodes(PlaceholderCount placeholder) && -> IdsQuery;

    //! Insert nodes without any values. Number of
    //! inserted nodes will be obtained as result
    //! of executing the \a subQuery.
    [[nodiscard]] auto nodes(CountQuery subQuery) && -> IdsQuery;

    //! Insert nodes with \a values. Number of nodes
    //! correspond to number of entries in \a values.
    [[nodiscard]] auto nodes(std::vector<std::vector<adb::KeyValue>> values) && -> IdsQuery;

    //! Insert nodes with values that will be bound
    //! later in place of \a placeholder. Number of
    //! nodes will correspond to the number of entries
    //! in the bound values.
    [[nodiscard]] auto nodes(PlaceholderValues placeholder) && -> IdsQuery;

    //! Insert ndoes with values that will be obtained
    //! as a result of executing the \a subQuery.
    //! Number of inserted nodes will correspond to
    //! the number of elements returned in the \a subQuery
    //! result.
    [[nodiscard]] auto nodes(ValuesQuery subQuery) && -> IdsQuery;

private:
    template<typename Data>
    [[nodiscard]] auto createPlaceholderQuery(std::string name, BindPlaceholderFunction bind) -> IdsQuery;
    template<typename Data>
    [[nodiscard]] auto createSubQueryQuery(Query &&subQuery, BindResultFunction bind) -> IdsQuery;
};
}

#endif
