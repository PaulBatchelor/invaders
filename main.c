#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

/* Bitmaps */

#define font_width 128
#define font_height 32
static char font_bits[] = {
  0x00, 0x18, 0x36, 0x36, 0x18, 0x42, 0x1C, 0x18, 0x30, 0x0C, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x00, 0x3C, 0x36, 0x36, 0x7C, 0x25, 0x36, 0x18, 
  0x18, 0x18, 0x66, 0x18, 0x00, 0x00, 0x00, 0x60, 0x00, 0x3C, 0x36, 0x7F, 
  0x06, 0x12, 0x1C, 0x0C, 0x0C, 0x30, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x30, 
  0x00, 0x18, 0x00, 0x36, 0x3C, 0x08, 0x6E, 0x00, 0x0C, 0x30, 0xFF, 0x7E, 
  0x00, 0x7E, 0x00, 0x18, 0x00, 0x18, 0x00, 0x7F, 0x60, 0x24, 0x3B, 0x00, 
  0x0C, 0x30, 0x3C, 0x18, 0x18, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x36, 
  0x3E, 0x52, 0x33, 0x00, 0x18, 0x18, 0x66, 0x18, 0x18, 0x00, 0x18, 0x06, 
  0x00, 0x18, 0x00, 0x36, 0x18, 0x21, 0x6E, 0x00, 0x30, 0x0C, 0x00, 0x00, 
  0x0C, 0x00, 0x18, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x18, 0x3E, 0x7E, 
  0x38, 0x3F, 0x3C, 0x7F, 0x1E, 0x3E, 0x00, 0x00, 0x30, 0x00, 0x0C, 0x3E, 
  0x32, 0x1C, 0x63, 0x30, 0x3C, 0x03, 0x06, 0x63, 0x23, 0x63, 0x00, 0x18, 
  0x18, 0x00, 0x18, 0x63, 0x63, 0x18, 0x70, 0x18, 0x36, 0x3F, 0x03, 0x30, 
  0x27, 0x63, 0x18, 0x18, 0x0C, 0x7E, 0x30, 0x60, 0x63, 0x18, 0x3C, 0x3C, 
  0x33, 0x60, 0x3F, 0x18, 0x3F, 0x7E, 0x18, 0x00, 0x06, 0x00, 0x60, 0x38, 
  0x63, 0x18, 0x1E, 0x60, 0x7F, 0x60, 0x63, 0x0C, 0x71, 0x60, 0x00, 0x18, 
  0x0C, 0x7E, 0x30, 0x0C, 0x26, 0x18, 0x07, 0x63, 0x30, 0x63, 0x63, 0x0C, 
  0x61, 0x30, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00, 0x1C, 0x7E, 0x7F, 0x3E, 
  0x30, 0x3E, 0x3E, 0x0C, 0x3E, 0x1E, 0x18, 0x0C, 0x30, 0x00, 0x0C, 0x0C, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3E, 0x1C, 0x3F, 0x3C, 0x1F, 0x7E, 0x7F, 0x7C, 
  0x63, 0x7E, 0x60, 0x63, 0x06, 0x63, 0x63, 0x3E, 0x63, 0x36, 0x63, 0x66, 
  0x33, 0x06, 0x03, 0x06, 0x63, 0x18, 0x60, 0x33, 0x06, 0x77, 0x67, 0x63, 
  0x7B, 0x63, 0x63, 0x03, 0x63, 0x06, 0x03, 0x03, 0x63, 0x18, 0x60, 0x1B, 
  0x06, 0x7F, 0x6F, 0x63, 0x7B, 0x63, 0x3F, 0x03, 0x63, 0x3E, 0x3F, 0x73, 
  0x7F, 0x18, 0x60, 0x0F, 0x06, 0x7F, 0x7F, 0x63, 0x7B, 0x7F, 0x63, 0x03, 
  0x63, 0x06, 0x03, 0x63, 0x63, 0x18, 0x60, 0x1F, 0x06, 0x6B, 0x7B, 0x63, 
  0x03, 0x63, 0x63, 0x66, 0x33, 0x06, 0x03, 0x66, 0x63, 0x18, 0x63, 0x3B, 
  0x06, 0x63, 0x73, 0x63, 0x1E, 0x63, 0x3F, 0x3C, 0x1F, 0x7E, 0x03, 0x7C, 
  0x63, 0x7E, 0x3E, 0x73, 0x7E, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3F, 0x3E, 0x3F, 0x1E, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x66, 0x7F, 0x3C, 
  0x3C, 0x3C, 0x08, 0x00, 0x63, 0x63, 0x63, 0x33, 0x18, 0x63, 0x63, 0x63, 
  0x77, 0x66, 0x70, 0x0C, 0x42, 0x30, 0x14, 0x00, 0x63, 0x63, 0x63, 0x03, 
  0x18, 0x63, 0x63, 0x6B, 0x3E, 0x66, 0x38, 0x0C, 0x99, 0x30, 0x22, 0x00, 
  0x63, 0x63, 0x73, 0x3E, 0x18, 0x63, 0x77, 0x7F, 0x1C, 0x3C, 0x1C, 0x0C, 
  0xA1, 0x30, 0x00, 0x00, 0x3F, 0x7B, 0x3F, 0x60, 0x18, 0x63, 0x3E, 0x7F, 
  0x3E, 0x18, 0x0E, 0x0C, 0xA1, 0x30, 0x00, 0x00, 0x03, 0x33, 0x3B, 0x63, 
  0x18, 0x63, 0x1C, 0x77, 0x77, 0x18, 0x07, 0x0C, 0x99, 0x30, 0x00, 0x00, 
  0x03, 0x5E, 0x73, 0x3E, 0x18, 0x3E, 0x08, 0x63, 0x63, 0x18, 0x7F, 0x3C, 
  0x42, 0x3C, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
};

#define enemy1_width 12
#define enemy1_height 12
static char enemy1_bits[] = {
  0x00, 0x00, 0xF0, 0x00, 0xFC, 0x03, 0x66, 0x06, 0x66, 0x06, 0xFE, 0x07, 
  0xFE, 0x07, 0x92, 0x04, 0x02, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 
  };


#define enemy2_width 12
#define enemy2_height 12
static char enemy2_bits[] = {
  0x00, 0x00, 0x04, 0x02, 0x68, 0x01, 0xFC, 0x03, 0x62, 0x04, 0xFE, 0x07, 
  0xFE, 0x07, 0xFA, 0x05, 0x0A, 0x05, 0x08, 0x01, 0x98, 0x01, 0x00, 0x00, 
  };

#define enemy3_width 12
#define enemy3_height 12
static char enemy3_bits[] = {
  0x00, 0x00, 0x60, 0x00, 0xF0, 0x00, 0xF8, 0x01, 0x68, 0x01, 0xF8, 0x01, 
  0xFC, 0x03, 0xFC, 0x03, 0x90, 0x00, 0x08, 0x01, 0x90, 0x00, 0x00, 0x00, 
  };

#define tank_width 32
#define tank_height 16
static char tank_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x03, 0x00, 
  0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 
  0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 
  0xE0, 0xFF, 0xFF, 0x07, 0xF8, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0x1F, 
  0xF8, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0x1F, 
  0xF8, 0xFF, 0xFF, 0x1F, };

#define WINDOW_WIDTH 224
#define WINDOW_HEIGHT 256
#define WINDOW_WIDTH_PADDED (WINDOW_WIDTH - 2*8)
#define ZOOM 2
#define GHOST_AMT 10
#define BROOD_SIZE 12
#define BROOD_PADDING 6

/* should be at least half of ship */
#define WINDOW_PADDING 8

/* debugging */
#define BOUNDING_BOX 0

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/* screen represents non-zoomed pixels, one byte per pixel */
uint8_t *screen = NULL;

/* framebuffer and backbuffer for diode ghosting effect */
uint8_t *pixels = NULL;
uint8_t *backbuf = NULL;

/* SDL stuff for framebuffer */
SDL_Rect viewport;
SDL_Texture *texture = NULL;

static volatile int running = 0;

double ship_pos = 0;
double velocity = 0;

double counter = 0;
double counter_max = 0.75;

/* Brood offset onscreen */

int brood_xoff = 0;
int brood_yoff = 0;

int score = 0;

/* max/min x coordinates used to determine when to change
 * direction
 */
int brood_max_x = BROOD_SIZE*11 + BROOD_PADDING*10;
int brood_min_x = 0;

/* Used to determine the bottom end of brood */
int brood_max_y = BROOD_SIZE*5 + BROOD_PADDING*4;

/* speed is abosolute value, direction
 * toggles +/- and makes it a vector */
int brood_speed = 4;
int brood_direction = 1;

/* how far to travel until game over? */
int brood_touchdown = WINDOW_HEIGHT - 32 - 8;

int gameover = 0;

/* Keep track of alive status of each enemy using bits
 * in 2 32-bit integers. 55 enemies fit in 64 bits
 */
uint32_t alive[2];

void destroy(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free(pixels);
    free(screen);
    free(backbuf);
}

void fire(void)
{
    /* TODO: implement fire */
    printf("fire!\n");
}

void process_event(SDL_Event *event, double dt)
{
    SDL_Keycode key = event->key.keysym.sym;

    if (event->key.type == SDL_KEYDOWN) {
        switch(key) {
            case SDLK_RIGHT:
                /* ship_pos += 500.0*dt; */
                /* ship_pos += 10; */
                if (!gameover) velocity += 200*dt;
                break;
            case SDLK_LEFT:
                /* ship_pos -= 500.0*dt; */
                /* ship_pos -= 10; */
                if (!gameover) velocity -= 200*dt;
                break;
            case SDLK_ESCAPE:
                running = 0;
                break;
            case SDLK_SPACE:
                fire();
            default:
                break;
        }
    }
}

void process_input(double dt)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        process_event(&event, dt);
    }
}

int is_alive(int x, int y)
{
    int r;
    int pos;

    pos = y * 11 + x;
    r = 0;

    if (pos >= 32) {
        pos -= 32;
        r = 1;
    }

    return (alive[r] & (1 << pos)) > 0;
}


void update(double dt)
{
    int x, y;
    int max_x, max_y, min_x;
    int last_x, last_y;
    int nalive;

    ship_pos += velocity;
    counter += dt;

    velocity = velocity - (velocity*0.9*dt);

    if (gameover) velocity = 0;

    /* bounce off walls */

    if (ship_pos < 0 || ship_pos > ((WINDOW_WIDTH-32)*ZOOM)) {
        velocity *= -1;
    }

    /* TODO check if bullet hit enemies */

    /* TODO update score if new enemy has been killed */

    /* update brood max coordinates */

    max_x = -1;
    max_y = -1;
    nalive = 0;
    min_x = 9999;

    for (y = 0; y < 5; y++) {
        last_x = -1;
        last_y =
            (y + 1) * BROOD_SIZE +
            y * BROOD_PADDING;
        for (x = 0; x < 11; x++) {
            if (is_alive(x, y)) {
                nalive++;
                last_x =
                    (x + 1) * BROOD_SIZE +
                    x * BROOD_PADDING;
                last_x = x;
            }
            if (last_x >= 0 && last_x < min_x) min_x = last_x;
        }

        if (last_x >= 0 && last_y > max_y) {
            max_y = last_y;
        }

        if (last_x > max_x) max_x = last_x;
    }

    brood_max_x = (max_x + 1)*BROOD_SIZE + max_x*BROOD_PADDING;
    brood_min_x = min_x*(BROOD_SIZE + BROOD_PADDING);
    brood_max_y = max_y;

    /* update urgency of enemy attack based on how many are alive */

    if (nalive == 1) {
        counter_max = 0.1;
        brood_speed = 10;
    } else if (nalive < 27) {
        counter_max = 0.5;
        brood_speed = 6;
    } else {
        counter_max = 0.75;
        brood_speed = 4;
    }

    /* win or die, it's all the same... */
    if (nalive == 0) {
        gameover = 1;
    }

    if (!gameover && counter > counter_max) {
        int brood_width;
        int xstart;
        int intersection;
        counter = 0;
        brood_xoff += brood_speed*brood_direction;

        brood_width = brood_max_x - brood_min_x;
        xstart = brood_xoff + brood_min_x + WINDOW_PADDING;

        /* if brood bounding box hits a wall, change direction */

        intersection =
            xstart <= WINDOW_PADDING ||
            (xstart + brood_width + WINDOW_PADDING) >
            WINDOW_WIDTH;

        if (intersection) {
            brood_direction *= -1;
            brood_yoff += 4;

            /* wrap-around x-offset for brood */
            while (xstart < WINDOW_PADDING) {
                brood_xoff += brood_speed*brood_direction;
                xstart = brood_xoff + brood_min_x + WINDOW_PADDING;
            }

            while ((xstart + brood_width + WINDOW_PADDING) >= WINDOW_WIDTH) {
                brood_xoff += brood_speed*brood_direction;
                xstart = brood_xoff + brood_min_x;
            }
        }

        if (brood_yoff + brood_max_y > brood_touchdown) {
            gameover = 1;
        }
    }
}

void set_pixel(int x, int y, int s)
{
    size_t pos;
    uint8_t color[3];
    int yz, xz;

    pos = (y*WINDOW_WIDTH + x);

    screen[pos] = s;
}

void draw_hline (int xpos, int ypos, int len)
{
    int x;
    for (x = 0; x < len; x++) set_pixel(xpos + x, ypos, 0xFF);
}

void draw_vline (int xpos, int ypos, int len)
{
    int y;
    for (y = 0; y < len; y++) set_pixel(xpos, ypos + y, 0xFF);
}

void draw_rect(int xpos, int ypos, int w, int h)
{
    int x, y;

    draw_hline(xpos, ypos, w);
    draw_hline(xpos, ypos + h, w);
    draw_vline(xpos, ypos, h);
    draw_vline(xpos + w, ypos, h);
}

void draw_enemy(int xpos, int ypos, const char *enemy)
{
    int x, y;
    for (y = 0; y < 12; y++) {
        for (x = 0; x < 12; x++) {
            int bpos;
            int c;
            bpos = (x / 16) + 2*y;
            if (x >= 8) {
                c = enemy[2*y + 1] & (1 << (x - 8));
            } else {
                c = enemy[2*y] & (1 << x);
            }
            c = c > 0 ? 0xFF : 0;
            set_pixel(xpos + x, ypos + y, c);
        }
    }
}

double lerp(double curval, double target, double speed)
{
    curval += (target - curval) * speed;
    return curval;
}

void draw_glyph(int xoff, int yoff, char c)
{
    int pos;
    int xpos, ypos;
    int x, y;

    pos = c - 0x20;

    ypos = pos / 16;
    xpos = pos % 16;

    for (y = 0; y < 8; y++) {
        uint8_t row;

        row = font_bits[(ypos*8 + y)*16 + xpos];
        for (x = 0; x < 8; x++) {
            uint8_t s;
            s = (row & (1 << x)) > 0 ? 0xFF : 0;
            set_pixel(xoff + x, yoff + y, s);
        }
    }
}

void draw_text(const char *txt, int x, int y)
{
    int len;
    int i;

    len = strlen(txt);

    for (i = 0; i < len; i++) {
        draw_glyph(x + i*8, y, txt[i]);
    }
}

void kill_enemy(int x, int y)
{
    int r;
    int pos;

    pos = y * 11 + x;
    r = 0;

    if (pos >= 32) {
        pos -= 32;
        r = 1;
    }

    alive[r] &= ~(1 << pos);
}

void draw(double dt)
{
    int x, y;
    char score_msg[128];

    memset(screen, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT);

    sprintf(score_msg, "SCORE: %d", score);
    draw_text(score_msg, 2, 2);

    if (gameover) {
        draw_text("GAME OVER", (WINDOW_WIDTH - 9*8)/2, WINDOW_HEIGHT/2);
    }


    for (y = 0; y < 5; y++) {
        for (x = 0; x < 11; x++) {
            const char *enemy;

            if (is_alive(x, y)) {
                if (y == 0) {
                    enemy = enemy3_bits;
                } else if (y < 3) {
                    enemy = enemy2_bits;
                } else {
                    enemy = enemy1_bits;
                }
                draw_enemy(
                    brood_xoff + WINDOW_PADDING + x*(BROOD_SIZE + BROOD_PADDING),
                    16 + brood_yoff + y*(BROOD_SIZE + BROOD_PADDING),
                    enemy);
            }
        }
    }

#if BOUNDING_BOX
    draw_rect(brood_xoff + brood_min_x + WINDOW_PADDING,
              brood_yoff + 16,
              brood_max_x - brood_min_x,
              brood_max_y);
    draw_vline((ship_pos + ZOOM*16)/ZOOM, 0, WINDOW_HEIGHT);
#endif

    /* Copy + scale to screen back buffer */
    for (y = 0; y < WINDOW_HEIGHT; y++) {
        for (x = 0; x < WINDOW_WIDTH; x++) {
            int c = screen[y*WINDOW_WIDTH + x];
            int yz, xz;

            for (yz = 0; yz < ZOOM; yz++) {
                for (xz = 0; xz < ZOOM; xz++) {
                    size_t pos = ((y*ZOOM + yz)*WINDOW_WIDTH*ZOOM) + (x*ZOOM + xz);
                    pos *= 3;

                    /* perform interpolation for ghosting effect */
                    if (c == 0xFF) {
                        uint8_t clr = (uint8_t)lerp(pixels[pos], 0xFF, dt * GHOST_AMT);
                        clr = 0xFF;
                        backbuf[pos] = clr;
                        backbuf[pos + 1] = clr;
                        backbuf[pos + 2] = clr;
                    } else {
                        uint8_t clr = (uint8_t)lerp(pixels[pos], 0x00, dt * GHOST_AMT);
                        clr = 0x00;
                        backbuf[pos] = clr;
                        backbuf[pos + 1] = clr;
                        backbuf[pos + 2] = clr;
                    }
                }
            }
        }
    }

    /* draw ship directly onto screen for smoother scrolling */
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 32; x++) {
            size_t pos;
            int xoff;
            int xz, yz;
            size_t rowpos;
            int c;

            xoff = (int)ship_pos;
            if (xoff < 0) {
                xoff = 0;
                ship_pos = 0;
            } else if (xoff > (WINDOW_WIDTH-32)*ZOOM) {
                xoff = (WINDOW_WIDTH-32)*ZOOM;
                ship_pos = xoff;
            }

            rowpos = ((y*ZOOM + (WINDOW_HEIGHT - 24)*ZOOM) * WINDOW_WIDTH*ZOOM);
            pos = rowpos + x*ZOOM + xoff;
            pos *= 3;

            /* get byte position (pixels -> bytes) */
            c = tank_bits[y*4 + (x/8)];

            /* get bits from byte (bytes -> bits) */
            c = c & (1 << (x - (8*(x/8))));

            /* determine color shade */
            c = c > 0 ? 0xFF : 0x00;

            if (c > 0) {
                for (yz = 0; yz < ZOOM; yz++) {
                    for (xz = 0; xz < ZOOM; xz++) {
                        int zoff;
                        zoff = xz + yz*WINDOW_WIDTH*ZOOM;
                        zoff *= 3;
                        backbuf[pos + zoff] = c;
                        backbuf[pos + zoff + 1] = c;
                        backbuf[pos + zoff + 2] = c;
                    }
                }
            }
        }
    }

    /* copy back buffer to screen with ghosting */

    for (y = 0; y < WINDOW_HEIGHT*ZOOM; y++) {
        for (x = 0; x < WINDOW_WIDTH*ZOOM; x++) {
            int pos;
            int c;

            /* only ghost if the pixel is turning off
             * In other words, pixels will instantly
             * turn on, but slowly turn off.
             */
            pos = (y*WINDOW_WIDTH*ZOOM + x)*3;
            c = backbuf[pos];
            if (c == 0) {
                c = (uint8_t)lerp(pixels[pos], c, dt * GHOST_AMT);
            }
            pixels[pos] = c;
            pixels[pos + 1] = c;
            pixels[pos + 2] = c;
        }
    }
    SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH*ZOOM*3);
	SDL_RenderCopy(renderer, texture, NULL, &viewport);
}

void main_loop(double dt)
{
    process_input(dt);
    SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
    SDL_RenderClear(renderer);

    update(dt);
    draw(dt);

    SDL_RenderPresent(renderer);
}

static double now_sec(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec*1e-6;
}

bool init()
{
    size_t nbytes;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH*ZOOM, WINDOW_HEIGHT*ZOOM, 0, &window, &renderer);
    if (window == NULL | renderer == NULL) {
        return false;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH*ZOOM, WINDOW_HEIGHT*ZOOM);

    if(texture == NULL || SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE)) {
        return false;
    }

    nbytes = WINDOW_WIDTH*ZOOM*WINDOW_HEIGHT*ZOOM*3;
    pixels = malloc(nbytes);
    memset(pixels, 0x64, nbytes);
    backbuf = malloc(nbytes);
    memset(pixels, 0x64, nbytes);

    nbytes = WINDOW_WIDTH*WINDOW_HEIGHT;
    screen = malloc(nbytes);
    memset(screen, 0x00, nbytes);

    if (SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32)) != 0) {
        return false;
    }

    viewport.x = 0;
    viewport.y = 0;
    viewport.w = WINDOW_WIDTH*ZOOM;
    viewport.h = WINDOW_HEIGHT*ZOOM;

    alive[0] = 0xFFFFFFFF;
    alive[1] = 0xFFFFFFFF;

    return true;
}


int main(int argc, char *argv[])
{
    init();

    running = 1;
    double now, then;

    now = now_sec();
    then = now;
    while (running) {
        double dt;
        now = now_sec();
        dt = now - then;
        if (dt > 0.0166)  {
            main_loop(dt);
            then = now;
        }
        SDL_Delay(1);
    }

    destroy();
    return 0;
}
