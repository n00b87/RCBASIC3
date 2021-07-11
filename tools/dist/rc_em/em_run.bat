cd emsdk
SET OUT_HTML=C:\Users\omega\Desktop\tst312\out\gf_web\gf.html
SET PROG_LOCATION=C:\Users\omega\Desktop\tst312@\
SET PROG_NAME=gf
SET THEORA_LIB=C:\Users\omega\Desktop\Projects\RCBasic Package Tool\assets\rc_em\libtheora-1.1.1\out\lib
SET THEORA_INCLUDE=C:\Users\omega\Desktop\Projects\RCBasic Package Tool\assets\rc_em\libtheora-1.1.1\out\include

emsdk activate latest

emsdk_env.bat

echo path is C:\Users\omega\Desktop\Projects\RCBasic Package Tool\assets\rc_em

cd ..\rcbasic_runtime


echo running command: em++ main.cpp theoraplay.c "-L%THEORA_LIB%" "-I%THEORA_INCLUDE%" -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_GFX=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_NET=2 -s USE_OGG=1 -s USE_VORBIS=1 -ltheora -ltheoradec -o "%OUT_HTML%" --preload-file "%PROG_LOCATION%" -O3 -s ASYNCIFY -s SDL2_IMAGE_FORMATS='["bmp","png","xpm"]' -s TOTAL_MEMORY=134217728

echo --------------------------

em++ main.cpp theoraplay.c "-L%THEORA_LIB%" "-I%THEORA_INCLUDE%" -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_GFX=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_NET=2 -s USE_OGG=1 -s USE_VORBIS=1 -ltheora -ltheoradec -o "%OUT_HTML%" --preload-file %PROG_LOCATION% -O3 -s ASYNCIFY -s SDL2_IMAGE_FORMATS='["bmp","png","xpm"]' -s TOTAL_MEMORY=134217728

cd ..\

