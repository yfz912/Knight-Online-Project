class mx.controls.listclasses.DataSelector extends Object
{
    var __vPosition, setVPosition, __dataProvider, enabled, lastSelected, lastSelID, selected, invUpdateControl, invalidate, multipleSelection, updateControl, __rowCount, rows;
    function DataSelector()
    {
        super();
    } // End of the function
    static function Initialize(obj)
    {
        var _loc3 = mx.controls.listclasses.DataSelector.mixinProps;
        var _loc4 = _loc3.length;
        obj = obj.prototype;
        for (var _loc1 = 0; _loc1 < _loc4; ++_loc1)
        {
            obj[_loc3[_loc1]] = mx.controls.listclasses.DataSelector.mixins[_loc3[_loc1]];
        } // end of for
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "dataProvider", true);
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "length", false);
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "value", false);
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "selectedIndex", true);
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "selectedIndices", true);
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "selectedItems", false);
        mx.controls.listclasses.DataSelector.mixins.createProp(obj, "selectedItem", true);
        return (true);
    } // End of the function
    function createProp(obj, propName, setter)
    {
        var p = propName.charAt(0).toUpperCase() + propName.substr(1);
        var _loc2 = null;
        var _loc3 = function (Void)
        {
            return (this["get" + p]());
        };
        if (setter)
        {
            _loc2 = function (val)
            {
                this["set" + p](val);
            };
        } // end if
        obj.addProperty(propName, _loc3, _loc2);
    } // End of the function
    function setDataProvider(dP)
    {
        if (__vPosition != 0)
        {
            this.setVPosition(0);
        } // end if
        this.clearSelected();
        __dataProvider.removeEventListener(this);
        __dataProvider = dP;
        dP.addEventListener("modelChanged", this);
        dP.addView(this);
        this.modelChanged({eventName: "updateAll"});
    } // End of the function
    function getDataProvider(Void)
    {
        return (__dataProvider);
    } // End of the function
    function addItemAt(index, label, data)
    {
        if (index < 0 || !enabled)
        {
            return;
        } // end if
        var _loc2 = __dataProvider;
        if (_loc2 == undefined)
        {
            _loc2 = __dataProvider = new Array();
            _loc2.addEventListener("modelChanged", this);
            index = 0;
        } // end if
        if (typeof(label) == "object" || typeof(_loc2.getItemAt(0)) == "string")
        {
            _loc2.addItemAt(index, label);
        }
        else
        {
            _loc2.addItemAt(index, {label: label, data: data});
        } // end else if
    } // End of the function
    function addItem(label, data)
    {
        this.addItemAt(__dataProvider.length, label, data);
    } // End of the function
    function removeItemAt(index)
    {
        return (__dataProvider.removeItemAt(index));
    } // End of the function
    function removeAll(Void)
    {
        __dataProvider.removeAll();
    } // End of the function
    function replaceItemAt(index, newLabel, newData)
    {
        if (typeof(newLabel) == "object")
        {
            __dataProvider.replaceItemAt(index, newLabel);
        }
        else
        {
            __dataProvider.replaceItemAt(index, {label: newLabel, data: newData});
        } // end else if
    } // End of the function
    function sortItemsBy(fieldName, order)
    {
        lastSelID = __dataProvider.getItemID(lastSelected);
        __dataProvider.sortItemsBy(fieldName, order);
    } // End of the function
    function sortItems(compareFunc, order)
    {
        lastSelID = __dataProvider.getItemID(lastSelected);
        __dataProvider.sortItems(compareFunc, order);
    } // End of the function
    function getLength(Void)
    {
        return (__dataProvider.length);
    } // End of the function
    function getItemAt(index)
    {
        return (__dataProvider.getItemAt(index));
    } // End of the function
    function modelChanged(eventObj)
    {
        var _loc3 = eventObj.firstItem;
        var _loc6 = eventObj.lastItem;
        var _loc7 = eventObj.eventName;
        if (_loc7 == undefined)
        {
            _loc7 = eventObj.event;
            _loc3 = eventObj.firstRow;
            _loc6 = eventObj.lastRow;
            if (_loc7 == "addRows")
            {
                _loc7 = eventObj.eventName = "addItems";
            }
            else if (_loc7 == "deleteRows")
            {
                _loc7 = eventObj.eventName = "removeItems";
            }
            else if (_loc7 == "updateRows")
            {
                _loc7 = eventObj.eventName = "updateItems";
            } // end else if
        } // end else if
        if (_loc7 == "addItems")
        {
            for (var _loc2 in selected)
            {
                var _loc5 = selected[_loc2];
                if (_loc5 != undefined && _loc5 >= _loc3)
                {
                    selected[_loc2] = selected[_loc2] + (_loc6 - _loc3 + 1);
                } // end if
            } // end of for...in
        }
        else if (_loc7 == "removeItems")
        {
            if (__dataProvider.length == 0)
            {
                delete this.selected;
            }
            else
            {
                var _loc9 = eventObj.removedIDs;
                var _loc10 = _loc9.length;
                for (var _loc2 = 0; _loc2 < _loc10; ++_loc2)
                {
                    var _loc4 = _loc9[_loc2];
                    if (selected[_loc4] != undefined)
                    {
                        delete selected[_loc4];
                    } // end if
                } // end of for
                for (var _loc2 in selected)
                {
                    if (selected[_loc2] >= _loc3)
                    {
                        selected[_loc2] = selected[_loc2] - (_loc6 - _loc3 + 1);
                    } // end if
                } // end of for...in
            } // end else if
        }
        else if (_loc7 == "sort")
        {
            if (typeof(__dataProvider.getItemAt(0)) != "object")
            {
                delete this.selected;
            }
            else
            {
                _loc10 = __dataProvider.length;
                for (var _loc2 = 0; _loc2 < _loc10; ++_loc2)
                {
                    if (this.isSelected(_loc2))
                    {
                        _loc4 = __dataProvider.getItemID(_loc2);
                        if (_loc4 == lastSelID)
                        {
                            lastSelected = _loc2;
                        } // end if
                        selected[_loc4] = _loc2;
                    } // end if
                } // end of for
            } // end else if
        }
        else if (_loc7 == "filterModel")
        {
            this.setVPosition(0);
        } // end else if
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function getValue(Void)
    {
        var _loc2 = this.getSelectedItem();
        if (typeof(_loc2) != "object")
        {
            return (_loc2);
        } // end if
        return (_loc2.data == undefined ? (_loc2.label) : (_loc2.data));
    } // End of the function
    function getSelectedIndex(Void)
    {
        for (var _loc3 in selected)
        {
            var _loc2 = selected[_loc3];
            if (_loc2 != undefined)
            {
                return (_loc2);
            } // end if
        } // end of for...in
    } // End of the function
    function setSelectedIndex(index)
    {
        if (index >= 0 && index < __dataProvider.length && enabled)
        {
            delete this.selected;
            this.selectItem(index, true);
            lastSelected = index;
            invUpdateControl = true;
            this.invalidate();
        }
        else if (index == undefined)
        {
            this.clearSelected();
        } // end else if
    } // End of the function
    function getSelectedIndices(Void)
    {
        var _loc2 = new Array();
        for (var _loc3 in selected)
        {
            _loc2.push(selected[_loc3]);
        } // end of for...in
        _loc2.reverse();
        return (_loc2.length > 0 ? (_loc2) : (undefined));
    } // End of the function
    function setSelectedIndices(indexArray)
    {
        if (multipleSelection != true)
        {
            return;
        } // end if
        delete this.selected;
        for (var _loc3 = 0; _loc3 < indexArray.length; ++_loc3)
        {
            var _loc2 = indexArray[_loc3];
            if (_loc2 >= 0 && _loc2 < __dataProvider.length)
            {
                this.selectItem(_loc2, true);
            } // end if
        } // end of for
        invUpdateControl = true;
        this.updateControl();
    } // End of the function
    function getSelectedItems(Void)
    {
        var _loc3 = this.getSelectedIndices();
        var _loc4 = new Array();
        for (var _loc2 = 0; _loc2 < _loc3.length; ++_loc2)
        {
            _loc4.push(this.getItemAt(_loc3[_loc2]));
        } // end of for
        return (_loc4.length > 0 ? (_loc4) : (undefined));
    } // End of the function
    function getSelectedItem(Void)
    {
        return (__dataProvider.getItemAt(this.getSelectedIndex()));
    } // End of the function
    function selectItem(index, selectedFlag)
    {
        if (selected == undefined)
        {
            selected = new Object();
        } // end if
        var _loc2 = __dataProvider.getItemID(index);
        if (_loc2 == undefined)
        {
            return;
        } // end if
        if (selectedFlag && !this.isSelected(index))
        {
            selected[_loc2] = index;
        }
        else if (!selectedFlag)
        {
            delete selected[_loc2];
        } // end else if
    } // End of the function
    function isSelected(index)
    {
        var _loc2 = __dataProvider.getItemID(index);
        if (_loc2 == undefined)
        {
            return (false);
        } // end if
        return (selected[_loc2] != undefined);
    } // End of the function
    function clearSelected(transition)
    {
        var _loc3 = 0;
        for (var _loc4 in selected)
        {
            var _loc2 = selected[_loc4];
            if (_loc2 != undefined && __vPosition <= _loc2 && _loc2 < __vPosition + __rowCount)
            {
                rows[_loc2 - __vPosition].drawRow(rows[_loc2 - __vPosition].item, "normal", transition && _loc3 % 3 == 0);
            } // end if
            ++_loc3;
        } // end of for...in
        delete this.selected;
    } // End of the function
    static var mixins = new mx.controls.listclasses.DataSelector();
    static var mixinProps = ["setDataProvider", "getDataProvider", "addItem", "addItemAt", "removeAll", "removeItemAt", "replaceItemAt", "sortItemsBy", "sortItems", "getLength", "getItemAt", "modelChanged", "calcPreferredWidthFromData", "calcPreferredHeightFromData", "getValue", "getSelectedIndex", "getSelectedItem", "getSelectedIndices", "getSelectedItems", "selectItem", "isSelected", "clearSelected", "setSelectedIndex", "setSelectedIndices"];
} // End of Class
