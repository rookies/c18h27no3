# Configuration

## Keys (specification not finished)
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
 * CONTROL__KEY_GOLEFT:int
  * Keycode for walking left
  * **Default:** sf::Keyboard::Left
 * CONTROL__KEY_GORIGHT:int
  * Keycode for walking right
  * **Default:** sf::Keyboard::Right
 * CONTROL__KEY_JUMP:int
  * Keycode for jumping
  * **Default:** sf::Keyboard::Space
 * CONTROL__KEY_SCREENSHOT:int
  * Keycode for taking a screenshot
  * **Default:** sf::Keyboard::F1
 * CONTROL__KEY_SHOOT:int
  * Keycode for shooting
  * **Default:** sf::Keyboard::LControl
 * CONTROL__KEY_WEAPONCHANGE:int
  * Keycode for changing the weapon
  * **Default:** sf::Keyboard::Tab
 * SOUND__ENABLE_MENU_MUSIC:int
  * Menu background music volume (0-100)
  * Special values:
   * 0 = disabled
  * **Default:** 100

## Unix
**File:** ~/.@GAME@/config.txt

### Format
```
@KEY@#@VALUE@
@KEY@#@VALUE@
[...]
```

## Windows
**Registry:** HKEY_CURRENT_USER\Software\@CORPORATION@\@GAME@

### Format
```
@KEY@:REG_SZ = @VALUE@
@KEY@:REG_SZ = @VALUE@
[...]
```
