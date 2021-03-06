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

#include "listbox.h"

#include "GL/glew.h"

#include "SDL2/SDL_opengl.h"

#include "../../core/log.h"
#include "../../render/mesh/guiquad.h"
#include "../../render/shaders.h"
#include "../../resources/resources.h"

#include "button.h"
#include "imagebutton.h"
#include "scrollbar.h"

using namespace std;

using namespace reone::render;
using namespace reone::resources;

namespace reone {

namespace gui {

static const int kItemPadding = 3;

ListBox::ListBox() : Control(ControlType::ListBox) {
}

ListBox::ListBox(const string &tag) : Control(ControlType::ListBox, tag) {
}

void ListBox::updateItems() {
    if (!_protoItem) return;

    _slotCount = _extent.height / (_protoItem->extent().height + _padding);

    if (_scrollBar) {
        _scrollBar->setVisible(_items.size() > _slotCount);
    }
}

void ListBox::clearItems() {
    _items.clear();
    _itemOffset = 0;
    updateItems();
}

void ListBox::add(const Item &item) {
    _items.push_back(item);
    updateItems();
}

void ListBox::load(const GffStruct &gffs) {
    Control::load(gffs);

    const GffField *protoItem = gffs.find("PROTOITEM");
    if (protoItem) {
        _protoItem = makeControl(protoItem->asStruct());
        updateItems();
    }

    const GffField *scrollBar = gffs.find("SCROLLBAR");
    if (scrollBar) {
        _scrollBar = makeControl(scrollBar->asStruct());
    }
}

bool ListBox::handleMouseMotion(int x, int y) {
    _hilightedIndex = getItemIndex(y);
    return false;
}

int ListBox::getItemIndex(int y) const {
    if (!_protoItem) return -1;

    const Control::Extent &protoExtent = _protoItem->extent();
    int idx = (y - protoExtent.top) / (protoExtent.height + _padding) + _itemOffset;

    return idx >= 0 && idx < _items.size() ? idx : -1;
}

bool ListBox::handleMouseWheel(int x, int y) {
    if (y < 0) {
        if (_items.size() - _itemOffset > _slotCount) _itemOffset++;
        return true;
    } else if (y > 0) {
        if (_itemOffset > 0) _itemOffset--;
        return true;
    }

    return false;
}

bool ListBox::handleClick(int x, int y) {
    int itemIdx = getItemIndex(y);
    if (itemIdx == -1) return false;

    if (_onItemClicked) {
        _onItemClicked(_tag, _items[itemIdx].tag);
        return true;
    }

    return false;
}

void ListBox::initGL() {
    Control::initGL();

    if (_protoItem) _protoItem->initGL();
    if (_scrollBar) _scrollBar->initGL();
}

void ListBox::render(const glm::ivec2 &offset, const string &textOverride) const {
    if (!_visible) return;

    Control::render(offset, textOverride);

    if (!_protoItem) return;

    glm::vec2 itemOffset(offset);
    const Control::Extent &protoExtent = _protoItem->extent();

    for (int i = 0; i < _slotCount; ++i) {
        int itemIdx = i + _itemOffset;
        if (itemIdx >= _items.size()) break;

        _protoItem->setFocus(_hilightedIndex == itemIdx);

        ImageButton *imageButton = dynamic_cast<ImageButton *>(_protoItem.get());
        if (imageButton) {
            imageButton->render(itemOffset, _items[itemIdx].text, _items[itemIdx].icon);
        } else {
            _protoItem->render(itemOffset, _items[itemIdx].text);
        }

        itemOffset.y += protoExtent.height + _padding;
    }

    if (_scrollBar) {
        ScrollBar &scrollBar = static_cast<ScrollBar &>(*_scrollBar);
        scrollBar.setCanScrollUp(_itemOffset > 0);
        scrollBar.setCanScrollDown(_items.size() - _itemOffset > _slotCount);
        scrollBar.render(offset, textOverride);
    }
}

void ListBox::stretch(float x, float y) {
    Control::stretch(x, y);

    if (_protoItem) _protoItem->stretch(x, 1.0f);
    if (_scrollBar) _scrollBar->stretch(1.0f, y);
}

void ListBox::setFocus(bool focus) {
    Control::setFocus(focus);
    if (!focus) {
        _hilightedIndex = -1;
    }
}

void ListBox::setExtent(const Extent &extent) {
    Control::setExtent(extent);
    updateItems();
}

const ListBox::Item &ListBox::getItemAt(int index) const {
    assert(index >= 0 && index < _items.size());
    return _items[index];
}

Control &ListBox::protoItem() const {
    return *_protoItem;
}

Control &ListBox::scrollBar() const {
    return *_scrollBar;
}

int ListBox::itemCount() const {
    return static_cast<int>(_items.size());
}

} // namespace gui

} // namespace reone
