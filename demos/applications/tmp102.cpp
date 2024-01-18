// Copyright 2024 Khalil Estell
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <libhal-tmp/tmp102.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>

#include "../hardware_map.hpp"

hal::status application(hardware_map& p_map)
{
  using namespace std::chrono_literals;
  using namespace hal::literals;

  auto& clock = *p_map.clock;
  auto& console = *p_map.console;
  auto& i2c = *p_map.i2c;

  hal::print(console, "tmp102 Application Starting...\n\n");
  auto tmp102 = HAL_CHECK(hal::tmp::tmp102::create(i2c));

  while (true) {
    hal::delay(clock, 500ms);
    hal::print(console, "Reading temperature... ");
    auto temperature = HAL_CHECK(tmp102.read()).temperature;
    hal::print<32>(console, "measured temperature = %f °C\n", temperature);
  }

  return hal::success();
}
