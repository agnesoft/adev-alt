export module abuild;

#ifdef _MSC_VER
export import : settings;
export import : build_cache;
export import : project_scanner;
export import : code_scanner;
#else
// clang-format off
import <astl.hpp>;
#include "settings.cpp"
#include "project.cpp"
#include "dependency.cpp"
#include "file.cpp"
#include "header.cpp"
#include "source.cpp"
#include "module.cpp"
#include "error.cpp"
#include "warning.cpp"
#include "build_cache.cpp"
#include "project_scanner.cpp"
#include "token.cpp"
#include "tokenizer.cpp"
#include "code_scanner.cpp"
// clang-format on
#endif
