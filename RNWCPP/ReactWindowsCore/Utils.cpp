// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "Utils.h"
#include <regex>

using namespace std;

namespace facebook { namespace react {

Url::Url(const string& source)
{
                  //      ( 1 )              ( 2 )   ( 3 (4) )   ( 5 )    ( 6 (7) )
  regex expression("(http|https|ws|wss)://([^:/\\?]+)(:(\\d+))?(/[^\\?]*)?(\\?(.*))?$");
                  //     protocol             host       port     path        query
  cmatch match;
  int index = 0;
  if (regex_match(source.c_str(), match, expression))
  {
    ++index;
    this->scheme = string(match[index].first, match[index].second);

    ++index;
    this->host = string(match[index].first, match[index].second);

    ++index;
    ++index;
    this->port = string(match[index].first, match[index].second);

    ++index;
    this->path = string(match[index].first, match[index].second);
    if (1 > path.length() || '/' != path.at(0))
      path.insert(0, "/");

    ++index;
    ++index;
    this->queryString = string(match[index].first, match[index].second);
  }
  else
  {
    throw std::exception("Could not parse URL.");
  }
}

string Url::Target()
{
  if (1 > queryString.length())
    return path;
  else
    return path.append("?").append(queryString);
}

}} // namespace facebook::react
