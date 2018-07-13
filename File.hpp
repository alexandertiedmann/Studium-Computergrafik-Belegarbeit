#pragma once
#ifndef File_Header
#define File_Header

#include "DateTime.hpp"
#include "ActualGame.hpp"
#include "ActualLevel.hpp"
#include <stdlib.h> 
#include <vector>

DateTime readSavedate(int savenum);
ActualGame readSave(int savenum);
ActualLevel readLevel(int levelnum);

#endif