#pragma once

#include <libjson/Json.h>
#include <libutils/String.h>

void environment_load(const char *buffer);

Json::Value &environment();

String environment_copy();
