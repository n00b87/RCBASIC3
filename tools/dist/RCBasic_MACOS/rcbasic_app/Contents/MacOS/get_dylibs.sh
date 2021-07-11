cp /usr/local/opt/libvorbis/lib/libvorbisfile.3.dylib libvorbisfile.3.dylib
cp /usr/local/opt/libvorbis/lib/libvorbis.0.dylib libvorbis.0.dylib
cp /usr/local/opt/libogg/lib/libogg.0.dylib libogg.0.dylib
cp /usr/local/opt/theora/lib/libtheoradec.1.dylib libtheoradec.1.dylib
cp /usr/local/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib libSDL2_ttf-2.0.0.dylib
cp /usr/local/opt/sdl2_net/lib/libSDL2_net-2.0.0.dylib libSDL2_net-2.0.0.dylib
cp /usr/local/opt/sdl2_mixer/lib/libSDL2_mixer-2.0.0.dylib libSDL2_mixer-2.0.0.dylib
cp /usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib libSDL2_image-2.0.0.dylib
cp /usr/local/opt/sdl2_gfx/lib/libSDL2_gfx-1.0.0.dylib libSDL2_gfx-1.0.0.dylib
cp /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib libSDL2-2.0.0.dylib
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbisfile.3.dylib @executable_path/libvorbisfile.3.dylib rcbasic
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbis.0.dylib @executable_path/libvorbis.0.dylib rcbasic
install_name_tool -change /usr/local/opt/libogg/lib/libogg.0.dylib @executable_path/libogg.0.dylib rcbasic
install_name_tool -change /usr/local/opt/theora/lib/libtheoradec.1.dylib @executable_path/libtheoradec.1.dylib rcbasic
install_name_tool -change /usr/local/opt/theora/lib/libtheora.0.dylib @executable_path/libtheora.0.dylib rcbasic
install_name_tool -change /usr/local/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib @executable_path/libSDL2_ttf-2.0.0.dylib rcbasic
install_name_tool -change /usr/local/opt/sdl2_net/lib/libSDL2_net-2.0.0.dylib @executable_path/libSDL2_net-2.0.0.dylib rcbasic
install_name_tool -change /usr/local/opt/sdl2_mixer/lib/libSDL2_mixer-2.0.0.dylib @executable_path/libSDL2_mixer-2.0.0.dylib rcbasic
install_name_tool -change /usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib @executable_path/libSDL2_image-2.0.0.dylib rcbasic
install_name_tool -change /usr/local/opt/sdl2_gfx/lib/libSDL2_gfx-1.0.0.dylib @executable_path/libSDL2_gfx-1.0.0.dylib rcbasic
install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2-2.0.0.dylib rcbasic
