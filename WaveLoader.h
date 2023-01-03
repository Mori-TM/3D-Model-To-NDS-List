#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#ifndef WAVE_BASIC_MATH
#define WAVE_BASIC_MATH

#define WAVEMAX(x, y) (((x) > (y)) ? (x) : (y))
#define WAVEMIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct
{
	float x;
	float y;
	float z;
} WaveVec3;

float WaveFastInverseSqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = number * 0.5f;
	y = number;
	i = *(long*)&y;              // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);   // what the fuck?
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed - it's for more accuracy

	return y;
}

extern inline WaveVec3 WaveNormalize(WaveVec3 v)
{
	float length = WaveFastInverseSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x *= length;
	v.y *= length;
	v.z *= length;

	return v;
}

extern inline WaveVec3 WaveCross(WaveVec3 a, WaveVec3 b)
{
	WaveVec3 r;
	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;

	return r;
}

extern inline float WaveDot(WaveVec3 a, WaveVec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

extern inline WaveVec3 WaveAdd(WaveVec3 a, WaveVec3 b)
{
	WaveVec3 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;

	return r;
}

extern inline WaveVec3 WaveSub(WaveVec3 a, WaveVec3 b)
{
	WaveVec3 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;

	return r;
}

extern inline WaveVec3 WaveMul(WaveVec3 a, WaveVec3 b)
{
	WaveVec3 r;
	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;

	return r;
}

extern inline WaveVec3 WaveDiv(WaveVec3 a, WaveVec3 b)
{
	WaveVec3 r;
	r.x = a.x / b.x;
	r.y = a.y / b.y;
	r.z = a.z / b.z;

	return r;
}

extern inline float WaveLength(WaveVec3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

extern inline WaveVec3 WaveVec3f(float v)
{
	WaveVec3 r;
	r.x = v;
	r.y = v;
	r.z = v;

	return r;
}
#endif

#define WAVE_ALLOCATION_CHUNK_SIZE 100000

typedef enum
{
	WAVE_GEN_UVS = 1,
	WAVE_GEN_NORMALS = 2,
	WAVE_FLIP_UVS = 4,
	WAVE_LOAD_MATERIAL = 8
} WaveSettings;

typedef struct
{
	uint32_t MaterialCount;
	uint32_t VertexIndex;

	char MaterialName[2048];

	WaveVec3 AmbientColor;
	WaveVec3 DiffuseColor;
	uint32_t SpecularExponent;
	WaveVec3 SpecularColor;
	char AmbientTexture[4096];
	char DiffuseTexture[4096];
	char SpecularTexture[4096];
	char AlphaTexture[4096];
	char NormalTexture[4096];
	char HeightTexture[4096];
} WaveModelMaterial;

typedef struct
{
	WaveVec3 Vertices;
	WaveVec3 TexCoords;
	WaveVec3 Normals;
	WaveVec3 VertexColor;
} WaveMeshData;

typedef struct
{
	int32_t HasMaterial;
	WaveModelMaterial* Material;

	uint32_t VertexCount;
	WaveMeshData* Mesh;
} WaveModelData;

typedef struct
{
	char Name[2048];
	uint32_t Pos;
} WaveObjMaterialDescription;

void WaveGenUVs(WaveModelData* Data, uint32_t i)
{
	float MinX = 1000000000.0;
	float MaxX = -1000000000.0;

	float MinY = 1000000000.0;
	float MaxY = -1000000000.0;

	//		float TempUVsqrt = sqrtf(Data->Mesh[i].Vertices.x * Data->Mesh[i].Vertices.x + Data->Mesh[i].Vertices.y * Data->Mesh[i].Vertices.y + Data->Mesh[i].Vertices.z * Data->Mesh[i].Vertices.z);
	//		Data->Mesh[i].TexCoords.x = sinf(cosf(Data->Mesh[i].Vertices.x / TempUVsqrt));
	//		Data->Mesh[i].TexCoords.y = sinf(sinf(Data->Mesh[i].Vertices.y / TempUVsqrt));

	float TempUVsqrt = sqrtf(Data->Mesh[i].Vertices.x * Data->Mesh[i].Vertices.x + Data->Mesh[i].Vertices.y * Data->Mesh[i].Vertices.y + Data->Mesh[i].Vertices.z * Data->Mesh[i].Vertices.z);
	Data->Mesh[i].TexCoords.x = sinf(cosf(Data->Mesh[i].Vertices.x / TempUVsqrt));
	Data->Mesh[i].TexCoords.y = sinf(sinf(Data->Mesh[i].Vertices.y / TempUVsqrt));

	//	MinX = WAVEMIN(MinX, Data->Mesh[i].Vertices.x);
	//	MinY = WAVEMIN(MinY, Data->Mesh[i].Vertices.y);
	//
	//	MaxX = WAVEMAX(MaxX, Data->Mesh[i].Vertices.x);
	//	MaxY = WAVEMAX(MaxY, Data->Mesh[i].Vertices.y);
	//
	//	float KX = 1 / (MaxX - MinX);
	//	float KY = 1 / (MaxY - MinY);
	//
	//	Data->Mesh[i].TexCoords.x = (Data->Mesh[i].Vertices.x - MinX) * KX;
	//	Data->Mesh[i].TexCoords.y = (Data->Mesh[i].Vertices.y - MinY) * KY;

	/*
	float DotProduct = 2 * WaveDot(Data->Mesh[i].Normals, Data->Mesh[i].Vertices);
	float X = Data->Mesh[i].Normals.x * DotProduct - Data->Mesh[i].Vertices.x;
	float Y = Data->Mesh[i].Normals.y * DotProduct - Data->Mesh[i].Vertices.y;
	float Z = Data->Mesh[i].Normals.z * DotProduct - Data->Mesh[i].Vertices.z;
	WaveVec3 R = { X, Y, Z };

	if ((R.x >= R.y) && (R.x >= R.z))
	{
		float UC = -R.z;
		float VC = -R.y;
		float M = fabsf(R.x);

		Data->Mesh[i].TexCoords.x = ((UC / M) + 1) / 2;
		Data->Mesh[i].TexCoords.y = ((VC / M) + 1) / 2;
	}

	if ((R.x <= R.y) && (R.x <= R.z))
	{
		float UC = +R.z;
		float VC = -R.y;
		float M = fabsf(R.x);

		Data->Mesh[i].TexCoords.x = ((UC / M) + 1) / 2;
		Data->Mesh[i].TexCoords.y = ((VC / M) + 1) / 2;
	}

	if ((R.y >= R.z) && (R.y >= R.x))
	{
		float UC = +R.x;
		float VC = +R.z;
		float M = fabsf(R.y);

		Data->Mesh[i].TexCoords.x = ((UC / M) + 1) / 2;
		Data->Mesh[i].TexCoords.y = ((VC / M) + 1) / 2;
	}

	if ((R.y <= R.z) && (R.y <= R.x))
	{
		float UC = +R.x;
		float VC = -R.z;
		float M = fabsf(R.y);

		Data->Mesh[i].TexCoords.x = ((UC / M) + 1) / 2;
		Data->Mesh[i].TexCoords.y = ((VC / M) + 1) / 2;
	}

	if ((R.z >= R.y) && (R.z >= R.x))
	{
		float UC = +R.x;
		float VC = -R.y;
		float M = fabsf(R.z);

		Data->Mesh[i].TexCoords.x = ((UC / M) + 1) / 2;
		Data->Mesh[i].TexCoords.y = ((VC / M) + 1) / 2;
	}

	if ((R.z <= R.y) && (R.z <= R.x))
	{
		float UC = -R.x;
		float VC = -R.y;
		float M = fabsf(R.z);

		Data->Mesh[i].TexCoords.x = ((UC / M) + 1) / 2;
		Data->Mesh[i].TexCoords.y = ((VC / M) + 1) / 2;
	}
	*/
}

void WaveGenSmoothNormals(WaveModelData* Data)
{
	WaveVec3 Normals;

	Normals.x = 0.0;
	Normals.y = 0.0;
	Normals.z = 0.0;


	for (uint32_t i = 0; i < Data->VertexCount; i++)
	{
		WaveVec3* Vertex = &Data->Mesh[i].Vertices;
		WaveVec3* Normal = &Data->Mesh[i].Normals;

		for (uint32_t j = 0; j < Data->VertexCount; j++)
		{
			WaveVec3* Vertex2 = &Data->Mesh[j].Vertices;

			WaveVec3 Edge = WaveSub(*Vertex2, *Vertex);
			float Length = WaveLength(Edge);

			if (Length > 0.0)
			{
				float y = 1.0 / Length;
				WaveVec3 x = { y, y, y };
				Edge = WaveMul(Edge, x);
			}

			float DotProduct = WaveDot(Edge, *Normal);

			if ((DotProduct < 0.0) && (Length > 0.0))
			{
				Normals.x += -Edge.x;
				Normals.y += -Edge.y;
				Normals.z += -Edge.z;
			}
		}

		float Length = WaveLength(*Normal);

		if (Length > 0.0)
		{
			float y = 1.0 / Length;
			WaveVec3 x = { y, y, y };
			*Normal = WaveMul(*Normal, x);
		}

		Normals = WaveNormalize(Normals);

		Data->Mesh[i].Normals = Normals;
	}
}

void WaveGenNormals(WaveModelData* Data)
{
	for (uint32_t i = 0; i < Data->VertexCount; i += 3)
	{
		WaveVec3 N = WaveCross(WaveSub(Data->Mesh[i + 1].Vertices, Data->Mesh[i].Vertices), WaveSub(Data->Mesh[i + 2].Vertices, Data->Mesh[i].Vertices));

		Data->Mesh[i].Normals = N;
		Data->Mesh[i + 1].Normals = N;
		Data->Mesh[i + 2].Normals = N;

		Data->Mesh[i].Normals = WaveNormalize(Data->Mesh[i].Normals);
		Data->Mesh[i + 1].Normals = WaveNormalize(Data->Mesh[i + 1].Normals);
		Data->Mesh[i + 2].Normals = WaveNormalize(Data->Mesh[i + 2].Normals);
	}
}

float WaveAngle(WaveVec3 a, WaveVec3 b)
{
	float Dot = WaveDot(a, b);
	float LenA = a.x * a.x + a.y * a.y + a.z * a.z;
	float LenB = b.x * b.x + b.y * b.y + b.z * b.z;

	float Angle = acos(Dot / sqrtf(LenA * LenB));

	return Angle;
}

typedef struct
{
	int32_t V;
	int32_t VT;
	int32_t VN;
} VertexReference;

WaveModelData WaveLoadOBJ(const char* Path, uint32_t Settings)
{
	FILE* File = fopen(Path, "r");
	if (!File)
	{
		printf("Failed to open obj Model: %s\n", Path);

		WaveModelData Data;
		Data.HasMaterial = 0;
		Data.Material = NULL;
		Data.VertexCount = 0;
		Data.Mesh = NULL;
		return Data;
	}

	uint32_t TempVertexCount = 1;
	uint32_t TempUVCount = 1;
	uint32_t TempNormalCount = 1;

	uint32_t TempVerticeAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	uint32_t TempUVAllocationCount = 3;
	uint32_t TempNormalAllocationCount = 3;
	WaveVec3* TempVertices = (WaveVec3*)malloc(TempVerticeAllocationCount * sizeof(WaveVec3));
	WaveVec3* TempUVs = (WaveVec3*)malloc(TempUVAllocationCount * sizeof(WaveVec3));
	WaveVec3* TempNormals = (WaveVec3*)malloc(TempUVAllocationCount * sizeof(WaveVec3));

	int32_t WaveHasMaterial = 0;
	int32_t MaterialCount = -1;
	WaveModelMaterial* Material = (WaveModelMaterial*)malloc(1 * sizeof(WaveModelMaterial));

	int32_t ObjMaterialCount = 0;
	WaveObjMaterialDescription* ObjMaterial = (WaveObjMaterialDescription*)malloc(1 * sizeof(WaveObjMaterialDescription));

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

	WaveModelData Data;
	uint32_t MeshCount = WAVE_ALLOCATION_CHUNK_SIZE;
	Data.Mesh = (WaveMeshData*)malloc(MeshCount * sizeof(WaveMeshData));
	Data.VertexCount = 0;

	uint32_t VertexReferenceIndex = 0;
	VertexReference VertexReferences[4];

	while (1)
	{
		char LineHeader[128];

		int32_t Res = fscanf(File, "%s", LineHeader);
		if (Res == EOF)
			break;

		if (strcmp(LineHeader, "mtllib") == 0 && (Settings & WAVE_LOAD_MATERIAL))
		{
			char Path[2048];

			fscanf(File, "%[^\r\n]%*c\r\n", &Path);

			FILE* MatFile = fopen(Path + 1, "r");
			if (!MatFile)
			{
				printf("Failed to open material file: %s\n", Path + 1);
				goto NoMatterial;
			}
			else
				WaveHasMaterial = 1;

			while (1)
			{
				char MatLineHeader[128];

				int32_t MatRes = fscanf(MatFile, "%s", MatLineHeader);
				if (MatRes == EOF)
					break;

				if (strcmp(MatLineHeader, "Ka") == 0)
					fscanf(MatFile, "%f %f %f\n", &Material[MaterialCount].AmbientColor.x, &Material[MaterialCount].AmbientColor.y, &Material[MaterialCount].AmbientColor.z);

				if (strcmp(MatLineHeader, "Kd") == 0)
					fscanf(MatFile, "%f %f %f\n", &Material[MaterialCount].DiffuseColor.x, &Material[MaterialCount].DiffuseColor.y, &Material[MaterialCount].DiffuseColor.z);

				if (strcmp(MatLineHeader, "Ks") == 0)
					fscanf(MatFile, "%f %f %f\n", &Material[MaterialCount].SpecularColor.x, &Material[MaterialCount].SpecularColor.y, &Material[MaterialCount].SpecularColor.z);

				if (strcmp(MatLineHeader, "Ns") == 0)
					fscanf(MatFile, "%f\n", &Material[MaterialCount].SpecularExponent);

				if (strcmp(MatLineHeader, "map_Ka") == 0)
					fscanf(MatFile, "%s\n", &Material[MaterialCount].AmbientTexture);

				if (strcmp(MatLineHeader, "map_Kd") == 0)
					fscanf(MatFile, "%[^\r\n]%*c\r\n", &Material[MaterialCount].DiffuseTexture);

				if (strcmp(MatLineHeader, "map_Ks") == 0)
					fscanf(MatFile, "%s\n", &Material[MaterialCount].SpecularTexture);

				if (strcmp(MatLineHeader, "map_d") == 0)
					fscanf(MatFile, "%s\n", &Material[MaterialCount].AlphaTexture);

				if (strcmp(MatLineHeader, "map_bump") == 0)
					fscanf(MatFile, "%s\n", &Material[MaterialCount].NormalTexture);

				if (strcmp(MatLineHeader, "disp") == 0)
					fscanf(MatFile, "%s\n", &Material[MaterialCount].HeightTexture);

				if (strcmp(MatLineHeader, "newmtl") == 0)
				{
					MaterialCount++;
					fscanf(MatFile, "%s\n", &Material[MaterialCount].MaterialName);

					Material = (WaveModelMaterial*)realloc(Material, (MaterialCount + 2) * sizeof(WaveModelMaterial));

				}
			}

			fclose(MatFile);
		}
	NoMatterial:

		if (strcmp(LineHeader, "usemtl") == 0 && WaveHasMaterial == 1 && Settings & WAVE_LOAD_MATERIAL)
		{
			fscanf(File, "%s\n", &ObjMaterial[ObjMaterialCount].Name);
			ObjMaterial[ObjMaterialCount].Pos = Data.VertexCount;
			ObjMaterialCount++;
			ObjMaterial = (WaveObjMaterialDescription*)realloc(ObjMaterial, (ObjMaterialCount + 1) * sizeof(WaveObjMaterialDescription));
		}

		if (strcmp(LineHeader, "v") == 0)
		{
			fscanf(File, "%f %f %f\n", &TempVertices[TempVertexCount].x, &TempVertices[TempVertexCount].y, &TempVertices[TempVertexCount].z);
			TempVertexCount++;

			if (TempVertexCount == TempVerticeAllocationCount - 1)
			{
				TempVerticeAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				TempVertices = (WaveVec3*)realloc(TempVertices, TempVerticeAllocationCount * sizeof(WaveVec3));
			}
		}

		if (strcmp(LineHeader, "vt") == 0)
		{
			fscanf(File, "%f %f\n", &TempUVs[TempUVCount].x, &TempUVs[TempUVCount].y);
			TempUVCount++;

			if (TempUVCount == TempUVAllocationCount - 1)
			{
				TempUVAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				TempUVs = (WaveVec3*)realloc(TempUVs, TempUVAllocationCount * sizeof(WaveVec3));
			}
		}

		if (strcmp(LineHeader, "vn") == 0)
		{
			fscanf(File, "%f %f %f\n", &TempNormals[TempNormalCount].x, &TempNormals[TempNormalCount].y, &TempNormals[TempNormalCount].z);
			TempNormalCount++;

			if (TempNormalCount == TempNormalAllocationCount - 1)
			{
				TempNormalAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				TempNormals = (WaveVec3*)realloc(TempNormals, TempNormalAllocationCount * sizeof(WaveVec3));
			}
		}

		if (strcmp(LineHeader, "f") == 0)
		{
			VertexReferenceIndex = 0;

			char ReadedLine[2048];
			fscanf(File, "%[^\n]%*c", &ReadedLine);
			char* Line = ReadedLine + 1;

			char* TempLine = strtok(Line, " ");
			while (TempLine)
			{
				int32_t v = 0;
				int32_t vt = 0;
				int32_t vn = 0;

				if (TempVertexCount > 1 && TempUVCount > 1 && TempNormalCount > 1)
					sscanf(TempLine, "%d/%d/%d", &v, &vt, &vn);

				else if (TempNormalCount == 1 && TempUVCount > 1)
					sscanf(TempLine, "%d/%d", &v, &vt);

				else if (TempUVCount == 1 && TempNormalCount > 1)
					sscanf(TempLine, "%d//%d", &v, &vn);

				else
					sscanf(TempLine, "%d", &v);

				v = (v >= 0 ? v : TempVertexCount + v);
				vt = (vt >= 0 ? vt : TempUVCount + vt);
				vn = (vn >= 0 ? vn : TempNormalCount + vn);

				VertexReferences[VertexReferenceIndex].V = v;
				VertexReferences[VertexReferenceIndex].VT = vt;
				VertexReferences[VertexReferenceIndex].VN = vn;

				VertexReferenceIndex++;
				TempLine = strtok(NULL, " ");
			}

			for (uint32_t i = 1; i + 1 < VertexReferenceIndex; i++)
			{
				VertexReference* p[3] = { &VertexReferences[0], &VertexReferences[i], &VertexReferences[i + 1] };

				const WaveVec3 NullVec = { 0.0, 0.0, 0.0 };

				for (size_t j = 0; j < 3; j++)
				{
					Data.Mesh[Data.VertexCount].Vertices = TempVertices[p[j]->V];
					Data.Mesh[Data.VertexCount].TexCoords = TempUVs[p[j]->VT];
					Data.Mesh[Data.VertexCount].Normals = p[j]->VN != 0 ? TempNormals[p[j]->VN] : NullVec;
					Data.Mesh[Data.VertexCount].VertexColor.x = 1.0;
					Data.Mesh[Data.VertexCount].VertexColor.y = 1.0;
					Data.Mesh[Data.VertexCount].VertexColor.z = 1.0;

					if ((Settings & WAVE_GEN_UVS) && TempUVCount == 1)
						WaveGenUVs(&Data, Data.VertexCount);

					Data.VertexCount++;
					if (Data.VertexCount == MeshCount - 1)
					{
						MeshCount += WAVE_ALLOCATION_CHUNK_SIZE;
						Data.Mesh = (WaveMeshData*)realloc(Data.Mesh, MeshCount * sizeof(WaveMeshData));
					}
				}
			}
		}
	}

	fclose(File);

	if (WaveHasMaterial && (Settings & WAVE_LOAD_MATERIAL))
	{
		Data.HasMaterial = 1;
		Data.Material = (WaveModelMaterial*)malloc(ObjMaterialCount * sizeof(WaveModelMaterial));
		int32_t Pos = 0;

	//	Material = (WaveModelMaterial*)realloc(Material, ObjMaterialCount * sizeof(WaveModelMaterial));

		for (uint32_t i = 0; i < ObjMaterialCount; i++)
		{
			for (int32_t j = 0; j < MaterialCount + 1; j++)
			{
				if (strcmp(ObjMaterial[i].Name, Material[j].MaterialName) == 0)
				{
					Data.Material[Pos] = Material[j];
					Data.Material[Pos].VertexIndex = ObjMaterial[i].Pos;
					Pos++;
				}
			}
		}

		Data.Material->MaterialCount = ObjMaterialCount;
	}
	else
		Data.HasMaterial = 0;

	if ((Settings & WAVE_GEN_NORMALS) && TempNormalCount == 1)
		WaveGenNormals(&Data);

	//	WaveGenSmoothNormals(&Data);

	free(Material);
	free(ObjMaterial);

	free(TempVertices);
	free(TempUVs);
	free(TempNormals);

	return Data;
}

typedef struct
{
	unsigned char Header[80];
	uint32_t Triangles;
} WaveSTLDescription;

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	WaveVec3 Normal;
	WaveVec3 Vertex1;
	WaveVec3 Vertex2;
	WaveVec3 Vertex3;
	int16_t ByteCount;
} WaveSTLVertex;

#pragma pack(pop)

WaveModelData WaveLoadSTL(const char* Path, uint32_t Settings)
{
	FILE* File = fopen(Path, "rb");
	if (!File)
	{
		printf("Failed to open stl Model: %s\n", Path);

		WaveModelData Data;
		Data.HasMaterial = 0;
		Data.Material = NULL;
		Data.VertexCount = 0;
		Data.Mesh = NULL;
		return Data;
	}

	char* Buffer;
	long Length;

	fseek(File, 0L, SEEK_END);
	Length = ftell(File);
	fseek(File, 0L, SEEK_SET);

	Buffer = (char*)malloc(Length);
	fread(Buffer, Length, 1, File);

	WaveSTLDescription* Description = (WaveSTLDescription*)Buffer;
	Buffer += sizeof(WaveSTLDescription);

	WaveSTLVertex* VertexArray = (WaveSTLVertex*)Buffer;

	uint32_t VertexCount = Description->Triangles * 3;

	WaveModelData Data;
	Data.HasMaterial = 0;
	Data.Mesh = (WaveMeshData*)malloc(VertexCount * sizeof(WaveMeshData));
	Data.VertexCount = VertexCount;

	WaveVec3 DefaultColor = { 1.0, 1.0, 1.0 };

	uint32_t j = 0;
	for (uint32_t i = 0; i < Description->Triangles; i++)
	{
		Data.Mesh[j].Vertices = VertexArray[i].Vertex1;
		Data.Mesh[j + 1].Vertices = VertexArray[i].Vertex2;
		Data.Mesh[j + 2].Vertices = VertexArray[i].Vertex3;

		Data.Mesh[j].Normals = VertexArray[i].Normal;
		Data.Mesh[j + 1].Normals = VertexArray[i].Normal;
		Data.Mesh[j + 2].Normals = VertexArray[i].Normal;

		Data.Mesh[j].VertexColor = DefaultColor;
		Data.Mesh[j + 1].VertexColor = DefaultColor;
		Data.Mesh[j + 2].VertexColor = DefaultColor;

		if (Settings & WAVE_GEN_UVS)
		{
			WaveGenUVs(&Data, j);
			WaveGenUVs(&Data, j + 1);
			WaveGenUVs(&Data, j + 2);
		}

		j += 3;
	}

//	WaveGenSmoothNormals(&Data);

	fclose(File);
	free(Description);
	//	free(Buffer);
	//	free(VertexArray);

	return Data;
}

typedef struct
{
	char* Line;
	uint32_t Length;

	uint32_t LineCount;
} WaveLine;

WaveLine* WaveGetLines(char* Buffer)
{
	uint32_t AllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveLine* FinalLines = (WaveLine*)malloc(AllocationCount * sizeof(WaveLine));

	uint32_t LineCount = 0;

	char* p = strtok(Buffer, "\n");
	while (p)
	{
		FinalLines[LineCount].Line = p;
		FinalLines[LineCount].Length = strlen(p);

		LineCount++;

		if (LineCount == AllocationCount - 1)
		{
			AllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
			FinalLines = (WaveLine*)realloc(FinalLines, AllocationCount * sizeof(WaveLine));
		}

		p = strtok(NULL, "\n");
	}

	FinalLines->LineCount = LineCount;

	free(p);

	return FinalLines;
}

typedef struct
{
	float* FloatArray;
	uint32_t FloatArrayCount;

	uint32_t ArrayCount;
} WaveFloatArray;

typedef struct
{
	char* CharArray;
	uint32_t CharArrayCount;

	uint32_t ArrayCount;
} WaveCharArray;

WaveFloatArray GetFloatsFromString(char* Line, long Length)
{
	WaveFloatArray FinalArray;

	uint32_t AllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	float* FloatArray = (float*)malloc(AllocationCount * sizeof(float));
	uint32_t FloatArrayCount = 0;

	char* p = strtok(Line, " ");
	while (p)
	{
		FloatArray[FloatArrayCount] = atof(p);
		FloatArrayCount++;

		if (FloatArrayCount == AllocationCount - 1)
		{
			AllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
			FloatArray = (float*)realloc(FloatArray, AllocationCount * sizeof(float));
		}

		p = strtok(NULL, " ");
	}

	FinalArray.FloatArray = FloatArray;
	FinalArray.FloatArrayCount = FloatArrayCount;
	free(p);
	return FinalArray;
}

WaveFloatArray WaveGetFloatsFromLine(char* Line, long Length)
{
	uint32_t AllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	char* FloatLine = (char*)malloc(AllocationCount * sizeof(char));
	uint32_t FloatLineCount = 0;

	WaveFloatArray FloatArray;

	for (uint32_t i = 0; i < Length; i++)
	{
		if (Line[i] == '>')
		{
			FloatLine = (char*)malloc(AllocationCount * sizeof(char));
			FloatLineCount = 0;

			while (1)
			{
				i++;

				if (Line[i] == '<')
				{
					FloatLine[FloatLineCount] = '\0';
					FloatArray = GetFloatsFromString(FloatLine, FloatLineCount);
					break;
				}

				FloatLine[FloatLineCount] = Line[i];
				FloatLineCount++;

				if (FloatLineCount == AllocationCount - 1)
				{
					AllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
					FloatLine = (char*)realloc(FloatLine, AllocationCount * sizeof(char));
				}
			}

			free(FloatLine);
			return FloatArray;
		}
	}
}

typedef struct
{
	WaveFloatArray* FloatArray;
	uint32_t VertexPos;
	uint32_t NormalPos;
	uint32_t TexCoordPos;
	uint32_t ColorPos;
	uint32_t IndexPos;
} WaveTempMeshData;

WaveTempMeshData WaveGetMeshData(WaveLine* Lines)
{
	WaveTempMeshData MeshData;

	uint32_t FloatArrayAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveFloatArray* FloatArray = (WaveFloatArray*)malloc(FloatArrayAllocationCount * sizeof(WaveFloatArray));
	uint32_t FloatArrayCount = 0;

	uint32_t VertexOrderAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveCharArray* VertexOrder = (WaveCharArray*)malloc(VertexOrderAllocationCount * sizeof(WaveCharArray));
	uint32_t VertexCount = 0;

	for (uint32_t i = 0; i < Lines->LineCount; i++)
	{
		char* FoundMeshNode = strstr(Lines[i].Line, "<mesh>");
		if (FoundMeshNode)
		{
			while (1)
			{
				char* FoundMeshNodeEnd = strstr(Lines[i].Line, "</mesh>");
				if (FoundMeshNodeEnd)
					break;

				char* FoundVertex = strstr(Lines[i].Line, "float_array");

				if (FoundVertex)
				{
					FloatArray[FloatArrayCount] = WaveGetFloatsFromLine(Lines[i].Line, Lines[i].Length);
					FloatArrayCount++;

					if (FloatArrayCount == FloatArrayAllocationCount - 1)
					{
						FloatArrayAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
						FloatArray = (WaveFloatArray*)realloc(FloatArray, FloatArrayAllocationCount * sizeof(WaveFloatArray));
					}
				}

				char* FoundIndex = strstr(Lines[i].Line, "<p>");

				if (FoundIndex)
				{
					FloatArray[FloatArrayCount] = WaveGetFloatsFromLine(Lines[i].Line, Lines[i].Length);
					FloatArrayCount++;

					if (FloatArrayCount == FloatArrayAllocationCount - 1)
					{
						FloatArrayAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
						FloatArray = (WaveFloatArray*)realloc(FloatArray, FloatArrayAllocationCount * sizeof(WaveFloatArray));
					}
				}

				char* FoundOffset = strstr(Lines[i].Line, "offset");

				if (FoundOffset)
				{
					VertexOrder[VertexCount].CharArray = Lines[i].Line;
					VertexOrder[VertexCount].CharArrayCount = strlen(Lines[i].Line);
					VertexCount++;

					if (VertexCount == VertexOrderAllocationCount - 1)
					{
						VertexOrderAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
						VertexOrder = (WaveCharArray*)realloc(VertexOrder, VertexOrderAllocationCount * sizeof(WaveCharArray));
					}
				}

				i++;
			}
		}
	}

	VertexOrder->ArrayCount = VertexCount;
	FloatArray->ArrayCount = FloatArrayCount;

	MeshData.FloatArray = FloatArray;

	MeshData.VertexPos = UINT32_MAX;
	MeshData.NormalPos = UINT32_MAX;
	MeshData.TexCoordPos = UINT32_MAX;
	MeshData.ColorPos = UINT32_MAX;

	for (uint32_t i = 0; i < VertexOrder->ArrayCount; i++)
	{
		char* FoundVertex = strstr(VertexOrder[i].CharArray, "VERTEX");

		if (FoundVertex)
			MeshData.VertexPos = i;

		char* FoundNormal = strstr(VertexOrder[i].CharArray, "NORMAL");

		if (FoundNormal)
			MeshData.NormalPos = i;

		char* FoundTexCoord = strstr(VertexOrder[i].CharArray, "TEXCOORD");

		if (FoundTexCoord)
			MeshData.TexCoordPos = i;

		char* FoundColor = strstr(VertexOrder[i].CharArray, "COLOR");

		if (FoundColor)
			MeshData.ColorPos = i;
	}

	free(VertexOrder);

	return MeshData;
}

WaveModelData WaveLoadDAE(const char* Path, uint32_t Settings)
{
	char* Buffer = 0;
	long Length = 0;

	FILE* File = fopen(Path, "r");
	if (!File)
	{
		printf("Failed to open dae Model: %s\n", Path);

		WaveModelData Data;
		Data.HasMaterial = 0;
		Data.Material = NULL;
		Data.VertexCount = 0;
		Data.Mesh = NULL;
		return Data;
	}

	fseek(File, 0, SEEK_END);
	Length = ftell(File);
	fseek(File, 0, SEEK_SET);
	Buffer = (char*)malloc(Length);
	fread(Buffer, sizeof(char), Length, File);

	WaveLine* Lines = WaveGetLines(Buffer);
	WaveTempMeshData MeshData = WaveGetMeshData(Lines);

	uint32_t FinalVerticesAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveVec3* FinalVertices = (WaveVec3*)malloc(FinalVerticesAllocationCount * sizeof(WaveVec3));
	uint32_t FinalNormalsAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveVec3* FinalNormlas = (WaveVec3*)malloc(FinalNormalsAllocationCount * sizeof(WaveVec3));
	uint32_t FinalTexCoordsAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveVec3* FinalTexCoords = (WaveVec3*)malloc(FinalTexCoordsAllocationCount * sizeof(WaveVec3));
	uint32_t FinalColorsAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	WaveVec3* FinalColors = (WaveVec3*)malloc(FinalColorsAllocationCount * sizeof(WaveVec3));

	uint32_t VerticesCount = 0;
	uint32_t NormalCount = 0;
	uint32_t TexCoordCount = 0;
	uint32_t ColorCount = 0;
	//Indices
	uint32_t FinalVerticeIndicesAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	uint32_t* FinalVerticeIndices = (uint32_t*)malloc(FinalVerticeIndicesAllocationCount * sizeof(uint32_t));
	uint32_t FinalNormalIndicesAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	uint32_t* FinalNormlaIndices = (uint32_t*)malloc(FinalNormalIndicesAllocationCount * sizeof(uint32_t));
	uint32_t FinalTexCoordIndicesAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	uint32_t* FinalTexCoordIndices = (uint32_t*)malloc(FinalTexCoordIndicesAllocationCount * sizeof(uint32_t));
	uint32_t FinalColorIndicesAllocationCount = WAVE_ALLOCATION_CHUNK_SIZE;
	uint32_t* FinalColorIndices = (uint32_t*)malloc(FinalColorIndicesAllocationCount * sizeof(uint32_t));

	uint32_t VerticesIndicesCount = 0;
	uint32_t NormalIndicesCount = 0;
	uint32_t TexCoordIndicesCount = 0;
	uint32_t ColorIndicesCount = 0;

	for (uint32_t i = 0; i < MeshData.FloatArray[MeshData.VertexPos].FloatArrayCount; i += 3)
	{
		FinalVertices[VerticesCount].x = MeshData.FloatArray[MeshData.VertexPos].FloatArray[i];
		FinalVertices[VerticesCount].y = MeshData.FloatArray[MeshData.VertexPos].FloatArray[i + 1];
		FinalVertices[VerticesCount].z = MeshData.FloatArray[MeshData.VertexPos].FloatArray[i + 2];
		VerticesCount++;

		if (VerticesCount == FinalVerticesAllocationCount - 1)
		{
			FinalVerticesAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
			FinalVertices = (WaveVec3*)realloc(FinalVertices, FinalVerticesAllocationCount * sizeof(WaveVec3));
		}
	}

	if (MeshData.NormalPos != UINT32_MAX)
		for (uint32_t i = 0; i < MeshData.FloatArray[MeshData.NormalPos].FloatArrayCount; i += 3)
		{
			FinalNormlas[NormalCount].x = MeshData.FloatArray[MeshData.NormalPos].FloatArray[i];
			FinalNormlas[NormalCount].y = MeshData.FloatArray[MeshData.NormalPos].FloatArray[i + 1];
			FinalNormlas[NormalCount].z = MeshData.FloatArray[MeshData.NormalPos].FloatArray[i + 2];
			NormalCount++;

			if (NormalCount == FinalNormalsAllocationCount - 1)
			{
				FinalNormalsAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				FinalNormlas = (WaveVec3*)realloc(FinalNormlas, FinalNormalsAllocationCount * sizeof(WaveVec3));
			}
		}

	if (MeshData.TexCoordPos != UINT32_MAX)
		for (uint32_t i = 0; i < MeshData.FloatArray[MeshData.TexCoordPos].FloatArrayCount; i += 2)
		{
			FinalTexCoords[TexCoordCount].x = MeshData.FloatArray[MeshData.TexCoordPos].FloatArray[i];
			FinalTexCoords[TexCoordCount].y = MeshData.FloatArray[MeshData.TexCoordPos].FloatArray[i + 1];
			FinalTexCoords[TexCoordCount].z = 0.0;
			TexCoordCount++;

			if (TexCoordCount == FinalTexCoordsAllocationCount - 1)
			{
				FinalTexCoordsAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				FinalTexCoords = (WaveVec3*)realloc(FinalTexCoords, FinalTexCoordsAllocationCount * sizeof(WaveVec3));
			}
		}

	if (MeshData.ColorPos != UINT32_MAX)
		for (uint32_t i = 0; i < MeshData.FloatArray[MeshData.ColorPos].FloatArrayCount; i += 4)
		{
			FinalColors[ColorCount].x = MeshData.FloatArray[MeshData.ColorPos].FloatArray[i];
			FinalColors[ColorCount].y = MeshData.FloatArray[MeshData.ColorPos].FloatArray[i + 1];
			FinalColors[ColorCount].z = MeshData.FloatArray[MeshData.ColorPos].FloatArray[i + 2];
			ColorCount++;

			if (ColorCount == FinalColorsAllocationCount - 1)
			{
				FinalColorsAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				FinalColors = (WaveVec3*)realloc(FinalColors, FinalColorsAllocationCount * sizeof(WaveVec3));
			}
		}

	for (uint32_t i = 0; i < MeshData.FloatArray[MeshData.FloatArray->ArrayCount - 1].FloatArrayCount; i += MeshData.FloatArray->ArrayCount - 1)
	{
		FinalVerticeIndices[VerticesIndicesCount] = MeshData.FloatArray[MeshData.FloatArray->ArrayCount - 1].FloatArray[i + MeshData.VertexPos];
		VerticesIndicesCount++;
		if (VerticesIndicesCount == FinalVerticeIndicesAllocationCount - 1)
		{
			FinalVerticeIndicesAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
			FinalVerticeIndices = (uint32_t*)realloc(FinalVerticeIndices, FinalVerticeIndicesAllocationCount * sizeof(uint32_t));
		}

		if (NormalCount != 0)
		{
			FinalNormlaIndices[NormalIndicesCount] = MeshData.FloatArray[MeshData.FloatArray->ArrayCount - 1].FloatArray[i + MeshData.NormalPos];
			NormalIndicesCount++;
			if (NormalIndicesCount == FinalNormalIndicesAllocationCount - 1)
			{
				FinalNormalIndicesAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				FinalNormlaIndices = (uint32_t*)realloc(FinalNormlaIndices, FinalNormalIndicesAllocationCount * sizeof(uint32_t));
			}
		}

		if (TexCoordCount != 0)
		{
			FinalTexCoordIndices[TexCoordIndicesCount] = MeshData.FloatArray[MeshData.FloatArray->ArrayCount - 1].FloatArray[i + MeshData.TexCoordPos];
			TexCoordIndicesCount++;
			if (TexCoordIndicesCount == FinalTexCoordIndicesAllocationCount - 1)
			{
				FinalTexCoordIndicesAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				FinalTexCoordIndices = (uint32_t*)realloc(FinalTexCoordIndices, FinalTexCoordIndicesAllocationCount * sizeof(uint32_t));
			}
		}

		if (ColorCount != 0)
		{
			FinalColorIndices[ColorIndicesCount] = MeshData.FloatArray[MeshData.FloatArray->ArrayCount - 1].FloatArray[i + MeshData.ColorPos];
			ColorIndicesCount++;
			if (ColorIndicesCount == FinalColorIndicesAllocationCount - 1)
			{
				FinalColorIndicesAllocationCount += WAVE_ALLOCATION_CHUNK_SIZE;
				FinalColorIndices = (uint32_t*)realloc(FinalColorIndices, FinalColorIndicesAllocationCount * sizeof(uint32_t));
			}
		}
	}

	WaveModelData Data;
	Data.HasMaterial = 0;
	Data.Mesh = (WaveMeshData*)malloc(VerticesIndicesCount * sizeof(WaveMeshData));
	Data.VertexCount = VerticesIndicesCount;

	for (uint32_t i = 0; i < VerticesIndicesCount; i++)
	{
		Data.Mesh[i].Vertices = FinalVertices[FinalVerticeIndices[i]];

		if (NormalIndicesCount != 0)
			Data.Mesh[i].Normals = FinalNormlas[FinalNormlaIndices[i]];

		if (TexCoordIndicesCount != 0)
		{
			if (Settings & WAVE_FLIP_UVS)
			{
				Data.Mesh[i].TexCoords.x = FinalTexCoords[FinalTexCoordIndices[i]].x;
				Data.Mesh[i].TexCoords.y = -FinalTexCoords[FinalTexCoordIndices[i]].y;
			}
			else
				Data.Mesh[i].TexCoords = FinalTexCoords[FinalTexCoordIndices[i]];
		}


		if (ColorIndicesCount != 0)
			Data.Mesh[i].VertexColor = FinalColors[FinalColorIndices[i]];
		else
		{
			Data.Mesh[i].VertexColor.x = 1.0;
			Data.Mesh[i].VertexColor.y = 1.0;
			Data.Mesh[i].VertexColor.z = 1.0;
		}

		if ((Settings & WAVE_GEN_UVS) && TexCoordIndicesCount == 0)
			WaveGenUVs(&Data, i);
		//	else
		//		Data.Material[i] = EmptyMaterial;
	}
	//	Data.Normals = WaveGenSmoothNormals(VerticesIndicesCount, Data.Vertices);
	if ((Settings & WAVE_GEN_NORMALS) && NormalIndicesCount == 0)
		WaveGenNormals(&Data);

	free(Buffer);
	free(Lines);
	free(FinalVertices);
	free(FinalNormlas);
	free(FinalTexCoords);
	free(FinalColors);

	free(FinalVerticeIndices);
	free(FinalNormlaIndices);
	free(FinalTexCoordIndices);
	free(FinalColorIndices);
	fclose(File);

	return Data;
}

extern inline WaveModelData WaveLoadModel(const char* Path, uint32_t Settings)
{
	WaveModelData ModelData;
	const char* Extension = strchr(Path, '.');

	if (strcmp(Extension + 1, "obj") == 0)
		ModelData = WaveLoadOBJ(Path, Settings);

	if (strcmp(Extension + 1, "stl") == 0)
		ModelData = WaveLoadSTL(Path, Settings);

	if (strcmp(Extension + 1, "dae") == 0)
		ModelData = WaveLoadDAE(Path, Settings);

	return ModelData;
}

extern inline void WaveFreeModel(WaveModelData* ModelData)
{
	if (ModelData->HasMaterial == 1)
		free(ModelData->Material);
	//	free(ModelData->Mesh);
}
