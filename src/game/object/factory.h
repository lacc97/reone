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

#pragma once

#include <cstdint>
#include <memory>

#include "../../resources/types.h"

#include "../area.h"
#include "../module.h"
#include "../types.h"

#include "creature.h"
#include "door.h"
#include "placeable.h"
#include "trigger.h"
#include "waypoint.h"

namespace reone {

namespace game {

class ObjectFactory {
public:
    ObjectFactory(resources::GameVersion version, const Options &opts);

    virtual std::unique_ptr<Module> newModule();
    virtual std::unique_ptr<Area> newArea();
    virtual std::unique_ptr<Creature> newCreature();
    virtual std::unique_ptr<Placeable> newPlaceable();
    virtual std::unique_ptr<Door> newDoor();
    virtual std::unique_ptr<Waypoint> newWaypoint();
    virtual std::unique_ptr<Trigger> newTrigger();

protected:
    resources::GameVersion _version { resources::GameVersion::KotOR };
    Options _options;
    uint32_t _counter { 2 }; // ids 0 and 1 are reserved

private:
    ObjectFactory(const ObjectFactory &) = delete;
    ObjectFactory &operator=(const ObjectFactory &) = delete;
};

} // namespace game

} // namespace reone
