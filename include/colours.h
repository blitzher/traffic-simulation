/* 
 * Found from
 * https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
 */
#pragma once

#define BLK "\x1B[0;30m"
#define RED "\x1B[0;31m"
#define GRN "\x1B[0;32m"
#define YEL "\x1B[0;33m"
#define BLU "\x1B[34;1m"
#define MAG "\x1B[0;35m"
#define CYN "\x1B[0;36m"
#define WHT "\x1B[0;37m"

#define CLR_RESET "\x1B[0m"

void c_printf(const char *string, char clr[8], ...);
/* wrap c_printf with warning colour */
void warn(const char* string, ...);
/* wrap c_printf with error colour */
void error(const char* string, ...);
