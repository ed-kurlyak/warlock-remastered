#include "backbuffer.h"

// GRAPH0.H - header file for basic graphics and sprites

// D E F I N E S  ////////////////////////////////////////////////////////////

#define SPRITE_WIDTH      16
#define SPRITE_HEIGHT     16

#define MAX_SPRITE_FRAMES 24
#define SPRITE_DEAD       0
#define SPRITE_ALIVE      1
#define SPRITE_DYING      2

// S T R U C T U R E S ///////////////////////////////////////////////////////

// this structure holds a RGB triple in three bytes

#pragma pack (push, my, 1)

typedef struct RGB_color_typ
        {

        unsigned char red;    // red   component of color 0-63
        unsigned char green;  // green component of color 0-63
        unsigned char blue;   // blue  component of color 0-63

        } RGB_color, *RGB_color_ptr;

typedef struct pcx_header_typ
        {
        char manufacturer;
        char version;
        char encoding;
        char bits_per_pixel;
        int x,y;
        int width,height;
        int horz_res;
        int vert_res;
        char ega_palette[48];
        char reserved;
        char num_color_planes;
        int bytes_per_line;
        int palette_type;
        char padding[58];

        } pcx_header, *pcx_header_ptr;


typedef struct pcx_picture_typ
        {
        pcx_header header;
        RGB_color palette[256];
        char *buffer;

        } pcx_picture, *pcx_picture_ptr;


typedef struct sprite_typ
        {
        int x,y;            // position of sprite
        int x_old,y_old;    // old position of sprite
        int width,height;   // dimensions of sprite in pixels
        int anim_clock;     // the animation clock
        int anim_speed;     // the animation speed
        int motion_speed;   // the motion speed
        int motion_clock;   // the motion clock

        char *frames[MAX_SPRITE_FRAMES]; // array of pointers to the images
        int curr_frame;                      // current frame being displayed
        int num_frames;                      // total number of frames
        int state;                           // state of sprite, alive, dead...
        char *background;                // whats under the sprite

        } sprite, *sprite_ptr;

#pragma pack (pop, my)

// E X T E R N A L S /////////////////////////////////////////////////////////

//extern Set_Mode(int mode);

// G L O B A L S  ////////////////////////////////////////////////////////////

extern unsigned int sprite_width;
extern unsigned int sprite_height;

// P R O T O T Y P E S ///////////////////////////////////////////////////////

void Set_Palette_Register(int index, RGB_color_ptr color);
void Get_Palette_Register(int index, RGB_color_ptr color);
void Plot_Pixel_Fast(int x,int y,unsigned char color);
void Plot_Pixel_Fast_D(int x,int y,unsigned char color);
void PCX_Init(pcx_picture_ptr image, short int width, short int height);
void PCX_Delete(pcx_picture *image);
void PCX_Load(char *filename, pcx_picture_ptr image, short int enable_palette,
			  short int width, short int height);

void PCX_Show_Buffer(pcx_picture_ptr image);
void Show_Double_Buffer(char far* buffer);
void Init_Double_Buffer(void);
void Blit_String(int x,int y,int color, char *string, int trans_flag);
unsigned char Get_Pixel(int x,int y);
unsigned char Get_Pixel_D(int x,int y);
void Sprite_Init(sprite_ptr sprite,int x,int y,int ac,int as,int mc,int ms);

void PCX_Grap_Bitmap(pcx_picture_ptr image,
                     sprite_ptr sprite,
                     int sprite_frame,
                     int grab_x, int grab_y);

void Blit_Char(int xc,int yc,char c,int color,int trans_flag);

void Plot_Pixel_Fast(int x,int y,unsigned char color);

void Plot_Pixel_Fast_D(int x,int y,unsigned char color);

unsigned char Get_Pixel(int x,int y);

unsigned char Get_Pixel_D(int x,int y);

void Sprite_Delete(sprite_ptr sprite);

void Behind_Sprite(sprite_ptr sprite);

void Erase_Sprite(sprite_ptr sprite);

void Draw_Sprite(sprite_ptr sprite);

void Behind_Sprite_VB(sprite_ptr sprite);

void Erase_Sprite_VB(sprite_ptr sprite);

void Draw_Sprite_VB(sprite_ptr sprite);

extern unsigned char* g_video_buffer;

