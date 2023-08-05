//
// Created by Jj on 23/07/2023.
//

#ifndef CHECKERS_EVENT_HANDLER_UTIL_H
#define CHECKERS_EVENT_HANDLER_UTIL_H

#include <stdbool.h>

bool isInsideBoard(int x, int y);
Position translateToBoardPosition(int x, int y);

#endif //CHECKERS_EVENT_HANDLER_UTIL_H
