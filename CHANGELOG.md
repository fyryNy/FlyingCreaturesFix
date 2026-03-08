[1.3.2]
- Updated gothic-api and union-api

[1.3.1]
- Fix addresses for g2/g2a ApplySomeSettings partialhook

[1.3.0]
- Switched back to PartialHooks for `Game_ApplySettings`  
- Switched HookType for `zCAIPlayer::CheckPhysics` hook to `Hook_Detours` to assert compatibility with Union 1.0m plugins  
- Removed unused hooks and empty funcs  

[1.2.0]
- Updated gothic-api to fix some crashes  
- Change Hooktype from Hook_Detours to Hook_Auto to prevent crashes in CoM and/or possibly any other Ikarus/Lego mods  
- Split `EdgesFixAffectAllNpcs` into 3 separate settings  
  - EdgesFixAffectPlayer - if true, stops preventing the player from falling off edges or cliffs (walk/sneak)  
  - EdgesFixAffectHumans - if true, stops preventing humans from falling off edges or cliffs  
  - EdgesFixAffectOtherMonsters - if true, stops preventing other monsters from falling off edges or cliffs  

[1.1.0]  
- Switched to [Patrix' union plugin template](https://github.com/Patrix9999/union-plugin-template)  
- Added new option `EdgesFixAffectAllNpcs` in gothic.ini/plugin settings menu.  
  If set to true, all NPCs will be prevented from falling off edges or cliffs.  
  If set to false, only flying monsters (Harpy, Bloodfly, Demon, Skeleton Mage) will be prevented from falling off edges or cliffs.  

[1.0.0]  
- Initial release  