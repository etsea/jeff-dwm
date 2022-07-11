/* APPEARANCE */
/* ---------- */
static const unsigned int borderpx = 1; // window border size
static const unsigned int gappx = 10;   // gap size between windows
static const unsigned int snap = 32;    // snap pixel
static const int showbar = 1;           // 0 means no bar
static const int topbar = 1;            // 0 means bottom bar
static const int horizpadbar = 12;      // horizontal bar padding
static const int vertpadbar = 8;        // vertical bar padding

static const char color_nfg[] = "#f8eee5"; // normal scheme fg color
static const char color_nbg[] = "#042843"; // normal scheme bg color
static const char color_nbd[] = "#0e4c73"; // normal scheme border color
static const char color_sfg[] = "#ff9278"; // selected scheme fg color
static const char color_sbg[] = "#0e4c73"; // selected scheme bg color
static const char color_sbd[] = "#d96248"; // selected scheme border color

static const char *colors[][3] = {
    // [SchemeName] = {foreground_color, background_color, border_color},
    [SchemeNorm] = {color_nfg, color_nbg, color_nbd},
    [SchemeSel] = {color_sfg, color_sbg, color_sbd},
};

static const unsigned int barfgalpha = 0xff; // 0-255 alpha value for bar fg
static const unsigned int barbgalpha = 0xd0; // 0-255 alpha value for bar bg
static const unsigned int barbdalpha = 0xff; // 0-255 alpha value for bar border

static const unsigned int alphas[][3] = {
    // [SchemeName] = {foreground_alpha, background_alpha, border_alpha},
    [SchemeNorm] = {barfgalpha, barbgalpha, barbdalpha},
    [SchemeSel] = {barfgalpha, barbgalpha, barbdalpha},
};

static const char *fonts[] = {
    // fonts for dwm to have access to
    "CaskaydiaCove Nerd Font:size=12:antialias=true:autohint=true",
};
static const char dmenufont[] =
    "CaskaydiaCove Nerd Font:size=12"; // font for dmenu app list

/* TAGGING */
/* ------- */
static const char *tags[] = {"1", "2", "3", "4", "5",
                             "6", "7", "8", "9"}; // virtual desktop tag names

static const Rule rules[] = {
    // {class, instance, title, tags_mask, isfloating, monitor}
    {"Gimp", NULL, NULL, 0, 1, -1},
    //{"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* LAYOUTS */
/* ------- */
static const float mfact = 0.5; // master area size factor [0.5...0.95]
static const int nmaster = 1;   // number of clients in master area
static const int resizehints =
    0; // 1 means respect size hints in tiled resizals
static const int lockfullscreen =
    1; // 1 will force focus on the fullscreen window

static const Layout layouts[] = {
    // {symbol, arrangement_function},
    {"[]=", tile}, // first entry is default
    {"><>", NULL}, // no layout function means floating behavior
    {"[M]", monocle},
};

/* KEY DEFINITIONS */
/* --------------- */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

// helper for spawning shell commands in pre-dwm5.0 fashion
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", "cmd", NULL }                     \
  }

/* COMMANDS */
/* -------- */
static char dmenumon[2] = "0"; // component of dmenucmd, manipulated in spawn()
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,  "-fn", dmenufont, "-nb", color_nfg, "-nf",
    color_nbg,   "-sb", color_sfg, "-sf", color_sbg, NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *shufbgcmd[] = {"shufbg", NULL};
static const char *browsercmd[] = {"firefox", NULL};

static Key keys[] = {
    // {modifier, key, function, argument},
    {MODKEY | ShiftMask, XK_b, spawn, {.v = shufbgcmd}}, // change wallpaper
    {MODKEY, XK_Return, spawn, {.v = dmenucmd}},         // spawn dmenu launcher
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}}, // spawn terminal
    {MODKEY, XK_b, spawn, {.v = browsercmd}},               // spawn browser
    {MODKEY, XK_s, togglebar, {0}},                         // toggle status bar
    {MODKEY, XK_j, focusstack, {.i = +1}},                  // focus next window
    {MODKEY, XK_k, focusstack, {.i = -1}},                  // focus last window
    {MODKEY, XK_i, incnmaster, {.i = +1}},         // increase master stack +1
    {MODKEY, XK_d, incnmaster, {.i = -1}},         // decrease master stack -1
    {MODKEY, XK_h, setmfact, {.f = -0.05}},        // decrease mfact by -0.05
    {MODKEY, XK_l, setmfact, {.f = +0.05}},        // increase mfact by +0.05
    {MODKEY | ControlMask, XK_Return, zoom, {0}},  // focused window to master
    {MODKEY, XK_Tab, view, {0}},                   // toggle desktop tags
    {MODKEY | ShiftMask, XK_c, killclient, {0}},   // kill window
    {MODKEY, XK_r, quit, {1}},                     // restart dwm
    {MODKEY | ShiftMask, XK_r, quit, {0}},         // kill dwm
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}}, // swap to tiled layout
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}}, // swap to floating layout
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}}, // swap to monocle layout
    {MODKEY, XK_space, setlayout, {0}},            // toggle layouts
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}}, // toggle window float
    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}}, // toggle window fullscreen
    {MODKEY, XK_0, view, {.ui = ~0}},               // view all tags
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},    // tag window for all tags
    {MODKEY, XK_comma, focusmon, {.i = -1}},  // decrement focused monitor -1
    {MODKEY, XK_period, focusmon, {.i = +1}}, // increment focused monitor +1
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},  // tag on last monitor
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}}, // tag on next monitor

    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

/* BUTTON DEFINITIONS */
/* ------------------ */
static Button buttons[] = {
    // {click, event_mask, button, function, argument},
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
