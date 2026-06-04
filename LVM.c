#include "fflang_rt.h"

static const char* l = NULL;
static FFList k = {0};
static int64_t s = 0;
static int64_t w = 0;
static FFList lc = {0};
static FFList fb = {0};
static FFWindow win = {0};
static FFList vgadat = {0};

static int64_t fbi(double x, double y);
static double pix(double fbi, double r, double g, double b);
static double vga(double x, double y, double ch);
static int64_t vgalookup(const char* ch);
static double txt(double x, double y, const char* t);
static double scr(double m, double c);
static FFList getkeys();

static int64_t fbi(double x, double y) {
    return ((int64_t)(((x * s) + (((y * w) * s) * s))) * 4);
    return 0;
}

static double pix(double fbi, double r, double g, double b) {
    for (int64_t i = 0; i < s; i++) {
        for (int64_t j = 0; j < s; j++) {
            double off = (fbi + ((j + ((i * w) * s)) * 4));
            fb.data[(int)(off)] = (float)(r);
            fb.data[(int)((off + 1))] = (float)(g);
            fb.data[(int)((off + 2))] = (float)(b);
            fb.data[(int)((off + 3))] = (float)(1.0);
        }
    }
    return 0.0;
}

static double vga(double x, double y, double ch) {
    int64_t ind = (int64_t)((((((fmod((double)(x), (double)(56)) * 4) + 2) + ((((fmod((double)(y), (double)(21)) * 6) + 2) * w) * s)) * s) * 4));
    if ((ch >= 0)) {
        for (int64_t a = 0; a < 5; a++) {
            for (int64_t b = 0; b < 3; b++) {
                double c = (double)(vgadat.data[(int)((int64_t)((((ch * 15) + (a * 3)) + b)))]);
                (void)(pix((int64_t)((ind + fbi(b, a))), c, c, c));
            }
        }
    }
    return 0.0;
}

static int64_t vgalookup(const char* ch) {
    return ff_strfind(" `1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?", ch);
    return 0;
}

static double txt(double x, double y, const char* t) {
    for (int64_t i = 0; i < (int64_t)strlen(t); i++) {
        (void)(vga((x + i), y, vgalookup(ff_strsub(t, (int64_t)(i), (int64_t)(1)))));
    }
    return 0.0;
}

static double scr(double m, double c) {
    switch ((int64_t)(m)) {
        case 0:
            (void)(txt(0, 0, "Light Virtual Machine"));
            switch ((int64_t)(c)) {
                case 0:
                    (void)(txt(0, 2, "> boot"));
                    (void)(txt(0, 3, "  configure machine"));
                    (void)(txt(0, 4, "  exit"));
                    break;
                case 1:
                    (void)(txt(0, 2, "  boot"));
                    (void)(txt(0, 3, "> configure machine"));
                    (void)(txt(0, 4, "  exit"));
                    break;
                case 2:
                    (void)(txt(0, 2, "  boot"));
                    (void)(txt(0, 3, "  configure machine"));
                    (void)(txt(0, 4, "> exit"));
                    break;
            }
            break;
        case 1:
            (void)(txt(0, 0, "Select kernel"));
            int64_t j = 0;
            for (int64_t i = 0; i < (int64_t)(((int64_t)lc.len / 2)); i++) {
                const char* sp = NULL;
                if ((i == c)) {
                    sp = "> ";
                } else {
                    sp = "  ";
                }
                (void)(txt(0, (i + 2), ff_strcat(sp, ff_strsub(l, (int64_t)(lc.data[(int)((i * 2))]), (int64_t)(lc.data[(int)(((i * 2) + 1))])))));
                j = i;
            }
            if ((c == (int64_t)(((int64_t)lc.len * 0.5)))) {
                (void)(txt(0, (j + 3), "> back"));
            } else {
                (void)(txt(0, (j + 3), "  back"));
            }
            break;
        case 2:
            (void)(txt(0, 0, "configure virtual machine"));
            switch ((int64_t)(c)) {
                case 0:
                    (void)(txt(0, 2, ff_strcat("> change registers size", "")));
                    (void)(txt(0, 3, "  back"));
                    break;
                case 1:
                    (void)(txt(0, 2, ff_strcat("  change registers size", "")));
                    (void)(txt(0, 3, "> back"));
                    break;
            }
            break;
    }
    return 0.0;
}

static FFList getkeys() {
    FFList _lt1 = ff_list_zeros((int)5);
    FFList o = _lt1;
    if ((ff_window_key(&win, "left") && (k.data[(int)(0)] == 0))) {
        o.data[(int)(0)] = (float)(1);
    }
    if ((ff_window_key(&win, "up") && (k.data[(int)(1)] == 0))) {
        o.data[(int)(1)] = (float)(1);
    }
    if ((ff_window_key(&win, "right") && (k.data[(int)(2)] == 0))) {
        o.data[(int)(2)] = (float)(1);
    }
    if ((ff_window_key(&win, "down") && (k.data[(int)(3)] == 0))) {
        o.data[(int)(3)] = (float)(1);
    }
    if ((ff_window_key(&win, "enter") && (k.data[(int)(4)] == 0))) {
        o.data[(int)(4)] = (float)(1);
    }
    k.data[(int)(0)] = (float)(ff_window_key(&win, "left"));
    k.data[(int)(1)] = (float)(ff_window_key(&win, "up"));
    k.data[(int)(2)] = (float)(ff_window_key(&win, "right"));
    k.data[(int)(3)] = (float)(ff_window_key(&win, "down"));
    k.data[(int)(4)] = (float)(ff_window_key(&win, "enter"));
    return o;
    return ff_list_zeros(0);
}

int main(void) {
    if ((ff_file_exists("config") == 0)) {
        FFList _lt2 = ff_list_zeros((int)2);
        FFList g = _lt2;
        g.data[(int)(0)] = (float)(64);
        g.data[(int)(1)] = (float)(16);
        FFList _lt3 = g;
        ff_save_list("config", _lt3);
    }
    FFList _lt4 = ff_load_list("config");
    FFList g = _lt4;
    double memlen = g.data[(int)(0)];
    double jmplen = g.data[(int)(1)];
    FFList _lt5 = ff_list_zeros((int)memlen);
    FFList mem = _lt5;
    FFList _lt6 = ff_list_zeros((int)jmplen);
    FFList jt = _lt6;
    w = 240;
    int64_t h = 135;
    s = 2;
    win = ff_window_new((int)(w * s), (int)(h * s), "LVMrt");
    FFList _lt7 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
    fb = _lt7;
    const char* vgabnk = ff_read_file("vga.dat");
    FFList _lt8 = ff_list_zeros((int)1425);
    vgadat = _lt8;
    int64_t ct = 0;
    int64_t j = 0;
    printf("%s\n", "loading vga font data");
    for (int64_t i = 0; i < (int64_t)strlen(vgabnk); i++) {
        if ((strcmp(ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1)), "\n") == 0)) {
            j = 0;
        } else {
            j = (j + 1);
            if ((((strcmp(ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1)), "0") == 0) || (strcmp(ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1)), "1") == 0)) && (j != 1))) {
                vgadat.data[(int)(ct)] = (float)((int64_t)atoi(ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1))));
                ct = (ct + 1);
            }
        }
    }
    vgabnk = "";
    printf("%lld\n", (long long)(ct));
    printf("%s\n", "done");
    int64_t c = 0;
    int64_t m = 0;
    (void)(scr(m, c));
    FFList _lt9 = ff_list_zeros((int)5);
    k = _lt9;
    l = "";
    FFList _lt10 = ff_list_zeros((int)1);
    lc = _lt10;
    int64_t r = 1;
    while (r) {
        r = ff_window_open(&win);
        FFList keys = getkeys();
        switch ((int64_t)(m)) {
            case 0:
                c = ff_clamp((double)((c - keys.data[(int)(1)]) + keys.data[(int)(3)]), (double)0, (double)2);
                switch ((int64_t)(c)) {
                    case 0:
                        int64_t ca = 0;
                        if (keys.data[(int)(4)]) {
                            l = ff_list_dir("./kernels");
                            FFList _lt11 = ff_list_zeros((int)0);
                            ff_list_free(&lc);
                            lc = _lt11;
                            ca = 0;
                            for (int64_t i = 0; i < (int64_t)strlen(l); i++) {
                                if ((strcmp(ff_strsub(l, (int64_t)(i), (int64_t)(1)), "\n") == 0)) {
                                    (void)((ff_list_append(&lc, (float)(ca)), 0));
                                    (void)((ff_list_append(&lc, (float)((i - ca))), 0));
                                    ca = (i + 1);
                                }
                            }
                            if ((ca < (int64_t)strlen(l))) {
                                (void)((ff_list_append(&lc, (float)(ca)), 0));
                                (void)((ff_list_append(&lc, (float)(((int64_t)strlen(l) - ca))), 0));
                            }
                            c = 0;
                            m = 1;
                            FFList _lt12 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt12;
                        }
                        break;
                    case 1:
                        if (keys.data[(int)(4)]) {
                            c = 0;
                            m = 2;
                            FFList _lt13 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt13;
                        }
                        break;
                    case 2:
                        if (keys.data[(int)(4)]) {
                            r = 0;
                        }
                        break;
                }
                break;
            case 1:
                c = ff_clamp((double)((c - keys.data[(int)(1)]) + keys.data[(int)(3)]), (double)0, (double)(int64_t)(((int64_t)lc.len * 0.5)));
                if ((c == (int64_t)(((int64_t)lc.len * 0.5)))) {
                    if (keys.data[(int)(4)]) {
                        c = 0;
                        m = 0;
                        FFList _lt14 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                        ff_list_free(&fb);
                        fb = _lt14;
                    }
                } else {
                    if (keys.data[(int)(4)]) {
                        FFList _lt15 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                        ff_list_free(&fb);
                        fb = _lt15;
                        const char* dat = NULL;
                        int64_t ca = 0;
                        int64_t i = 0;
                        const char* kw = NULL;
                        const char* tl = NULL;
                        int64_t t = 0;
                        const char* v = NULL;
                        int64_t ti = 0;
                        if (ff_file_exists(ff_strcat("kernels/", ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]))))) {
                            dat = ff_read_file(ff_strcat("kernels/", ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]))));
                            FFList _lt16 = ff_list_zeros((int)1);
                            FFList dati = _lt16;
                            ca = 0;
                            for (int64_t i = 0; i < (int64_t)strlen(dat); i++) {
                                if ((strcmp(ff_strsub(dat, (int64_t)(i), (int64_t)(1)), "\n") == 0)) {
                                    (void)((ff_list_append(&dati, (float)(ca)), 0));
                                    (void)((ff_list_append(&dati, (float)((i + 1))), 0));
                                    ca = 0;
                                } else {
                                    ca = (ca + 1);
                                }
                            }
                            (void)((ff_list_append(&dati, (float)(ca)), 0));
                            FFList _lt17 = ff_list_zeros((int)0);
                            FFList ki = _lt17;
                            for (int64_t i = 0; i < (int64_t)(((int64_t)dati.len * 0.5)); i++) {
                                double lo = dati.data[(int)((i * 2))];
                                double ll = dati.data[(int)(((i * 2) + 1))];
                                const char* p = ff_strsub(dat, (int64_t)(lo), (int64_t)(ll));
                                ca = 0;
                                while ((ca < ll)) {
                                    while (((ca < ll) && ((strcmp(ff_strsub(p, (int64_t)(ca), (int64_t)(1)), " ") == 0) || (strcmp(ff_strsub(p, (int64_t)(ca), (int64_t)(1)), ",") == 0)))) {
                                        ca = (ca + 1);
                                    }
                                    j = 0;
                                    while (((((j + ca) < ll) && ((strcmp(ff_strsub(p, (int64_t)((j + ca)), (int64_t)(1)), " ") == 0) != 1)) && ((strcmp(ff_strsub(p, (int64_t)((j + ca)), (int64_t)(1)), ",") == 0) != 1))) {
                                        j = (j + 1);
                                    }
                                    if ((j > 0)) {
                                        (void)((ff_list_append(&ki, (float)((lo + ca))), 0));
                                        (void)((ff_list_append(&ki, (float)(j)), 0));
                                    }
                                    ca = ((ca + j) + 1);
                                }
                            }
                            i = 0;
                            ca = 0;
                            kw = "labmovaddsubmuldivjmpvgakeyslphlt";
                            tl = "12222222210";
                            t = 0;
                            v = "";
                            FFList _lt18 = ff_list_zeros((int)0);
                            FFList a = _lt18;
                            FFList _lt19 = ff_list_zeros((int)0);
                            FFList a1 = _lt19;
                            FFList _lt20 = ff_list_zeros((int)0);
                            FFList a2 = _lt20;
                            ti = 0;
                            while ((ti < (int64_t)(((int64_t)ki.len * 0.5)))) {
                                v = ff_strsub(dat, (int64_t)(ki.data[(int)((ti * 2))]), (int64_t)(ki.data[(int)(((ti * 2) + 1))]));
                                int64_t u = 0;
                                if ((t == 0)) {
                                    if (((int64_t)a1.len < (int64_t)a.len)) {
                                        (void)((ff_list_append(&a1, (float)(0)), 0));
                                    }
                                    if (((int64_t)a2.len < (int64_t)a.len)) {
                                        (void)((ff_list_append(&a2, (float)(0)), 0));
                                    }
                                    u = (-1);
                                    for (int64_t i = 0; i < (int64_t)(((int64_t)strlen(kw) / 3)); i++) {
                                        if ((strcmp(ff_strsub(kw, (int64_t)((i * 3)), (int64_t)(3)), v) == 0)) {
                                            u = i;
                                            t = (int64_t)atoi(ff_strsub(tl, (int64_t)(i), (int64_t)(1)));
                                            break;
                                        }
                                    }
                                    if ((u == (-1))) {
                                        ca = 1;
                                        printf("%s\n", ff_strcat("invalid keyword: ", v));
                                        (void)(txt(0, 0, ff_strcat(ff_strcat("keyword '", v), "' is invalid")));
                                        (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                        (void)((ff_window_tick(&win, (int)(0)), 0));
                                        (void)((ff_sleep((double)2), 0));
                                        FFList _lt21 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                        ff_list_free(&fb);
                                        fb = _lt21;
                                        break;
                                    }
                                    (void)((ff_list_append(&a, (float)(u)), 0));
                                } else if ((t == 1)) {
                                    if ((strcmp(ff_strsub(v, (int64_t)(0), (int64_t)(1)), "c") == 0)) {
                                        (void)((ff_list_append(&a2, (float)((int64_t)atoi(ff_strsub(v, (int64_t)(1), (int64_t)strlen(v))))), 0));
                                    } else {
                                        if ((atof(v) >= 0)) {
                                            (void)((ff_list_append(&a2, (float)((atof(v) + memlen))), 0));
                                        } else {
                                            (void)((ff_list_append(&a2, (float)(atof(v))), 0));
                                        }
                                    }
                                    t = (t - 1);
                                } else if ((t == 2)) {
                                    if ((strcmp(ff_strsub(v, (int64_t)(0), (int64_t)(1)), "c") == 0)) {
                                        (void)((ff_list_append(&a1, (float)((int64_t)atoi(ff_strsub(v, (int64_t)(1), (int64_t)strlen(v))))), 0));
                                    } else {
                                        if ((atof(v) >= 0)) {
                                            (void)((ff_list_append(&a1, (float)((atof(v) + memlen))), 0));
                                        } else {
                                            (void)((ff_list_append(&a1, (float)(atof(v))), 0));
                                        }
                                    }
                                    t = (t - 1);
                                }
                                ti = (ti + 1);
                            }
                            if (((int64_t)a1.len < (int64_t)a.len)) {
                                (void)((ff_list_append(&a1, (float)(0)), 0));
                            }
                            if (((int64_t)a2.len < (int64_t)a.len)) {
                                (void)((ff_list_append(&a2, (float)(0)), 0));
                            }
                            ff_list_print(a);
                            ff_list_print(a1);
                            ff_list_print(a2);
                            if (((int64_t)strlen(dat) > 0)) {
                                if ((ca == 0)) {
                                    i = 0;
                                    for (int64_t i = 0; i < memlen; i++) {
                                        mem.data[(int)(i)] = (float)(0);
                                    }
                                    for (int64_t i = 0; i < jmplen; i++) {
                                        jt.data[(int)(i)] = (float)(0);
                                    }
                                    i = 0;
                                    while ((r && ff_window_open(&win))) {
                                        double ma1 = a1.data[(int)(i)];
                                        double ma2 = a2.data[(int)(i)];
                                        int64_t f1 = 0;
                                        int64_t f2 = 0;
                                        switch ((int64_t)(a.data[(int)(i)])) {
                                            case 0:
                                                if ((ma2 >= memlen)) {
                                                    jt.data[(int)((ma2 - memlen))] = (float)(i);
                                                } else if ((ma2 >= 0)) {
                                                    jt.data[(int)(mem.data[(int)(ma2)])] = (float)(i);
                                                } else {
                                                    jt.data[(int)(ma2)] = (float)(i);
                                                }
                                                i = (i + 1);
                                                break;
                                            case 1:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f1 = mem.data[(int)(ma2)];
                                                } else {
                                                    f1 = ma2;
                                                }
                                                mem.data[(int)(ma1)] = (float)(f1);
                                                i = (i + 1);
                                                break;
                                            case 2:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f1 = mem.data[(int)(ma2)];
                                                } else {
                                                    f1 = ma2;
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] + f1));
                                                i = (i + 1);
                                                break;
                                            case 3:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f1 = mem.data[(int)(ma2)];
                                                } else {
                                                    f1 = ma2;
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] - f1));
                                                i = (i + 1);
                                                break;
                                            case 4:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f1 = mem.data[(int)(ma2)];
                                                } else {
                                                    f1 = ma2;
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] * f1));
                                                i = (i + 1);
                                                break;
                                            case 5:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f1 = mem.data[(int)(ma2)];
                                                } else {
                                                    f1 = ma2;
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] / f1));
                                                i = (i + 1);
                                                break;
                                            case 6:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f1 = mem.data[(int)(ma2)];
                                                } else {
                                                    f1 = ma2;
                                                }
                                                if ((f1 != 0)) {
                                                    if ((ma1 >= memlen)) {
                                                        i = jt.data[(int)((ma1 - memlen))];
                                                    } else if ((ma1 >= 0)) {
                                                        i = jt.data[(int)(mem.data[(int)(ma1)])];
                                                    } else {
                                                        i = jt.data[(int)(ma1)];
                                                    }
                                                } else {
                                                    i = (i + 1);
                                                }
                                                break;
                                            case 7:
                                                if ((ma2 >= memlen)) {
                                                    f2 = (ma2 - memlen);
                                                } else if ((ma2 >= 0)) {
                                                    f2 = mem.data[(int)(ma2)];
                                                } else {
                                                    f2 = ma2;
                                                }
                                                if ((ma1 >= memlen)) {
                                                    f1 = (ma1 - memlen);
                                                } else if ((ma1 >= 0)) {
                                                    f1 = mem.data[(int)(ma1)];
                                                } else {
                                                    f1 = ma1;
                                                }
                                                (void)(vga((f1 % 56), (int64_t)((f1 / 56)), f2));
                                                i = (i + 1);
                                                break;
                                            case 8:
                                                if ((ma1 >= memlen)) {
                                                    f1 = (ma1 - memlen);
                                                } else if ((ma1 >= 0)) {
                                                    f1 = mem.data[(int)(ma1)];
                                                } else {
                                                    f1 = ma1;
                                                }
                                                mem.data[(int)(ma2)] = (float)(ff_window_key(&win, ff_strsub(" `1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?", (int64_t)(f1), (int64_t)(1))));
                                                i = (i + 1);
                                                break;
                                            case 9:
                                                if ((ma2 >= memlen)) {
                                                    (void)((ff_sleep((double)(ma2 - memlen)), 0));
                                                } else if ((ma2 >= 0)) {
                                                    (void)((ff_sleep((double)mem.data[(int)(ma2)]), 0));
                                                } else {
                                                    (void)((ff_sleep((double)ma2), 0));
                                                }
                                                i = (i + 1);
                                                break;
                                            case 10:
                                                r = 0;
                                                break;
                                                break;
                                        }
                                        i = (i % (int64_t)a.len);
                                        (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                        (void)((ff_window_tick(&win, (int)(1024)), 0));
                                    }
                                    FFList _lt22 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                    ff_list_free(&fb);
                                    fb = _lt22;
                                    r = 1;
                                } else {
                                    (void)(txt(0, 0, ff_strcat(ff_strcat("kernels/", ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]))), " is invalid")));
                                    (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                    (void)((ff_window_tick(&win, (int)(0)), 0));
                                    (void)((ff_sleep((double)2), 0));
                                    FFList _lt23 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                    ff_list_free(&fb);
                                    fb = _lt23;
                                }
                            } else {
                                (void)(txt(0, 0, ff_strcat(ff_strcat("kernels/", ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]))), " is empty")));
                                (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                (void)((ff_window_tick(&win, (int)(0)), 0));
                                (void)((ff_sleep((double)2), 0));
                                FFList _lt24 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                ff_list_free(&fb);
                                fb = _lt24;
                            }
                        } else {
                            (void)(txt(0, 0, ff_strcat(ff_strcat("kernels/", ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]))), " does not exist")));
                            (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                            (void)((ff_window_tick(&win, (int)(0)), 0));
                            (void)((ff_sleep((double)2), 0));
                            FFList _lt25 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt25;
                        }
                        c = 0;
                    }
                }
                break;
            case 2:
                c = ff_clamp((double)((c - keys.data[(int)(1)]) + keys.data[(int)(3)]), (double)0, (double)1);
                if (((c == 1) && keys.data[(int)(4)])) {
                    c = 0;
                    m = 0;
                    FFList _lt26 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                    ff_list_free(&fb);
                    fb = _lt26;
                }
                break;
        }
        (void)(scr(m, c));
        (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
        (void)((ff_window_tick(&win, (int)(30)), 0));
    }

    cleanupkernel();
    return 0;
}