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

#include "hud.h"

#include "../../gui/control/label.h"

using namespace std;

using namespace reone::gui;
using namespace reone::render;
using namespace reone::resources;

namespace reone {

namespace game {

HUD::HUD(const render::GraphicsOptions &opts) : GUI(opts) {
    _resolutionX = 800;
    _resolutionY = 600;
    _scaling = ScalingMode::PositionRelativeToCenter;
}

void HUD::load(GameVersion version) {
    GUI::load(getResRef(version), BackgroundType::None);

    hideControl("BTN_CLEARALL");
    hideControl("BTN_TARGET0");
    hideControl("BTN_TARGET1");
    hideControl("BTN_TARGET2");
    hideControl("BTN_TARGETDOWN0");
    hideControl("BTN_TARGETDOWN1");
    hideControl("BTN_TARGETDOWN2");
    hideControl("BTN_TARGETUP0");
    hideControl("BTN_TARGETUP1");
    hideControl("BTN_TARGETUP2");
    hideControl("LBL_ACTIONDESCBG");
    hideControl("LBL_ACTIONTYPE0");
    hideControl("LBL_ACTIONTYPE1");
    hideControl("LBL_ACTIONTYPE2");
    hideControl("LBL_ACTIONTYPE3");
    hideControl("LBL_ACTIONTYPE4");
    hideControl("LBL_ACTIONTYPE5");
    hideControl("LBL_ACTIONDESC");
    hideControl("LBL_ARROW_MARGIN");
    hideControl("LBL_CASH");
    hideControl("LBL_CMBTEFCTINC1");
    hideControl("LBL_CMBTEFCTINC2");
    hideControl("LBL_CMBTEFCTINC3");
    hideControl("LBL_CMBTEFCTRED1");
    hideControl("LBL_CMBTEFCTRED2");
    hideControl("LBL_CMBTEFCTRED3");
    hideControl("LBL_CMBTMODEMSG");
    hideControl("LBL_CMBTMSGBG");
    hideControl("LBL_COMBATBG1");
    hideControl("LBL_COMBATBG2");
    hideControl("LBL_COMBATBG3");
    hideControl("LBL_DARKSHIFT");
    hideControl("LBL_DEBILATATED1");
    hideControl("LBL_DEBILATATED2");
    hideControl("LBL_DEBILATATED3");
    hideControl("LBL_DISABLE1");
    hideControl("LBL_DISABLE2");
    hideControl("LBL_DISABLE3");
    hideControl("LBL_JOURNAL");
    hideControl("LBL_HEALTHBG");
    hideControl("LBL_INDICATE");
    hideControl("LBL_INDICATEBG");
    hideControl("LBL_ITEMRCVD");
    hideControl("LBL_ITEMLOST");
    hideControl("LBL_LEVELUP1");
    hideControl("LBL_LEVELUP2");
    hideControl("LBL_LEVELUP3");
    hideControl("LBL_LIGHTSHIFT");
    hideControl("LBL_LVLUPBG1");
    hideControl("LBL_LVLUPBG2");
    hideControl("LBL_LVLUPBG3");
    hideControl("LBL_MAP");
    hideControl("LBL_MOULDING1");
    hideControl("LBL_MOULDING2");
    hideControl("LBL_MOULDING3");
    hideControl("LBL_MOULDING4");
    hideControl("LBL_NAME");
    hideControl("LBL_NAMEBG");
    hideControl("LBL_PLOTXP");
    hideControl("LBL_STEALTHXP");

    hideControl("LBL_MAPBORDER");
    hideControl("LBL_MAPVIEW");
    hideControl("LBL_ARROW");
    hideControl("LBL_TARGET0");
    hideControl("BTN_MINIMAP");
    hideControl("LBL_ACTION0");
    hideControl("BTN_ACTION0");
    hideControl("BTN_ACTIONUP0");
    hideControl("BTN_ACTIONDOWN0");
    hideControl("LBL_ACTION1");
    hideControl("BTN_ACTION1");
    hideControl("BTN_ACTIONUP1");
    hideControl("BTN_ACTIONDOWN1");
    hideControl("LBL_ACTION2");
    hideControl("BTN_ACTION2");
    hideControl("BTN_ACTIONUP2");
    hideControl("BTN_ACTIONDOWN2");
    hideControl("LBL_ACTION3");
    hideControl("BTN_ACTION3");
    hideControl("BTN_ACTIONUP3");
    hideControl("BTN_ACTIONDOWN3");
    hideControl("LBL_ACTION4");
    hideControl("BTN_ACTION4");
    hideControl("BTN_ACTIONUP4");
    hideControl("BTN_ACTIONDOWN4");
    hideControl("LBL_ACTION5");
    hideControl("BTN_ACTION5");
    hideControl("BTN_ACTIONUP5");
    hideControl("BTN_ACTIONDOWN5");
}

string HUD::getResRef(GameVersion version) const {
    string resRef("mipc28x6");
    if (version == GameVersion::TheSithLords) {
        resRef += "_p";
    }

    return resRef;
}

void HUD::update(const HudContext &ctx) {
    size_t partySize = ctx.partyPortraits.size();
    if (partySize > 0) {
        Control &label = getControl("LBL_CHAR1");
        label.border().fill = ctx.partyPortraits[0];
        label.setVisible(true);

        showControl("LBL_BACK1");
    } else {
        hideControl("LBL_CHAR1");
        hideControl("LBL_BACK1");
    }

    if (partySize > 1) {
        Control &label = getControl("LBL_CHAR3");
        label.border().fill = ctx.partyPortraits[1];
        label.setVisible(true);

        showControl("LBL_BACK3");
    } else {
        hideControl("LBL_CHAR3");
        hideControl("LBL_BACK3");
    }

    if (partySize > 2) {
        Control &label = getControl("LBL_CHAR2");
        label.border().fill = ctx.partyPortraits[2];
        label.setVisible(true);

        showControl("LBL_CHAR2");
        showControl("LBL_BACK2");
    } else {
        hideControl("LBL_CHAR2");
        hideControl("LBL_BACK2");
    }
}

} // namespace game

} // namespace reone
