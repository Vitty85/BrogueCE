/*
 *  GlobalsBase.h
 *  Brogue
 *
 *  Created by Brian Walker on 2/8/09.
 *  Copyright 2012. All rights reserved.
 *
 *  This file is part of Brogue.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GLOBALBASE_H
#define GLOBALBASE_H

extern tcell tmap[DCOLS][DROWS];                        // grids with info about the map
extern pcell pmap[DCOLS][DROWS];                        // grids with info about the map

// Returns a pointer to the `tcell` at the given position. The position must be in-bounds.
static inline tcell* tmapAt(pos p) {
  brogueAssert(p.x >= 0 && p.x < DCOLS && p.y >= 0 && p.y < DROWS);
  return &tmap[p.x][p.y];
}
// Returns a pointer to the `pcell` at the given position. The position must be in-bounds.
static inline pcell* pmapAt(pos p) {
  brogueAssert(p.x >= 0 && p.x < DCOLS && p.y >= 0 && p.y < DROWS);
  return &pmap[p.x][p.y];
}

const short nbDirs[8][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};

// Returns the `pos` which is one cell away in the provided direction.
// The direction must not be `NO_DIRECTION`.
static inline pos posNeighborInDirection(pos p, enum directions direction_to_step) {
  brogueAssert(direction_to_step >= 0 && direction_to_step < 8);
  return (pos) { .x = p.x + nbDirs[direction_to_step][0], .y = p.y + nbDirs[direction_to_step][1] };
}

extern short **scentMap;
extern screenDisplayBuffer displayBuffer;
extern short terrainRandomValues[DCOLS][DROWS][8];
extern short **safetyMap;                                       // used to help monsters flee
extern short **allySafetyMap;
extern short **chokeMap;

const short cDirs[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
extern levelData *levels;
extern creature player;
extern playerCharacter rogue;
extern const gameConstants *gameConst;
extern int gameVariant;
extern creatureList *monsters;
extern creatureList *dormantMonsters;
extern creatureList purgatory;
extern item *floorItems;
extern item *packItems;
extern item *monsterItemsHopper;
extern short numberOfWaypoints;

extern char displayedMessage[MESSAGE_LINES][COLS*2];
extern short messagesUnconfirmed;
extern char combatText[COLS*2];
extern short messageArchivePosition;
extern archivedMessage messageArchive[MESSAGE_ARCHIVE_ENTRIES];

extern char currentFilePath[BROGUE_FILENAME_MAX];
extern unsigned long randomNumbersGenerated;

extern char displayDetail[DCOLS][DROWS];

#ifdef AUDIT_RNG
extern FILE *RNGLogFile;
#endif

#define MENU_TITLE_WIDTH    68
#define MENU_TITLE_HEIGHT   26

extern unsigned char inputRecordBuffer[INPUT_RECORD_BUFFER + 100];
extern unsigned short locationInRecordingBuffer;

extern unsigned long positionInPlaybackFile;
extern unsigned long lengthOfPlaybackFile;
extern unsigned long recordingLocation;
extern unsigned long maxLevelChanges;
extern char annotationPathname[BROGUE_FILENAME_MAX];    // pathname of annotation file
extern uint64_t previousGameSeed;

// basic colors
const color white =                 {100,   100,    100,    0,      0,          0,          0,      false};
const color gray =                  {50,    50,     50,     0,      0,          0,          0,      false};
const color darkGray =              {30,    30,     30,     0,      0,          0,          0,      false};
const color veryDarkGray =          {15,    15,     15,     0,      0,          0,          0,      false};
const color black =                 {0,     0,      0,      0,      0,          0,          0,      false};
const color yellow =                {100,   100,    0,      0,      0,          0,          0,      false};
const color darkYellow =            {50,    50,     0,      0,      0,          0,          0,      false};
const color teal =                  {30,    100,    100,    0,      0,          0,          0,      false};
const color purple =                {100,   0,      100,    0,      0,          0,          0,      false};
const color darkPurple =            {50,    0,      50,     0,      0,          0,          0,      false};
const color brown =                 {60,    40,     0,      0,      0,          0,          0,      false};
const color green =                 {0,     100,    0,      0,      0,          0,          0,      false};
const color darkGreen =             {0,     50,     0,      0,      0,          0,          0,      false};
const color orange =                {100,   50,     0,      0,      0,          0,          0,      false};
const color darkOrange =            {50,    25,     0,      0,      0,          0,          0,      false};
const color blue =                  {0,     0,      100,    0,      0,          0,          0,      false};
const color darkBlue =              {0,     0,      50,     0,      0,          0,          0,      false};
const color darkTurquoise =         {0,     40,     65,     0,      0,          0,          0,      false};
const color lightBlue =             {40,    40,     100,    0,      0,          0,          0,      false};
const color pink =                  {100,   60,     66,     0,      0,          0,          0,      false};
const color darkPink =              {50,    30,     33,     0,      0,          0,          0,      false};
const color red  =                  {100,   0,      0,      0,      0,          0,          0,      false};
const color darkRed =               {50,    0,      0,      0,      0,          0,          0,      false};
const color tanColor =              {80,    67,     15,     0,      0,          0,          0,      false};
const color rainbow =               {-70,   -70,    -70,    170,    170,        170,        0,      true};


extern const char monsterBehaviorFlagDescriptions[32][COLS];
extern const char monsterAbilityFlagDescriptions[32][COLS];
extern const char monsterBookkeepingFlagDescriptions[32][COLS];

const windowpos WINDOW_POSITION_DUNGEON_TOP_LEFT;

// charm constants
#define CHARM_EFFECT_DURATION_INCREMENT_ARRAY_SIZE 50
const fixpt POW_0_CHARM_INCREMENT[] = { // 1.0
    65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536,
    65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536,
    65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536};
const fixpt POW_120_CHARM_INCREMENT[] = { // 1.20^x fixed point, with x from 1 to 50 in increments of 1:
    78643, 94371, 113246, 135895, 163074, 195689, 234827, 281792, 338151, 405781, 486937, 584325, 701190, 841428, 1009714, 1211657,
    1453988, 1744786, 2093744, 2512492, 3014991, 3617989, 4341587, 5209905, 6251886, 7502263, 9002716, 10803259, 12963911, 15556694,
    18668032, 22401639, 26881967, 32258360, 38710033, 46452039, 55742447, 66890937, 80269124, 96322949, 115587539, 138705047, 166446056,
    199735268, 239682321, 287618785, 345142543, 414171051, 497005262, 596406314, 715687577};
const fixpt POW_125_CHARM_INCREMENT[] = { // 1.25^x fixed point, with x from 1 to 50 in increments of 1:
    81920, 102400, 128000, 160000, 200000, 250000, 312500, 390625, 488281, 610351, 762939, 953674, 1192092, 1490116, 1862645, 2328306,
    2910383, 3637978, 4547473, 5684341, 7105427, 8881784, 11102230, 13877787, 17347234, 21684043, 27105054, 33881317, 42351647, 52939559,
    66174449, 82718061, 103397576, 129246970, 161558713, 201948391, 252435489, 315544362, 394430452, 493038065, 616297582, 770371977,
    962964972, 1203706215, 1504632769, 1880790961, 2350988701, 2938735877, 3673419846, 4591774807, 5739718509};

#endif
