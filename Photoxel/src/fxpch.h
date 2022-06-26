#pragma once
#ifndef _FXPCH_H_
#define _FXPCH_H_

#if __cplusplus

#include <iostream>
#include <fstream>
#include <sstream>

#include <utility>
#include <algorithm>

#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <string>
#include <string_view>

#include <optional>
#include <variant>
#include <any>
#include <functional>
#include <iterator>
#include <memory>
#include <filesystem>

#include <thread>
#include <mutex>

#include <chrono>
#include <ctime>
#include <stdint.h>

// C++20
#include <format>
#include <source_location>

#if _WIN32
#include "Window/Platform/Win32/IncludeWindow.h"
#endif

#endif

#endif