#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

#define MAP_FILE L"../Stage2Objects.json"
#define OBJECTS_FILE L"../Stage2Objects.txt"

#define MAP_HEIGHT 192

enum OBJECT_TYPE
{
    SIMON = 0,
    WHIP = 1,
    BRICK = 2,
    TORCH = 3,
    BIGHEART = 4,
    PORTAL = 5,
    CANDLE = 6,
    GHOUL = 7,
    PANTHER = 8,
    MONEYBAG = 9,
    STAIR = 10,
    MORNINGSTAR = 11,
    DAGGER = 12,
    AXE = 13,
    HOLYWATERBOTTLE = 14,
    SUBWEAPONITEM = 15,
    SMALLHEART = 16,
    TRIGGERZONE = 17,
    BREAKABLEBRICK = 18
};

string GetObjectDetail(int objectType)
{
    switch (objectType)
    {
    case BRICK: return "#Brick, extra seting: width, height";
    case TORCH: return "#Torch, extra setting: item's objectid drop when hit";
    case CANDLE: return "#Candle, extra setting: item's objectid drop when hit";
    case BREAKABLEBRICK: return "#Breakable brick, extra setting: type brick, item drop when break";
    case GHOUL: return "#Ghoul, extra setting: positive when start";
    case PANTHER: return "#Panther, extra setting: positive when start";
    case STAIR: return "#Stair, extra setting : up or down(1: up, -1 : down), left or right(1: right, -1 : left)";
    case TRIGGERZONE: return "#TriggerZone, extra setting: width, height, obj id spawn when trigger, spawnX, spawnY, extra setting for obj spawn";
    case PORTAL: return "#Portal, extra setting: width, height, scene will be changed to, entry id postition when change";
    default: return "#ObjectType " + to_string(objectType);
    }
}

struct GameObjectExport
{
    int id;
    int objectType;
    float x, y, width, height;
    vector<int> otherParams;
};

int main()
{
    ifstream inputFile(MAP_FILE);
    if (!inputFile.is_open()) {
        cerr << "Can't open map file" << endl;
        return 1;
    }

    json mapData;
    inputFile >> mapData;
    inputFile.close();

    unordered_map<int, vector<GameObjectExport>> groupedObjects;

    for (const auto& layer : mapData["layers"])
    {
        if (layer["type"] == "objectgroup")
        {
            for (const auto& object : layer["objects"])
            {
                GameObjectExport obj;

                obj.id = object["id"];
                float x = object["x"];
                float y = object["y"];
                obj.width = object["width"];
                obj.height = object["height"];
                obj.x = x + obj.width / 2.0f;
                obj.y = MAP_HEIGHT - y - obj.height / 2.0f;

                obj.objectType = -1;

                if (object.contains("properties"))
                {
                    for (const auto& prop : object["properties"])
                    {
                        if (prop["name"] == "ObjectType") {
                            obj.objectType = prop["value"];
                        }
                        else {
                            obj.otherParams.push_back(prop["value"]);
                        }
                    }
                }

                if (obj.objectType != -1)
                    groupedObjects[obj.objectType].push_back(obj);
            }
        }
    }

    ofstream outputFile(OBJECTS_FILE);
    if (!outputFile.is_open()) {
        cerr << "Can't create output file" << endl;
        return 1;
    }

    outputFile << "#object_id object_type x y width height extra_setting...\n";

    for (const auto& it : groupedObjects)
    {
        int objectType = it.first;
        const vector<GameObjectExport>& objects = it.second;

        outputFile << GetObjectDetail(objectType) << "\n";

        for (const auto& obj : objects)
        {
            outputFile << obj.id << " "
                << obj.objectType << " "
                << obj.x << " "
                << obj.y << " "
                << obj.width << " "
                << obj.height;

            for (int param : obj.otherParams)
                outputFile << " " << param;

            outputFile << "\n\n";
        }
    }

    outputFile.close();
    cout << "Done" << endl;
    return 0;
}
