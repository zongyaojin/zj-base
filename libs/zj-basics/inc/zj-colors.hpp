/**
 * @file zj-colors.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 *
 * @note They appear good on console with nice colors, but in log files they may appear as the underlying literal characters or sometime
 * even garbage characters
 */

#pragma once

/// Reset colors
#define ZJ_PLAIN "\033[0m"

/// @{ Regular colors
#define ZJ_BLACK "\033[0;30m"
#define ZJ_RED "\033[0;31m"
#define ZJ_GREEN "\033[0;32m"
#define ZJ_YELLOW "\033[0;33m"
#define ZJ_BLUE "\033[0;34m"
#define ZJ_PURPLE "\033[0;35m"
#define ZJ_CYAN "\033[0;36m"
#define ZJ_WHITE "\033[0;37m"
/// @}

/// @{ Bold colors
#define ZJ_B_BLACK "\033[1;30m"
#define ZJ_B_RED "\033[1;31m"
#define ZJ_B_GREEN "\033[1;32m"
#define ZJ_B_YELLOW "\033[1;33m"
#define ZJ_B_BLUE "\033[1;34m"
#define ZJ_B_PURPLE "\033[1;35m"
#define ZJ_B_CYAN "\033[1;36m"
#define ZJ_B_WHITE "\033[1;37m"
/// @}

/// @{ Colors with underline
#define ZJ_U_BLACK "\033[4;30m"
#define ZJ_U_RED "\033[4;31m"
#define ZJ_U_GREEN "\033[4;32m"
#define ZJ_U_YELLOW "\033[4;33m"
#define ZJ_U_BLUE "\033[4;34m"
#define ZJ_U_PURPLE "\033[4;35m"
#define ZJ_U_CYAN "\033[4;36m"
#define ZJ_U_WHITE "\033[4;37m"
/// @}

/// @{ Background color
#define ZJ_G_BLACK "\033[40m"
#define ZJ_G_RED "\033[41m"
#define ZJ_G_GREEN "\033[42m"
#define ZJ_G_YELLOW "\033[43m"
#define ZJ_G_BLUE "\033[44m"
#define ZJ_G_PURPLE "\033[45m"
#define ZJ_G_CYAN "\033[46m"
#define ZJ_G_WHITE "\033[47m"
/// @}

/// @{ High intensity colors
#define ZJ_I_BLACK "\033[0;90m"
#define ZJ_I_RED "\033[0;91m"
#define ZJ_I_GREEN "\033[0;92m"
#define ZJ_I_YELLOW "\033[0;93m"
#define ZJ_I_BLUE "\033[0;94m"
#define ZJ_I_PURPLE "\033[0;95m"
#define ZJ_I_CYAN "\033[0;96m"
#define ZJ_I_WHITE "\033[0;97m"
/// @}

/// @{ Bold high intensity colors
#define ZJ_BI_BLACK "\033[1;90m"
#define ZJ_BI_RED "\033[1;91m"
#define ZJ_BI_GREEN "\033[1;92m"
#define ZJ_BI_YELLOW "\033[1;93m"
#define ZJ_BI_BLUE "\033[1;94m"
#define ZJ_BI_PURPLE "\033[1;95m"
#define ZJ_BI_CYAN "\033[1;96m"
#define ZJ_BI_WHITE "\033[1;97m"
/// @}

/// @{ High intensity background colors
#define ZJ_GI_BLACK "\033[0;100m"
#define ZJ_GI_RED "\033[0;101m"
#define ZJ_GI_GREEN "\033[0;102m"
#define ZJ_GI_YELLOW "\033[0;103m"
#define ZJ_GI_BLUE "\033[0;104m"
#define ZJ_GI_PURPLE "\033[10;95m"
#define ZJ_GI_CYAN "\033[0;106m"
#define ZJ_GI_WHITE "\033[0;107m"
/// @}
