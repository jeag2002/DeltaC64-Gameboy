call D:\workspace-gameboy\workspace-final-3\clean.bat

D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wf--debug -Wf-bo6 -ID:/workspace-gameboy/workspace-final-3/hugedriver/include -c D:\workspace-gameboy\workspace-final-3\sample_song.c -o D:\workspace-gameboy\workspace-final-3\sample_song.o
D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o D:\workspace-gameboy\workspace-final-3\global.o D:\workspace-gameboy\workspace-final-3\global.c
D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wf-bo4 -Wl-m -Wf--debug -Wl-y -Wl-w -c -o D:\workspace-gameboy\workspace-final-3\splash_map.o D:\workspace-gameboy\workspace-final-3\splash_map.c
D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wf-bo4 -Wl-m -Wf--debug -Wl-y -Wl-w -c -o D:\workspace-gameboy\workspace-final-3\splash_tile_map.o D:\workspace-gameboy\workspace-final-3\splash_tile_map.c
D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wf--debug -ID:/workspace-gameboy/workspace-final-3/hugedriver/include -c D:\workspace-gameboy\workspace-final-3\splash.c -o D:\workspace-gameboy\workspace-final-3\splash.o
D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o D:\workspace-gameboy\workspace-final-3\main.o D:\workspace-gameboy\workspace-final-3\main.c


D:\workspaces\workspaceGameBoy\gbdk-2020-1\bin\lcc -msm83:gb -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -Wl-yt0x01 -Wl-yo8 -Wl-ya0 -ID:/workspace-gameboy/workspace-final-3/hugedriver/include -Wl-lD:/workspace-gameboy/workspace-final-3/hugedriver/gbdk/hUGEDriver.lib -o D:\workspace-gameboy\workspace-final-3\main_1.gb D:\workspace-gameboy\workspace-final-3\sample_song.o D:\workspace-gameboy\workspace-final-3\global.o D:\workspace-gameboy\workspace-final-3\splash_map.o D:\workspace-gameboy\workspace-final-3\splash_tile_map.o D:\workspace-gameboy\workspace-final-3\splash.o  D:\workspace-gameboy\workspace-final-3\main.o 