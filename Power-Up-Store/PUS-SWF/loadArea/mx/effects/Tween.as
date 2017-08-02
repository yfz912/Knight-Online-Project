class mx.effects.Tween extends Object
{
    var arrayMode, listener, initVal, endVal, startTime, updateFunc, endFunc, ID;
    static var IntervalToken;
    function Tween(listenerObj, init, end, dur)
    {
        super();
        if (listenerObj == undefined)
        {
            return;
        } // end if
        if (typeof(init) != "number")
        {
            arrayMode = true;
        } // end if
        listener = listenerObj;
        initVal = init;
        endVal = end;
        if (dur != undefined)
        {
            duration = dur;
        } // end if
        startTime = getTimer();
        if (duration == 0)
        {
            this.endTween();
        }
        else
        {
            mx.effects.Tween.AddTween(this);
        } // end else if
    } // End of the function
    static function AddTween(tween)
    {
        tween.ID = mx.effects.Tween.ActiveTweens.length;
        mx.effects.Tween.ActiveTweens.push(tween);
        if (mx.effects.Tween.IntervalToken == undefined)
        {
            mx.effects.Tween.Dispatcher.DispatchTweens = mx.effects.Tween.DispatchTweens;
            IntervalToken = setInterval(mx.effects.Tween.Dispatcher, "DispatchTweens", mx.effects.Tween.Interval);
        } // end if
    } // End of the function
    static function RemoveTweenAt(index)
    {
        var _loc2 = mx.effects.Tween.ActiveTweens;
        if (index >= _loc2.length || index < 0 || index == undefined)
        {
            return;
        } // end if
        _loc2.splice(index, 1);
        var _loc4 = _loc2.length;
        for (var _loc1 = index; _loc1 < _loc4; ++_loc1)
        {
            --_loc2[_loc1].ID;
        } // end of for
        if (_loc4 == 0)
        {
            clearInterval(mx.effects.Tween.IntervalToken);
            delete mx.effects.Tween.IntervalToken;
        } // end if
    } // End of the function
    static function DispatchTweens(Void)
    {
        var _loc2 = mx.effects.Tween.ActiveTweens;
        var _loc3 = _loc2.length;
        for (var _loc1 = 0; _loc1 < _loc3; ++_loc1)
        {
            _loc2[_loc1].doInterval();
        } // end of for
        updateAfterEvent();
    } // End of the function
    function doInterval()
    {
        var _loc2 = getTimer() - startTime;
        var _loc3 = this.getCurVal(_loc2);
        if (_loc2 >= duration)
        {
            this.endTween();
        }
        else if (updateFunc != undefined)
        {
            listener[updateFunc](_loc3);
        }
        else
        {
            listener.onTweenUpdate(_loc3);
        } // end else if
    } // End of the function
    function getCurVal(curTime)
    {
        if (arrayMode)
        {
            var _loc3 = new Array();
            for (var _loc2 = 0; _loc2 < initVal.length; ++_loc2)
            {
                _loc3[_loc2] = this.easingEquation(curTime, initVal[_loc2], endVal[_loc2] - initVal[_loc2], duration);
            } // end of for
            return (_loc3);
        }
        else
        {
            return (this.easingEquation(curTime, initVal, endVal - initVal, duration));
        } // end else if
    } // End of the function
    function endTween()
    {
        if (endFunc != undefined)
        {
            listener[endFunc](endVal);
        }
        else
        {
            listener.onTweenEnd(endVal);
        } // end else if
        mx.effects.Tween.RemoveTweenAt(ID);
    } // End of the function
    function setTweenHandlers(update, end)
    {
        updateFunc = update;
        endFunc = end;
    } // End of the function
    function easingEquation(t, b, c, d)
    {
        return (c / 2 * (Math.sin(3.141593 * (t / d - 0.500000)) + 1) + b);
    } // End of the function
    static var ActiveTweens = new Array();
    static var Interval = 10;
    static var Dispatcher = new Object();
    var duration = 3000;
} // End of Class
