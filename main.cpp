#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <d3d11.h>
#include <vector>
#include <string>

#include <stdint.h>

#define BIT(n) (1 << (n))

//! 8 bit unsigned integer.
typedef uint8_t		uint8;
//! 16 bit unsigned integer.
typedef uint16_t	uint16;
//! 32 bit unsigned integer.
typedef uint32_t	uint32;
//! 64 bit unsigned integer.
typedef uint64_t	uint64;

//! 8 bit signed integer.
typedef int8_t		int8;
//! 16 bit signed integer.
typedef int16_t		int16;
//! 32 bit signed integer.
typedef int32_t		int32;
//! 64 bit signed integer.
typedef int64_t		int64;

//! 32 bit signed floating point number.
typedef float		float32;
//! 64 bit signed floating point number.
typedef double		float64;

//! 8 bit volatile unsigned integer.
typedef volatile uint8_t	vuint8;
//! 16 bit volatile unsigned integer.
typedef volatile uint16_t	vuint16;
//! 32 bit volatile unsigned integer.
typedef volatile uint32_t	vuint32;
//! 64 bit volatile unsigned integer.
typedef volatile uint64_t	vuint64;

//! 8 bit volatile signed integer.
typedef volatile int8_t		vint8;
//! 16 bit volatile signed integer.
typedef volatile int16_t	vint16;
//! 32 bit volatile signed integer.
typedef volatile int32_t	vint32;
//! 64 bit volatile signed integer.
typedef volatile int64_t	vint64;

//! 32 bit volatile signed floating point number.
typedef volatile float32        vfloat32;
//! 64 bit volatile signed floating point number.
typedef volatile float64        vfloat64;

//! 8 bit unsigned integer.
typedef uint8_t		byte;

//! 8 bit unsigned integer.
typedef uint8_t		u8;
//! 16 bit unsigned integer.
typedef uint16_t	u16;
//! 32 bit unsigned integer.
typedef uint32_t	u32;
//! 64 bit unsigned integer.
typedef uint64_t	u64;

//! 8 bit signed integer.
typedef int8_t		s8;
//! 16 bit signed integer.
typedef int16_t		s16;
//! 32 bit signed integer.
typedef int32_t		s32;
//! 64 bit signed integer.
typedef int64_t		s64;

//! 8 bit volatile unsigned integer.
typedef volatile u8          vu8;
//! 16 bit volatile unsigned integer.
typedef volatile u16         vu16;
//! 32 bit volatile unsigned integer.
typedef volatile u32         vu32;
//! 64 bit volatile unsigned integer.
typedef volatile u64         vu64;

//! 8 bit volatile signed integer.
typedef volatile s8           vs8;
//! 16 bit volatile signed integer.
typedef volatile s16          vs16;
//! 32 bit volatile signed integer.
typedef volatile s32          vs32;
//! 64 bit volatile signed integer.
typedef volatile s64          vs64;

typedef uint32_t sec_t;

typedef uint16 fixed12d3; /*!< \brief Used for depth (glClearDepth, glCutoffDepth) */

#define intto12d3(n)    ((n) << 3) /*!< \brief convert int to fixed12d3 */
#define floatto12d3(n)  ((fixed12d3)((n) * (1 << 3))) /*!< \brief convert float to fixed12d3 */
#define GL_MAX_DEPTH      0x7FFF /*!< \brief the maximum value for type fixed12d3 */

//////////////////////////////////////////////////////////////////////

typedef short t16;        /*!< \brief text coordinate 12.4 fixed point */
#define f32tot16(n)          ((t16)(n >> 8)) /*!< \brief convert f32 to t16 */
#define inttot16(n)          ((n) << 4) /*!< \brief convert int to t16 */
#define t16toint(n)          ((n) >> 4) /*!< \brief convert t16 to int */
#define floattot16(n)        ((t16)((n) * (1 << 4))) /*!< \brief convert float to t16 */
#define TEXTURE_PACK(u,v)    (((u) & 0xFFFF) | ((v) << 16)) /*!< \brief Pack 2 t16 texture coordinate values into a 32bit value */

typedef short int v16;       /*!< \brief vertex 4.12 fixed format */
#define inttov16(n)          ((n) << 12) /*!< \brief convert int to v16 */
#define f32tov16(n)          (n) /*!< \brief f32 to v16 */
#define v16toint(n)          ((n) >> 12) /*!< \brief convert v16 to int */
#define floattov16(n)        ((v16)((n) * (1 << 12))) /*!< \brief convert float to v16 */
#define VERTEX_PACK(x,y)     (u32)(((x) & 0xFFFF) | ((y) << 16)) /*!< \brief Pack to v16 values into one 32bit value */

typedef short int v10;       /*!< \brief normal .10 fixed point, NOT USED FOR 10bit VERTEXES!!!*/
#define inttov10(n)          ((n) << 9) /*!< \brief convert int to v10 */
#define f32tov10(n)          ((v10)(n >> 3)) /*!< \brief convert f32 to v10 */
#define v10toint(n)          ((n) >> 9) /*!< \brief convert v10 to int */
#define floattov10(n)        ((n>.998) ? 0x1FF : ((v10)((n)*(1<<9)))) /*!< \brief convert float to v10 */
#define NORMAL_PACK(x,y,z)   (u32)(((x) & 0x3FF) | (((y) & 0x3FF) << 10) | ((z) << 20)) /*!< \brief Pack 3 v10 normals into a 32bit value */

#define GFX_CONTROL           (*(vu16*) 0x04000060)

#define GFX_RDLINES_COUNT     (*(vu32*) 0x04000320)

#define GFX_FIFO              (*(vu32*) 0x04000400)
#define GFX_STATUS            (*(vu32*) 0x04000600)
#define GFX_COLOR             (*(vu32*) 0x04000480)

#define GFX_VERTEX10          (*(vu32*) 0x04000490)
#define GFX_VERTEX_XY         (*(vu32*) 0x04000494)
#define GFX_VERTEX_XZ         (*(vu32*) 0x04000498)
#define GFX_VERTEX_YZ         (*(vu32*) 0x0400049C)
#define GFX_VERTEX_DIFF       (*(vu32*) 0x040004A0)

#define GFX_VERTEX16          (*(vu32*) 0x0400048C)
#define GFX_TEX_COORD         (*(vu32*) 0x04000488)
#define GFX_TEX_FORMAT        (*(vu32*) 0x040004A8)
#define GFX_PAL_FORMAT        (*(vu32*) 0x040004AC)

#define GFX_CLEAR_COLOR       (*(vu32*) 0x04000350)
#define GFX_CLEAR_DEPTH       (*(vu16*) 0x04000354)
#define GFX_CLRIMAGE_OFFSET   (*(vu16*) 0x04000356)

#define GFX_LIGHT_VECTOR      (*(vu32*) 0x040004C8)
#define GFX_LIGHT_COLOR       (*(vu32*) 0x040004CC)
#define GFX_NORMAL            (*(vu32*) 0x04000484)

#define GFX_DIFFUSE_AMBIENT   (*(vu32*) 0x040004C0)
#define GFX_SPECULAR_EMISSION (*(vu32*) 0x040004C4)
#define GFX_SHININESS         (*(vu32*) 0x040004D0)

#define GFX_POLY_FORMAT       (*(vu32*) 0x040004A4)
#define GFX_ALPHA_TEST        (*(vu16*) 0x04000340)

#define GFX_BEGIN			(*(vu32*) 0x04000500)
#define GFX_END				(*(vu32*) 0x04000504)
#define GFX_FLUSH			(*(vu32*) 0x04000540)
#define GFX_VIEWPORT		(*(vu32*) 0x04000580)
#define GFX_TOON_TABLE		((vu16*)  0x04000380)
#define GFX_EDGE_TABLE		((vu16*)  0x04000330)
#define GFX_FOG_COLOR		(*(vu32*) 0x04000358)
#define GFX_FOG_OFFSET		(*(vu32*) 0x0400035C)
#define GFX_FOG_TABLE		((vu8*)   0x04000360)
#define GFX_BOX_TEST		(*(vs32*)  0x040005C0)
#define GFX_POS_TEST		(*(vu32*) 0x040005C4)
#define GFX_POS_RESULT		((vs32*)   0x04000620)
#define GFX_VEC_TEST		(*(vu32*) 0x040005C8)
#define GFX_VEC_RESULT      ((vs16*)   0x04000630)

#define GFX_BUSY (GFX_STATUS & BIT(27))

#define GFX_VERTEX_RAM_USAGE	(*(vu16*)  0x04000606)
#define GFX_POLYGON_RAM_USAGE	(*(vu16*)  0x04000604)

#define GFX_CUTOFF_DEPTH		(*(vu16*)0x04000610)

#define FIFO_COMMAND_PACK(c1,c2,c3,c4) (((c4) << 24) | ((c3) << 16) | ((c2) << 8) | (c1)) /*!< \brief packs four packed commands into a 32bit command for sending to the GFX FIFO */

#define REG2ID(r)				(u8)( ( ((u32)(&(r)))-0x04000400 ) >> 2 ) /*!< \brief converts a GFX command for use in a packed command list */

#define FIFO_NOP				REG2ID(GFX_FIFO) /*!< \brief packed command for nothing, just here to pad your command lists */
#define FIFO_STATUS				REG2ID(GFX_STATUS) /*!< \brief packed command for geometry engine status register<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dstatus">GBATEK http://problemkaputt.de/gbatek.htm#ds3dstatus</A> */
#define FIFO_COLOR				REG2ID(GFX_COLOR) /*!< \brief packed command for vertex color directly<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonattributes">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonattributes</A> */

#define FIFO_VERTEX16			REG2ID(GFX_VERTEX16) /*!< \brief packed command for a vertex with 3 16bit paramaters (and 16bits of padding)<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A> */
#define FIFO_VERTEX10			REG2ID(GFX_VERTEX10) /*!< \brief packed command for a vertex with 3 10bit paramaters (and 2bits of padding)<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A> */
#define FIFO_VERTEX_XY			REG2ID(GFX_VERTEX_XY) /*!< \brief packed command for a vertex with 2 16bit paramaters (reusing current last-set vertex z value)<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A> */
#define FIFO_VERTEX_XZ			REG2ID(GFX_VERTEX_XZ) /*!< \brief packed command for a vertex with 2 16bit paramaters (reusing current last-set vertex y value)<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A> */
#define FIFO_VERTEX_YZ			REG2ID(GFX_VERTEX_YZ) /*!< \brief packed command for a vertex with 2 16bit paramaters (reusing current last-set vertex x value)<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A> */
#define FIFO_TEX_COORD			REG2ID(GFX_TEX_COORD) /*!< \brief packed command for a texture coordinate<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dtexturecoordinates">GBATEK http://problemkaputt.de/gbatek.htm#ds3dtexturecoordinates</A> */
#define FIFO_TEX_FORMAT			REG2ID(GFX_TEX_FORMAT) /*!< \brief packed command for texture format<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dtextureformats">GBATEK http://problemkaputt.de/gbatek.htm#ds3dtextureformats</A> */
#define FIFO_PAL_FORMAT			REG2ID(GFX_PAL_FORMAT) /*!< \brief packed command for texture palette attributes<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dtextureattributes">GBATEK http://problemkaputt.de/gbatek.htm#ds3dtextureattributes</A> */

#define FIFO_CLEAR_COLOR		REG2ID(GFX_CLEAR_COLOR) /*!< \brief packed command for clear color of the rear plane<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3drearplane">GBATEK http://problemkaputt.de/gbatek.htm#ds3drearplane</A> */
#define FIFO_CLEAR_DEPTH		REG2ID(GFX_CLEAR_DEPTH) /*!< \brief sets depth of the rear plane<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3drearplane">GBATEK http://problemkaputt.de/gbatek.htm#ds3drearplane</A> */

#define FIFO_LIGHT_VECTOR		REG2ID(GFX_LIGHT_VECTOR) /*!< \brief packed command for direction of a light source<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters</A> */
#define FIFO_LIGHT_COLOR		REG2ID(GFX_LIGHT_COLOR) /*!< \brief packed command for color for a light<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters</A> */
#define FIFO_NORMAL				REG2ID(GFX_NORMAL) /*!< \brief packed command for normal for following vertices<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters</A> */

#define FIFO_DIFFUSE_AMBIENT	REG2ID(GFX_DIFFUSE_AMBIENT) /*!< \brief packed command for setting diffuse and ambient material properties for the following vertices<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters</A> */
#define FIFO_SPECULAR_EMISSION	REG2ID(GFX_SPECULAR_EMISSION) /*!< \brief packed command for setting specular and emmissive material properties for the following vertices<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters</A> */
#define FIFO_SHININESS			REG2ID(GFX_SHININESS) /*!< \brief packed command for setting the shininess table to be used for the following vertices<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonlightparameters</A> */

#define FIFO_POLY_FORMAT		REG2ID(GFX_POLY_FORMAT) /*!< \brief packed command for setting polygon attributes<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygonattributes">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygonattributes</A> */

#define FIFO_BEGIN				REG2ID(GFX_BEGIN) /*!< \brief packed command that starts a polygon vertex list<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A>*/
#define FIFO_END				REG2ID(GFX_END) /*!< \brief packed command that has no discernable effect, it's probably best to never use it since it bloats the size of the list.<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices">GBATEK http://problemkaputt.de/gbatek.htm#ds3dpolygondefinitionsbyvertices</A>*/
#define FIFO_FLUSH				REG2ID(GFX_FLUSH) /*!< \brief packed command that has the same effect as swiWaitForVBlank()<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3ddisplaycontrol">GBATEK http://problemkaputt.de/gbatek.htm#ds3ddisplaycontrol</A> */
#define FIFO_VIEWPORT			REG2ID(GFX_VIEWPORT) /*!< \brief packed command for setting viewport<BR><A HREF="http://problemkaputt.de/gbatek.htm#ds3ddisplaycontrol">GBATEK http://problemkaputt.de/gbatek.htm#ds3ddisplaycontrol</A> */


s32 ToF32(float n)
{
	return (s32)(n * 4096.0f);
}

#define floattof32(n) ((n) * (1 << 12))

using namespace std;

#include <ImGui/imconfig.h>
#include <ImGui/imgui_tables.cpp>
#include <ImGui/imgui_internal.h>
#include <ImGui/imgui.cpp>
#include <ImGui/imgui_draw.cpp>
#include <ImGui/imgui_widgets.cpp>
#include <ImGui/imgui_impl_win32.cpp>
#include <ImGui/imgui_impl_dx11.cpp>

#include "WaveLoader.h"

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int ConsoleIndex = 0;
char Console[8192];

char RenderModelPath[4096];
char CollisionModelPath[4096];
char OutPath[4096];
WaveModelData RenderModel;
WaveModelData CollisionModel;

bool UsedMaterials[4096];
bool AlphaTextures[4096];
bool MirroredTextures[4096];
int TextureSize = 32;

void WriteConsoleIm(const char* Msg)
{
	size_t Length = strlen(Msg);

	if (ConsoleIndex + Length >= 8192)
	{
		ConsoleIndex = 0;
		memset(Console, 0, 8192);
	}
		

	memcpy(&Console[ConsoleIndex], Msg, Length);
	ConsoleIndex += Length;
}

#include "WaveLayer.h"


void OpenModel(char* Path, bool RenderModel)
{
	if (WaveOpenFileDialog(Path, false, NULL, "All Models\0*.obj;*.stl\0") && RenderModel)
	{
		strcpy(OutPath, Path);
		//	char* Path = VideoPath;
		int i = strlen(OutPath) - 1;
		for (; i > 0; i--)
			if (OutPath[i] == '.')
			{
				OutPath[i] = '\0';
				break;
			}
	}
}

typedef enum
{
	COLLISION_TYPE_SPHERE = 0,
	COLLISION_TYPE_MESH = 1,
} CollisionTypes;

/*
* File Doc:
* Byte 0-1(char): Collision Type
* Byte 1-9(f32[2](Fixed Point)): Sphere: (Radius, Y-Offset), Bean (Radius, Height)
* Byte 9-13(u32): Vertex Count if not mesh 0
* if Mesh Type:	
*	Byte 13-End(f32[3](Fixed Point)): All vertices
*/
void ExportCollisionModel(char CollisionType, float Data[2])
{
	WaveGenNormals(&CollisionModel);
	char Path[4096];
	sprintf(Path, "%sCollision.bin", OutPath);
	FILE* File = fopen(Path, "wb");
	fwrite(&CollisionType, 1, 1, File);
	v16 x = floattov16(Data[0]);
	v16 y = floattov16(Data[1]);
	v16 z;
	v16 w;
//	u32 Cmd;
	
	fwrite(&x, 2, 1, File);
	fwrite(&y, 2, 1, File);
	u16 VertexCount = CollisionModel.VertexCount;
	fwrite(&VertexCount, 2, 1, File);
	uint16_t i = 0;
	while (i < VertexCount)
	{
		/*
		Cmd = floattof32(CollisionModel.Mesh[i].Vertices.x);
		fwrite(&Cmd, 4, 1, File);
		Cmd = floattof32(CollisionModel.Mesh[i].Vertices.y);
		fwrite(&Cmd, 4, 1, File);
		Cmd = floattof32(CollisionModel.Mesh[i].Vertices.y);
		fwrite(&Cmd, 4, 1, File);

		Cmd = floattof32(CollisionModel.Mesh[i + 1].Vertices.x);
		fwrite(&Cmd, 4, 1, File);
		Cmd = floattof32(CollisionModel.Mesh[i + 1].Vertices.y);
		fwrite(&Cmd, 4, 1, File);
		Cmd = floattof32(CollisionModel.Mesh[i + 1].Vertices.y);
		fwrite(&Cmd, 4, 1, File);
		*/

		x = floattov16(CollisionModel.Mesh[i].Vertices.x);
		y = floattov16(CollisionModel.Mesh[i].Vertices.y);
		z = floattov16(CollisionModel.Mesh[i].Vertices.z);
		w = floattov16(CollisionModel.Mesh[i].Normals.x);
		fwrite(&x, 2, 1, File);
		fwrite(&y, 2, 1, File);
		fwrite(&z, 2, 1, File);
		fwrite(&w, 2, 1, File);
		i++;

		x = floattov16(CollisionModel.Mesh[i].Vertices.x);
		y = floattov16(CollisionModel.Mesh[i].Vertices.y);
		z = floattov16(CollisionModel.Mesh[i].Vertices.z);
		w = floattov16(CollisionModel.Mesh[i].Normals.y);
		fwrite(&x, 2, 1, File);
		fwrite(&y, 2, 1, File);
		fwrite(&z, 2, 1, File);
		fwrite(&w, 2, 1, File);
		i++;

		x = floattov16(CollisionModel.Mesh[i].Vertices.x);
		y = floattov16(CollisionModel.Mesh[i].Vertices.y);
		z = floattov16(CollisionModel.Mesh[i].Vertices.z);
		w = floattov16(CollisionModel.Mesh[i].Normals.z);
		fwrite(&x, 2, 1, File);
		fwrite(&y, 2, 1, File);
		fwrite(&z, 2, 1, File);
		fwrite(&w, 2, 1, File);
		i++;

		/*
		Cmd = VERTEX_PACK(floattov16(CollisionModel.Mesh[i].Vertices.x), floattov16(CollisionModel.Mesh[i].Vertices.y));
		fwrite(&Cmd, 4, 1, File);
		Cmd = VERTEX_PACK(floattov16(CollisionModel.Mesh[i].Vertices.z), floattov16(CollisionModel.Mesh[i].Normals.x));
		fwrite(&Cmd, 4, 1, File);
		i++;
		Cmd = VERTEX_PACK(floattov16(CollisionModel.Mesh[i].Vertices.x), floattov16(CollisionModel.Mesh[i].Vertices.y));
		fwrite(&Cmd, 4, 1, File);
		Cmd = VERTEX_PACK(floattov16(CollisionModel.Mesh[i].Vertices.z), floattov16(CollisionModel.Mesh[i].Normals.y));
		fwrite(&Cmd, 4, 1, File);
		i++;
		Cmd = VERTEX_PACK(floattov16(CollisionModel.Mesh[i].Vertices.x), floattov16(CollisionModel.Mesh[i].Vertices.y));
		fwrite(&Cmd, 4, 1, File);
		Cmd = VERTEX_PACK(floattov16(CollisionModel.Mesh[i].Vertices.z), floattov16(CollisionModel.Mesh[i].Normals.z));
		fwrite(&Cmd, 4, 1, File);
		i++;
		*/
	//	x = ToF32(CollisionModel.Mesh[i].Vertices.x);
	//	y = ToF32(CollisionModel.Mesh[i].Vertices.y);
	//	z = ToF32(CollisionModel.Mesh[i].Vertices.z);
	//	fwrite(&x, 4, 1, File);
	//	fwrite(&y, 4, 1, File);
	//	fwrite(&z, 4, 1, File);		
	}
	/*
	fprintf(File, "%c", CollisionType);
	fprintf(File, "%d%d", ToF32(Data[0]), ToF32(Data[1]));
	fprintf(File, "%d", CollisionModel.VertexCount);
	for (uint32_t i = 0; i < CollisionModel.VertexCount; i++)
	{
		fprintf(File, "%d%d%d", ToF32(CollisionModel.Mesh[i].Vertices.x), ToF32(CollisionModel.Mesh[i].Vertices.y), ToF32(CollisionModel.Mesh[i].Vertices.z));
	}
	*/
	fclose(File);
}

char* GetFileNameFromPath(char* Path)
{
	if (Path == NULL)
		return NULL;

	char* FileName = Path;
	for (char* Cur = Path; *Cur != '\0'; Cur++)
	{
		if (*Cur == '/' || *Cur == '\\')
			FileName = Cur + 1;
	}

	return FileName;
}

void ExportRenderModel(FILE* IncFile)
{
	WaveModelData* Data = &RenderModel;
	uint32_t* MaterialVertices = (uint32_t*)malloc(Data->Material->MaterialCount * sizeof(uint32_t));
	uint32_t MaterialIndex = 0;

	for (uint32_t i = 0; i < Data->Material->MaterialCount; i++)
	{
		if (UsedMaterials[i])
		{
			char DiffTexture[4096];
			memset(DiffTexture, 0, 4096);
			memcpy(DiffTexture, Data->Material[i].DiffuseTexture + 1, strlen(Data->Material[i].DiffuseTexture) - 5);
			//Data->Material[i].DiffuseTexture[strlen(Data->Material[i].DiffuseTexture) - 4] = '\0';
			//char* DiffuseTexture = GetFileNameFromPath(Data->Material[i].DiffuseTexture) + 1;
			char* MaterialName = GetFileNameFromPath(Data->Material[i].MaterialName);
			fprintf(IncFile, "#include \"Tex%s_pcx.h\"\n", DiffTexture);
			fprintf(IncFile, "#include \"%s%s_bin.h\"\n", GetFileNameFromPath(OutPath), MaterialName);

		}
		
		//	printf("#include \"%s\"\n", Data->Material[i].DiffuseTexture);
		//	strcpy(Data->Material[i].DiffuseTexture, FileName);
		//	Data->Material[i].DiffuseTexture[strlen(Data->Material[i].DiffuseTexture) - 4] = '\0';
		/*
		strcat(Data->Material[i].MaterialName, "Model");
		char* NewName = (char*)malloc(strlen(FileName) + strlen("Model") + 1);
		strcpy(NewName, "Tex");
		strcat(NewName, FileName);
		strcpy(FileName, NewName);

		FileName[strlen(FileName) - 4] = '\0';
		//	strcat(FileName, ".h");
		printf("#include \"%s\"\n", FileName);
		strcpy(Data->Material[i].DiffuseTexture, FileName);
		printf("%d\n", Data->Material[i].VertexIndex);
		fprintf(IncFile, "#include \"%s_pcx.h\"\n", FileName + 1);
		
		char Path[4096];
		memset(Path, 0, 4096);
		fprintf(IncFile, "#include \"%sModel_bin.h\"\n", FileName + 4);
		*/
	}

	{
		size_t lenght = strlen(OutPath);
		char* FunctionName = (char*)malloc(lenght + 1);
		strcpy(FunctionName, GetFileNameFromPath(OutPath));
		FunctionName[lenght - 2] = '\0';

		printf("FunctionName: %s\n", FunctionName);

		u32 MaterialCount = 0;
		for (uint32_t i = 0; i < Data->Material->MaterialCount; i++)
			if (UsedMaterials[i])
				MaterialCount++;

		fprintf(IncFile, "int %sTextures[%d];\n", FunctionName, MaterialCount);
		fprintf(IncFile, "void %sLoadTextures()\n", FunctionName);
		fprintf(IncFile, "{\n");
		MaterialCount = 0;
		for (uint32_t i = 0; i < Data->Material->MaterialCount; i++)
		{
			if (UsedMaterials[i])
			{
				char DiffTexture[4096];
				memset(DiffTexture, 0, 4096);
				memcpy(DiffTexture, Data->Material[i].DiffuseTexture + 1, strlen(Data->Material[i].DiffuseTexture) - 5);
				if (MirroredTextures[i])
					fprintf(IncFile, "\tLoadMirrored = true;\n");
				if (AlphaTextures[i])
					fprintf(IncFile, "\tLoadAlpha = true;\n");

				fprintf(IncFile, "\t%sTextures[%d] = LoadTexture(TEXTURE_SIZE_%d, (u8*)Tex%s_pcx);\n", FunctionName, MaterialCount, TextureSize, DiffTexture);
				MaterialCount++;
			}
		
		}
		fprintf(IncFile, "}\n");

		fprintf(IncFile, "void %sDraw()\n", FunctionName);
		fprintf(IncFile, "{\n");
		MaterialCount = 0;
		for (uint32_t i = 0; i < Data->Material->MaterialCount; i++)
		{
			if (UsedMaterials[i])
			{
				fprintf(IncFile, "\tglBindTexture(GL_TEXTURE_2D, %sTextures[%d]);\n", FunctionName, MaterialCount);
				MaterialCount++;
				char* MaterialName = GetFileNameFromPath(Data->Material[i].MaterialName);
				fprintf(IncFile, "\tglCallList((u32*)%s%s_bin);\n", GetFileNameFromPath(OutPath), MaterialName);
			}
			
		}
		fprintf(IncFile, "}\n");

		fprintf(IncFile, "void %sDeleteTextures()\n", FunctionName);
		fprintf(IncFile, "{\n");
		fprintf(IncFile, "\tglDeleteTextures(%d, %sTextures);\n", MaterialCount, FunctionName);
		fprintf(IncFile, "}\n");
	}

	fclose(IncFile);

	for (uint32_t i = 0; i < Data->Material->MaterialCount; i++)
	{
		if (UsedMaterials[i])
		{
			if (i + 1 != Data->Material->MaterialCount)
				MaterialVertices[i] = Data->Material[i + 1].VertexIndex - Data->Material[i].VertexIndex;
			else
				MaterialVertices[i] = Data->VertexCount - Data->Material[i].VertexIndex;
		}
		

		//	printf("mat: %d\n", Data->Material[i].VertexIndex - Data->Material[i + 1].VertexIndex);
	}

	for (uint32_t j = 0; j < Data->Material->MaterialCount; j++)
	{
		if (UsedMaterials[j])
		{
			uint32_t End = 0;
			if (j + 1 != Data->Material->MaterialCount)
				End = Data->Material[j + 1].VertexIndex;
			else
				End = Data->VertexCount;

			uint32_t i = Data->Material[j].VertexIndex;

			char Path[4096];
			memset(Path, 0, 4096);
			sprintf(Path, "%s%s.bin", OutPath, Data->Material[j].MaterialName);
			FILE* File = fopen(Path, "wb");

			//	memset(Path, 0, 4096);
			//	sprintf(Path, "%s_bin.h", OutPath, Data->Material[j].MaterialName);
			//	fprintf(IncFile, "#include \"%s_pcx.h\"\n", FileName);

			u32 Size = (MaterialVertices[j] - 2) * 5 + 11;
			fwrite(&Size, 4, 1, File);
			u32 Cmd = FIFO_COMMAND_PACK(FIFO_BEGIN, FIFO_TEX_COORD, FIFO_NORMAL, FIFO_VERTEX16);
			fwrite(&Cmd, 4, 1, File);
			Cmd = 0;
			fwrite(&Cmd, 4, 1, File);
			Cmd = TEXTURE_PACK(floattot16(Data->Mesh[i].TexCoords.x * TextureSize), floattot16(Data->Mesh[i].TexCoords.y * TextureSize));
			fwrite(&Cmd, 4, 1, File);
			Cmd = NORMAL_PACK(floattov10(Data->Mesh[i].Normals.x), floattov10(Data->Mesh[i].Normals.y), floattov10(Data->Mesh[i].Normals.z));
			fwrite(&Cmd, 4, 1, File);
			Cmd = VERTEX_PACK(floattov16(Data->Mesh[i].Vertices.x), floattov16(Data->Mesh[i].Vertices.y));
			fwrite(&Cmd, 4, 1, File);
			Cmd = VERTEX_PACK(floattov16(Data->Mesh[i].Vertices.z), 0);
			fwrite(&Cmd, 4, 1, File);
			i++;
			for (; i < End - 1; i++)
			{
				Cmd = FIFO_COMMAND_PACK(FIFO_TEX_COORD, FIFO_NORMAL, FIFO_VERTEX16, FIFO_NOP);
				fwrite(&Cmd, 4, 1, File);
				Cmd = TEXTURE_PACK(floattot16(Data->Mesh[i].TexCoords.x * TextureSize), floattot16(Data->Mesh[i].TexCoords.y * TextureSize));
				fwrite(&Cmd, 4, 1, File);
				Cmd = NORMAL_PACK(floattov10(Data->Mesh[i].Normals.x), floattov10(Data->Mesh[i].Normals.y), floattov10(Data->Mesh[i].Normals.z));
				fwrite(&Cmd, 4, 1, File);
				Cmd = VERTEX_PACK(floattov16(Data->Mesh[i].Vertices.x), floattov16(Data->Mesh[i].Vertices.y));
				fwrite(&Cmd, 4, 1, File);
				Cmd = VERTEX_PACK(floattov16(Data->Mesh[i].Vertices.z), 0);
				fwrite(&Cmd, 4, 1, File);
			}
			Cmd = FIFO_COMMAND_PACK(FIFO_TEX_COORD, FIFO_NORMAL, FIFO_VERTEX16, FIFO_END);
			fwrite(&Cmd, 4, 1, File);
			Cmd = TEXTURE_PACK(floattot16(Data->Mesh[i].TexCoords.x * TextureSize), floattot16(Data->Mesh[i].TexCoords.y * TextureSize));
			fwrite(&Cmd, 4, 1, File);
			Cmd = NORMAL_PACK(floattov10(Data->Mesh[i].Normals.x), floattov10(Data->Mesh[i].Normals.y), floattov10(Data->Mesh[i].Normals.z));
			fwrite(&Cmd, 4, 1, File);
			Cmd = VERTEX_PACK(floattov16(Data->Mesh[i].Vertices.x), floattov16(Data->Mesh[i].Vertices.y));
			fwrite(&Cmd, 4, 1, File);
			Cmd = VERTEX_PACK(floattov16(Data->Mesh[i].Vertices.z), 0);
			fwrite(&Cmd, 4, 1, File);
			//	fprintf(File, "%d", );

				/*
				fprintf(File, "const u32 %s[] =\n", Data->Material[j].MaterialName);
				fprintf(File, "{\n");

				fprintf(File, "\t%d,\n", (MaterialVertices[j] - 2) * 5 + 11);

				fprintf(File, "\tFIFO_COMMAND_PACK(FIFO_BEGIN, FIFO_TEX_COORD, FIFO_NORMAL, FIFO_VERTEX16),\n");
				fprintf(File, "\tGL_TRIANGLE,\n");
				fprintf(File, "\tTEXTURE_PACK(floattot16(%f), floattot16(%f)),\n", Data->Mesh[i].TexCoords.x * TEX_SIZE, Data->Mesh[i].TexCoords.y * TEX_SIZE);
				fprintf(File, "\tNORMAL_PACK(floattov10(%f), floattov10(%f), floattov10(%f)),\n", Data->Mesh[i].Normals.x, Data->Mesh[i].Normals.y, Data->Mesh[i].Normals.z);
				fprintf(File, "\tVERTEX_PACK(floattov16(%f), floattov16(%f)),\n", Data->Mesh[i].Vertices.x, Data->Mesh[i].Vertices.y);
				fprintf(File, "\tVERTEX_PACK(floattov16(%f), 0),\n", Data->Mesh[i].Vertices.z);
				i++;

				for (; i < End - 1; i++)
				{
					fprintf(File, "\tFIFO_COMMAND_PACK(FIFO_TEX_COORD, FIFO_NORMAL, FIFO_VERTEX16, FIFO_NOP),\n");
					fprintf(File, "\tTEXTURE_PACK(floattot16(%f), floattot16(%f)),\n", Data->Mesh[i].TexCoords.x * TEX_SIZE, Data->Mesh[i].TexCoords.y * TEX_SIZE);
					fprintf(File, "\tNORMAL_PACK(floattov10(%f), floattov10(%f), floattov10(%f)),\n", Data->Mesh[i].Normals.x, Data->Mesh[i].Normals.y, Data->Mesh[i].Normals.z);
					fprintf(File, "\tVERTEX_PACK(floattov16(%f), floattov16(%f)),\n", Data->Mesh[i].Vertices.x, Data->Mesh[i].Vertices.y);
					fprintf(File, "\tVERTEX_PACK(floattov16(%f), 0),\n", Data->Mesh[i].Vertices.z);
				}

				fprintf(File, "\tFIFO_COMMAND_PACK(FIFO_TEX_COORD, FIFO_NORMAL, FIFO_VERTEX16, FIFO_END),\n");
				fprintf(File, "\tTEXTURE_PACK(floattot16(%f), floattot16(%f)),\n", Data->Mesh[i].TexCoords.x * TEX_SIZE, Data->Mesh[i].TexCoords.y * TEX_SIZE);
				fprintf(File, "\tNORMAL_PACK(floattov10(%f), floattov10(%f), floattov10(%f)),\n", Data->Mesh[i].Normals.x, Data->Mesh[i].Normals.y, Data->Mesh[i].Normals.z);
				fprintf(File, "\tVERTEX_PACK(floattov16(%f), floattov16(%f)),\n", Data->Mesh[i].Vertices.x, Data->Mesh[i].Vertices.y);
				fprintf(File, "\tVERTEX_PACK(floattov16(%f), 0),\n", Data->Mesh[i].Vertices.z);
				fprintf(File, "};\n");
				*/
			fclose(File);
		}

		
	}

	free(MaterialVertices);
}

void ExportModels(char CollisionType, float Data[2])
{
	
//	if (strlen(CollisionModelPath) != 0)
	ExportCollisionModel(CollisionType, Data);
	char Path[4096];
	sprintf(Path, "%s.h", OutPath);
	FILE* File = fopen(Path, "wb");
	fprintf(File, "#include \"%sCollision_bin.h\"\n", GetFileNameFromPath(OutPath));
	ExportRenderModel(File);
}

void SaveSettings(char* Path)
{
	FILE* File = fopen(Path, "wb");
	fwrite(UsedMaterials, sizeof(bool), 4096, File);
	fwrite(AlphaTextures, sizeof(bool), 4096, File);
	fwrite(MirroredTextures, sizeof(bool), 4096, File);
	fclose(File);
}

void LoadSettings(char* Path)
{
	FILE* File = fopen(Path, "rb");
	fread(UsedMaterials, sizeof(bool), 4096, File);
	fread(AlphaTextures, sizeof(bool), 4096, File);
	fread(MirroredTextures, sizeof(bool), 4096, File);
	fclose(File);
}

void Render(bool& done)
{
	// Poll and handle messages (inputs, window resize, etc.)
		// See the WndProc() function below for our to dispatch events to the Win32 backend.
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			done = true;
	}
	

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_MenuBar;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("###DockSpace", (bool*)0, window_flags);
	{
		ImGui::PopStyleVar();

		ImGui::PopStyleVar(1);

		ImGui::InputText("Render Model Path", RenderModelPath, 4096);
		ImGui::InputText("Collision Model Path", CollisionModelPath, 4096);
		
		if (ImGui::Button("Load"))
		{
		//	strcpy(RenderModelPath, "C:/Users/Moritz Desktop/source/repos/WaveToNDS/WaveToNDS/Kokiri Forest/Update/KokiriForest.obj");
		//	strcpy(CollisionModelPath, "C:/Users/Moritz Desktop/source/repos/WaveToNDS/WaveToNDS/Kokiri Forest/Update/Collision.stl");
		//	strcpy(OutPath, "C:/Users/Moritz Desktop/source/repos/WaveToNDS/WaveToNDS/Kokiri Forest/Update/KokiriForest");
			if (strlen(RenderModelPath) == 0)
			{
				WriteConsoleIm("Error, please select a model path\n");
			}
			else
			{
				
			//	SetCurrentDirectory("C:/Users/Moritz Desktop/source/repos/WaveToNDS/WaveToNDS/Kokiri Forest/Update/");
				WriteConsoleIm("Start model loading\n");
				RenderModel = WaveLoadModel(RenderModelPath, WAVE_LOAD_MATERIAL | WAVE_FLIP_UVS | WAVE_GEN_NORMALS | WAVE_GEN_UVS);
				if (RenderModel.HasMaterial == 0)
				{
					RenderModel.HasMaterial = 1;
					RenderModel.Material = (WaveModelMaterial*)malloc(sizeof(WaveModelMaterial));
					WaveModelMaterial EmptyMaterial =
					{
						1,
						0,
						"Default",
						{ 1.0, 1.0, 1.0 },
						{ 1.0, 1.0, 1.0 },
						1.0,
						{ 1.0, 1.0, 1.0 },
						"NoTexture",
						"NoTexture",
						"NoTexture",
						"NoTexture",
						"NoTexture",
						"NoTexture"
					};
					memcpy(RenderModel.Material, &EmptyMaterial, sizeof(WaveModelMaterial));					
				}
				if (strlen(CollisionModelPath) != 0)
				{
					CollisionModel = WaveLoadModel(CollisionModelPath, WAVE_FLIP_UVS | WAVE_GEN_NORMALS | WAVE_GEN_UVS);
					if (CollisionModel.VertexCount == 0)
						WriteConsoleIm("Failed to load Collision Model\n");
				}
				
				if (RenderModel.VertexCount == 0)
					WriteConsoleIm("Failed to load Render Model\n");
				WriteConsoleIm("Loaded Models\n");
				memset(UsedMaterials, 0, sizeof(bool) * 4096);
				memset(AlphaTextures, 0, sizeof(bool) * 4096);
				memset(MirroredTextures, 0, sizeof(bool) * 4096);
				for (uint32_t i = 0; i < RenderModel.Material->MaterialCount; i++)
				{
					UsedMaterials[i] = true;
				}

			}
		}

		ImGui::NewLine();
		
		if (RenderModel.VertexCount != 0)
		{
			ImGui::Text("Export Settings");
			if (ImGui::Button("Load Settings"))
			{
				char Path[4096];
				if (WaveOpenFileDialog(Path, 0, NULL, "Wave Settings\0*.wave\0"))
					LoadSettings(Path);
			}
			const char* items[] = { "8", "16", "32", "64", "128", "256", "512", "1024" };
			static const char* current_item = "32";
			if (ImGui::BeginCombo("Texture Size", current_item)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(items[n], is_selected))
					{
						TextureSize = atoi(items[n]);
						current_item = items[n];
					}						
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
			//ImGui::SliderInt("Texture Size", &TextureSize, 8, 512);
			ImGui::Text("Used Render Materials:");
			for (uint32_t i = 0; i < RenderModel.Material->MaterialCount; i++)
			{
				ImGui::Checkbox(RenderModel.Material[i].MaterialName, &UsedMaterials[i]);				
				ImGui::SameLine();	
				ImGui::PushID(i * 2);
				ImGui::Checkbox("Alpha Texture", &AlphaTextures[i]);
				ImGui::PopID();
				ImGui::SameLine();
				ImGui::PushID(i * 2 + RenderModel.Material->MaterialCount);
				ImGui::Checkbox("Mirrored Texture", &MirroredTextures[i]);
				ImGui::PopID();
			}
			if (ImGui::Button("Save Settings"))
			{
				char Path[4096];
				if (WaveSaveFileDialog(Path, "Wave Settings\0*.wave\0"))
					SaveSettings(Path);
			}
			ImGui::InputText("Output Path", OutPath, 4096);
			
			if (ImGui::Button("Export"))
			{
				float D[] = { 1.0, 2.0 };
				ExportModels(COLLISION_TYPE_MESH, D);
			}
		}

		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::NewLine();

		ImGui::InputTextMultiline("Console", Console, 8192);
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			ConsoleIndex = 0;
			memset(Console, 0, 8192);
		}

		//   ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	   //    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	   //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	   //    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	   //    ImGui::Checkbox("Another Window", &show_another_window);
	}
	ImGui::End();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Render Model", "STRG+O"))
			{
				OpenModel(RenderModelPath, true);
			}
			if (ImGui::MenuItem("Open Collision Model", "STRG+O"))
			{
				OpenModel(CollisionModelPath, false);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	// Rendering
	ImGui::Render();
	const float clear_color_with_alpha[4] = { 1.0, 1.0, 1.0, 1.0 };
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	g_pSwapChain->Present(1, 0); // Present with vsync
	//g_pSwapChain->Present(0, 0); // Present without vsync
}

// Main code
int main(int, char**)
{
	// Create application window
	//ImGui_ImplWin32_EnableDpiAwareness();
	WNDCLASSEX wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "ImGui Example", NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, "Wave To NDS", WS_OVERLAPPEDWINDOW, 100, 100, 600, 400, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	//io.ConfigViewportsNoDefaultParent = true;
	//io.ConfigDockingAlwaysTabBar = true;
	//io.ConfigDockingTransparentPayload = true;
	//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
	//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	bool done = false;
	while (!done)
	{
		Render(done);
		if (done)
			break;
	}

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_DPICHANGED:
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		{
			//const int dpi = HIWORD(wParam);
			//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
			const RECT* suggested_rect = (RECT*)lParam;
			::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
/*
int main()
{
//	ToAnimation("TopG/skeleton.mp4", 1, 120, 0, 5);

	char Path[4096];
	int Speed = 1;
	int Res = 120;
	int Start = 0;
	int End = 0;

	printf("File(TopG/skeleton.mp4): ");
	scanf("%s", Path);

	printf("Speed(1-10): ");
	scanf("%d", &Speed);

	printf("Resolution(10-512): ");
	scanf("%d", &Res);

	printf("Start Frame: ");
	scanf("%d", &Start);

	printf("End Frame(0 if whole video): ");
	scanf("%d", &End);

	ToAnimation(Path, Speed, Res, Start, End);

	return 0;
}
*/