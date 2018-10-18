/*
 * Copyright 2015 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "monster_generated.h"  // Already includes "flatbuffers/flatbuffers.h".
#include "edgestore_generated.h"
#include "flatbuffers/util.h"
#include <map>
#include <unordered_set>

using namespace MyGame::Sample;

// Example how to use FlatBuffers to create and read binary buffers.

int mainOne(int /*argc*/, const char * /*argv*/ []) {
    // Build up a serialized buffer algorithmically:
    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::FlatBufferBuilder builder2;

    std::string fileName = "test.txt";

    // First, lets serialize some weapons for the Monster: A 'sword' and an 'axe'.
    auto weapon_one_name = builder.CreateString("Sword");
    short weapon_one_damage = 3;

    auto weapon_two_name = builder.CreateString("Axe");
    short weapon_two_damage = 5;

    // Use the `CreateWeapon` shortcut to create Weapons with all fields set.
    auto sword = CreateWeapon(builder, weapon_one_name, weapon_one_damage);
    auto axe = CreateWeapon(builder, weapon_two_name, weapon_two_damage);

    // Create a FlatBuffer's `vector` from the `std::vector`.
    std::vector<flatbuffers::Offset<Weapon>> weapons_vector;
    weapons_vector.push_back(sword);
    weapons_vector.push_back(axe);
    auto weapons = builder.CreateVector(weapons_vector);

    // Second, serialize the rest of the objects needed by the Monster.
    auto position = Vec3(1.0f, 2.0f, 3.0f);

    auto name = builder.CreateString("MyMonster");

    unsigned char inv_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto inventory = builder.CreateVector(inv_data, 10);

    // Shortcut for creating monster with all fields set:
    auto orc = CreateMonster(builder, &position, 150, 80, name, inventory,
                             Color_Red, weapons, Equipment_Weapon, axe.Union());

    builder.Finish(orc);  // Serialize the root of the object.

    flatbuffers::SaveFile(fileName.c_str(),(const char *)builder.GetBufferPointer(),(size_t)builder.GetSize(),true);



    // We now have a FlatBuffer we can store on disk or send over a network.

    // ** file/network code goes here :) **
    // access builder.GetBufferPointer() for builder.GetSize() bytes

    // Instead, we're going to access it right away (as if we just received it).

    //bool result = false;

    //std::string buffer;
    //result = flatbuffers::LoadFile(fileName.c_str(), false, &buffer);
    //printf("\nLoadFile Result = %d", result);

    //flatbuffers::

    //BELOW CODE WILL SHOW HOW TO LOAD ALREADY SAVED FLATBUFFER OBJECT FROM A FILE AND DESERIALIZE IT

    std::ifstream infile;
    infile.open("test.txt", std::ios::binary | std::ios::in);
    infile.seekg(0,std::ios::end);
    int length = infile.tellg();
    infile.seekg(0,std::ios::beg);
    char *data = new char[length];
    infile.read(data, length);
    infile.close();

    auto monster = GetMonster(data);

    // Get access to the root:
    //auto monster = GetMonster(builder.GetBufferPointer());

    // Get and test some scalar types from the FlatBuffer.
    assert(monster->hp() == 80);
    assert(monster->mana() == 150);  // default
    assert(monster->name()->str() == "MyMonster");

    // Get and test a field of the FlatBuffer's `struct`.
    auto pos = monster->pos();
    assert(pos);
    assert(pos->z() == 3.0f);
    (void)pos;

    // Get a test an element from the `inventory` FlatBuffer's `vector`.
    auto inv = monster->inventory();
    assert(inv);
    assert(inv->Get(9) == 9);
    (void)inv;

    // Get and test the `weapons` FlatBuffers's `vector`.
    std::string expected_weapon_names[] = { "Sword", "Axe" };
    short expected_weapon_damages[] = { 3, 5 };
    auto weps = monster->weapons();
    for (unsigned int i = 0; i < weps->size(); i++) {
        assert(weps->Get(i)->name()->str() == expected_weapon_names[i]);
        assert(weps->Get(i)->damage() == expected_weapon_damages[i]);
    }
    (void)expected_weapon_names;
    (void)expected_weapon_damages;

    // Get and test the `Equipment` union (`equipped` field).
    assert(monster->equipped_type() == Equipment_Weapon);
    auto equipped = static_cast<const Weapon *>(monster->equipped());
    assert(equipped->name()->str() == "Axe");
    assert(equipped->damage() == 5);
    (void)equipped;

    printf("The FlatBuffer was successfully created and verified!\n");
}

int main(){
    flatbuffers::FlatBufferBuilder builder;
    std::vector<long> longvectorone;
    std::vector<long> longvectortwo;

    std::map<long,std::vector<long>> localSubGraphMap;


    std::string fileName = "acacia.edgestore.db";

    long keyOne = 34;
    long keyTwo = 89;
    longvectorone.push_back(45);
    longvectorone.push_back(59);
    longvectortwo.push_back(77);
    longvectortwo.push_back(99);

    localSubGraphMap.insert(std::make_pair(keyOne,longvectorone));
    localSubGraphMap.insert(std::make_pair(keyTwo,longvectortwo));

    int size = localSubGraphMap.size();


    auto vectorValuesOne = builder.CreateVector(longvectorone);
    auto vectorValuesTwo = builder.CreateVector(longvectortwo);

    auto edgeStoreEntryOne = CreateEdgeStoreEntry(builder,keyOne,vectorValuesOne);
    auto edgeStoreEntryTwo = CreateEdgeStoreEntry(builder,keyTwo,vectorValuesTwo);

    std::vector<flatbuffers::Offset<EdgeStoreEntry>> edgeStoreEntriesVector;
    edgeStoreEntriesVector.push_back(edgeStoreEntryOne);
    edgeStoreEntriesVector.push_back(edgeStoreEntryTwo);

   // auto flatbufferEdgeStoreEntryVector = builder.CreateVector(edgeStoreEntriesVector);

    auto flatbufferEdgeStoreEntryVector = builder.CreateVectorOfSortedTables(&edgeStoreEntriesVector);

    auto edgeStore = CreateEdgeStore(builder,flatbufferEdgeStoreEntryVector);

    builder.Finish(edgeStore);

    flatbuffers::SaveFile(fileName.c_str(),(const char *)builder.GetBufferPointer(),(size_t)builder.GetSize(),true);

    std::ifstream infile;
    infile.open("edgeStore.db", std::ios::binary | std::ios::in);
    infile.seekg(0,std::ios::end);
    int length = infile.tellg();
    infile.seekg(0,std::ios::beg);
    char *data = new char[length];
    infile.read(data, length);
    infile.close();

    auto retrievedEdgeStore = GetEdgeStore(data);

    auto allEntries = retrievedEdgeStore->entries();

    auto entry = allEntries->LookupByKey(34);

    auto values = entry->value();

    auto value = values->Get(0);

    /*for (unsigned int i=0;i<allEntries->size();i++) {
        auto entry = allEntries->LookupByKey("34");

    }*/


    printf("Successfully Completed");

}