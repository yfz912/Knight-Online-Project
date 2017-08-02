class mx.controls.RadioButtonGroup
{
    var radioList, __groupName, selectedRadio, __get__groupName, __get__selectedData, __get__selection, __get__labelPlacement, __get__enabled, __set__enabled, __set__groupName, __set__labelPlacement, __set__selectedData, __set__selection;
    function RadioButtonGroup()
    {
        this.init();
        mx.events.UIEventDispatcher.initialize(this);
    } // End of the function
    function init(Void)
    {
        radioList = new Array();
    } // End of the function
    function setGroupName(groupName)
    {
        if (groupName == undefined || groupName == "")
        {
            return;
        } // end if
        var _loc6 = __groupName;
        _parent[groupName] = this;
        for (var _loc5 in radioList)
        {
            radioList[_loc5].groupName = groupName;
            var _loc3 = radioList[_loc5];
        } // end of for...in
        _loc3.deleteGroupObj(_loc6);
    } // End of the function
    function getGroupName()
    {
        return (__groupName);
    } // End of the function
    function addInstance(instance)
    {
        instance.indexNumber = indexNumber++;
        radioList.push(instance);
    } // End of the function
    function getValue()
    {
        if (selectedRadio.data == "")
        {
            return (selectedRadio.label);
        }
        else
        {
            return (selectedRadio.__data);
        } // end else if
    } // End of the function
    function getLabelPlacement()
    {
        for (var _loc3 in radioList)
        {
            var _loc2 = radioList[_loc3].getLabelPlacement();
        } // end of for...in
        return (_loc2);
    } // End of the function
    function setLabelPlacement(pos)
    {
        for (var _loc3 in radioList)
        {
            radioList[_loc3].setLabelPlacement(pos);
        } // end of for...in
    } // End of the function
    function setEnabled(val)
    {
        for (var _loc3 in radioList)
        {
            radioList[_loc3].enabled = val;
        } // end of for...in
    } // End of the function
    function setSize(val, val1)
    {
        for (var _loc3 in radioList)
        {
            radioList[_loc3].setSize(val, val1);
        } // end of for...in
    } // End of the function
    function getEnabled()
    {
        for (var _loc4 in radioList)
        {
            var _loc2 = radioList[_loc4].enabled;
            var _loc3 = t + (_loc2 + 0);
        } // end of for...in
        if (_loc3 == radioList.length)
        {
            return (true);
        } // end if
        if (_loc3 == 0)
        {
            return (false);
        } // end if
    } // End of the function
    function setStyle(name, val)
    {
        for (var _loc4 in radioList)
        {
            radioList[_loc4].setStyle(name, val);
        } // end of for...in
    } // End of the function
    function setInstance(val)
    {
        for (var _loc3 in radioList)
        {
            if (radioList[_loc3] == val)
            {
                radioList[_loc3].selected = true;
            } // end if
        } // end of for...in
    } // End of the function
    function getInstance()
    {
        return (selectedRadio);
    } // End of the function
    function setValue(val)
    {
        for (var _loc4 in radioList)
        {
            if (radioList[_loc4].__data == val || radioList[_loc4].label == val)
            {
                var _loc2 = _loc4;
                break;
            } // end if
        } // end of for...in
        if (_loc2 != undefined)
        {
            selectedRadio.setState(false);
            selectedRadio.hitArea_mc._height = selectedRadio.__height;
            selectedRadio.hitArea_mc._width = selectedRadio.__width;
            selectedRadio = radioList[_loc2];
            selectedRadio.setState(true);
            selectedRadio.hitArea_mc._height = selectedRadio.hitArea_mc._width = 0;
        } // end if
    } // End of the function
    function set groupName(groupName)
    {
        if (groupName == undefined || groupName == "")
        {
            return;
        } // end if
        var _loc6 = __groupName;
        _parent[groupName] = this;
        for (var _loc5 in radioList)
        {
            radioList[_loc5].groupName = groupName;
            var _loc3 = radioList[_loc5];
        } // end of for...in
        _loc3.deleteGroupObj(_loc6);
        //return (this.groupName());
        null;
    } // End of the function
    function get groupName()
    {
        return (__groupName);
    } // End of the function
    function set selectedData(val)
    {
        for (var _loc4 in radioList)
        {
            if (radioList[_loc4].__data == val || radioList[_loc4].label == val)
            {
                var _loc2 = _loc4;
                break;
            } // end if
        } // end of for...in
        if (_loc2 != undefined)
        {
            selectedRadio.setState(false);
            selectedRadio = radioList[_loc2];
            selectedRadio.setState(true);
        } // end if
        //return (this.selectedData());
        null;
    } // End of the function
    function get selectedData()
    {
        if (selectedRadio.data == "" || selectedRadio.data == undefined)
        {
            return (selectedRadio.label);
        }
        else
        {
            return (selectedRadio.__data);
        } // end else if
    } // End of the function
    function get selection()
    {
        return (selectedRadio);
    } // End of the function
    function set selection(val)
    {
        for (var _loc3 in radioList)
        {
            if (radioList[_loc3] == val)
            {
                radioList[_loc3].selected = true;
            } // end if
        } // end of for...in
        //return (this.selection());
        null;
    } // End of the function
    function set labelPlacement(pos)
    {
        for (var _loc3 in radioList)
        {
            radioList[_loc3].setLabelPlacement(pos);
        } // end of for...in
        //return (this.labelPlacement());
        null;
    } // End of the function
    function get labelPlacement()
    {
        for (var _loc3 in radioList)
        {
            var _loc2 = radioList[_loc3].getLabelPlacement();
        } // end of for...in
        return (_loc2);
    } // End of the function
    function set enabled(val)
    {
        for (var _loc3 in radioList)
        {
            radioList[_loc3].enabled = val;
        } // end of for...in
        //return (this.enabled());
        null;
    } // End of the function
    function get enabled()
    {
        var _loc2 = 0;
        for (var _loc3 in radioList)
        {
            _loc2 = _loc2 + radioList[_loc3].enabled;
        } // end of for...in
        if (_loc2 == 0)
        {
            return (false);
        } // end if
        if (_loc2 == radioList.length)
        {
            return (true);
        } // end if
    } // End of the function
    static var symbolName = "RadioButtonGroup";
    static var symbolOwner = mx.controls.RadioButtonGroup;
    static var version = "2.0.2.127";
    var className = "RadioButtonGroup";
    var indexNumber = 0;
} // End of Class
