#pragma once
#include <string>

#define GL_CALL(x) ClearError(); \
    x; \
    PrintOutError(__FILE__, __LINE__);

void ClearError();
bool PrintOutError(const std::string& file, int line);