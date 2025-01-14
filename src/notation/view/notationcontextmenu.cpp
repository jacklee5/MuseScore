//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2020 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#include "notationcontextmenu.h"
#include "translation.h"

#include "ui/view/iconcodes.h"

using namespace mu::notation;
using namespace mu::ui;

MenuItemList NotationContextMenu::items(const ElementType& elementType) const
{
    switch (elementType) {
    case ElementType::MEASURE:
        return addViewItems(measureItems());
    case ElementType::PAGE:
        return addViewItems(pageItems());
    default:
        return addViewItems(elementItems());
    }
}

MenuItem NotationContextMenu::makeItem(const UiAction& action, const QString& section, bool enabled, bool checked) const
{
    MenuItem item = action;
    item.section = section;
    item.state.enabled = enabled;
    item.state.checked = checked;
    return item;
}

MenuItemList NotationContextMenu::measureItems() const
{
    MenuItemList items = defaultCopyPasteItems();
    items << makeItem(actionsRegister()->action("staff-properties"));

    return items;
}

MenuItemList NotationContextMenu::pageItems() const
{
    MenuItemList items {

        makeItem(actionsRegister()->action("edit-style")),
        makeItem(actionsRegister()->action("page-settings")),
        makeItem(actionsRegister()->action("load-style"))
    };

    return items;
}

MenuItemList NotationContextMenu::elementItems() const
{
    MenuItemList items = defaultCopyPasteItems();
    items << makeItem(actionsRegister()->action("select-similar"))
          << makeItem(actionsRegister()->action("select-similar-staff"))
          << makeItem(actionsRegister()->action("select-similar-range"))
          << makeItem(actionsRegister()->action("inspector"))
          << makeItem(actionsRegister()->action("select-dialog"));

    return items;
}

MenuItemList NotationContextMenu::defaultCopyPasteItems() const
{
    MenuItemList items {
        makeItem(actionsRegister()->action("cut")),
        makeItem(actionsRegister()->action("copy")),
        makeItem(actionsRegister()->action("paste")),
        makeItem(actionsRegister()->action("swap")),
        makeItem(actionsRegister()->action("delete")),
    };

    return items;
}

MenuItem NotationContextMenu::makeMenu(const std::string& title, const MenuItemList& actions, bool enabled, const ActionCode& menuActionCode) const
{
    MenuItem item;
    item.code = menuActionCode;
    item.title = title;
    item.subitems = actions;
    item.enabled = enabled;
    return item;
}

MenuItemList NotationContextMenu::addViewItems(MenuItemList items) const
{
    MenuItemList toolsItems{
        makeItem(actionsRegister()->action("toggle-palette")),
        makeItem(actionsRegister()->action("toggle-instruments")),
        makeItem(actionsRegister()->action("masterpalette")),
        makeItem(actionsRegister()->action("inspector")),
        makeItem(actionsRegister()->action("toggle-navigator")),
        makeItem(actionsRegister()->action("toggle-mixer")),
    };

    MenuItem item = makeMenu(trc("appshell", "&View"), toolsItems);

    items << item;

    /*items 
        << makeSeparator()
        << makeItem(actionsRegister()->action("toggle-palette"))
        << makeItem(actionsRegister()->action("toggle-instruments"))
        << makeItem(actionsRegister()->action("masterpalette"))
        << makeItem(actionsRegister()->action("inspector"))
        << makeItem(actionsRegister()->action("toggle-navigator"))
        << makeItem(actionsRegister()->action("toggle-mixer"));*/

    return items;
}