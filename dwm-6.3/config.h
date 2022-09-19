  /* See LICENSE file fof copyright and license details. */

/* appearance */
static unsigned int lineheight = 15;            /* -h option; minimum height of a menu line     */
static const unsigned int gappx     = 9;        /* gaps between windows */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Medium:size=12", "monospace:size=12" };
static const char dmenufont[]       = "Iosevka Medium Oblique:size=12";
static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#3f4148";
static const char col_gray2[]       = "#4e5375";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_green[]       = "#00A19D";
static const char col_white[]       = "#fbebc1";
/* static const char col_yellow[]      = "#FFB344"; */
static const char col_current[]      = "#e36891";
/* static const char col_primary[]     = "#018bad"; */
/* static const char col_primary[]     = "#dea7bb"; */
static const char col_primary[]     = "#da9cb4";
static const char *colors[][3]      = {
  /*               fg         bg          border      */
  [SchemeNorm] = { col_white, col_gray1,  col_green   },
  [SchemeSel]  = { col_white, col_primary, col_current  },
};

/* tagging */
static const char *tags[] = { "○", "○", "○", "○", "○", "○", "○", "○", "○" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp",     NULL,       NULL,       0,            0,           -1 },
  /* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
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
#define     XF86AudioPlay           0x1008ff14
#define     XF86AudioNext           0x1008ff17
#define     XF86AudioPrev           0x1008ff16
#define     XF86AudioLowerVolume    0x1008ff11
#define     XF86AudioRaiseVolume    0x1008ff13
/* #define     XF86AudioMute           0x1008ff12 //not implemented */ 
#define     MODKEY                  Mod4Mask
#define     ALT                     Mod1Mask
#define     TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]      = { "st", NULL };
static const char *kittyTerm[]    = { "kitty", NULL };
static const char *firefox[]      = { "firefox & notify-send -t 5000\"Firefox is starting...\"", NULL };
static const char *slock[]        = { "cmus-remote -U & slock", NULL };

/* alt = Mod1Mask; ctrl = ControlMask; */
static Key keys[] = {
  /* modifier                     key                     function        argument */
  { MODKEY,                       XK_d,                   spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return,              spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_Return,              spawn,          {.v = kittyTerm } },
  /* { MODKEY,                       XK_n,                   spawn,          {.v = firefox } }, */
  { MODKEY,                       XK_n,                   spawn,          SHCMD("notify-send -t 5000 \"Firefox is starting...\" \"\"; firefox") },
  { ALT|ControlMask,              XK_l,                   spawn,          {.v = slock } },
  { MODKEY,                       XK_b,                   togglebar,      {0} },
  { MODKEY,                       XK_j,                   focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,                   focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,                   incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_i,                   incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,                   setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,                   setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_space,               zoom,           {0} },
  { MODKEY,                       XK_Tab,                 view,           {0} },
  { MODKEY,                       XK_q,                   killclient,     {0} },
  { MODKEY,                       XK_t,                   setlayout,      {.v = &layouts[0]} },
  { MODKEY|ShiftMask,             XK_f,                   setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,                   setlayout,      {.v = &layouts[2]} },
  // { MODKEY,                       XK_space,  setlayout,      {0} },
  // { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_f,                   togglefullscr,  {0} },
  { MODKEY,                       XK_0,                   view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,                   tag,            {.ui = ~0 } },
  { MODKEY,                       XK_x,                   focusmon,       {.i = -1 } },
  { MODKEY,                       XK_z,                   focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_x,                   tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_z,                   tagmon,         {.i = +1 } },
  { MODKEY,                       XK_minus,               setgaps,        {.i = -1 } },
  { MODKEY,                       XK_equal,               setgaps,        {.i = +1 } },
  { MODKEY|ShiftMask,             XK_equal,               setgaps,        {.i = 0  } },
  { MODKEY,                       XK_c,                   spawn,          SHCMD("set-cursor") },
  { MODKEY|ShiftMask,             XK_r,                   spawn,          SHCMD("pkill X && startx") },
  { 0,                            XF86AudioPlay,          spawn,          SHCMD("cmus-remote -u") },
  { 0,                            XF86AudioPrev,          spawn,          SHCMD("cmus-remote -r") },
  { 0,                            XF86AudioNext,          spawn,          SHCMD("cmus-remote -n") },
  { ShiftMask,                    XF86AudioPrev,          spawn,          SHCMD("cmus-remote -k -10") },
  { ShiftMask,                    XF86AudioNext,          spawn,          SHCMD("cmus-remote -k +10") },
  { 0,                            XF86AudioRaiseVolume,   spawn,          SHCMD("cmus-remote -v +5%") },
  { 0,                            XF86AudioLowerVolume,   spawn,          SHCMD("cmus-remote -v -5%") },
  /* { 0,                            XF86AudioMute,          spawn,          SHCMD("cmus-remote") }, //not implemented*/
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
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

