// LightMapExtractor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <format>

enum LumpIds {
    ENTITIES = 0x0000,
    BRUSH_PLANES = 0x0001,
    TEXTURE_DATA = 0x0002,
    VERTICES = 0x0003,
    LIGHTPROBE_PARENT_INFOS = 0x0004,
    SHADOW_ENVIRONMENTS = 0x0005,
    LIGHTPROBE_BSP_NODES = 0x0006,
    LIGHTPROBE_BSP_REF_IDS = 0x0007, // indexes ? (Mod_LoadLightProbeBSPRefIdxs)
    UNUSED_8 = 0x0008,
    UNUSED_9 = 0x0009,
    UNUSED_10 = 0x000A,
    UNUSED_11 = 0x000B,
    UNUSED_12 = 0x000C,
    UNUSED_13 = 0x000D,
    MODELS = 0x000E,
    UNUSED_15 = 0x000F,
    UNUSED_16 = 0x0010,
    UNUSED_17 = 0x0011,
    UNUSED_18 = 0x0012,
    UNUSED_19 = 0x0013,
    UNUSED_20 = 0x0014,
    UNUSED_21 = 0x0015,
    UNUSED_22 = 0x0016,
    UNUSED_23 = 0x0017,
    ENTITY_PARTITIONS = 0x0018,
    UNUSED_25 = 0x0019,
    UNUSED_26 = 0x001A,
    UNUSED_27 = 0x001B,
    UNUSED_28 = 0x001C,
    PHYSICS_COLLIDE = 0x001D,
    VERTEX_NORMALS = 0x001E,
    UNUSED_31 = 0x001F,
    UNUSED_32 = 0x0020,
    UNUSED_33 = 0x0021,
    UNUSED_34 = 0x0022,
    GAME_LUMP = 0x0023,
    LEAF_WATER_DATA = 0x0024,
    UNUSED_37 = 0x0025,
    UNUSED_38 = 0x0026,
    UNUSED_39 = 0x0027,
    PAKFILE = 0x0028,  // zip file, contains cubemaps
    UNUSED_41 = 0x0029,
    CUBEMAPS = 0x002A,
    TEXTURE_DATA_STRING_DATA = 0x002B,
    TEXTURE_DATA_STRING_TABLE = 0x002C,
    UNUSED_45 = 0x002D,
    UNUSED_46 = 0x002E,
    UNUSED_47 = 0x002F,
    UNUSED_48 = 0x0030,
    UNUSED_49 = 0x0031,
    UNUSED_50 = 0x0032,
    UNUSED_51 = 0x0033,
    UNUSED_52 = 0x0034,
    UNUSED_53 = 0x0035,
    WORLD_LIGHTS = 0x0036,  // versions 1 - 3 supported(0 might cause a crash, idk)
    WORLD_LIGHT_PARENT_INFOS = 0x0037,
    UNUSED_56 = 0x0038,
    UNUSED_57 = 0x0039,
    UNUSED_58 = 0x003A,
    UNUSED_59 = 0x003B,
    UNUSED_60 = 0x003C,
    UNUSED_61 = 0x003D,
    UNUSED_62 = 0x003E,
    UNUSED_63 = 0x003F,
    UNUSED_64 = 0x0040,
    UNUSED_65 = 0x0041,
    TRICOLL_TRIANGLES = 0x0042,
    UNUSED_67 = 0x0043,
    TRICOLL_NODES = 0x0044,
    TRICOLL_HEADERS = 0x0045,
    UNUSED_70 = 0x0046,
    VERTEX_UNLIT = 0x0047,        // VERTEX_RESERVED_0
    VERTEX_LIT_FLAT = 0x0048,     // VERTEX_RESERVED_1
    VERTEX_LIT_BUMP = 0x0049,     // VERTEX_RESERVED_2
    VERTEX_UNLIT_TS = 0x004A,     // VERTEX_RESERVED_3
    VERTEX_BLINN_PHONG = 0x004B,  // VERTEX_RESERVED_4
    VERTEX_RESERVED_5 = 0x004C,
    VERTEX_RESERVED_6 = 0x004D,
    VERTEX_RESERVED_7 = 0x004E,
    MESH_INDICES = 0x004F,
    MESHES = 0x0050,
    MESH_BOUNDS = 0x0051,
    MATERIAL_SORTS = 0x0052,
    LIGHTMAP_HEADERS = 0x0053,
    UNUSED_84 = 0x0054,
    CM_GRID = 0x0055,
    CM_GRID_CELLS = 0x0056,
    CM_GEO_SETS = 0x0057,
    CM_GEO_SET_BOUNDS = 0x0058,
    CM_PRIMITIVES = 0x0059,
    CM_PRIMITIVE_BOUNDS = 0x005A,
    CM_UNIQUE_CONTENTS = 0x005B,
    CM_BRUSHES = 0x005C,
    CM_BRUSH_SIDE_PLANE_OFFSETS = 0x005D,
    CM_BRUSH_SIDE_PROPERTIES = 0x005E,
    CM_BRUSH_SIDE_TEXTURE_VECTORS = 0x005F,
    TRICOLL_BEVEL_STARTS = 0x0060,
    TRICOLL_BEVEL_INDICES = 0x0061,
    LIGHTMAP_DATA_SKY = 0x0062,
    CSM_AABB_NODES = 0x0063,
    CSM_OBJ_REFERENCES = 0x0064,
    LIGHTPROBES = 0x0065,
    STATIC_PROP_LIGHTPROBE_INDICES = 0x0066,
    LIGHTPROBE_TREE = 0x0067,
    LIGHTPROBE_REFERENCES = 0x0068,
    LIGHTMAP_DATA_REAL_TIME_LIGHTS = 0x0069,
    CELL_BSP_NODES = 0x006A,
    CELLS = 0x006B,
    PORTALS = 0x006C,
    PORTAL_VERTICES = 0x006D,
    PORTAL_EDGES = 0x006E,
    PORTAL_VERTEX_EDGES = 0x006F,
    PORTAL_VERTEX_REFERENCES = 0x0070,
    PORTAL_EDGE_REFERENCES = 0x0071,
    PORTAL_EDGE_INTERSECT_AT_EDGE = 0x0072,
    PORTAL_EDGE_INTERSECT_AT_VERTEX = 0x0073,
    PORTAL_EDGE_INTERSECT_HEADER = 0x0074,
    OCCLUSION_MESH_VERTICES = 0x0075,
    OCCLUSION_MESH_INDICES = 0x0076,
    CELL_AABB_NODES = 0x0077,
    OBJ_REFERENCES = 0x0078,
    OBJ_REFERENCE_BOUNDS = 0x0079,
    LIGHTMAP_DATA_RTL_PAGE = 0x007A,
    LEVEL_INFO = 0x007B,
    SHADOW_MESH_OPAQUE_VERTICES = 0x007C,
    SHADOW_MESH_ALPHA_VERTICES = 0x007D,
    SHADOW_MESH_INDICES = 0x007E,
    SHADOW_MESHES = 0x007F
};

struct LightMap {
    uint32_t type;
    uint16_t width;
    uint16_t height;
};

struct LumpHeader {
    uint32_t offset;
    uint32_t length;
    uint32_t version;
    uint32_t fourCC;
};


struct BspHeader {
    uint32_t   magic;
    uint32_t   version;
    uint32_t   revision;
    uint32_t   _127;
    LumpHeader lumps[128];
};

template<typename T> std::vector<T> loadLump(const BspHeader& header,std::ifstream& file,int index) {
	std::vector<T> vec;
	file.seekg(header.lumps[index].offset,std::ios::beg);
    vec.resize(header.lumps[index].length/sizeof(T));
	file.read((char*)vec.data(), header.lumps[index].length);

	return vec;
}
#pragma push(pack,1)
struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + 786432;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
};

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 512; // in pixels
    int32_t height = 512; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
};
#pragma pop(pack)


void initBmpFile(std::ofstream& out, uint16_t width, uint16_t height) {
    BmpHeader bmpHeader;
    bmpHeader.sizeOfBitmapFile = 54 + 3 * height * width;
    BmpInfoHeader bmpInfo;
    bmpInfo.height = height;
    bmpInfo.width = width;
    out.write(bmpHeader.bitmapSignatureBytes, 2);
    out.write((char*)&bmpHeader.sizeOfBitmapFile, sizeof(uint32_t));
    out.write((char*)&bmpHeader.reservedBytes, sizeof(uint32_t));
    out.write((char*)&bmpHeader.pixelDataOffset, sizeof(uint32_t));

    out.write((char*)&bmpInfo.sizeOfThisHeader, sizeof(uint32_t));
    out.write((char*)&bmpInfo.width, sizeof(int32_t));
    out.write((char*)&bmpInfo.height, sizeof(int32_t));
    out.write((char*)&bmpInfo.numberOfColorPlanes, sizeof(uint16_t));
    out.write((char*)&bmpInfo.colorDepth, sizeof(uint16_t));
    out.write((char*)&bmpInfo.compressionMethod, sizeof(uint32_t));
    out.write((char*)&bmpInfo.rawBitmapDataSize, sizeof(uint32_t));
    out.write((char*)&bmpInfo.horizontalResolution, sizeof(int32_t));
    out.write((char*)&bmpInfo.verticalResolution, sizeof(int32_t));
    out.write((char*)&bmpInfo.colorTableEntries, sizeof(uint32_t));
    out.write((char*)&bmpInfo.importantColors, sizeof(uint32_t));
}


int main()
{
    const char* fileName = "H:\\r2\\r2_vpk\\maps\\sp_tday.bsp";
    BspHeader header;
    std::ifstream file{};
    file.open(fileName,std::ios::binary);
    file.seekg(0,std::ios::beg);
    file.read((char*) & header, sizeof(header));
    
    std::vector<LightMap> lightMaps = loadLump<LightMap>(header,file,LIGHTMAP_HEADERS);
    std::vector<uint8_t> realTimeLights = loadLump<uint8_t>(header,file,LIGHTMAP_DATA_REAL_TIME_LIGHTS);
    std::vector<uint8_t> skyLightMaps = loadLump<uint8_t>(header,file,LIGHTMAP_DATA_SKY);
    size_t rtlPtr = 0;
    size_t skyPtr = 0;
    int lightmapIndex = 0;;
    const char* letters[3] = { "A","B","C"};
    for (const auto& map : lightMaps) {
        for (int k = 0; k < 3; k++) {
            
            std::ofstream outRtl{std::format("mapsCombined\\realTimeLightmap {} {}.bmp",lightmapIndex,letters[k]),std::ios::binary};
            initBmpFile(outRtl,map.width,map.height);

            for (uint16_t i = 0; i < map.height; i++) {
                for (uint16_t j = 0; j < map.width; j++) {
                    uint8_t pixel[3];
                    switch (k) {
                    case 0:
                        pixel[2] = realTimeLights[rtlPtr+0];//*realTimeLights[rtlPtr+3])/255;
                        pixel[1] = 0;//*realTimeLights[rtlPtr+3])/255;
                        pixel[0] = 0;//*realTimeLights[rtlPtr+3])/255;
                        
                        rtlPtr+=4;
                        break;
                    case 1:
                        pixel[2] = realTimeLights[rtlPtr+0];//*realTimeLights[rtlPtr+3])/255;
                        pixel[1] = realTimeLights[rtlPtr+1];//*realTimeLights[rtlPtr+3])/255;
                        pixel[0] = realTimeLights[rtlPtr+2];//*realTimeLights[rtlPtr+3])/255;
                        
                        rtlPtr+=4;
                        break;
                    case 2:
                        pixel[1] = realTimeLights[rtlPtr]*7;//*realTimeLights[rtlPtr+3])/255;
                        pixel[2] = 0;
                        pixel[0] = 0;
                        rtlPtr++;
                        break;
                    }
                    outRtl.write((char*)pixel,3);
                        

                    
                }
            }
            outRtl.close();
            
        }
        for (int k = 0; k < 2; k++) {
            std::ofstream outSky{std::format("mapsCombined\\lightmapSky {} {}.bmp",lightmapIndex,letters[k]),std::ios::binary};
            initBmpFile(outSky,map.width,map.height);
            for (uint16_t i = 0; i < map.height; i++) {
                for (uint16_t j = 0; j < map.width; j++) {
                    uint8_t pixel[3];
                    pixel[2] = skyLightMaps[skyPtr+0];//*realTimeLights[rtlPtr+3])/255;
                    pixel[1] = skyLightMaps[skyPtr+1];//*realTimeLights[rtlPtr+3])/255;
                    pixel[0] = skyLightMaps[skyPtr+2];//*realTimeLights[rtlPtr+3])/255;
                    outSky.write((char*)pixel,3);
                    skyPtr+=4;
                }
            }
            outSky.close();
        }
        



        lightmapIndex++;
        
    }
    
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
