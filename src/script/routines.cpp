/*
 * Copyright � 2020 Vsevolod Kremianskii
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "routines.h"

#include <cassert>

#include "../core/log.h"

using namespace std;

namespace reone {

namespace script {

RoutineManager &RoutineManager::instance() {
    static RoutineManager instance;
    return instance;
}

void RoutineManager::add(const std::string &name, VariableType retType, const std::vector<VariableType> &argTypes) {
    _routines.emplace_back(name, retType, argTypes);
}

void RoutineManager::add(
    const std::string &name,
    VariableType retType,
    const std::vector<VariableType> &argTypes,
    const std::function<Variable(const std::vector<Variable> &, ExecutionContext &ctx)> &fn) {

    _routines.emplace_back(name, retType, argTypes, fn);
}

const Routine &RoutineManager::get(int index) {
    assert(index >= 0 && index < _routines.size());
    return _routines[index];
}

} // namespace game

} // namespace reone
