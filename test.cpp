//
//  main.cpp
//  WallRender
//
//  Created by Jan Legleitner on 08.06.14.
//  Copyright (c) 2014 Jarar-works. All rights reserved.
//
 
#include <SDL/SDL.h>
// #include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lodepng.h"
 
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))

#define sign(v) (((v) > 0) - ((v) < 0))
 
#define FULLSCREEN
#define DEG_2_RAD 0.0174533f
#define PLAYER_EYE_HEIGHT 32.0f
#define SECTOR_ITERATION_LIMIT 32
 
typedef unsigned char byte;
typedef unsigned short word;
 
typedef struct
{
    byte r, g, b;
} Color_t;
 
typedef struct
{
    int width, height;
    Color_t *data;
} Texture_t;
 
typedef struct
{
    float x, y;
} Vector_2D;
 
typedef struct
{
    float x, y, z;
} Vector_3D;
 
typedef struct
{
    Vector_3D position, velocity;
    float angle, yaw;
    int sector;
} Player_t;
 
typedef struct
{
    int portalSector;
     
    Vector_2D p1, p2;
    Texture_t texture;
} Wall_t;
 
typedef struct
{
    int wallCount;
    int floorHeight, ceilHeight;
    float brightness;
     
    Wall_t *walls;
    Texture_t floorTex, ceilTex;
} Sector_t;
 
 
 
SDL_Event event;
SDL_Surface *screen;
byte keys[320];
Color_t *frameBuffer;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
bool running = true;
int fps = 0;
float oldTime = 0.0f;
float timeC = 0.0f;
float deltaTime = 0.0f;
float distToPP = 1.0f;
 
int sectorCount;
Player_t player;
Sector_t *sectors = NULL;
 
int curSector;
Wall_t oldWall;
int drawMinY, drawMaxY;

Color_t grey; 
Color_t black; 

bool IsPointLeftFromLine(Vector_2D l1, Vector_2D l2, Vector_2D p)
{
    return ((l2.x - l1.x)*(p.y - l1.y) - (l2.y - l1.y)*(p.x - l1.x)) > 0;
}
 
static inline byte lineSegLineSegIntersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s02_x;
    float s02_y;
    float s10_x;
    float s10_y;
    float s32_x;
    float s32_y;
    float s_numer;
    float t_numer;
    float denom;
    float t;
     
    s10_x = p1_x - p0_x;
    s10_y = p1_y - p0_y;
    s32_x = p3_x - p2_x;
    s32_y = p3_y - p2_y;
     
    denom = s10_x * s32_y - s32_x * s10_y;
     
    if(denom == 0.0f)
    {
        return 0;
    }
     
    byte denomPositive = denom > 0;
     
    s02_x = p0_x - p2_x;
    s02_y = p0_y - p2_y;
    s_numer = s10_x * s02_y - s10_y * s02_x;
     
    if((s_numer < 0) == denomPositive)
    {
        return 0;
    }
     
    t_numer = s32_x * s02_y - s32_y * s02_x;
     
    if((t_numer < 0) == denomPositive)
    {
        return 0;
    }
     
    if(((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
    {
        return 0;
    }
     
    t = t_numer / denom;
    *i_x = p0_x + (t * s10_x);
    *i_y = p0_y + (t * s10_y);
     
    return 1;
}
 
 
void drawBufferToScreen(Color_t *buffer, SDL_Surface *screen)
{
    Uint32 *bufp;
    bufp = (Uint32 *) screen->pixels;
     
    for(int y=0; y<SCREEN_HEIGHT; y++)
    {
        for(int x=0; x<SCREEN_WIDTH; x++)
        {
            Color_t *c = &buffer[x*SCREEN_HEIGHT + y];
            Uint32 cm = SDL_MapRGB(screen->format, c->r, c->g, c->b);
            *bufp = cm;
            bufp++;
        }
         
        bufp += screen->pitch / 4;
        bufp -= SCREEN_WIDTH;
    }
     
    SDL_UpdateRect(screen, 0, 0, 0, 0);
}
 
void clearFrameBuffer(Color_t *buffer, Color_t c)
{
    int i, j;
    for(i=0; i<SCREEN_WIDTH; i++)
    {
        for(j=0; j<SCREEN_HEIGHT; j++)
        {
            buffer[i*SCREEN_HEIGHT + j] = c;
        }
    }
}
 
void putPixel(int x, int y, Color_t c, Color_t *fb)
{
    if(x>=0 && x<SCREEN_WIDTH && y>=0 && y<SCREEN_HEIGHT)
        fb[x*SCREEN_HEIGHT+y] = c;
}
 
void drawVertLine(int y1, int y2, int x, Color_t c, Color_t *fb)
{
    for(; y1<y2; y1++)
    {
        putPixel(x, y1, c, fb);
    }
}
 
void drawLine(int x1, int y1, int x2, int y2, Color_t c, Color_t *fb)
{
    bool yLonger = false;
    int incrementVal;
    int endVal;
     
    int shortLen = y2-y1;
    int longLen = x2-x1;
     
    if(abs(shortLen) > abs(longLen))
    {
        int swap = shortLen;
        shortLen = longLen;
        longLen = swap;
        yLonger = true;
    }
     
    endVal = longLen;
     
    if(longLen < 0)
    {
        incrementVal = -1;
        longLen = -longLen;
    }
    else
    {
        incrementVal = 1;
    }
     
    double decInc;
     
    if(longLen == 0)
    {
        decInc = (double) shortLen;
    }
    else
    {
        decInc = ((double) shortLen / (double) longLen);
    }
     
    double j = 0.0;
     
    if(yLonger)
    {
        for(int i=0; i != endVal; i+=incrementVal)
        {
            putPixel(x1 + (int) j, y1+i, c, fb);
            j += decInc;
        }
    }
    else
    {
        for(int i=0; i != endVal; i+=incrementVal)
        {   
            putPixel(x1+i, y1 + (int) j, c, fb);
            j += decInc;
        }
    }
}
 
 
 
Texture_t textureFromPng(const char *path)
{
    unsigned width, height;
    std::vector<unsigned char> image;
    unsigned err = lodepng::decode(image, width, height, path);
     
    if(err)
    {
        printf("Error decoding png <%s>\n", path);
        exit(1);
    }
     
    Texture_t tex;
    tex.width = width;
    tex.height = height;
    tex.data = (Color_t *) malloc(tex.width * tex.height * sizeof(Color_t));
     
    for(int x=0; x<tex.width; x++)
    {
        for(int y=0; y<tex.height; y++)
        {
            byte r = image[4*tex.width*y+4*x+0];
            byte g = image[4*tex.width*y+4*x+1];
            byte b = image[4*tex.width*y+4*x+2];
            tex.data[y*tex.width+x].r = r;
            tex.data[y*tex.width+x].g = g;
            tex.data[y*tex.width+x].b = b;
        }
    }
     
    return tex;
}
 
 
Sector_t *LoadMap(const char *path)
{
    Texture_t texTable[5];
    texTable[0] = textureFromPng("/Users/Jan/Documents/Projekte/RaycasterSdl/RaycasterSdl/Data/textures/greystone.png");
    texTable[1] = textureFromPng("/Users/Jan/Documents/Projekte/RaycasterSdl/RaycasterSdl/Data/textures/colorstone.png");
    texTable[2] = textureFromPng("/Users/Jan/Documents/Projekte/RaycasterSdl/RaycasterSdl/Data/textures/bluestone.png");
    texTable[3] = textureFromPng("/Users/Jan/Documents/Projekte/RaycasterSdl/RaycasterSdl/Data/textures/wood.png");
    texTable[4] = textureFromPng("/Users/Jan/Documents/Projekte/RaycasterSdl/RaycasterSdl/Data/textures/redbrick.png");
     
    FILE *file = fopen(path, "r");
     
    if(!file)
    {
        printf("Error opening file <%s>\n", path);
        exit(1);
    }
     
    fscanf(file, "%i %f %f %f %i", &sectorCount, &player.position.x, &player.position.y, &player.angle, &player.sector);
    Sector_t *secs = (Sector_t *) malloc(sectorCount * sizeof(Sector_t));
    player.angle = player.angle * DEG_2_RAD;
     
    printf("Reading %i sectors...\n", sectorCount);
     
    for(int i=0; i<sectorCount; i++)
    {
        int floorTexIndex, ceilTexIndex;
        fscanf(file, "%i %i %i %i %i %f", &secs[i].wallCount, &secs[i].floorHeight, &secs[i].ceilHeight, &floorTexIndex, &ceilTexIndex, &secs[i].brightness);
        secs[i].walls = (Wall_t *) malloc(secs[i].wallCount * sizeof(Wall_t));
        secs[i].floorTex = texTable[floorTexIndex];
        secs[i].ceilTex = texTable[ceilTexIndex];
         
        printf("\nReading %i walls from sector %i:\n", secs[i].wallCount, i);
         
        for(int j=0; j<secs[i].wallCount; j++)
        {
            int texIndex;
            fscanf(file, "%i", &texIndex);
            secs[i].walls[j].texture = texTable[texIndex];
             
            fscanf(file, "%i", &secs[i].walls[j].portalSector);
             
            float x1, y1, x2, y2;
            fscanf(file, "%f %f %f %f", &x1, &y1, &x2, &y2);
            secs[i].walls[j].p1.x = x1;
            secs[i].walls[j].p1.y = y1;
            secs[i].walls[j].p2.x = x2;
            secs[i].walls[j].p2.y = y2;
             
            printf("Wall %i: %f %f %f %f\n", j, x1, y1, x2, y2);
        }
    }
     
    fclose(file);
    return secs;
}
 
void CheckInput()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            running = false;
        else if(event.type == SDL_KEYDOWN)
            keys[event.key.keysym.sym] = true;
        else if(event.type == SDL_KEYUP)
            keys[event.key.keysym.sym] = false;
    }
}
 
 
void MovePlayer()
{
    if(keys[SDLK_UP])
    {
        player.velocity.x = cos(player.angle) * 10.0f;
        player.velocity.y = sin(player.angle) * 10.0f;
    }
     
    if(keys[SDLK_DOWN])
    {
        player.velocity.x = -cos(player.angle) * 10.0f;
        player.velocity.y = -sin(player.angle) * 10.0f;
    }
     
    if(keys[SDLK_LEFT])
        player.angle -= 1.6f * deltaTime;
     
    if(keys[SDLK_RIGHT])
        player.angle += 1.6f * deltaTime;
     
    if(keys[SDLK_PAGEDOWN])
        player.velocity.z = -40.0f;
    else if(keys[SDLK_PAGEUP])
        player.velocity.z = 80.0f;
     
    if(keys[SDLK_ESCAPE])
        running = false;
     
    player.velocity.x -= player.velocity.x * 6.0f * deltaTime;
    player.velocity.y -= player.velocity.y * 6.0f * deltaTime;
     
     
    if(player.velocity.x > 1.0f || player.velocity.x < 1.0f || player.velocity.y > 1.0f || player.velocity.y < 1.0f)
    {
        Sector_t sector = sectors[player.sector];
         
        for(int i=0; i<sector.wallCount; i++)
        {
            Wall_t wall = sector.walls[i];
            Vector_2D newPos = { player.position.x + player.velocity.x * deltaTime, player.position.y + player.velocity.y * deltaTime };
             
            // Bug: if player gets too close to a wall, the program gets too slow and delta time goes high, which leads the new player position
            // to be very far away (multiplied with deltaTime) so the next sector will be choses instead of the first
             
            if(IntersectBox(player.position.x, player.position.y, newPos.x, newPos.y, wall.p1.x, wall.p1.y, wall.p2.x, wall.p2.y))
            {
                if(IsPointLeftFromLine(wall.p1, wall.p2, newPos))
                {
                    // Player crossed a wall of his sector, check all neigbour sectors to which sector he wants to go and
                    // let the player collide with the wall, if it isnt a portal to another sector or the wall is to high for him to climb it
                     
                    if(wall.portalSector >= 0)
                    {
                        // Wall is a portal to another sector
                        player.sector = wall.portalSector;
                        player.position.z = sectors[wall.portalSector].floorHeight;
                         
                        goto breakLoop;
                    }
                     
                    //Collide with the wall - let player slide on the wall
                    Vector_2D wd = { wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y };
                    player.velocity.x = wd.x * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                    player.velocity.x = wd.y * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                }
            }
        }
         
                    // Player crossed a wall of his sector, check all neigbour sectors to which sector he wants to go and
                    // thelet player collide with the wall, if it isnt a portal to another sector or the wall is to high for him to climb it
                     
                    //Vector_2D wd = { wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y };
                     
                    //Let player slide on the wall
                    //player.velocity.x = wd.x * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                    //player.velocity.x = wd.y * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                     
                    /*for(int j=0; j<sector.neighbourCount; j++)
                    {
                        for(int n=0; n<sectors[sector.neighbours[j]].wallCount; n++)
                        {
                            Wall_t nWall = sectors[sector.neighbours[j]].walls[n];
                             
                            if((nWall.p1.x == wall.p1.x && nWall.p1.y == wall.p1.y && nWall.p2.x == wall.p2.x && nWall.p2.y == wall.p2.y) ||
                               (nWall.p1.x == wall.p2.x && nWall.p1.y == wall.p2.y))
                            {*/
                                /*float maxFloor = max(sector.floorHeight, sectors[sector.neighbours[j]].floorHeight);
                                float minCeil = min(sector.ceilHeight, sectors[sector.neighbours[j]].ceilHeight);
                                 
                                //Ceiling is too low for the player or floor too high, so player collides with the wall
                                if(minCeil < player.position.z + 10 || maxFloor > player.position.z + 5)
                                {
                                    Vector_2D wd = { wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y };
                                     
                                    //Let player slide on the wall
                                    player.velocity.x = wd.x * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                                    player.velocity.x = wd.y * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                                }
                                else*/
                                /*{
                                    player.sector = sector.neighbours[j];
                                    printf("Player is now in sector %i\n", player.sector);
                                }
                                 
                                goto neighbourLoop;
                            }
                        }
                    }
                     
                     
                    //Vector_2D wd = { wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y };
                     
                    //Let player slide on the wall
                    //player.velocity.x = wd.x * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                    //player.velocity.x = wd.y * (player.velocity.x*deltaTime*wd.x + player.velocity.y*deltaTime*wd.y) / (wd.x*wd.x + wd.y*wd.y);
                     
                     
                   // break;
                }
            }
        }*/
         
        breakLoop:
         
        player.position.x += player.velocity.x * deltaTime;
        player.position.y += player.velocity.y * deltaTime;
    }
    else
    {
        player.velocity.x = 0.0f;
        player.velocity.y = 0.0f;
    }
     
    int floorHeight = sectors[player.sector].floorHeight;
     
    if(player.position.z < floorHeight + PLAYER_EYE_HEIGHT)
    {
        player.position.z = floorHeight + PLAYER_EYE_HEIGHT;
        player.velocity.z = 0.0f;
    }
    else
    {
        player.velocity.z -= 300.0f * deltaTime;
    }
     
    player.position.z += player.velocity.z * deltaTime;
}
 
 
void CalcTime()
{
    oldTime = timeC;
    timeC = SDL_GetTicks();
    deltaTime = (timeC - oldTime) / 1000.0f;
    fps = (int) (1.0f / deltaTime);
}
 
 
void DrawMap()
{
    //Draw player position
    putPixel(10+player.position.x*4, 10+player.position.y*4, grey, frameBuffer);
     
    //Draw all sectors
    for(int i=0; i<sectorCount; i++)
    {
        for(int j=0; j<sectors[i].wallCount; j++)
        {
            drawLine(10+sectors[i].walls[j].p1.x*4, 10+sectors[i].walls[j].p1.y*4,
                     10+sectors[i].walls[j].p2.x*4, 10+sectors[i].walls[j].p2.y*4,
                     grey, frameBuffer);
        }
    }
     
    //Draw player sector
    for(int j=0; j<sectors[player.sector].wallCount; j++)
    {
        drawLine(10+sectors[player.sector].walls[j].p1.x*4, 10+sectors[player.sector].walls[j].p1.y*4,
                 10+sectors[player.sector].walls[j].p2.x*4, 10+sectors[player.sector].walls[j].p2.y*4,
                 grey, frameBuffer);
    }
}
 
int DrawWall(Wall_t wall, Sector_t sector, Vector_2D rayEnd, float rayAngle, int x)
{
    //Check if the ray (defined by Player and rayEnd) hits the given wall, if not exit function
     
    float hitX, hitY;
    if(lineSegLineSegIntersection(wall.p1.x, wall.p1.y, wall.p2.x, wall.p2.y, player.position.x, player.position.y, rayEnd.x, rayEnd.y, &hitX, &hitY))
    {
        //Ray intersects with the wall, check if its a portal wall to another sector
         
        if(wall.portalSector >= 0)
        {
            //Wall is a portal to another sector, render upper / lower wall if the floor height of
            //the portal sector is lower than our sector height
             
            Sector_t portalSector = sectors[wall.portalSector];
             
            if(portalSector.floorHeight > sector.floorHeight)
            {
                //Render lower wall
                 
                //Calculate the distance from the player to the intersection point with the wall
                float dist = sqrtf(((hitX-player.position.x)*(hitX-player.position.x))+((hitY-player.position.y)*(hitY-player.position.y)));
                dist *= cos(rayAngle-player.angle);
                 
                float distToWall = dist * 32.0f;
                float drawStart = (SCREEN_HEIGHT / 2) + ((player.position.z - portalSector.floorHeight) / distToWall) * distToPP;
                float drawEnd =  (SCREEN_HEIGHT / 2) + ((player.position.z - sector.floorHeight) / distToWall) * distToPP;
                 
                //Prevent drawing the solid wall (the last solid wall until no more portals come)
                //above a nearer (already drawn) wall
                drawMaxY = drawStart;
                 
                //Do the actual drawing
                for(int i=(int) drawStart; i<(int) drawEnd; i++)
                {
                    if(i >= 0 && i <= SCREEN_HEIGHT-1)
                    {
                        frameBuffer[x*SCREEN_HEIGHT + i] = grey;
                    }
                }
            }
             
            if(portalSector.ceilHeight < sector.ceilHeight)
            {
                //Render upper wall
                 
                //Calculate the distance from the player to the intersection point with the wall
                float dist = sqrtf(((hitX-player.position.x)*(hitX-player.position.x))+((hitY-player.position.y)*(hitY-player.position.y)));
                dist *= cos(rayAngle-player.angle);
                 
                float distToWall = dist * 32.0f;
                float drawStart = (SCREEN_HEIGHT / 2) + ((player.position.z - sector.ceilHeight) / distToWall) * distToPP;
                float drawEnd =  (SCREEN_HEIGHT / 2) + ((player.position.z - portalSector.ceilHeight) / distToWall) * distToPP;
                 
                //Prevent drawing the solid wall (the last wall until no more portals come)
                //above a nearer (already drawn) wall
                drawMinY = drawEnd;
                 
                //Do the actual drawing
                for(int i=(int) drawStart; i<(int) drawEnd; i++)
                {
                    if(i >= 0 && i <= SCREEN_HEIGHT-1)
                    {
                        frameBuffer[x*SCREEN_HEIGHT + i] = grey;
                    }
                }
            }
             
            return 2;
        }
        else
        {
            //Wall is a solid wall and can be rendered from our floor to our ceiling - (if we already were in a portal from yMin to yMax)
            //so it fills the whole portal from the old sector
             
            //Calculate the distance from the player to the intersection point with the wall
            float dist = sqrtf(((hitX-player.position.x)*(hitX-player.position.x))+((hitY-player.position.y)*(hitY-player.position.y)));
            dist *= cos(rayAngle-player.angle);
             
            float distToWall = dist * 32.0f;
            float lineHeight = ((sector.ceilHeight-sector.floorHeight) / distToWall) * distToPP;
            float drawStart = (SCREEN_HEIGHT / 2) + ((player.position.z - sector.ceilHeight) / distToWall) * distToPP;
            float drawEnd =  (SCREEN_HEIGHT / 2) + ((player.position.z - sector.floorHeight) / distToWall) * distToPP;
             

			 ///////////////////////////
            float tx = wall.p1.x - hitX;
            float txsq = tx * tx;
            float ty = wall.p1.y - hitY;
            float tysq = ty * ty;
            float intersectionLen = sqrtf(txsq + tysq) * (wall.texture.width / (65.0f * (1.0f
				/ (wall.texture.width / sector.ceilHeight-sector.floorHeight))));
            float texCount = floor(intersectionLen / wall.texture.width);
            float fullLenTex = texCount * wall.texture.width;
            float texX = intersectionLen - fullLenTex;
            
            float texScale = wall.texture.height / lineHeight;
            float texIndexf = 0.0f;
             
            for(int i=(int) drawStart; i<(int) drawEnd; i++)
            {
                if(i>0 && i<SCREEN_HEIGHT)
                {
                    int texIndex = (int) texIndexf;
                    int texDataIndex = (int) (wall.texture.width*texIndex + texX);
                     
                    if(texDataIndex < wall.texture.width * wall.texture.height)
                    {
                        Color_t texCol = wall.texture.data[texDataIndex];
                         
                        float l = sector.brightness / (distToWall/32) * 32.0f;
                         
                        if(l > 1.0f)
                            l = 1.0f;
                         
                        byte r =(byte)texCol.r*l;
                        byte g =(byte)texCol.g*l;
                        byte b =(byte)texCol.b*l;
                         
                        Color_t colShade = { r, g, b };
                        frameBuffer[x*SCREEN_HEIGHT + i] = colShade;
                         
                    }
                     
                }
                texIndexf += texScale;
            }
             ////////////////////////////////////



            //Do the actual drawing
            for(int i=(int) drawStart; i<(int) drawEnd; i++)
            {
                if(i >= 0 && i <= SCREEN_HEIGHT-1)
                {
                    if(i > drawMinY && i < drawMaxY)
                    {
                        frameBuffer[x*SCREEN_HEIGHT + i] = grey;
                    }
                }
            }
             
            return 1;
        }
    }
     
    return 0;
}
 
bool DrawSector(Vector_2D rayEnd, float rayAngle, int x)
{
    //Try to draw all visible walls of this sector, if there is a portal exit loop
    //(of course draw upper and lower tex first) with portal sector as start sector
     
    Sector_t sector = sectors[curSector];
     
    for(int i=0; i<sector.wallCount; i++)
    {
        Wall_t wall = sector.walls[i];
         
        //Check if this wall is the same wall as the old wall (only in the new sector)
        if((oldWall.p1.x == wall.p1.x && oldWall.p1.y == wall.p1.y && oldWall.p2.x == wall.p2.x && oldWall.p2.y == wall.p2.y) ||
           (oldWall.p1.x == wall.p2.x && oldWall.p1.y == wall.p2.y))
        {
            continue;
        }
         
        //Check if we can draw this wall
        int result = DrawWall(wall, sector, rayEnd, rayAngle, x);
         
        if(result == 1)
        {
            //A solid wall has been drawn
            return true;
        }
        else if(result == 2)
        {
            //A portal is hit, draw the sector behind the portal. Save the old wall
            //to prevent checking the same wall in the portal sector again
            curSector = wall.portalSector;
            oldWall = wall;
             
            return false;
        }
    }
     
    return false;
}
 
void DrawPlayerPerspective()
{
    float rayAngle = (-30.0f * DEG_2_RAD) + player.angle;
     
    for(int x=0; x<SCREEN_WIDTH; x++)
    {
        Vector_2D rayEnd = { player.position.x + cosf(rayAngle) * 200.0f, player.position.y + sinf(rayAngle) * 200.0f };
        curSector = player.sector;
        drawMinY = 0; drawMaxY = SCREEN_HEIGHT-1;
         
        bool finished = false;
        int iterationCount = 0;
         
        do
        {
            iterationCount++;
             
            if(iterationCount >= SECTOR_ITERATION_LIMIT)
            {
                printf("Sector itertion limit (%i) reached!\n", SECTOR_ITERATION_LIMIT);
                break;
            }
             
            finished = DrawSector(rayEnd, rayAngle, x);
        } while(!finished);
         
        rayAngle += (60.0f * DEG_2_RAD) / SCREEN_WIDTH;
    }
}
 
 
 
 
 
 
 
 
/*float hitX, hitY;
 if(lineSegLineSegIntersection(wall.p1.x, wall.p1.y, wall.p2.x, wall.p2.y, player.position.x, player.position.y, rayEnd.x, rayEnd.y, &hitX, &hitY))
 {
 if(wall.portalSector >= 0)
 {
 // Wall is a portal to another sector, render upper / lower wall if the floor height of
 // the portal sector is lower than our sector height
  
 Sector_t portalSector = sectors[sector.walls[i].portalSector];
  
 if(portalSector.floorHeight > sector.floorHeight)
 {
 // Render lower wall
  
  
 }
 }
  
 float dist = sqrtf(((hitX-player.position.x)*(hitX-player.position.x))+((hitY-player.position.y)*(hitY-player.position.y)));
 dist *= cos(rayAngle-player.angle);
  
 float distToWall = dist * 32.0f;
 float sectorHeight = sector.ceilHeight-sector.floorHeight;
 float lineHeight = ((sectorHeight / distToWall) * distToProjectionPlane);
 float drawStart = (SCREEN_HEIGHT / 2) + ((player.position.z - sector.ceilHeight) / distToWall) * distToProjectionPlane;
 float drawEnd =  (SCREEN_HEIGHT / 2) + ((player.position.z + sector.floorHeight) / distToWall) * distToProjectionPlane;
  
 float tx = wall.p1.x - hitX;
 float txsq = tx * tx;
 float ty = wall.p1.y - hitY;
 float tysq = ty * ty;
 float intersectionLen = sqrtf(txsq + tysq) * (wall.texture.width / (3.0f * (1.0f / (wall.texture.width / sectorHeight))));
 float texCount = floor(intersectionLen / wall.texture.width);
 float fullLenTex = texCount * wall.texture.width;
 float texX = intersectionLen - fullLenTex;
  
 float texScale = wall.texture.height / lineHeight;
 float texIndexf = 0.0f;
  
 for(int i=(int) drawStart; i<(int) drawEnd; i++)
 {
 if(i>0 && i<SCREEN_HEIGHT)
 {
 int texIndex = (int) texIndexf;
 int texDataIndex = (int) (wall.texture.width*texIndex + texX);
  
 if(texDataIndex < wall.texture.width * wall.texture.height)
 {
 Color_t texCol = wall.texture.data[texDataIndex];
  
 float l = sector.brightness / (distToWall/32) * 32.0f;
  
 if(l > 1.0f)
 l = 1.0f;
  
 byte r =(byte)texCol.r*l;
 byte g =(byte)texCol.g*l;
 byte b =(byte)texCol.b*l;
  
 Color_t colShade = { r, g, b };
 frameBuffer[x*SCREEN_HEIGHT + i] = colShade;
  
 }
 }
  
 texIndexf += texScale;
 }
 }*/
 
 
 
 
 
 
 
 
void DrawScene()
{
    DrawPlayerPerspective();
    DrawMap();
     
    drawBufferToScreen(frameBuffer, screen);
    clearFrameBuffer(frameBuffer, black);
}
  
int main(int argc, char *argv[])
{
    grey.r = 125;
    grey.g = 125;
    grey.b = 125;

    black.r = 0;
    black.g = 0;
    black.b = 0;

    oldWall.portalSector = 0;
    oldWall.p1.x = 0;
    oldWall.p2.x = 0;
    oldWall.p1.y = 0;
    oldWall.p2.y = 0;
    oldWall.texture.width = 0;
    oldWall.texture.height = 0;
    oldWall.texture.data->r = 0;
    oldWall.texture.data->g = 0;
    oldWall.texture.data->b = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
     
    //const SDL_VideoInfo *info = SDL_GetVideoInfo();
    //SCREEN_WIDTH = info->current_w;
    //SCREEN_HEIGHT = info->current_h;
     
    SCREEN_WIDTH = 320*2;
    SCREEN_HEIGHT = 240*2;
     
    distToPP = (SCREEN_WIDTH / tanf(30.0f * DEG_2_RAD));
     
    int screenFlags = SDL_SWSURFACE;
 
#ifdef FULLSCREEN
    screenFlags = SDL_SWSURFACE | SDL_FULLSCREEN;
#endif
     
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, screenFlags);
     
    SDL_WM_SetCaption("RAYCASTER", NULL);
    SDL_ShowCursor(0);
    SDL_WM_GrabInput( SDL_GRAB_ON );
     
    frameBuffer = (Color_t *) malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Color_t));
    sectors = LoadMap("/Users/Jan/Documents/Projekte/WallRender/WallRender/DATA/map.txt");
     
    while(running)
    {
        CheckInput();
        MovePlayer();
        DrawScene();
        CalcTime();
    }
 
     
    SDL_Delay(100);
    free(frameBuffer); frameBuffer = NULL;
     
    SDL_Quit();
    return 0;
}