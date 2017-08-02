class mx.controls.listclasses.DataProvider extends Object
{
    var __ID__, length, splice, index, dispatchEvent, sortOn, reverse, sort;
    function DataProvider(obj)
    {
        super();
    } // End of the function
    static function Initialize(obj)
    {
        var _loc4 = mx.controls.listclasses.DataProvider.mixinProps;
        var _loc6 = _loc4.length;
        obj = obj.prototype;
        for (var _loc3 = 0; _loc3 < _loc6; ++_loc3)
        {
            obj[_loc4[_loc3]] = mx.controls.listclasses.DataProvider.mixins[_loc4[_loc3]];
            _global.ASSetPropFlags(obj, _loc4[_loc3], 1);
        } // end of for
        mx.events.EventDispatcher.initialize(obj);
        _global.ASSetPropFlags(obj, "addEventListener", 1);
        _global.ASSetPropFlags(obj, "removeEventListener", 1);
        _global.ASSetPropFlags(obj, "dispatchEvent", 1);
        _global.ASSetPropFlags(obj, "dispatchQueue", 1);
        Object.prototype.LargestID = 0;
        Object.prototype.getID = function ()
        {
            if (__ID__ == undefined)
            {
                __ID__ = Object.prototype.LargestID++;
                _global.ASSetPropFlags(this, "__ID__", 1);
            } // end if
            return (__ID__);
        };
        _global.ASSetPropFlags(Object.prototype, "LargestID", 1);
        _global.ASSetPropFlags(Object.prototype, "getID", 1);
        return (true);
    } // End of the function
    function addItemAt(index, value)
    {
        if (index < length)
        {
            this.splice(index, 0, value);
        }
        else if (index > length)
        {
            trace ("Cannot add an item past the end of the DataProvider");
            return;
        } // end else if
        this[index] = value;
        this.updateViews("addItems", index, index);
    } // End of the function
    function addItem(value)
    {
        this.addItemAt(length, value);
    } // End of the function
    function addItemsAt(index, newItems)
    {
        index = Math.min(length, index);
        newItems.unshift(index, 0);
        splice.apply(this, newItems);
        newItems.splice(0, 2);
        this.updateViews("addItems", index, index + newItems.length - 1);
    } // End of the function
    function removeItemsAt(index, len)
    {
        var _loc3 = new Array();
        for (var _loc2 = 0; _loc2 < len; ++_loc2)
        {
            _loc3.push(this.getItemID(index + _loc2));
        } // end of for
        var _loc6 = this.splice(index, len);
        this.dispatchEvent({type: "modelChanged", eventName: "removeItems", firstItem: index, lastItem: index + len - 1, removedItems: _loc6, removedIDs: _loc3});
    } // End of the function
    function removeItemAt(index)
    {
        var _loc2 = this[index];
        this.removeItemsAt(index, 1);
        return (_loc2);
    } // End of the function
    function removeAll(Void)
    {
        this.splice(0);
        this.updateViews("removeItems", 0, length - 1);
    } // End of the function
    function replaceItemAt(index, itemObj)
    {
        if (index < 0 || index >= length)
        {
            return;
        } // end if
        var _loc3 = this.getItemID(index);
        this[index] = itemObj;
        this[index].__ID__ = _loc3;
        this.updateViews("updateItems", index, index);
    } // End of the function
    function getItemAt(index)
    {
        return (this[index]);
    } // End of the function
    function getItemID(index)
    {
        var _loc2 = this[index];
        if (typeof(_loc2) != "object" && _loc2 != undefined)
        {
            return (index);
        }
        else
        {
            return (_loc2.getID());
        } // end else if
    } // End of the function
    function sortItemsBy(fieldName, order)
    {
        if (typeof(order) == "string")
        {
            this.sortOn(fieldName);
            if (order.toUpperCase() == "DESC")
            {
                this.reverse();
            } // end if
        }
        else
        {
            this.sortOn(fieldName, order);
        } // end else if
        this.updateViews("sort");
    } // End of the function
    function sortItems(compareFunc, optionFlags)
    {
        this.sort(compareFunc, optionFlags);
        this.updateViews("sort");
    } // End of the function
    function editField(index, fieldName, newData)
    {
        this[index][fieldName] = newData;
        this.dispatchEvent({type: "modelChanged", eventName: "updateField", firstItem: index, lastItem: index, fieldName: fieldName});
    } // End of the function
    function getEditingData(index, fieldName)
    {
        return (this[index][fieldName]);
    } // End of the function
    function updateViews(event, first, last)
    {
        this.dispatchEvent({type: "modelChanged", eventName: event, firstItem: first, lastItem: last});
    } // End of the function
    static var mixinProps = ["addView", "addItem", "addItemAt", "removeAll", "removeItemAt", "replaceItemAt", "getItemAt", "getItemID", "sortItemsBy", "sortItems", "updateViews", "addItemsAt", "removeItemsAt", "getEditingData", "editField"];
    static var evtDipatcher = mx.events.EventDispatcher;
    static var mixins = new mx.controls.listclasses.DataProvider();
} // End of Class
