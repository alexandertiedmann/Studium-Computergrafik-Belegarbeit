#pragma once
#ifndef File_Header
#define File_Header

#include "DateTime.hpp"
#include "ActualGame.hpp"

DateTime readSavedate(int savenum);
ActualGame readSave(int savenum);

#endif