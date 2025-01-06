/* See LICENSE file for copyright and license details. */

/* Custom functions */
// This will only work for at most 2 monitors
static void
focusmonx(const Arg *arg)
{
	Monitor *m = (arg->i && mons->next) ? mons->next : mons;
    if (m == selmon)
        return;

	unfocus(selmon->sel, 0);
	selmon = m;
	focus(NULL);
}
//
// This will also only work for at most 2 monitors
void
tagmonx(const Arg *arg)
{
	Monitor *m = (arg->i && mons->next) ? mons->next : mons;
    if (m == selmon)
        return;
    if (selmon->sel == NULL)
        return;

	sendmon(selmon->sel, m);
}

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "monospace:size=10" };
static const char my_normal_bgc[]   = "#2d3560";
static const char my_normal_fgc[]   = "#b0b0b0";
static const char my_normal_brd[]   = "#404040";
static const char my_selected_bgc[] = "#2d3560";
static const char my_selected_fgc[] = "#ffffff";
static const char my_selected_brd[] = "#2d3560";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { my_normal_fgc, my_normal_bgc, my_normal_brd },
	[SchemeSel]  = { my_selected_fgc, my_selected_bgc, my_selected_brd  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating  canfocus   monitor   border width */
 	{ "Gimp",     NULL,       NULL,       0,            1,         1,         -1, -1 },
 	{ "Firefox",  NULL,       NULL,       1 << 8,       0,         1,         -1, -1 },
	{ "Synapse",  NULL,       NULL,       0,            0,         0,         -1, 0 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]  = { "kitty", NULL };
static const char *discordcmd[]  = { "discord", NULL };
static const char *webbrowsercmd[]  = { "waterfox-g", NULL };
static const char *filebrowsercmd[]  = { "pcmanfm", NULL };
static const char *musiccmd[]  = { "spotify", NULL };
static const char *screenshotcmd[]  = { "/home/erik/.local/bin/screenshot.sh", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ ControlMask|AltMask,          XK_t,      spawn,          {.v = termcmd } },
	{ ControlMask|AltMask,          XK_d,      spawn,          {.v = discordcmd } },
	{ ControlMask|AltMask,          XK_w,      spawn,          {.v = webbrowsercmd } },
	{ ControlMask|AltMask,          XK_h,      spawn,          {.v = filebrowsercmd } },
	{ ControlMask|AltMask,          XK_m,      spawn,          {.v = musiccmd } },
    { MODKEY,                       XK_x,      spawn,          {.v = screenshotcmd} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_period, incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_comma,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_d,      focusmonx,      { .i = 0 } },
	{ MODKEY,                       XK_r,      focusmonx,      { .i = 1 } },
	{ MODKEY|ShiftMask,             XK_d,      tagmonx,        { .i = 0 } },
	{ MODKEY|ShiftMask,             XK_r,      tagmonx,        { .i = 1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

