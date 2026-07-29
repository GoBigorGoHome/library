#include <string>
#include <ostream>
#include <ranges>
#include <sstream>

template <class T, size_t size = std::tuple_size<T>::value>
std::string to_debug(T, std::string s = "") requires(not std::ranges::range<T>);

std::string to_debug(auto x) requires requires(std::ostream& os) { os << x; }
#ifdef __EDG__
         && (not requires { typename std::tuple_size<decltype(x)>::type; })
#endif
{ 
  return static_cast<std::ostringstream>(std::ostringstream() << x).str();
}

std::string to_debug(std::ranges::range auto x, std::string s = "") requires(not std::is_same_v<decltype(x), std::string>) {
  for (auto xi : x) { s += ", " + to_debug(xi); }
  return "[" + s.substr(s.empty() ? 0 : 2) + "]";
}

template <class T, size_t size>
std::string to_debug(T x, std::string s) requires(not std::ranges::range<T>) {
  [&]<size_t... I>(std::index_sequence<I...>) { ((s += ", " + to_debug(get<I>(x))), ...); }(std::make_index_sequence<size>());
  return "(" + s.substr(s.empty() ? 0 : 2) + ")";
}

// #define debug(...) cerr << __LINE__ << ": (" #__VA_ARGS__ ") = " << to_debug(tuple(__VA_ARGS__)) << "\n"
// 以上是 Heltion 的原版 debug.h，包括此行上一行（被我注释掉了）。#ifdef __EDG__ ... #endif 那一段是我加的，为了让 vscode 的 intellisense 闭嘴。

// 判断是否为字符串字面量 (const char 数组)
template<typename T>
struct is_string_literal : std::false_type {};
template<size_t N>
struct is_string_literal<const char(&)[N]> : std::true_type {};

// 模式 A: 带有 Label (第一个参数是字面量，且参数个数 > 1)
template<typename T, typename... Args>
void debug_impl(int line, const char* names, T&& first, Args&&... args) {
    if constexpr (is_string_literal<T>::value && sizeof...(args) > 0) {
        std::cerr << line << ": " << first;
        ((std::cerr << " " << to_debug(std::forward<Args>(args))), ...);
        std::cerr << std::endl;
    } else {
        // 模式 B: 标准模式 (打印变量名 = 值)
        std::cerr << line << ": (" << names << ") = " 
                  << to_debug(std::forward_as_tuple(std::forward<T>(first), std::forward<Args>(args)...)) 
                  << std::endl;
    }
}

// --- 3. 宏定义 ---

#define debug(...) debug_impl(__LINE__, #__VA_ARGS__, __VA_ARGS__)

