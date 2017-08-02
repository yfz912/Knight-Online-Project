class mx.core.View extends mx.core.UIComponent
{
    var tabChildren, tabEnabled, boundingBox_mc, border_mc, __get__height, __get__width, __tabIndex, __get__tabIndex, depth, createObject, createClassObject, loadExternal, __get__numChildren, destroyObject, createClassChildAtDepth, doLater, __set__tabIndex;
    function View()
    {
        super();
    } // End of the function
    function init()
    {
        super.init();
        tabChildren = true;
        tabEnabled = false;
        boundingBox_mc._visible = false;
        boundingBox_mc._width = boundingBox_mc._height = 0;
    } // End of the function
    function size()
    {
        border_mc.move(0, 0);
        border_mc.setSize(this.__get__width(), this.__get__height());
        this.doLayout();
    } // End of the function
    function draw()
    {
        this.size();
    } // End of the function
    function get numChildren()
    {
        var _loc3 = mx.core.View.childNameBase;
        for (var _loc2 = 0; true; ++_loc2)
        {
            if (this[_loc3 + _loc2] == undefined)
            {
                return (_loc2);
            } // end if
        } // end of for
        return (-1);
    } // End of the function
    function get tabIndex()
    {
        return (tabEnabled ? (__tabIndex) : (undefined));
    } // End of the function
    function set tabIndex(n)
    {
        __tabIndex = n;
        //return (this.tabIndex());
        null;
    } // End of the function
    function addLayoutObject(object)
    {
    } // End of the function
    function createChild(className, instanceName, initProps)
    {
        if (depth == undefined)
        {
            depth = 1;
        } // end if
        var _loc2;
        if (typeof(className) == "string")
        {
            _loc2 = this.createObject(className, instanceName, depth++, initProps);
        }
        else
        {
            _loc2 = this.createClassObject(className, instanceName, depth++, initProps);
        } // end else if
        if (_loc2 == undefined)
        {
            _loc2 = this.loadExternal(className, _loadExternalClass, instanceName, depth++, initProps);
        }
        else
        {
            set(mx.core.View.childNameBase + this.__get__numChildren(), _loc2);
            _loc2._complete = true;
            this.childLoaded(_loc2);
        } // end else if
        this.addLayoutObject(_loc2);
        return (_loc2);
    } // End of the function
    function getChildAt(childIndex)
    {
        return (this[mx.core.View.childNameBase + childIndex]);
    } // End of the function
    function destroyChildAt(childIndex)
    {
        if (!(childIndex >= 0 && childIndex < this.__get__numChildren()))
        {
            return;
        } // end if
        var _loc4 = mx.core.View.childNameBase + childIndex;
        var _loc6 = this.__get__numChildren();
        var _loc3;
        for (var _loc3 in this)
        {
            if (_loc3 == _loc4)
            {
                _loc4 = "";
                this.destroyObject(_loc3);
                break;
            } // end if
        } // end of for...in
        for (var _loc2 = Number(childIndex); _loc2 < _loc6 - 1; ++_loc2)
        {
            set(mx.core.View.childNameBase + _loc2, this[mx.core.View.childNameBase + (_loc2 + 1)]);
        } // end of for
        delete this[mx.core.View.childNameBase + (_loc6 - 1)];
        --depth;
    } // End of the function
    function initLayout()
    {
        if (!hasBeenLayedOut)
        {
            this.doLayout();
        } // end if
    } // End of the function
    function doLayout()
    {
        hasBeenLayedOut = true;
    } // End of the function
    function createChildren()
    {
        if (border_mc == undefined)
        {
            border_mc = this.createClassChildAtDepth(_global.styles.rectBorderClass, mx.managers.DepthManager.kBottom, {styleName: this});
        } // end if
        this.doLater(this, "initLayout");
    } // End of the function
    function convertToUIObject(obj)
    {
    } // End of the function
    function childLoaded(obj)
    {
        this.convertToUIObject(obj);
    } // End of the function
    static function extension()
    {
        mx.core.ExternalContent.enableExternalContent();
    } // End of the function
    static var symbolName = "View";
    static var symbolOwner = mx.core.View;
    static var version = "2.0.2.127";
    var className = "View";
    static var childNameBase = "_child";
    var hasBeenLayedOut = false;
    var _loadExternalClass = "UIComponent";
} // End of Class
