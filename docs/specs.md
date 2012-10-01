# Configuration

## Keys
 * GENERAL__LANGUAGE:string
  * Language of the game
  * **Default:** en
 * GENERAL__FPSCOUNTER:bool
  * Enable FPS gauge
  * **Default:** false
 * GRAPHICS__RESOLUTION_X:int
  * Screen resolution (width)
  * Special Values:
   * 0 = get from Desktop Video Mode
  * **Default:** 0
 * GRAPHICS__RESOLUTION_Y:int
  * Screen resolution (height)
  * Special Values:
   * 0 = get from Desktop Video Mode
  * **Default:** 0
 * GRAPHICS__FULLSCREEN:bool
  * Enable fullscreen mode
  * **Default:** true
 * CONTROL__...
 * SOUND__...
 * ...

## Unix
**File:** ~/.@GAME@/config.txt

### Format
```
@KEY@#@VALUE@
@KEY@#@VALUE@
...
```

## Windows
**Registry:** HKEY_CURRENT_USER\Software\@CORPORATION@\@GAME@

### Format
```
@KEY@:REG_SZ = @VALUE@
@KEY@:REG_SZ = @VALUE@
...
```
