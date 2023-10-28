void
runAutostart(void) {
	system("feh --bg-scale wallpaper/bg6.jpg &");
	system("compton -f --vsync opengl-oml &");
	system("~/dwm/status &");
	system("xss-lock ~/dwm/lock &");
	system("sleep 2 && setxkbmap -option 'ctrl:nocaps' ; setxkbmap 'us,ru' ',winkeys' 'grp:alt_shift_toggle' &");
}
