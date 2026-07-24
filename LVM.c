#include "fflang_rt.h"

static FFList mem = {0};
static FFList fb = {0};
static int64_t w = 0;
static int64_t n_embd = 0;
static FFList g = {0};
static FFMutex lock1 = {0};
static FFMutex lock2 = {0};
static FFMutex lock0 = {0};
static int64_t memb_off = 0;
static const char* l = NULL;
static double memlen = 0.0;
static FFList k = {0};
static FFList lc = {0};
static FFList vgadat = {0};
static int64_t s = 0;
static FFMutex lock3 = {0};
static FFWindow win = {0};
static FFBlob mblob = {0};
static int64_t h = 0;

static int64_t fbi(double x, double y);
static double pix(double fbi, double r, double g, double b);
static double vga(double x, double y, double ch);
static int64_t vgalookup(const char* ch);
static double txt(double x, double y, const char* t);
static double scr(double m, double c);
static FFList getkeys();
static double rdm(double v);
static double rd(double v, FFList priv, FFList mem, double memlen, double PRIV);
static double wr(double d, double val, FFList priv, FFList mem, double PRIV);
static FFList gpack(FFList gins, FFList mem, double vlen);
static double gunpack(FFList outbuf, FFList mem, double obase, double vlen);
static int64_t core(FFList a, FFList a1, FFList a2, FFList mem, FFList jt, double ip0, double tid0, double count, double memlen);
static double clrrow(double row);
static double showstr(const char* t, double row);
static const char* readline(double row);
static int64_t gsz(double t);
static double gskipval(double o, double t);
static double gguf_parse();
static double load_emb(double tok, double base);

/* thread spawn glue */
struct _spawn_core { FFList a0; FFList a1; FFList a2; FFList a3; FFList a4; double a5; double a6; double a7; double a8; int64_t _ret; };
static void* _tramp_core(void* _p) {
    struct _spawn_core* _s = (struct _spawn_core*)_p;
    _s->_ret = core(_s->a0, _s->a1, _s->a2, _s->a3, _s->a4, _s->a5, _s->a6, _s->a7, _s->a8);
    return NULL;
}

static int64_t fbi(double x, double y) {
    return ((int64_t)(((x * s) + (((y * w) * s) * s))) * 4);
}

static double pix(double fbi, double r, double g, double b) {
    for (int64_t i = 0; i < s; i++) {
        double off = 0.0;
        for (int64_t j = 0; j < s; j++) {
            off = (double)((fbi + ((j + ((i * w) * s)) * 4)));
            fb.data[(int)(off)] = (float)(r);
            fb.data[(int)((off + 1))] = (float)(g);
            fb.data[(int)((off + 2))] = (float)(b);
            fb.data[(int)((off + 3))] = (float)(1.0);
        }
    }
    return 0.0;
}

static double vga(double x, double y, double ch) {
    int64_t ind = (int64_t)((int64_t)((((((ff_fmod_py((double)(x), (double)(56)) * 4) + 2) + ((((ff_fmod_py((double)(y), (double)(21)) * 6) + 2) * w) * s)) * s) * 4)));
    if ((ch >= 0)) {
        for (int64_t a = 0; a < 5; a++) {
            double c = 0.0;
            for (int64_t b = 0; b < 3; b++) {
                c = (double)((double)(vgadat.data[(int)((int64_t)((((ch * 15) + (a * 3)) + b)))]));
                (void)(pix((int64_t)((ind + fbi(b, a))), c, c, c));
            }
        }
    }
    return 0.0;
}

static int64_t vgalookup(const char* ch) {
    return ff_strfind(" `1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?", ch);
}

static double txt(double x, double y, const char* t) {
    for (int64_t i = 0; i < (int64_t)strlen(t); i++) {
        const char* _s1 = ff_strsub(t, (int64_t)(i), (int64_t)(1));
        (void)(vga((x + i), y, vgalookup(_s1)));
        free((void*)_s1);
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
            int64_t j = (int64_t)(0);
            for (int64_t i = 0; i < (int64_t)(((double)((int64_t)lc.len) / (double)(2))); i++) {
                const char* sp = ff_strdup("");
                if ((i == c)) {
                    const char* _olds2 = sp;
                    sp = ff_strdup("> ");
                    free((void*)_olds2);
                } else {
                    const char* _olds3 = sp;
                    sp = ff_strdup("  ");
                    free((void*)_olds3);
                }
                const char* _s4 = ff_strsub(l, (int64_t)(lc.data[(int)((i * 2))]), (int64_t)(lc.data[(int)(((i * 2) + 1))]));
                const char* _s5 = ff_strcat(sp, _s4);
                (void)(txt(0, (i + 2), _s5));
                free((void*)_s4);
                free((void*)_s5);
                j = (int64_t)(i);
                free((void*)sp);
            }
            if ((c == (int64_t)(((int64_t)lc.len * 0.5)))) {
                (void)(txt(0, (j + 3), "> back"));
            } else {
                (void)(txt(0, (j + 3), "  back"));
            }
            break;
        case 2:
            (void)(txt(0, 0, "configure virtual machine (exit and restart to take effect)"));
            switch ((int64_t)(c)) {
                case 0:
                    const char* _s6 = ff_str((double)(g.data[(int)(0)]));
                    const char* _s7 = ff_strcat("> change registers size", _s6);
                    const char* _s8 = ff_strcat(_s7, "        ");
                    (void)(txt(0, 2, _s8));
                    free((void*)_s6);
                    free((void*)_s7);
                    free((void*)_s8);
                    (void)(txt(0, 3, "  change jump table size         "));
                    (void)(txt(0, 4, "  back"));
                    break;
                case 1:
                    (void)(txt(0, 2, "  change registers size         "));
                    const char* _s9 = ff_str((double)(g.data[(int)(1)]));
                    const char* _s10 = ff_strcat("> change jump table size", _s9);
                    const char* _s11 = ff_strcat(_s10, "        ");
                    (void)(txt(0, 3, _s11));
                    free((void*)_s9);
                    free((void*)_s10);
                    free((void*)_s11);
                    (void)(txt(0, 4, "  back"));
                    break;
                case 2:
                    (void)(txt(0, 2, "  change registers size         "));
                    (void)(txt(0, 3, "  change jump table size         "));
                    (void)(txt(0, 4, "> back"));
                    break;
            }
            break;
    }
    return 0.0;
}

static FFList getkeys() {
    FFList _lt12 = ff_list_zeros((int)5);
    FFList o = _lt12;
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
}

static double rdm(double v) {
    if ((v >= memlen)) {
        return (v - memlen);
    }
    if ((v >= 0)) {
        return mem.data[(int)((int64_t)(v))];
    }
    return v;
}

static double rd(double v, FFList priv, FFList mem, double memlen, double PRIV) {
    if ((v >= memlen)) {
        return (v - memlen);
    }
    if ((v >= PRIV)) {
        return mem.data[(int)((int64_t)(v))];
    }
    if ((v >= 0)) {
        return priv.data[(int)((int64_t)(v))];
    }
    return v;
}

static double wr(double d, double val, FFList priv, FFList mem, double PRIV) {
    if ((d >= PRIV)) {
        mem.data[(int)((int64_t)(d))] = (float)(val);
    } else {
        priv.data[(int)((int64_t)(d))] = (float)(val);
    }
    return 0.0;
}

static FFList gpack(FFList gins, FFList mem, double vlen) {
    int64_t numvecs = (int64_t)((int64_t)gins.len);
    FFList _lt13 = ff_list_zeros((int)(int64_t)((numvecs * vlen)));
    FFList inbuf = _lt13;
    int64_t base = 0;
    for (int64_t si = 0; si < numvecs; si++) {
        base = (int64_t)((int64_t)(gins.data[(int)(si)]));
        for (int64_t e = 0; e < vlen; e++) {
            inbuf.data[(int)((int64_t)(((si * vlen) + e)))] = (float)(mem.data[(int)((int64_t)((base + e)))]);
        }
    }
    return inbuf;
}

static double gunpack(FFList outbuf, FFList mem, double obase, double vlen) {
    for (int64_t e = 0; e < vlen; e++) {
        mem.data[(int)((int64_t)((obase + e)))] = (float)(outbuf.data[(int)(e)]);
    }
    return 0.0;
}

static int64_t core(FFList a, FFList a1, FFList a2, FFList mem, FFList jt, double ip0, double tid0, double count, double memlen) {
    int64_t PRIV = (int64_t)(16);
    int64_t P = (int64_t)(4);
    double lid = (double)(tid0);
    int64_t ic = (int64_t)(0);
    double ip = 0.0;
    int64_t running = 0;
    while ((lid < count)) {
        FFList _lt14 = ff_list_zeros((int)PRIV);
        FFList priv = _lt14;
        ip = (double)(ip0);
        running = (int64_t)(1);
        double op = 0.0;
        double m1 = 0.0;
        double m2 = 0.0;
        while (running) {
            op = (double)(a.data[(int)((int64_t)(ip))]);
            m1 = (double)(a1.data[(int)((int64_t)(ip))]);
            m2 = (double)(a2.data[(int)((int64_t)(ip))]);
            int64_t lk = 0;
            int64_t lku = 0;
            if ((op == 1)) {
                (void)(wr(m1, rd(m2, priv, mem, memlen, PRIV), priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 2)) {
                (void)(wr(m1, (rd(m1, priv, mem, memlen, PRIV) + rd(m2, priv, mem, memlen, PRIV)), priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 3)) {
                (void)(wr(m1, (rd(m1, priv, mem, memlen, PRIV) - rd(m2, priv, mem, memlen, PRIV)), priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 4)) {
                (void)(wr(m1, (rd(m1, priv, mem, memlen, PRIV) * rd(m2, priv, mem, memlen, PRIV)), priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 5)) {
                (void)(wr(m1, ((double)(rd(m1, priv, mem, memlen, PRIV)) / (double)(rd(m2, priv, mem, memlen, PRIV))), priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 6)) {
                (void)(wr(m1, ff_fmod_py((double)(rd(m1, priv, mem, memlen, PRIV)), (double)(rd(m2, priv, mem, memlen, PRIV))), priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 7)) {
                if ((rd(m2, priv, mem, memlen, PRIV) != 0)) {
                    if ((m1 >= memlen)) {
                        ip = (double)(jt.data[(int)((int64_t)((m1 - memlen)))]);
                    } else if ((m1 >= 0)) {
                        ip = (double)(jt.data[(int)((int64_t)(mem.data[(int)((int64_t)(m1))]))]);
                    } else {
                        ip = (double)(jt.data[(int)((int64_t)(m1))]);
                    }
                } else {
                    ip = (double)((ip + 1));
                }
            } else if ((op == 15)) {
                (void)(wr(m2, lid, priv, mem, PRIV));
                ip = (double)((ip + 1));
            } else if ((op == 16)) {
                lk = (int64_t)((int64_t)(rd(m2, priv, mem, memlen, PRIV)));
                if ((lk == 0)) {
                    (void)((ff_mutex_lock(&lock0), 0));
                } else if ((lk == 1)) {
                    (void)((ff_mutex_lock(&lock1), 0));
                } else if ((lk == 2)) {
                    (void)((ff_mutex_lock(&lock2), 0));
                } else {
                    (void)((ff_mutex_lock(&lock3), 0));
                }
                ip = (double)((ip + 1));
            } else if ((op == 17)) {
                lku = (int64_t)((int64_t)(rd(m2, priv, mem, memlen, PRIV)));
                if ((lku == 0)) {
                    (void)((ff_mutex_unlock(&lock0), 0));
                } else if ((lku == 1)) {
                    (void)((ff_mutex_unlock(&lock1), 0));
                } else if ((lku == 2)) {
                    (void)((ff_mutex_unlock(&lock2), 0));
                } else {
                    (void)((ff_mutex_unlock(&lock3), 0));
                }
                ip = (double)((ip + 1));
            } else if ((op == 14)) {
                running = (int64_t)(0);
            } else if ((op == 12)) {
                running = (int64_t)(0);
            } else {
                ip = (double)((ip + 1));
            }
            ic = (int64_t)((ic + 1));
        }
        lid = (double)((lid + P));
        ff_list_free(&priv);
    }
    return ic;
}

static double clrrow(double row) {
    for (int64_t xx = 0; xx < 56; xx++) {
        (void)(vga(xx, row, 0));
    }
    return 0.0;
}

static double showstr(const char* t, double row) {
    for (int64_t ry = row; ry < 21; ry++) {
        (void)(clrrow(ry));
    }
    int64_t cx = (int64_t)(0);
    double cy = (double)(row);
    const char* ch = ff_strdup("");
    for (int64_t i = 0; i < (int64_t)strlen(t); i++) {
        const char* _s15 = ff_strsub(t, (int64_t)(i), (int64_t)(1));
        const char* _olds16 = ch;
        ch = _s15;
        free((void*)_olds16);
        if ((strcmp(ch, "\n") == 0)) {
            cx = (int64_t)(0);
            cy = (double)((cy + 1));
        } else {
            if ((cy < 21)) {
                (void)(vga(cx, cy, vgalookup(ch)));
            }
            cx = (int64_t)((cx + 1));
            if ((cx >= 56)) {
                cx = (int64_t)(0);
                cy = (double)((cy + 1));
            }
        }
    }
    return 0.0;
}

static const char* readline(double row) {
    const char* ks = ff_strdup("abcdefghijklmnopqrstuvwxyz0123456789");
    const char* buf = ff_strdup("");
    int64_t editing = (int64_t)(1);
    while ((editing && ff_window_open(&win))) {
        const char* ch = ff_strdup("");
        for (int64_t i = 0; i < (int64_t)strlen(ks); i++) {
            const char* _s17 = ff_strsub(ks, (int64_t)(i), (int64_t)(1));
            const char* _olds18 = ch;
            ch = _s17;
            free((void*)_olds18);
            if (ff_window_key_pressed(&win, ch)) {
                const char* _s19 = ff_strcat(buf, ch);
                const char* _olds20 = buf;
                buf = _s19;
                free((void*)_olds20);
            }
        }
        if (ff_window_key_pressed(&win, "space")) {
            const char* _s21 = ff_strcat(buf, " ");
            const char* _olds22 = buf;
            buf = _s21;
            free((void*)_olds22);
        }
        if (ff_window_key_pressed(&win, "backspace")) {
            if (((int64_t)strlen(buf) > 0)) {
                const char* _s23 = ff_strsub(buf, (int64_t)(0), (int64_t)(((int64_t)strlen(buf) - 1)));
                const char* _olds24 = buf;
                buf = _s23;
                free((void*)_olds24);
            }
        }
        if (ff_window_key_pressed(&win, "enter")) {
            editing = (int64_t)(0);
        }
        (void)(clrrow(row));
        const char* _s25 = ff_strcat("> ", buf);
        (void)(txt(0, row, _s25));
        free((void*)_s25);
        (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
        (void)((ff_window_tick(&win, (int)(30)), 0));
        free((void*)ch);
    }
    return ff_strdup(buf);
}

static int64_t gsz(double t) {
    if ((t == 0)) {
        return 1;
    }
    if ((t == 1)) {
        return 1;
    }
    if ((t == 2)) {
        return 2;
    }
    if ((t == 3)) {
        return 2;
    }
    if ((t == 4)) {
        return 4;
    }
    if ((t == 5)) {
        return 4;
    }
    if ((t == 6)) {
        return 4;
    }
    if ((t == 7)) {
        return 1;
    }
    if ((t == 10)) {
        return 8;
    }
    if ((t == 11)) {
        return 8;
    }
    if ((t == 12)) {
        return 8;
    }
    return 4;
}

static double gskipval(double o, double t) {
    FFBlob b = mblob;
    if ((t == 8)) {
        return ((o + 8) + ff_blob_u64(b, (int64_t)(o)));
    }
    int64_t et = 0;
    int64_t ln = 0;
    if ((t == 9)) {
        et = (int64_t)(ff_blob_u32(b, (int64_t)(o)));
        ln = (int64_t)(ff_blob_u64(b, (int64_t)((o + 4))));
        o = (double)((o + 12));
        int64_t zk = 0;
        if ((et == 8)) {
            zk = (int64_t)(0);
            while ((zk < ln)) {
                o = (double)(((o + 8) + ff_blob_u64(b, (int64_t)(o))));
                zk = (int64_t)((zk + 1));
            }
            return o;
        }
        return (o + (gsz(et) * ln));
    }
    return (o + gsz(t));
}

static double gguf_parse() {
    FFBlob b = mblob;
    int64_t nt = 0;
    int64_t nkv = 0;
    int64_t o = 0;
    int64_t kv = 0;
    int64_t embo = 0;
    int64_t ne = 0;
    int64_t ti = 0;
    if ((ff_blob_size(b) >= 32)) {
        nt = (int64_t)(ff_blob_u64(b, (int64_t)(8)));
        nkv = (int64_t)(ff_blob_u64(b, (int64_t)(16)));
        o = (int64_t)(24);
        kv = (int64_t)(0);
        int64_t vt = 0;
        while ((kv < nkv)) {
            o = (int64_t)(((o + 8) + ff_blob_u64(b, (int64_t)(o))));
            vt = (int64_t)(ff_blob_u32(b, (int64_t)(o)));
            o = (int64_t)((o + 4));
            o = (int64_t)(gskipval(o, vt));
            kv = (int64_t)((kv + 1));
        }
        embo = (int64_t)(0);
        ne = (int64_t)(0);
        ti = (int64_t)(0);
        int64_t nl = 0;
        const char* name = ff_strdup("");
        int64_t nd = 0;
        int64_t d0 = 0;
        int64_t toff = 0;
        while ((ti < nt)) {
            nl = (int64_t)(ff_blob_u64(b, (int64_t)(o)));
            const char* _s26 = ff_blob_str(b, (int64_t)((o + 8)), (int64_t)(nl));
            const char* _olds27 = name;
            name = _s26;
            free((void*)_olds27);
            o = (int64_t)(((o + 8) + nl));
            nd = (int64_t)(ff_blob_u32(b, (int64_t)(o)));
            o = (int64_t)((o + 4));
            d0 = (int64_t)(ff_blob_u64(b, (int64_t)(o)));
            o = (int64_t)((o + (nd * 8)));
            o = (int64_t)((o + 4));
            toff = (int64_t)(ff_blob_u64(b, (int64_t)(o)));
            o = (int64_t)((o + 8));
            if ((strcmp(name, "token_embd.weight") == 0)) {
                embo = (int64_t)(toff);
                ne = (int64_t)(d0);
            }
            ti = (int64_t)((ti + 1));
        }
        memb_off = (int64_t)((((int64_t)(((double)((o + 31)) / (double)(32))) * 32) + embo));
        n_embd = (int64_t)(ne);
    }
    return 0.0;
}

static double load_emb(double tok, double base) {
    FFBlob b = mblob;
    int64_t nblk = (int64_t)((int64_t)(((double)(n_embd) / (double)(32))));
    int64_t blk0 = (int64_t)((int64_t)(((double)((tok * n_embd)) / (double)(32))));
    int64_t bi = (int64_t)(0);
    int64_t bo = 0;
    double sc = 0.0;
    int64_t j = 0;
    while ((bi < nblk)) {
        bo = (int64_t)((memb_off + ((blk0 + bi) * 34)));
        sc = (double)(ff_blob_f16(b, (int64_t)(bo)));
        j = (int64_t)(0);
        int64_t q = 0;
        while ((j < 32)) {
            q = (int64_t)(ff_blob_u8(b, (int64_t)(((bo + 2) + j))));
            if ((q >= 128)) {
                q = (int64_t)((q - 256));
            }
            mem.data[(int)((int64_t)(((base + (bi * 32)) + j)))] = (float)((q * sc));
            j = (int64_t)((j + 1));
        }
        bi = (int64_t)((bi + 1));
    }
    return 0.0;
}

int main(void) {
    /* load kernels */
    int _kernel_gexec = loadkernel("gexec.cl", "gexec");
    if (_kernel_gexec < 0) { fprintf(stderr, "kernel gexec failed\n"); return 1; }

    if ((ff_file_exists("config") == 0)) {
        FFList _lt28 = ff_list_zeros((int)2);
        g = _lt28;
        g.data[(int)(0)] = (float)(64);
        g.data[(int)(1)] = (float)(16);
        ff_save_list("config", g);
    }
    FFList _lt29 = ff_load_list("config");
    g = _lt29;
    memlen = (double)(g.data[(int)(0)]);
    double jmplen = (double)(g.data[(int)(1)]);
    FFList _lt30 = ff_list_zeros((int)memlen);
    mem = _lt30;
    FFList _lt31 = ff_list_zeros((int)jmplen);
    FFList jt = _lt31;
    w = (int64_t)(240);
    h = (int64_t)(135);
    s = (int64_t)(2);
    win = ff_window_new((int)(w * s), (int)(h * s), "LVMrt");
    FFList _lt32 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
    fb = _lt32;
    const char* _s33 = ff_read_file("vga.dat");
    const char* vgabnk = _s33;
    FFList _lt34 = ff_list_zeros((int)1425);
    vgadat = _lt34;
    int64_t ct = (int64_t)(0);
    int64_t j = (int64_t)(0);
    printf("%s\n", "loading vga font data");
    for (int64_t i = 0; i < (int64_t)strlen(vgabnk); i++) {
        const char* _s35 = ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1));
        int _c36 = ((strcmp(_s35, "\n") == 0)) ? 1 : 0;
        free((void*)_s35);
        if (_c36) {
            j = (int64_t)(0);
        } else {
            j = (int64_t)((j + 1));
            const char* _s37 = ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1));
            const char* _s38 = ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1));
            int _c39 = ((((strcmp(_s37, "0") == 0) || (strcmp(_s38, "1") == 0)) && (j != 1))) ? 1 : 0;
            free((void*)_s37);
            free((void*)_s38);
            if (_c39) {
                const char* _s40 = ff_strsub(vgabnk, (int64_t)(i), (int64_t)(1));
                vgadat.data[(int)(ct)] = (float)((int64_t)atoi(_s40));
                free((void*)_s40);
                ct = (int64_t)((ct + 1));
            }
        }
    }
    const char* _olds41 = vgabnk;
    vgabnk = ff_strdup("");
    free((void*)_olds41);
    printf("%lld\n", (long long)(ct));
    printf("%s\n", "done");
    lock0 = ff_mutex_new();
    lock1 = ff_mutex_new();
    lock2 = ff_mutex_new();
    lock3 = ff_mutex_new();
    FFList _lt42 = ff_list_zeros((int)0);
    FFList gprog = _lt42;
    FFList _lt43 = ff_list_zeros((int)0);
    FFList gconst = _lt43;
    FFList _lt44 = ff_list_zeros((int)0);
    FFList gins = _lt44;
    int64_t VLEN = (int64_t)(0);
    const char* userline = ff_strdup("");
    mblob = ff_blob_open("C:\\llama\\LFM2.5-350M-Q8_0.gguf");
    memb_off = (int64_t)(0);
    n_embd = (int64_t)(0);
    int64_t c = (int64_t)(0);
    int64_t m = (int64_t)(0);
    (void)(scr(m, c));
    FFList _lt45 = ff_list_zeros((int)5);
    k = _lt45;
    l = ff_strdup("");
    FFList _lt46 = ff_list_zeros((int)1);
    lc = _lt46;
    int64_t r = (int64_t)(1);
    while (r) {
        r = (int64_t)(ff_window_open(&win));
        FFList _lt47 = getkeys();
        FFList keys = _lt47;
        switch ((int64_t)(m)) {
            case 0:
                c = (int64_t)(ff_clamp((double)((c - keys.data[(int)(1)]) + keys.data[(int)(3)]), (double)0, (double)2));
                switch ((int64_t)(c)) {
                    case 0:
                        int64_t ca = 0;
                        if (keys.data[(int)(4)]) {
                            const char* _s48 = ff_list_dir("./kernels");
                            const char* _olds49 = l;
                            l = _s48;
                            free((void*)_olds49);
                            FFList _lt50 = ff_list_zeros((int)0);
                            ff_list_free(&lc);
                            lc = _lt50;
                            ca = (int64_t)(0);
                            for (int64_t i = 0; i < (int64_t)strlen(l); i++) {
                                const char* _s51 = ff_strsub(l, (int64_t)(i), (int64_t)(1));
                                int _c52 = ((strcmp(_s51, "\n") == 0)) ? 1 : 0;
                                free((void*)_s51);
                                if (_c52) {
                                    (void)((ff_list_append(&lc, (float)(ca)), 0));
                                    (void)((ff_list_append(&lc, (float)((i - ca))), 0));
                                    ca = (int64_t)((i + 1));
                                }
                            }
                            if ((ca < (int64_t)strlen(l))) {
                                (void)((ff_list_append(&lc, (float)(ca)), 0));
                                (void)((ff_list_append(&lc, (float)(((int64_t)strlen(l) - ca))), 0));
                            }
                            c = (int64_t)(0);
                            m = (int64_t)(1);
                            FFList _lt53 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt53;
                        }
                        break;
                    case 1:
                        if (keys.data[(int)(4)]) {
                            c = (int64_t)(0);
                            m = (int64_t)(2);
                            FFList _lt54 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt54;
                        }
                        break;
                    case 2:
                        if (keys.data[(int)(4)]) {
                            r = (int64_t)(0);
                        }
                        break;
                }
                break;
            case 1:
                c = (int64_t)(ff_clamp((double)((c - keys.data[(int)(1)]) + keys.data[(int)(3)]), (double)0, (double)(int64_t)(((int64_t)lc.len * 0.5))));
                if ((c == (int64_t)(((int64_t)lc.len * 0.5)))) {
                    if (keys.data[(int)(4)]) {
                        c = (int64_t)(0);
                        m = (int64_t)(0);
                        FFList _lt55 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                        ff_list_free(&fb);
                        fb = _lt55;
                    }
                } else {
                    if (keys.data[(int)(4)]) {
                        FFList _lt56 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                        ff_list_free(&fb);
                        fb = _lt56;
                        const char* dat = ff_strdup("");
                        int64_t ca = 0;
                        int64_t i = 0;
                        const char* kw = ff_strdup("");
                        const char* tl = ff_strdup("");
                        int64_t t = 0;
                        const char* v = ff_strdup("");
                        int64_t ti = 0;
                        const char* _s57 = ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]));
                        const char* _s58 = ff_strcat("kernels/", _s57);
                        int _c59 = (ff_file_exists(_s58)) ? 1 : 0;
                        free((void*)_s57);
                        free((void*)_s58);
                        if (_c59) {
                            const char* _s60 = ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]));
                            const char* _s61 = ff_strcat("kernels/", _s60);
                            const char* _s62 = ff_read_file(_s61);
                            const char* _olds63 = dat;
                            dat = _s62;
                            free((void*)_olds63);
                            free((void*)_s60);
                            free((void*)_s61);
                            FFList _lt64 = ff_list_zeros((int)1);
                            FFList dati = _lt64;
                            ca = (int64_t)(0);
                            for (int64_t i = 0; i < (int64_t)strlen(dat); i++) {
                                const char* _s65 = ff_strsub(dat, (int64_t)(i), (int64_t)(1));
                                int _c66 = ((strcmp(_s65, "\n") == 0)) ? 1 : 0;
                                free((void*)_s65);
                                if (_c66) {
                                    (void)((ff_list_append(&dati, (float)(ca)), 0));
                                    (void)((ff_list_append(&dati, (float)((i + 1))), 0));
                                    ca = (int64_t)(0);
                                } else {
                                    ca = (int64_t)((ca + 1));
                                }
                            }
                            (void)((ff_list_append(&dati, (float)(ca)), 0));
                            FFList _lt67 = ff_list_zeros((int)0);
                            FFList ki = _lt67;
                            double lo = 0.0;
                            double ll = 0.0;
                            const char* p = ff_strdup("");
                            for (int64_t i = 0; i < (int64_t)(((int64_t)dati.len * 0.5)); i++) {
                                lo = (double)(dati.data[(int)((i * 2))]);
                                ll = (double)(dati.data[(int)(((i * 2) + 1))]);
                                const char* _s68 = ff_strsub(dat, (int64_t)(lo), (int64_t)(ll));
                                const char* _olds69 = p;
                                p = _s68;
                                free((void*)_olds69);
                                ca = (int64_t)(0);
                                while ((ca < ll)) {
                                    while (1) {
                                        const char* _s70 = ff_strsub(p, (int64_t)(ca), (int64_t)(1));
                                        const char* _s71 = ff_strsub(p, (int64_t)(ca), (int64_t)(1));
                                        int _c72 = (((ca < ll) && ((strcmp(_s70, " ") == 0) || (strcmp(_s71, ",") == 0)))) ? 1 : 0;
                                        free((void*)_s70);
                                        free((void*)_s71);
                                        if (!(_c72)) break;
                                        ca = (int64_t)((ca + 1));
                                    }
                                    j = (int64_t)(0);
                                    while (1) {
                                        const char* _s73 = ff_strsub(p, (int64_t)((j + ca)), (int64_t)(1));
                                        const char* _s74 = ff_strsub(p, (int64_t)((j + ca)), (int64_t)(1));
                                        int _c75 = (((((j + ca) < ll) && ((strcmp(_s73, " ") == 0) != 1)) && ((strcmp(_s74, ",") == 0) != 1))) ? 1 : 0;
                                        free((void*)_s73);
                                        free((void*)_s74);
                                        if (!(_c75)) break;
                                        j = (int64_t)((j + 1));
                                    }
                                    if ((j > 0)) {
                                        (void)((ff_list_append(&ki, (float)((lo + ca))), 0));
                                        (void)((ff_list_append(&ki, (float)(j)), 0));
                                    }
                                    ca = (int64_t)(((ca + j) + 1));
                                }
                            }
                            i = (int64_t)(0);
                            ca = (int64_t)(0);
                            const char* _olds76 = kw;
                            kw = ff_strdup("labmovaddsubmuldivmodjmpvgalogkeyslphltparrettidlckulkvlngclgibgcagaogrugsminpmldemb");
                            free((void*)_olds76);
                            const char* _olds77 = tl;
                            tl = ff_strdup("1222222221210201111011212102");
                            free((void*)_olds77);
                            t = (int64_t)(0);
                            const char* _olds78 = v;
                            v = ff_strdup("");
                            free((void*)_olds78);
                            FFList _lt79 = ff_list_zeros((int)0);
                            FFList a = _lt79;
                            FFList _lt80 = ff_list_zeros((int)0);
                            FFList a1 = _lt80;
                            FFList _lt81 = ff_list_zeros((int)0);
                            FFList a2 = _lt81;
                            ti = (int64_t)(0);
                            while ((ti < (int64_t)(((int64_t)ki.len * 0.5)))) {
                                const char* _s82 = ff_strsub(dat, (int64_t)(ki.data[(int)((ti * 2))]), (int64_t)(ki.data[(int)(((ti * 2) + 1))]));
                                const char* _olds83 = v;
                                v = _s82;
                                free((void*)_olds83);
                                int64_t u = 0;
                                if ((t == 0)) {
                                    if (((int64_t)a1.len < (int64_t)a.len)) {
                                        (void)((ff_list_append(&a1, (float)(0)), 0));
                                    }
                                    if (((int64_t)a2.len < (int64_t)a.len)) {
                                        (void)((ff_list_append(&a2, (float)(0)), 0));
                                    }
                                    u = (int64_t)(-1);
                                    for (int64_t i = 0; i < (int64_t)(((double)((int64_t)strlen(kw)) / (double)(3))); i++) {
                                        const char* _s84 = ff_strsub(kw, (int64_t)((i * 3)), (int64_t)(3));
                                        int _c85 = ((strcmp(_s84, v) == 0)) ? 1 : 0;
                                        free((void*)_s84);
                                        if (_c85) {
                                            u = (int64_t)(i);
                                            const char* _s86 = ff_strsub(tl, (int64_t)(i), (int64_t)(1));
                                            t = (int64_t)((int64_t)atoi(_s86));
                                            free((void*)_s86);
                                            break;
                                        }
                                    }
                                    if ((u == -1)) {
                                        ca = (int64_t)(1);
                                        const char* _s87 = ff_strcat("invalid keyword: ", v);
                                        printf("%s\n", _s87);
                                        free((void*)_s87);
                                        const char* _s88 = ff_strcat("keyword '", v);
                                        const char* _s89 = ff_strcat(_s88, "' is invalid");
                                        (void)(txt(0, 0, _s89));
                                        free((void*)_s88);
                                        free((void*)_s89);
                                        (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                        (void)((ff_window_tick(&win, (int)(0)), 0));
                                        (void)((ff_sleep((double)2), 0));
                                        FFList _lt90 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                        ff_list_free(&fb);
                                        fb = _lt90;
                                        break;
                                    }
                                    (void)((ff_list_append(&a, (float)(u)), 0));
                                } else if ((t == 1)) {
                                    const char* _s91 = ff_strsub(v, (int64_t)(0), (int64_t)(1));
                                    int _c92 = ((strcmp(_s91, "c") == 0)) ? 1 : 0;
                                    free((void*)_s91);
                                    if (_c92) {
                                        const char* _s93 = ff_strsub(v, (int64_t)(1), (int64_t)strlen(v));
                                        (void)((ff_list_append(&a2, (float)((int64_t)atoi(_s93))), 0));
                                        free((void*)_s93);
                                    } else {
                                        if ((atof(v) >= 0)) {
                                            (void)((ff_list_append(&a2, (float)((atof(v) + memlen))), 0));
                                        } else {
                                            (void)((ff_list_append(&a2, (float)(atof(v))), 0));
                                        }
                                    }
                                    t = (int64_t)((t - 1));
                                } else if ((t == 2)) {
                                    const char* _s94 = ff_strsub(v, (int64_t)(0), (int64_t)(1));
                                    int _c95 = ((strcmp(_s94, "c") == 0)) ? 1 : 0;
                                    free((void*)_s94);
                                    if (_c95) {
                                        const char* _s96 = ff_strsub(v, (int64_t)(1), (int64_t)strlen(v));
                                        (void)((ff_list_append(&a1, (float)((int64_t)atoi(_s96))), 0));
                                        free((void*)_s96);
                                    } else {
                                        if ((atof(v) >= 0)) {
                                            (void)((ff_list_append(&a1, (float)((atof(v) + memlen))), 0));
                                        } else {
                                            (void)((ff_list_append(&a1, (float)(atof(v))), 0));
                                        }
                                    }
                                    t = (int64_t)((t - 1));
                                }
                                ti = (int64_t)((ti + 1));
                            }
                            if (((int64_t)a1.len < (int64_t)a.len)) {
                                (void)((ff_list_append(&a1, (float)(0)), 0));
                            }
                            if (((int64_t)a2.len < (int64_t)a.len)) {
                                (void)((ff_list_append(&a2, (float)(0)), 0));
                            }
                            ff_list_print_inline(a);
                            printf("\n");
                            ff_list_print_inline(a1);
                            printf("\n");
                            ff_list_print_inline(a2);
                            printf("\n");
                            if (((int64_t)strlen(dat) > 0)) {
                                double it = 0.0;
                                double tt = 0.0;
                                double lt = 0.0;
                                int64_t la = 0;
                                int64_t d = 0;
                                int64_t fc = 0;
                                int64_t pri = 0;
                                if ((ca == 0)) {
                                    i = (int64_t)(0);
                                    for (int64_t i = 0; i < memlen; i++) {
                                        mem.data[(int)(i)] = (float)(0);
                                    }
                                    for (int64_t i = 0; i < jmplen; i++) {
                                        jt.data[(int)(i)] = (float)(0);
                                    }
                                    i = (int64_t)(0.0);
                                    it = (double)(0.0);
                                    tt = (double)(0.0);
                                    lt = (double)(ff_time());
                                    la = (int64_t)((int64_t)a.len);
                                    d = (int64_t)(0);
                                    fc = (int64_t)(0);
                                    pri = (int64_t)(0);
                                    while ((pri < la)) {
                                        if (((a.data[(int)(pri)] == 0) && (a2.data[(int)(pri)] >= memlen))) {
                                            jt.data[(int)((int64_t)((a2.data[(int)(pri)] - memlen)))] = (float)(pri);
                                        }
                                        pri = (int64_t)((pri + 1));
                                    }
                                    double ma1 = 0.0;
                                    double ma2 = 0.0;
                                    int64_t f1 = 0;
                                    int64_t f2 = 0;
                                    while ((r && ff_window_open(&win))) {
                                        ma1 = (double)(a1.data[(int)(i)]);
                                        ma2 = (double)(a2.data[(int)(i)]);
                                        f1 = (int64_t)(0);
                                        f2 = (int64_t)(0);
                                        double _sw97 = a.data[(int)(i)];
                                        switch ((int64_t)(_sw97)) {
                                            case 0:
                                                if ((ma2 >= memlen)) {
                                                    jt.data[(int)((ma2 - memlen))] = (float)(i);
                                                } else if ((ma2 >= 0)) {
                                                    jt.data[(int)(mem.data[(int)(ma2)])] = (float)(i);
                                                } else {
                                                    jt.data[(int)(ma2)] = (float)(i);
                                                }
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 1:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                mem.data[(int)(ma1)] = (float)(f1);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 2:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] + f1));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 3:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] - f1));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 4:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                mem.data[(int)(ma1)] = (float)((mem.data[(int)(ma1)] * f1));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 5:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                mem.data[(int)(ma1)] = (float)(((double)(mem.data[(int)(ma1)]) / (double)(f1)));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 6:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                mem.data[(int)(ma1)] = (float)(ff_fmod_py((double)(mem.data[(int)(ma1)]), (double)(f1)));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 7:
                                                if ((ma2 >= memlen)) {
                                                    f1 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f1 = (int64_t)(ma2);
                                                }
                                                if ((f1 != 0)) {
                                                    if ((ma1 >= memlen)) {
                                                        i = (int64_t)(jt.data[(int)((ma1 - memlen))]);
                                                    } else if ((ma1 >= 0)) {
                                                        i = (int64_t)(jt.data[(int)(mem.data[(int)(ma1)])]);
                                                    } else {
                                                        i = (int64_t)(jt.data[(int)(ma1)]);
                                                    }
                                                } else {
                                                    i = (int64_t)((i + 1));
                                                }
                                                break;
                                            case 8:
                                                if ((ma2 >= memlen)) {
                                                    f2 = (int64_t)((ma2 - memlen));
                                                } else if ((ma2 >= 0)) {
                                                    f2 = (int64_t)(mem.data[(int)(ma2)]);
                                                } else {
                                                    f2 = (int64_t)((0 - ma2));
                                                }
                                                if ((ma1 >= memlen)) {
                                                    f1 = (int64_t)((ma1 - memlen));
                                                } else if ((ma1 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma1)]);
                                                } else {
                                                    f1 = (int64_t)(ma1);
                                                }
                                                const char* f3 = ff_strdup("");
                                                if ((f1 < 0)) {
                                                    f1 = (int64_t)((f1 * -1));
                                                    const char* _s98 = ff_str_int((int64_t)(f2));
                                                    const char* _olds99 = f3;
                                                    f3 = _s98;
                                                    free((void*)_olds99);
                                                    for (int64_t q = 0; q < (int64_t)strlen(f3); q++) {
                                                        const char* _s100 = ff_strsub(f3, (int64_t)(q), (int64_t)(1));
                                                        (void)(vga(ff_imod((int64_t)((f1 + q)), (int64_t)(56)), (int64_t)(((double)((f1 + q)) / (double)(56))), (vgalookup(_s100) - 1)));
                                                        free((void*)_s100);
                                                    }
                                                } else {
                                                    (void)(vga(ff_imod((int64_t)(f1), (int64_t)(56)), (int64_t)(((double)(f1) / (double)(56))), (f2 + 1)));
                                                }
                                                d = (int64_t)(1);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 9:
                                                if ((ma2 >= memlen)) {
                                                    const char* _s101 = ff_str((double)((ma2 - memlen)));
                                                    printf("%s\n", _s101);
                                                    free((void*)_s101);
                                                } else if ((ma2 >= 0)) {
                                                    const char* _s102 = ff_str((double)(mem.data[(int)(ma2)]));
                                                    printf("%s\n", _s102);
                                                    free((void*)_s102);
                                                } else {
                                                    const char* _s103 = ff_str((double)(ma2));
                                                    printf("%s\n", _s103);
                                                    free((void*)_s103);
                                                }
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 10:
                                                if ((ma1 >= memlen)) {
                                                    f1 = (int64_t)((ma1 - memlen));
                                                } else if ((ma1 >= 0)) {
                                                    f1 = (int64_t)(mem.data[(int)(ma1)]);
                                                } else {
                                                    f1 = (int64_t)(ma1);
                                                }
                                                const char* _s104 = ff_strsub(" `1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?", (int64_t)(f1), (int64_t)(1));
                                                mem.data[(int)(ma2)] = (float)(ff_window_key(&win, _s104));
                                                free((void*)_s104);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 11:
                                                if ((ma2 >= memlen)) {
                                                    (void)((ff_sleep((double)(ma2 - memlen)), 0));
                                                } else if ((ma2 >= 0)) {
                                                    (void)((ff_sleep((double)mem.data[(int)(ma2)]), 0));
                                                } else {
                                                    (void)((ff_sleep((double)ma2), 0));
                                                }
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 12:
                                                r = (int64_t)(0);
                                                break;
                                                break;
                                            case 13:
                                                double plabel = 0.0;
                                                if ((ma1 >= memlen)) {
                                                    plabel = (double)(jt.data[(int)((int64_t)((ma1 - memlen)))]);
                                                } else if ((ma1 >= 0)) {
                                                    plabel = (double)(jt.data[(int)((int64_t)(mem.data[(int)((int64_t)(ma1))]))]);
                                                } else {
                                                    plabel = (double)(jt.data[(int)((int64_t)(ma1))]);
                                                }
                                                double pcount = (double)(rdm(ma2));
                                                struct _spawn_core* _sp105 = (struct _spawn_core*)malloc(sizeof(struct _spawn_core));
                                                _sp105->a0 = a;
                                                _sp105->a1 = a1;
                                                _sp105->a2 = a2;
                                                _sp105->a3 = mem;
                                                _sp105->a4 = jt;
                                                _sp105->a5 = plabel;
                                                _sp105->a6 = 0;
                                                _sp105->a7 = pcount;
                                                _sp105->a8 = memlen;
                                                FFTask _tk106 = ff_task_start(_tramp_core, _sp105);
                                                FFTask t0 = _tk106;
                                                struct _spawn_core* _sp107 = (struct _spawn_core*)malloc(sizeof(struct _spawn_core));
                                                _sp107->a0 = a;
                                                _sp107->a1 = a1;
                                                _sp107->a2 = a2;
                                                _sp107->a3 = mem;
                                                _sp107->a4 = jt;
                                                _sp107->a5 = plabel;
                                                _sp107->a6 = 1;
                                                _sp107->a7 = pcount;
                                                _sp107->a8 = memlen;
                                                FFTask _tk108 = ff_task_start(_tramp_core, _sp107);
                                                FFTask t1 = _tk108;
                                                struct _spawn_core* _sp109 = (struct _spawn_core*)malloc(sizeof(struct _spawn_core));
                                                _sp109->a0 = a;
                                                _sp109->a1 = a1;
                                                _sp109->a2 = a2;
                                                _sp109->a3 = mem;
                                                _sp109->a4 = jt;
                                                _sp109->a5 = plabel;
                                                _sp109->a6 = 2;
                                                _sp109->a7 = pcount;
                                                _sp109->a8 = memlen;
                                                FFTask _tk110 = ff_task_start(_tramp_core, _sp109);
                                                FFTask t2 = _tk110;
                                                struct _spawn_core* _sp111 = (struct _spawn_core*)malloc(sizeof(struct _spawn_core));
                                                _sp111->a0 = a;
                                                _sp111->a1 = a1;
                                                _sp111->a2 = a2;
                                                _sp111->a3 = mem;
                                                _sp111->a4 = jt;
                                                _sp111->a5 = plabel;
                                                _sp111->a6 = 3;
                                                _sp111->a7 = pcount;
                                                _sp111->a8 = memlen;
                                                FFTask _tk112 = ff_task_start(_tramp_core, _sp111);
                                                FFTask t3 = _tk112;
                                                ff_task_join(&t0);
                                                int64_t _jr113 = ((struct _spawn_core*)t0.arg)->_ret;
                                                free(t0.arg);
                                                (void)(_jr113);
                                                ff_task_join(&t1);
                                                int64_t _jr114 = ((struct _spawn_core*)t1.arg)->_ret;
                                                free(t1.arg);
                                                (void)(_jr114);
                                                ff_task_join(&t2);
                                                int64_t _jr115 = ((struct _spawn_core*)t2.arg)->_ret;
                                                free(t2.arg);
                                                (void)(_jr115);
                                                ff_task_join(&t3);
                                                int64_t _jr116 = ((struct _spawn_core*)t3.arg)->_ret;
                                                free(t3.arg);
                                                (void)(_jr116);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 14:
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 15:
                                                mem.data[(int)((int64_t)(ma2))] = (float)(0);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 16:
                                                int64_t lk = (int64_t)((int64_t)(rdm(ma2)));
                                                if ((lk == 0)) {
                                                    (void)((ff_mutex_lock(&lock0), 0));
                                                } else if ((lk == 1)) {
                                                    (void)((ff_mutex_lock(&lock1), 0));
                                                } else if ((lk == 2)) {
                                                    (void)((ff_mutex_lock(&lock2), 0));
                                                } else {
                                                    (void)((ff_mutex_lock(&lock3), 0));
                                                }
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 17:
                                                int64_t lku = (int64_t)((int64_t)(rdm(ma2)));
                                                if ((lku == 0)) {
                                                    (void)((ff_mutex_unlock(&lock0), 0));
                                                } else if ((lku == 1)) {
                                                    (void)((ff_mutex_unlock(&lock1), 0));
                                                } else if ((lku == 2)) {
                                                    (void)((ff_mutex_unlock(&lock2), 0));
                                                } else {
                                                    (void)((ff_mutex_unlock(&lock3), 0));
                                                }
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 18:
                                                VLEN = (int64_t)(rdm(ma2));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 19:
                                                FFList _lt117 = ff_list_zeros((int)0);
                                                ff_list_free(&gprog);
                                                gprog = _lt117;
                                                FFList _lt118 = ff_list_zeros((int)0);
                                                ff_list_free(&gconst);
                                                gconst = _lt118;
                                                FFList _lt119 = ff_list_zeros((int)0);
                                                ff_list_free(&gins);
                                                gins = _lt119;
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 20:
                                                (void)((ff_list_append(&gins, (float)(rdm(ma2))), 0));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 21:
                                                (void)((ff_list_append(&gconst, (float)(rdm(ma2))), 0));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 22:
                                                (void)((ff_list_append(&gprog, (float)(rdm(ma1))), 0));
                                                (void)((ff_list_append(&gprog, (float)(rdm(ma2))), 0));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 23:
                                                int64_t vln = (int64_t)((int64_t)(VLEN));
                                                int64_t nv = (int64_t)((int64_t)gins.len);
                                                int64_t pl = (int64_t)((int64_t)(((double)((int64_t)gprog.len) / (double)(2))));
                                                FFList _lt120 = gpack(gins, mem, vln);
                                                FFList inbuf = _lt120;
                                                FFList _lt121 = ff_list_zeros((int)vln);
                                                FFList outbuf = _lt121;
                                                cl_mem _ob122 = outbuf.pinned ? outbuf.gpu_buf : loadbuf(outbuf.data, outbuf.len, 0);
                                                cl_mem _rb123 = inbuf.pinned ? inbuf.gpu_buf : loadbuf(inbuf.data, inbuf.len, 1);
                                                cl_mem _rb124 = gprog.pinned ? gprog.gpu_buf : loadbuf(gprog.data, gprog.len, 1);
                                                cl_mem _rb125 = gconst.pinned ? gconst.gpu_buf : loadbuf(gconst.data, gconst.len, 1);
                                                int _sv126 = (int)(nv);
                                                int _sv127 = (int)(pl);
                                                int _sv128 = (int)(vln);
                                                advrunkernel(_kernel_gexec, (size_t)vln, 7, &_rb123, sizeof(cl_mem), &_rb124, sizeof(cl_mem), &_rb125, sizeof(cl_mem), &_sv126, sizeof(int), &_sv127, sizeof(int), &_sv128, sizeof(int), &_ob122, sizeof(cl_mem));
                                                if (!outbuf.pinned) readbuf(_ob122, outbuf.data, outbuf.len);
                                                if (!inbuf.pinned) freebuf(_rb123);
                                                if (!gprog.pinned) freebuf(_rb124);
                                                if (!gconst.pinned) freebuf(_rb125);
                                                if (!outbuf.pinned) freebuf(_ob122);
                                                (void)(gunpack(outbuf, mem, (int64_t)(rdm(ma2)), vln));
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 24:
                                                int64_t sbase = (int64_t)((int64_t)(rdm(ma1)));
                                                double sv = (double)(0.0);
                                                for (int64_t se = 0; se < (int64_t)(VLEN); se++) {
                                                    sv = (double)((sv + mem.data[(int)((int64_t)((sbase + se)))]));
                                                }
                                                mem.data[(int)((int64_t)(ma2))] = (float)(sv);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 25:
                                                const char* _s129 = readline((int64_t)(rdm(ma2)));
                                                const char* _olds130 = userline;
                                                userline = _s129;
                                                free((void*)_olds130);
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 26:
                                                (void)(gguf_parse());
                                                i = (int64_t)((i + 1));
                                                break;
                                            case 27:
                                                (void)(load_emb((int64_t)(rdm(ma1)), (int64_t)(rdm(ma2))));
                                                i = (int64_t)((i + 1));
                                                break;
                                        }
                                        i = (int64_t)(ff_imod((int64_t)(i), (int64_t)(la)));
                                        if (d) {
                                            (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                            fc = (int64_t)(64);
                                            d = (int64_t)(0);
                                        }
                                        fc = (int64_t)((fc + 1));
                                        if ((fc >= 64)) {
                                            fc = (int64_t)(0);
                                            (void)((ff_window_tick(&win, (int)(1048576)), 0));
                                        }
                                        it = (double)((it + 1));
                                    }
                                    tt = (double)((ff_time() - lt));
                                    const char* _s131 = ff_str((double)(it));
                                    const char* _s132 = ff_strcat("instructions ran: ", _s131);
                                    printf("%s\n", _s132);
                                    free((void*)_s131);
                                    free((void*)_s132);
                                    const char* _s133 = ff_fmt("%.4f", (double)(tt));
                                    const char* _s134 = ff_strcat("time taken: ", _s133);
                                    printf("%s\n", _s134);
                                    free((void*)_s133);
                                    free((void*)_s134);
                                    const char* _s135 = ff_fmt("%.4f", (double)(((double)(tt) / (double)(it))));
                                    const char* _s136 = ff_strcat("time(s) per instruction: ", _s135);
                                    printf("%s\n", _s136);
                                    free((void*)_s135);
                                    free((void*)_s136);
                                    FFList _lt137 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                    ff_list_free(&fb);
                                    fb = _lt137;
                                    r = (int64_t)(1);
                                } else {
                                    const char* _s138 = ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]));
                                    const char* _s139 = ff_strcat("kernels/", _s138);
                                    const char* _s140 = ff_strcat(_s139, " is invalid");
                                    (void)(txt(0, 0, _s140));
                                    free((void*)_s138);
                                    free((void*)_s139);
                                    free((void*)_s140);
                                    (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                    (void)((ff_window_tick(&win, (int)(0)), 0));
                                    (void)((ff_sleep((double)2), 0));
                                    FFList _lt141 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                    ff_list_free(&fb);
                                    fb = _lt141;
                                }
                            } else {
                                const char* _s142 = ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]));
                                const char* _s143 = ff_strcat("kernels/", _s142);
                                const char* _s144 = ff_strcat(_s143, " is empty");
                                (void)(txt(0, 0, _s144));
                                free((void*)_s142);
                                free((void*)_s143);
                                free((void*)_s144);
                                (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                                (void)((ff_window_tick(&win, (int)(0)), 0));
                                (void)((ff_sleep((double)2), 0));
                                FFList _lt145 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                                ff_list_free(&fb);
                                fb = _lt145;
                            }
                        } else {
                            const char* _s146 = ff_strsub(l, (int64_t)(lc.data[(int)((c * 2))]), (int64_t)(lc.data[(int)(((c * 2) + 1))]));
                            const char* _s147 = ff_strcat("kernels/", _s146);
                            const char* _s148 = ff_strcat(_s147, " does not exist");
                            (void)(txt(0, 0, _s148));
                            free((void*)_s146);
                            free((void*)_s147);
                            free((void*)_s148);
                            (void)((ff_window_draw(&win, fb.data, (int)(w * s), (int)(h * s)), 0));
                            (void)((ff_window_tick(&win, (int)(0)), 0));
                            (void)((ff_sleep((double)2), 0));
                            FFList _lt149 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt149;
                        }
                        c = (int64_t)(0);
                    }
                }
                break;
            case 2:
                c = (int64_t)(ff_clamp((double)((c - keys.data[(int)(1)]) + keys.data[(int)(3)]), (double)0, (double)2));
                switch ((int64_t)(c)) {
                    case 0:
                        if (keys.data[(int)(4)]) {
                            g.data[(int)(0)] = (float)((g.data[(int)(0)] * 2));
                            if ((g.data[(int)(0)] > 16777216)) {
                                g.data[(int)(0)] = (float)(8);
                            }
                            ff_save_list("config", g);
                        }
                        break;
                    case 1:
                        if (keys.data[(int)(4)]) {
                            g.data[(int)(1)] = (float)((g.data[(int)(1)] * 2));
                            if ((g.data[(int)(1)] > 2048)) {
                                g.data[(int)(1)] = (float)(4);
                            }
                            ff_save_list("config", g);
                        }
                        break;
                    case 2:
                        if (keys.data[(int)(4)]) {
                            c = (int64_t)(0);
                            m = (int64_t)(0);
                            FFList _lt150 = ff_list_zeros((int)((((w * s) * h) * s) * 4));
                            ff_list_free(&fb);
                            fb = _lt150;
                        }
                        break;
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