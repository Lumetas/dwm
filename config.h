/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int border_radius = 0;
static const unsigned int gappih    = 13;
static const unsigned int gappiv    = 13;
static const unsigned int gappoh    = 13;
static const unsigned int gappov    = 13;
static const int smartgaps          = 0;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "FontAwesome:size=10" }; /* добавлен FontAwesome для иконок */
static const char dmenufont[]       = "monospace:size=10";
/* Цветовая схема на основе новой палитры */
static const char col_dark0[]      = "#051b35";   /* Глубокий синий */
static const char col_dark1[]      = "#0e4466";   /* Тёмный сине-серый */
static const char col_dark2[]      = "#1d5e72";   /* Серо-синий */
static const char col_dark3[]      = "#246f8b";   /* Умеренный синий */
static const char col_dark4[]      = "#308fad";   /* Светлый синий */
static const char col_light0[]     = "#d6b8a1";   /* Светло-бежевый */
static const char col_light1[]     = "#bb794a";   /* Коричневый */
static const char col_light2[]     = "#a34c65";   /* Приглушённый розовый */
static const char col_light3[]     = "#644862";   /* Тёмный фиолетово-коричневый */
static const char col_light4[]     = "#53b0bc";   /* Бирюзовый */

/* Акцентные цвета */
static const char col_accent_blue[] = "#308fad";
static const char col_accent_green[] = "#53b0bc";
static const char col_accent_yellow[] = "#d6b8a1";
static const char col_accent_red[] = "#a34c65";

/* Текстовые цвета */
static const char col_text_normal[] = "#d6b8a1";
static const char col_text_selected[] = "#ffffff";
static const char col_text_dim[] = "#246f8b";

static const char *colors[][3]      = {
	/*               fg (текст)        bg (фон)        border   */
	[SchemeNorm] = { col_text_normal,     col_dark0,      col_light3 },	// passive tag
	[SchemeSel]  = { col_text_selected,   col_dark2,      col_light4 }, // active tag
	[SchemeApp] =  { col_text_selected,   col_dark0,      col_light0 }, // appname
};

/* Дополнительные схемы для bar (если используются в config.def.h) */
static const char col_bar_bg[]      = "#0C0B15";   /* Фон бара */
static const char col_bar_fg[]      = "#D18AFF";   /* Текст бара */
// static const char col_bar_active[]  = "#E0B0FF";   /* Активный тег */
static const char col_bar_active[]  = "#5A5775";   /* Активный тег */
static const char col_bar_inactive[]= "#5A5775";   /* Неактивный тег */
// static const char col_bar_urgent[]  = "#FF6B8B";   /* Срочный тег */
static const char col_bar_urgent[]  = "#5A5775";   /* Срочный тег */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const int restartdwm = 1; /* включить автоперезапуск */

/* Медиаклавиши */
#define XF86XK_AudioLowerVolume 0x1008ff11
#define XF86XK_AudioRaiseVolume 0x1008ff13
#define XF86XK_AudioMute        0x1008ff12
#define XF86XK_MonBrightnessUp  0x1008ff02
#define XF86XK_MonBrightnessDown 0x1008ff03
#define XF86XK_AudioPlay        0x1008ff14
#define XF86XK_AudioPrev        0x1008ff16
#define XF86XK_AudioNext        0x1008ff17
#define XF86XK_KbLightUp		0x1008ff05
#define XF86XK_KbLightDown		0x1008ff06

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/* Команда для увеличения яркости клавиатуры с ограничением до 255 */
static const char *kbd_backlight_up[] = { 
    "/bin/bash", "-c", 
    "brightness=$(cat /sys/class/leds/smc::kbd_backlight/brightness); "
    "new_brightness=$((brightness + 50)); "
    "if [ $new_brightness -gt 255 ]; then new_brightness=255; fi; "
    "echo $new_brightness > /sys/class/leds/smc::kbd_backlight/brightness", 
    NULL 
};

/* Команда для уменьшения яркости клавиатуры с ограничением до 0 */
static const char *kbd_backlight_down[] = { 
    "/bin/bash", "-c", 
    "brightness=$(cat /sys/class/leds/smc::kbd_backlight/brightness); "
    "new_brightness=$((brightness - 50)); "
    "if [ $new_brightness -lt 0 ]; then new_brightness=0; fi; "
    "echo $new_brightness > /sys/class/leds/smc::kbd_backlight/brightness", 
    NULL 
};

static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	// { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = kando } },
	{ MODKEY|ControlMask|ShiftMask, XK_r,      quit,           {1} }, /* перезапуск dwm с сохранением окон */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_u,      spawn,          {.v = (const char*[]){"/bin/sh", "-c", "firefox-esr", NULL}}},
	{ MODKEY,                       XK_p,      spawn,          {.v = (const char*[]){"/bin/sh", "-c", "flameshot gui", NULL}}},
	{ MODKEY,                       XK_s,      spawn,          {.v = (const char*[]){"/bin/sh", "-c", "~/dwm/screen -a", NULL}}},
	{ MODKEY,                       XK_m,      spawn,          {.v = (const char*[]){"/bin/sh", "-c", "~/dwm/lock", NULL}}},
	{ MODKEY,                       XK_n,      spawn,          {.v = (const char*[]){"/bin/sh", "-c", "nvide", NULL}}},
	
	/* Медиаклавиши */
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = (const char*[]){"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL}} },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = (const char*[]){"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL}} },
    { 0, XF86XK_KbLightUp,   spawn, {.v = kbd_backlight_up} },
    { 0, XF86XK_KbLightDown, spawn, {.v = kbd_backlight_down} },
	{ 0,                            XF86XK_AudioMute,        spawn, {.v = (const char*[]){"pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL}} },
	{ 0,                            XF86XK_MonBrightnessUp,  spawn, {.v = (const char*[]){"brightnessctl", "set", "+5%", NULL}} },
	{ 0,                            XF86XK_MonBrightnessDown,spawn, {.v = (const char*[]){"brightnessctl", "set", "5%-", NULL}} },
	{ 0,                            XF86XK_AudioPlay,        spawn, {.v = (const char*[]){"playerctl", "play-pause", NULL}} },
	{ 0,                            XF86XK_AudioPrev,        spawn, {.v = (const char*[]){"playerctl", "previous", NULL}} },
	{ 0,                            XF86XK_AudioNext,        spawn, {.v = (const char*[]){"playerctl", "next", NULL}} },
	
	
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_y,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    // { MODKEY,                       XK_f,      fullscreen,     {0} },
	// { MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating,      {0} },
	// { MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
    // gaps
    { MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	// { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

