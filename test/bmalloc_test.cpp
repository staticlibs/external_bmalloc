/*
 * Copyright 2018, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   bmalloc_test.cpp
 * Author: alex
 *
 * Created on January 31, 2018, 2:41 PM
 */

#include <iostream>

#include "bmalloc.h"

#include "staticlib/config/assert.hpp"

int main() {
    auto chunk = bmalloc::api::tryMalloc(42);
    slassert(nullptr != chunk);
    bmalloc::api::free(chunk);
    bmalloc::api::scavengeThisThread();
    return 0;
}

