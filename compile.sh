g++ -o gui -std=c++14 -pedantic -I/c/fltk/fltk-1.3.7_win64/include -mwindows -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -I.. GUI_menu.cpp main.cpp ../Graph_lib/Graph.cpp ../Graph_lib/GUI.cpp ../Graph_lib/Window.cpp -L/c/fltk/fltk-1.3.7_win64/lib -mwindows -lfltk_images -lfltk_png -lfltk_z -lfltk_jpeg -lfltk -ldl -lole32 -luuid -lcomctl32