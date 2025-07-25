#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
    .affineAnims = gDummySpriteAffineAnimTable,                                                                                         \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
            .affineAnims = gDummySpriteAffineAnimTable,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    [SPECIES_CHARMANDER_CONNOR] =
   {
        .baseHP        = 39,
        .baseAttack    = 52,
        .baseDefense   = 43,
        .baseSpeed     = 65,
        .baseSpAttack  = 60,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Soggmander"),
        .cryId = CRY_CHARMANDER_CONNOR,
        .natDexNum = NATIONAL_DEX_CHARMANDER_CONNOR,
        .categoryName = _("Lizard"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Soggmander,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Soggmander,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Soggmander,
       .shinyPalette = gMonShinyPalette_Soggmander,
        .iconSprite = gMonIcon_Soggmander,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_CHARMELEON_CONNOR}), 
       FOOTPRINT(Soggmander)
        OVERWORLD(
        sPicTable_Soggmander,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Soggmander,
        gShinyOverworldPalette_Soggmander,
        )
        .levelUpLearnset = sCHARMANDER_CONNORLevelUpLearnset,
        .teachableLearnset = sCHARMANDER_CONNORTeachableLearnset
       

    },
    [SPECIES_CHARMELEON_CONNOR] =
   {
        .baseHP        = 58,
        .baseAttack    = 64,
        .baseDefense   = 58,
        .baseSpeed     = 80,
        .baseSpAttack  = 80,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Soggmeleon"),
        .cryId = CRY_CHARMELEON_CONNOR,
        .natDexNum = NATIONAL_DEX_CHARMELEON_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Soggmeleon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Soggmeleon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Soggmeleon,
       .shinyPalette = gMonShinyPalette_Soggmeleon,
        .iconSprite = gMonIcon_Soggmeleon,
        .iconPalIndex = 0,
 .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_CHARIZARD_CONNOR}),
       FOOTPRINT(Soggmeleon)
        OVERWORLD(
        sPicTable_Soggmeleon,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Soggmeleon,
        gShinyOverworldPalette_Soggmeleon,
        )
        .levelUpLearnset = sCHARMELEON_CONNORLevelUpLearnset,
        .teachableLearnset = sCHARMELEON_CONNORTeachableLearnset
 
   
   },
    [SPECIES_CHARIZARD_CONNOR] =
   {
        .baseHP        = 68,
        .baseAttack    = 84,
        .baseDefense   = 78,
        .baseSpeed     = 110,
        .baseSpAttack  = 119,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_WATER, TYPE_FIRE),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Soggizard"),
        .cryId = CRY_CHARIZARD_CONNOR,
        .natDexNum = NATIONAL_DEX_CHARIZARD_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Soggizard,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Soggizard,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Soggizard,
       .shinyPalette = gMonShinyPalette_Soggizard,
        .iconSprite = gMonIcon_Soggizard,
        .iconPalIndex = 0,
       FOOTPRINT(Soggizard)
        OVERWORLD(
        sPicTable_Soggizard,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Soggizard,
        gShinyOverworldPalette_Soggizard,
        )
        .levelUpLearnset = sCHARIZARD_CONNORLevelUpLearnset,
        .teachableLearnset = sCHARIZARD_CONNORTeachableLearnset     
    },

  [SPECIES_BULBASAUR_CONNOR] =
   {
        .baseHP        = 45,
        .baseAttack    = 49,
        .baseDefense   = 49,
        .baseSpeed     = 45,
        .baseSpAttack  = 65,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Cindesaur"),
        .cryId = CRY_BULBASAUR_CONNOR,
        .natDexNum = NATIONAL_DEX_BULBASAUR_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cindesaur,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cindesaur,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Cindesaur,
       .shinyPalette = gMonShinyPalette_Cindesaur,
        .iconSprite = gMonIcon_Cindesaur,
        .iconPalIndex = 6,
  .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_IVYSAUR_CONNOR}), 
       FOOTPRINT(Cindesaur)
        OVERWORLD(
        sPicTable_Cindesaur,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Cindesaur,
        gShinyOverworldPalette_Cindesaur,
        )
        .levelUpLearnset = sBULBASAUR_CONNORLevelUpLearnset,
        .teachableLearnset = sBULBASAUR_CONNORTeachableLearnset
       

    },
    [SPECIES_IVYSAUR_CONNOR] =
   {
        .baseHP        = 60,
        .baseAttack    = 62,
        .baseDefense   = 63,
        .baseSpeed     = 60,
        .baseSpAttack  = 80,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Charresaur"),
        .cryId = CRY_IVYSAUR_CONNOR,
        .natDexNum = NATIONAL_DEX_IVYSAUR_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Charresaur,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Charresaur,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Charresaur,
       .shinyPalette = gMonShinyPalette_Charresaur,
        .iconSprite = gMonIcon_Charresaur,
        .iconPalIndex = 6,
 .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_VENUSAUR_CONNOR}),
       FOOTPRINT(Charresaur)
        OVERWORLD(
        sPicTable_Charresaur,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Charresaur,
        gShinyOverworldPalette_Charresaur,
        )
        .levelUpLearnset = sIVYSAUR_CONNORLevelUpLearnset,
        .teachableLearnset = sIVYSAUR_CONNORTeachableLearnset
 
   
   },
    [SPECIES_VENUSAUR_CONNOR] =
   {
        .baseHP        = 80,
        .baseAttack    = 90,
        .baseDefense   = 113,
        .baseSpeed     = 100,
        .baseSpAttack  = 132,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GRASS),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Scorresaur"),
        .cryId = CRY_VENUSAUR_CONNOR,
        .natDexNum = NATIONAL_DEX_VENUSAUR_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Scorresaur,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Scorresaur,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Scorresaur,
       .shinyPalette = gMonShinyPalette_Scorresaur,
        .iconSprite = gMonIcon_Scorresaur,
        .iconPalIndex = 6,
       FOOTPRINT(Scorresaur)
        OVERWORLD(
        sPicTable_Scorresaur,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Scorresaur,
        gShinyOverworldPalette_Scorresaur,
        )
        .levelUpLearnset = sVENUSAUR_CONNORLevelUpLearnset,
        .teachableLearnset = sVENUSAUR_CONNORTeachableLearnset     
    },

    [SPECIES_SQUIRTLE_CONNOR] =
   {
        .baseHP        = 44,
        .baseAttack    = 50,
        .baseDefense   = 65,
        .baseSpeed     = 43,
        .baseSpAttack  = 48,
        .baseSpDefense = 64,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_1),
        .abilities = {  ABILITY_OVERGROW, ABILITY_NONE, ABILITY_SWIFT_SWIM  },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Mosstle"),
        .cryId = CRY_SQUIRTLE_CONNOR,
        .natDexNum = NATIONAL_DEX_SQUIRTLE_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Mosstle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
       .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Mosstle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Mosstle,
       .shinyPalette = gMonShinyPalette_Mosstle,
        .iconSprite = gMonIcon_Mosstle,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_WARTORTLE_CONNOR}), 
       FOOTPRINT(Mosstle)
        OVERWORLD(
        sPicTable_Mosstle,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Mosstle,
        gShinyOverworldPalette_Mosstle,
        )
        .levelUpLearnset = sSQUIRTLE_CONNORLevelUpLearnset,
        .teachableLearnset = sSQUIRTLE_CONNORTeachableLearnset
       

    },
    [SPECIES_WARTORTLE_CONNOR] =
   {
        .baseHP        = 59,
        .baseAttack    = 65,
        .baseDefense   = 80,
        .baseSpeed     = 58,
        .baseSpAttack  = 63,
        .baseSpDefense = 58,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_SWIFT_SWIM },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Mosstortle"),
        .cryId = CRY_WARTORTLE_CONNOR,
        .natDexNum = NATIONAL_DEX_WARTORTLE_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Mosstortle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Mosstortle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Mosstortle,
       .shinyPalette = gMonShinyPalette_Mosstortle,
        .iconSprite = gMonIcon_Mosstortle,
        .iconPalIndex = 1,
 .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_BLASTOISE_CONNOR}),
       FOOTPRINT(Mosstortle)
        OVERWORLD(
        sPicTable_Mosstortle,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Mosstortle,
        gShinyOverworldPalette_Mosstortle,
        )
        .levelUpLearnset = sWARTORTLE_CONNORLevelUpLearnset,
        .teachableLearnset = sWARTORTLE_CONNORTeachableLearnset
 
   
   },

    [SPECIES_BLASTOISE_CONNOR] =
   {
        .baseHP        = 78,
        .baseAttack    = 135,
        .baseDefense   = 110,
        .baseSpeed     = 90,
        .baseSpAttack  = 101,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_GRASS, TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_SWIFT_SWIM },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Algetoise"),
        .cryId = CRY_BLASTOISE_CONNOR,
        .natDexNum = NATIONAL_DEX_BLASTOISE_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Algetoise,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Algetoise,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Algetoise,
       .shinyPalette = gMonShinyPalette_Algetoise,
        .iconSprite = gMonIcon_Algetoise,
        .iconPalIndex = 1,
       FOOTPRINT(Algetoise)
        OVERWORLD(
        sPicTable_Algetoise,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Algetoise,
        gShinyOverworldPalette_Algetoise,
        )
        .levelUpLearnset = sBLASTOISE_CONNORLevelUpLearnset,
        .teachableLearnset = sBLASTOISE_CONNORTeachableLearnset     
    },

 [SPECIES_DELTA_DRACOVISH] =
   {
        .baseHP        = 90,
        .baseAttack    = 100,
        .baseDefense   = 100,
        .baseSpeed     = 85,
        .baseSpAttack  = 50,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FIRE, TYPE_PSYCHIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_STRONG_JAW, ABILITY_FLASH_FIRE, ABILITY_SHEER_FORCE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Dracovish"),
        .cryId = CRY_DELTA_DRACOVISH,
        .natDexNum = NATIONAL_DEX_DELTA_DRACOVISH,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Dracovish,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Dracovish,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Dracovish,
       .shinyPalette = gMonShinyPalette_Delta_Dracovish,
        .iconSprite = gMonIcon_Delta_Dracovish,
        .iconPalIndex = 6,
       FOOTPRINT(Dracovish)
        OVERWORLD(
        sPicTable_Dracovish,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Dracovish,
        gShinyOverworldPalette_Delta_Dracovish,
        )
        .levelUpLearnset = sDELTA_DRACOVISHLevelUpLearnset,
        .teachableLearnset = sDELTA_DRACOVISHTeachableLearnset
       
    },

    [SPECIES_CATERPIE_CONNOR] =
   {
        .baseHP        = 45,
        .baseAttack    = 40,
        .baseDefense   = 45,
        .baseSpeed     = 55,
        .baseSpAttack  = 30,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_BUG, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_COMPOUND_EYES, ABILITY_NONE, ABILITY_GOOEY },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Caterphi"),
        .cryId = CRY_CATERPIE_CONNOR,
        .natDexNum = NATIONAL_DEX_CATERPIE_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Caterphi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Caterphi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Caterphi,
       .shinyPalette = gMonShinyPalette_Caterphi,
        .iconSprite = gMonIcon_Caterphi,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 12, SPECIES_METAPOD_CONNOR}), 
       FOOTPRINT(Caterphi)
        OVERWORLD(
        sPicTable_Caterpie,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Caterphi,
        gShinyOverworldPalette_Caterphi,
        )
        .levelUpLearnset = sCATERPIE_CONNORLevelUpLearnset,
        .teachableLearnset = sCATERPIE_CONNORTeachableLearnset
       

    },

    [SPECIES_METAPOD_CONNOR] =
   {
        .baseHP        = 88,
        .baseAttack    = 34,
        .baseDefense   = 108,
        .baseSpeed     = 40,
        .baseSpAttack  = 40,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_BUG, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_STURDY, ABILITY_NONE, ABILITY_IMPOSTER },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Chrysapod"),
        .cryId = CRY_METAPOD_CONNOR,
        .natDexNum = NATIONAL_DEX_METAPOD_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Chrysapod,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Chrysapod,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Chrysapod,
       .shinyPalette = gMonShinyPalette_Chrysapod,
        .iconSprite = gMonIcon_Chrysapod,
        .iconPalIndex = 0,
 .evolutions = EVOLUTION({EVO_LEVEL, 22, SPECIES_BUTTERFREE_CONNOR}),
       FOOTPRINT(Chrysapod)
        OVERWORLD(
        sPicTable_Metapod,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Chrysapod,
        gShinyOverworldPalette_Chrysapod,
        )
        .levelUpLearnset = sMETAPOD_CONNORLevelUpLearnset,
        .teachableLearnset = sMETAPOD_CONNORTeachableLearnset
 
   
   },

    [SPECIES_BUTTERFREE_CONNOR] =
   {
        .baseHP        = 80,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 90,
        .baseSpAttack  = 110,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_BUG, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_EFFECT_SPORE, ABILITY_WIND_RIDER, ABILITY_IMPOSTER },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Butterfae"),
        .cryId = CRY_BUTTERFREE_CONNOR,
        .natDexNum = NATIONAL_DEX_BUTTERFREE_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Butterfae,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 2,
        .backPic = gMonBackPic_Butterfae,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Butterfae,
       .shinyPalette = gMonShinyPalette_Butterfae,
        .iconSprite = gMonIcon_Butterfae,
        .iconPalIndex = 0,
       FOOTPRINT(Butterfae)
        OVERWORLD(
        sPicTable_Butterfree,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Butterfae,
        gShinyOverworldPalette_Butterfae,
        )
        .levelUpLearnset = sBUTTERFREE_CONNORLevelUpLearnset,
        .teachableLearnset = sBUTTERFREE_CONNORTeachableLearnset     
    },

 [SPECIES_WEEDLE_CONNOR] =
   {
        .baseHP        = 40,
        .baseAttack    = 35,
        .baseDefense   = 30,
        .baseSpeed     = 50,
        .baseSpAttack  = 20,
        .baseSpDefense = 20,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_COMPOUND_EYES, ABILITY_NONE, ABILITY_SHARPNESS },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Dronedle"),
        .cryId = CRY_WEEDLE_CONNOR,
        .natDexNum = NATIONAL_DEX_WEEDLE_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Drondle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
       .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Drondle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Drondle,
       .shinyPalette = gMonShinyPalette_Drondle,
        .iconSprite = gMonIcon_Drondle,
        .iconPalIndex = 6,
  .evolutions = EVOLUTION({EVO_LEVEL, 12, SPECIES_KAKUNA_CONNOR}), 
       FOOTPRINT(Drondle)
        OVERWORLD(
        sPicTable_Weedle,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Drondle,
        gShinyOverworldPalette_Drondle,
        )
        .levelUpLearnset = sWEEDLE_CONNORLevelUpLearnset,
        .teachableLearnset = sWEEDLE_CONNORTeachableLearnset
       

    },

    [SPECIES_KAKUNA_CONNOR] =
   {
        .baseHP        = 55,
        .baseAttack    = 25,
        .baseDefense   = 70,
        .baseSpeed     = 35,
        .baseSpAttack  = 25,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_STURDY, ABILITY_NONE, ABILITY_DISGUISE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Drokuna"),
        .cryId = CRY_KAKUNA_CONNOR,
        .natDexNum = NATIONAL_DEX_KAKUNA_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Drokuna,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Drokuna,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Drokuna,
       .shinyPalette = gMonShinyPalette_Drokuna,
        .iconSprite = gMonIcon_Drokuna,
        .iconPalIndex = 6,
 .evolutions = EVOLUTION({EVO_LEVEL, 22, SPECIES_BEEDRILL_CONNOR}),
       FOOTPRINT(Drokuna)
        OVERWORLD(
        sPicTable_Kakuna,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Drokuna,
        gShinyOverworldPalette_Drokuna,
        )
        .levelUpLearnset = sKAKUNA_CONNORLevelUpLearnset,
        .teachableLearnset = sKAKUNA_CONNORTeachableLearnset
 
   
   },

    [SPECIES_BEEDRILL_CONNOR] =
   {
        .baseHP        = 85,
        .baseAttack    = 110,
        .baseDefense   = 60,
        .baseSpeed     = 95,
        .baseSpAttack  = 45,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SIMPLE, ABILITY_NONE, ABILITY_SHARPNESS },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Dronedrill"),
        .cryId = CRY_BEEDRILL_CONNOR,
        .natDexNum = NATIONAL_DEX_BEEDRILL_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dronedrill,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 6,
        .backPic = gMonBackPic_Dronedrill,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Dronedrill,
       .shinyPalette = gMonShinyPalette_Dronedrill,
        .iconSprite = gMonIcon_Dronedrill,
        .iconPalIndex = 6,
       FOOTPRINT(Dronedrill)
        OVERWORLD(
        sPicTable_Beedrill,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Dronedrill,
        gShinyOverworldPalette_Dronedrill,
        )
        .levelUpLearnset = sBEEDRILL_CONNORLevelUpLearnset,
        .teachableLearnset = sBEEDRILL_CONNORTeachableLearnset     

    },

 [SPECIES_GLIGAR_CONNOR] =
   {
        .baseHP        = 65,
        .baseAttack    = 75,
        .baseDefense   = 105,
        .baseSpeed     = 85,
        .baseSpAttack  = 35,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_ICE, TYPE_ELECTRIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = {  ABILITY_STRONG_JAW, ABILITY_ICE_BODY, ABILITY_ICE_SCALES },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Icegar"),
        .cryId = CRY_GLIGAR_CONNOR,
        .natDexNum = NATIONAL_DEX_GLIGAR_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Icegar,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_Icegar,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Icegar,
        .shinyPalette = gMonShinyPalette_Icegar,
        .iconSprite = gMonIcon_Icegar,
        .iconPalIndex = 1,
       .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_GLISCOR, CONDITIONS({IF_TIME, TIME_NIGHT}, {IF_HOLD_ITEM, ITEM_RAZOR_FANG})},
                                {EVO_ITEM, ITEM_RAZOR_FANG, SPECIES_GLISCOR_CONNOR, CONDITIONS({IF_TIME, TIME_NIGHT})}),
       FOOTPRINT(Icegar)
        OVERWORLD(
        sPicTable_Gligar,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Icegar,
        gShinyOverworldPalette_Icegar,
        )
        .levelUpLearnset = sGLIGAR_CONNORLevelUpLearnset,
        .teachableLearnset = sGLIGAR_CONNORTeachableLearnset
       

    },

    [SPECIES_GLISCOR_CONNOR] =
   {
        .baseHP        = 75,
        .baseAttack    = 115,
        .baseDefense   = 125,
        .baseSpeed     = 95,
        .baseSpAttack  = 45,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_ICE, TYPE_ELECTRIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_STRONG_JAW, ABILITY_ICE_BODY, ABILITY_ICE_SCALES },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Icescor"),
        .cryId = CRY_GLISCOR_CONNOR,
        .natDexNum = NATIONAL_DEX_GLISCOR_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Icescor,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
       .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 4,
        .backPic = gMonBackPic_Icescor,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Icescor,
       .shinyPalette = gMonShinyPalette_Icescor,
        .iconSprite = gMonIcon_Icescor,
        .iconPalIndex = 1,
       FOOTPRINT(Icescor)
        OVERWORLD(
        sPicTable_Gliscor,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Icescor,
        gShinyOverworldPalette_Icescor,
        )
        .levelUpLearnset = sGLISCOR_CONNORLevelUpLearnset,
        .teachableLearnset = sGLISCOR_CONNORTeachableLearnset
 
   
   },

  [SPECIES_SKORUPI_CONNOR] =
   {
        .baseHP        = 40,
        .baseAttack    = 50,
        .baseDefense   = 65,
        .baseSpeed     = 65,
        .baseSpAttack  = 30,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_GROUND, TYPE_ELECTRIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_INFILTRATOR, ABILITY_SAND_VEIL, ABILITY_SURGE_SURFER },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Skorvolt"),
        .cryId = CRY_SKORUPI_CONNOR,
        .natDexNum = NATIONAL_DEX_SKORUPI_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skorvolt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skorvolt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Skorvolt,
       .shinyPalette = gMonShinyPalette_Skorvolt,
        .iconSprite = gMonIcon_Skorvolt,
        .iconPalIndex = 1,
.evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_DRAPION_CONNOR}),
       FOOTPRINT(Skorvolt)
        OVERWORLD(
        sPicTable_Skorupi,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Skorvolt,
        gShinyOverworldPalette_Skorvolt,
        )
        .levelUpLearnset = sSKORUPI_CONNORLevelUpLearnset,
        .teachableLearnset = sSKORUPI_CONNORTeachableLearnset     
    },

 [SPECIES_DRAPION_CONNOR] =
   {
        .baseHP        = 70,
        .baseAttack    = 100,
        .baseDefense   = 110,
        .baseSpeed     = 95,
        .baseSpAttack  = 50,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_GROUND, TYPE_ELECTRIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_INFILTRATOR, ABILITY_SAND_VEIL, ABILITY_SURGE_SURFER  },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Drapiamp"),
        .cryId = CRY_DRAPION_CONNOR,
        .natDexNum = NATIONAL_DEX_DRAPION_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Drapiamp,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
       .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Drapiamp,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Drapiamp,
       .shinyPalette = gMonShinyPalette_Drapiamp,
        .iconSprite = gMonIcon_Drapiamp,
        .iconPalIndex = 6,
       FOOTPRINT(Drapiamp)
        OVERWORLD(
        sPicTable_Drapion,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Drapiamp,
        gShinyOverworldPalette_Drapiamp,
        )
        .levelUpLearnset = sDRAPION_CONNORLevelUpLearnset,
        .teachableLearnset = sDRAPION_CONNORTeachableLearnset
       
    },

  [SPECIES_DELTA_DURANT] =
   {
        .baseHP        = 58,
        .baseAttack    = 109,
        .baseDefense   = 112,
        .baseSpeed     = 109,
        .baseSpAttack  = 48,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_BUG, TYPE_FIRE),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(100),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_STEELWORKER, ABILITY_TECHNICIAN, ABILITY_THERMAL_EXCHANGE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Durant"),
        .cryId = CRY_DELTA_DURANT,
        .natDexNum = NATIONAL_DEX_DELTA_DURANT,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Durant,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 12,
      .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Durant,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Durant,
       .shinyPalette = gMonShinyPalette_Delta_Durant,
        .iconSprite = gMonIcon_Delta_Durant,
        .iconPalIndex = 1,
       FOOTPRINT(Durant)
        OVERWORLD(
        sPicTable_Durant,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Durant,
        gShinyOverworldPalette_Delta_Durant,
        )
        .levelUpLearnset = sDELTA_DURANTLevelUpLearnset,
        .teachableLearnset = sDELTA_DURANTTeachableLearnset     
    },
 [SPECIES_DELTA_COMBEE] =
   {
        .baseHP        = 30,
        .baseAttack    = 30,
        .baseDefense   = 42,
        .baseSpeed     = 60,
        .baseSpAttack  = 30,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(100),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_QUEENLY_MAJESTY, ABILITY_RIVALRY, ABILITY_SERENE_GRACE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Combee"),
        .cryId = CRY_DELTA_COMBEE,
        .natDexNum = NATIONAL_DEX_DELTA_COMBEE,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Combee,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 2,
        .backPic = gMonBackPic_Delta_Combee,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 22,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Combee,
       .shinyPalette = gMonShinyPalette_Delta_Combee,
        .iconSprite = gMonIcon_Delta_Combee,
        .iconPalIndex = 1,
.evolutions = EVOLUTION({EVO_LEVEL, 21, SPECIES_DELTA_VESPIQUEN}),
       FOOTPRINT(Combee)
        OVERWORLD(
        sPicTable_Combee,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Combee,
        gShinyOverworldPalette_Delta_Combee,
        )
        .levelUpLearnset = sDELTA_COMBEELevelUpLearnset,
        .teachableLearnset = sDELTA_COMBEETeachableLearnset     
    },

 [SPECIES_DELTA_VESPIQUEN] =
   {
        .baseHP        = 40,
        .baseAttack    = 102,
        .baseDefense   = 80,
        .baseSpeed     = 70,
        .baseSpAttack  = 102,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(100),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_QUEENLY_MAJESTY, ABILITY_RIVALRY, ABILITY_SERENE_GRACE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Vespiquen"),
        .cryId = CRY_DELTA_VESPIQUEN,
        .natDexNum = NATIONAL_DEX_DELTA_VESPIQUEN,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Vespiquen,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 7,
        .backPic = gMonBackPic_Delta_Vespiquen,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Vespiquen,
       .shinyPalette = gMonShinyPalette_Delta_Vespiquen,
        .iconSprite = gMonIcon_Delta_Vespiquen,
        .iconPalIndex = 6,
       FOOTPRINT(Vespiquen)
        OVERWORLD(
        sPicTable_Vespiquen,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Vespiquen,
        gShinyOverworldPalette_Delta_Vespiquen,
        )
        .levelUpLearnset = sDELTA_VESPIQUENLevelUpLearnset,
        .teachableLearnset = sDELTA_VESPIQUENTeachableLearnset
       
    },
 [SPECIES_DELTA_SPINARAK] =
   {
        .baseHP        = 40,
        .baseAttack    = 60,
        .baseDefense   = 40,
        .baseSpeed     = 30,
        .baseSpAttack  = 40,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_BUG, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_TOUGH_CLAWS, ABILITY_COMPOUND_EYES, ABILITY_UNAWARE},
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Spinarak"),
        .cryId = CRY_DELTA_SPINARAK,
        .natDexNum = NATIONAL_DEX_DELTA_SPINARAK,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Spinarak,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .backPic = gMonBackPic_Delta_Spinarak,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Spinarak,
       .shinyPalette = gMonShinyPalette_Delta_Spinarak,
        .iconSprite = gMonIcon_Delta_Spinarak,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 22, SPECIES_DELTA_ARIADOS}),
       FOOTPRINT(Spinarak)
        OVERWORLD(
        sPicTable_Spinarak,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Spinarak,
        gShinyOverworldPalette_Delta_Spinarak,
        )
        .levelUpLearnset = sDELTA_SPINARAKLevelUpLearnset,
        .teachableLearnset = sDELTA_SPINARAKTeachableLearnset     
    },

 [SPECIES_DELTA_ARIADOS] =
   {
        .baseHP        = 70,
        .baseAttack    = 90,
        .baseDefense   = 70,
        .baseSpeed     = 60,
        .baseSpAttack  = 40,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_BUG, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_TOUGH_CLAWS, ABILITY_COMPOUND_EYES, ABILITY_UNAWARE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("ARIADOS"),
        .cryId = CRY_DELTA_ARIADOS,
        .natDexNum = NATIONAL_DEX_DELTA_ARIADOS,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Ariados,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Ariados,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Ariados,
       .shinyPalette = gMonShinyPalette_Delta_Ariados,
        .iconSprite = gMonIcon_Delta_Ariados,
        .iconPalIndex = 6,
       FOOTPRINT(Ariados)
        OVERWORLD(
        sPicTable_Ariados,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Ariados,
        gShinyOverworldPalette_Delta_Ariados,
        )
        .levelUpLearnset = sDELTA_ARIADOSLevelUpLearnset,
        .teachableLearnset = sDELTA_ARIADOSTeachableLearnset
       
    },
  [SPECIES_DELTA_YANMA] =
   {
        .baseHP        = 65,
        .baseAttack    = 65,
        .baseDefense   = 45,
        .baseSpeed     = 95,
        .baseSpAttack  = 75,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_BUG, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SPEED_BOOST, ABILITY_NONE, ABILITY_SUPER_LUCK },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Yanma"),
        .cryId = CRY_DELTA_YANMA,
        .natDexNum = NATIONAL_DEX_DELTA_YANMA,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Yanma,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
         .enemyMonElevation = 5,
        .backPic = gMonBackPic_Delta_Yanma,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Yanma,
       .shinyPalette = gMonShinyPalette_Delta_Yanma,
        .iconSprite = gMonIcon_Delta_Yanma,
        .iconPalIndex = 1,
 .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_DELTA_YANMEGA, CONDITIONS({IF_KNOWS_MOVE, MOVE_ANCIENT_POWER})}),
       FOOTPRINT(Yanma)
        OVERWORLD(
        sPicTable_Yanma,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Yanma,
        gShinyOverworldPalette_Delta_Yanma,
        )
        .levelUpLearnset = sDELTA_YANMALevelUpLearnset,
        .teachableLearnset = sDELTA_YANMATeachableLearnset     
    },

 [SPECIES_DELTA_YANMEGA] =
   {
        .baseHP        = 86,
        .baseAttack    = 76,
        .baseDefense   = 86,
        .baseSpeed     = 95,
        .baseSpAttack  = 116,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_BUG, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SPEED_BOOST, ABILITY_NONE, ABILITY_SUPER_LUCK },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Yanmega"),
        .cryId = CRY_DELTA_YANMEGA,
        .natDexNum = NATIONAL_DEX_DELTA_YANMEGA,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Yanmega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_Delta_Yanmega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Yanmega,
       .shinyPalette = gMonShinyPalette_Delta_Yanmega,
        .iconSprite = gMonIcon_Delta_Yanmega,
        .iconPalIndex = 6,
       FOOTPRINT(Yanmega)
        OVERWORLD(
        sPicTable_Yanmega,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Yanmega,
        gShinyOverworldPalette_Delta_Yanmega,
        )
        .levelUpLearnset = sDELTA_YANMEGALevelUpLearnset,
        .teachableLearnset = sDELTA_YANMEGATeachableLearnset
       
    },
     [SPECIES_DELTA_LARVESTA] =
   {
        .baseHP        = 39,
        .baseAttack    = 52,
        .baseDefense   = 43,
        .baseSpeed     = 65,
        .baseSpAttack  = 60,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Larvesta"),
        .cryId = CRY_DELTA_LARVESTA,
        .natDexNum = NATIONAL_DEX_DELTA_LARVESTA,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Larvesta,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Larvesta,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Larvesta,
       .shinyPalette = gMonShinyPalette_Delta_Larvesta,
        .iconSprite = gMonIcon_Delta_Larvesta,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_DELTA_VOLCARONA}), 
       FOOTPRINT(Larvesta)
        OVERWORLD(
        sPicTable_Larvesta,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Larvesta,
        gShinyOverworldPalette_Delta_Larvesta,
        )
        .levelUpLearnset = sDELTA_LARVESTALevelUpLearnset,
        .teachableLearnset = sDELTA_LARVESTATeachableLearnset
       

    },
    [SPECIES_DELTA_VOLCARONA] =
   {
        .baseHP        = 58,
        .baseAttack    = 64,
        .baseDefense   = 58,
        .baseSpeed     = 80,
        .baseSpAttack  = 80,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Volcarona"),
        .cryId = CRY_DELTA_VOLCARONA,
        .natDexNum = NATIONAL_DEX_DELTA_VOLCARONA,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Volcarona,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Volcarona,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Volcarona,
       .shinyPalette = gMonShinyPalette_Delta_Volcarona,
        .iconSprite = gMonIcon_Delta_Volcarona,
        .iconPalIndex = 0,
       FOOTPRINT(Volcarona)
        OVERWORLD(
        sPicTable_Volcarona,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Volcarona,
        gShinyOverworldPalette_Delta_Volcarona,
        )
        .levelUpLearnset = sDELTA_VOLCARONALevelUpLearnset,
        .teachableLearnset = sDELTA_VOLCARONATeachableLearnset
 
 },  
 
  [SPECIES_DELTA_SANDILE] =
   {
        .baseHP        = 45,
        .baseAttack    = 49,
        .baseDefense   = 49,
        .baseSpeed     = 45,
        .baseSpAttack  = 65,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Sandile"),
        .cryId = CRY_DELTA_SANDILE,
        .natDexNum = NATIONAL_DEX_DELTA_SANDILE,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Sandile,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Sandile,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Sandile,
       .shinyPalette = gMonShinyPalette_Delta_Sandile,
        .iconSprite = gMonIcon_Delta_Sandile,
        .iconPalIndex = 6,
  .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_DELTA_KROKOROK}), 
       FOOTPRINT(Sandile)
        OVERWORLD(
        sPicTable_Sandile,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Sandile,
        gShinyOverworldPalette_Delta_Sandile,
        )
        .levelUpLearnset = sDELTA_SANDILELevelUpLearnset,
        .teachableLearnset = sDELTA_SANDILETeachableLearnset
       

    },
    [SPECIES_DELTA_KROKOROK] =
   {
        .baseHP        = 60,
        .baseAttack    = 62,
        .baseDefense   = 63,
        .baseSpeed     = 60,
        .baseSpAttack  = 80,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Krokorok"),
        .cryId = CRY_DELTA_KROKOROK,
        .natDexNum = NATIONAL_DEX_DELTA_KROKOROK,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Krokorok,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Krokorok,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Krokorok,
       .shinyPalette = gMonShinyPalette_Delta_Krokorok,
        .iconSprite = gMonIcon_Delta_Krokorok,
        .iconPalIndex = 6,
 .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_DELTA_KROOKODILE}),
       FOOTPRINT(Krokorok)
        OVERWORLD(
        sPicTable_Krokorok,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Krokorok,
        gShinyOverworldPalette_Delta_Krokorok,
        )
        .levelUpLearnset = sDELTA_KROKOROKLevelUpLearnset,
        .teachableLearnset = sDELTA_KROKOROKTeachableLearnset
 
   
   },
    [SPECIES_DELTA_KROOKODILE] =
   {
        .baseHP        = 80,
        .baseAttack    = 90,
        .baseDefense   = 113,
        .baseSpeed     = 100,
        .baseSpAttack  = 132,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GRASS),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Krookodile"),
        .cryId = CRY_DELTA_KROOKODILE,
        .natDexNum = NATIONAL_DEX_DELTA_KROOKODILE,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Krookodile,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Krookodile,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Krookodile,
       .shinyPalette = gMonShinyPalette_Delta_Krookodile,
        .iconSprite = gMonIcon_Delta_Krookodile,
        .iconPalIndex = 6,
       FOOTPRINT(Krookodile)
        OVERWORLD(
        sPicTable_Krookodile,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Krookodile,
        gShinyOverworldPalette_Delta_Krookodile,
        )
        .levelUpLearnset = sDELTA_KROOKODILELevelUpLearnset,
        .teachableLearnset = sDELTA_KROOKODILETeachableLearnset     
    },
   [SPECIES_DELTA_TYRUNT] =
   {
        .baseHP        = 44,
        .baseAttack    = 50,
        .baseDefense   = 65,
        .baseSpeed     = 43,
        .baseSpAttack  = 48,
        .baseSpDefense = 64,
        .types = MON_TYPES(TYPE_FIRE, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_DRAGON),
        .abilities = {  ABILITY_OVERGROW, ABILITY_NONE, ABILITY_SWIFT_SWIM  },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Tyrunt"),
        .cryId = CRY_DELTA_TYRUNT,
        .natDexNum = NATIONAL_DEX_DELTA_TYRUNT,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Tyrunt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Tyrunt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Tyrunt,
       .shinyPalette = gMonShinyPalette_Delta_Tyrunt,
        .iconSprite = gMonIcon_Delta_Tyrunt,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_DELTA_TYRANTRUM}), 
       FOOTPRINT(Tyrunt)
        OVERWORLD(
        sPicTable_Tyrunt,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Tyrunt,
        gShinyOverworldPalette_Delta_Tyrunt,
        )
        .levelUpLearnset = sDELTA_TYRUNTLevelUpLearnset,
        .teachableLearnset = sDELTA_TYRUNTTeachableLearnset
       

    },
    [SPECIES_DELTA_TYRANTRUM] =
   {
        .baseHP        = 59,
        .baseAttack    = 65,
        .baseDefense   = 80,
        .baseSpeed     = 58,
        .baseSpAttack  = 63,
        .baseSpDefense = 58,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_SWIFT_SWIM },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Tyrantrum"),
        .cryId = CRY_DELTA_TYRANTRUM,
        .natDexNum = NATIONAL_DEX_DELTA_TYRANTRUM,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Tyrantrum,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Tyrantrum,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Tyrantrum,
       .shinyPalette = gMonShinyPalette_Delta_Tyrantrum,
        .iconSprite = gMonIcon_Delta_Tyrantrum,
        .iconPalIndex = 1,
       FOOTPRINT(Tyrantrum)
        OVERWORLD(
        sPicTable_Tyrantrum,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Tyrantrum,
        gShinyOverworldPalette_Delta_Tyrantrum,
        )
        .levelUpLearnset = sDELTA_TYRANTRUMLevelUpLearnset,
        .teachableLearnset = sDELTA_TYRANTRUMTeachableLearnset
 },
  [SPECIES_DELTA_KABUTO] =
   {
        .baseHP        = 30,
        .baseAttack    = 80,
        .baseDefense   = 90,
        .baseSpeed     = 55,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = {  ABILITY_STURDY, ABILITY_NONE, ABILITY_GALVANIZE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Kabuto"),
        .cryId = CRY_DELTA_KABUTO,
        .natDexNum = NATIONAL_DEX_DELTA_KABUTO,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Kabuto,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Kabuto,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Kabuto,
       .shinyPalette = gMonShinyPalette_Delta_Kabuto,
        .iconSprite = gMonIcon_Delta_Kabuto,
        .iconPalIndex = 1,
  .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_DELTA_KABUTOPS}), 
       FOOTPRINT(Kabuto)
        OVERWORLD(
        sPicTable_Kabuto,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Kabuto,
        gShinyOverworldPalette_Delta_Kabuto,
        )
        .levelUpLearnset = sDELTA_KABUTOLevelUpLearnset,
        .teachableLearnset = sDELTA_KABUTOTeachableLearnset
       

    },
    [SPECIES_DELTA_KABUTOPS] =
   {
        .baseHP        = 60,
        .baseAttack    = 115,
        .baseDefense   = 85,
        .baseSpeed     = 100,
        .baseSpAttack  = 65,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_STURDY, ABILITY_NONE, ABILITY_GALVANIZE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Kabutops"),
        .cryId = CRY_DELTA_KABUTOPS,
        .natDexNum = NATIONAL_DEX_DELTA_KABUTOPS,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Delta_Kabutops,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
         ANIMCMD_FRAME(0, 1),
         ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Delta_Kabutops,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Delta_Kabutops,
       .shinyPalette = gMonShinyPalette_Delta_Kabutops,
        .iconSprite = gMonIcon_Delta_Kabutops,
        .iconPalIndex = 1,
       FOOTPRINT(Kabutops)
        OVERWORLD(
        sPicTable_Kabutops,
        SIZE_32x32,
        SHADOW_SIZE_M,
        TRACKS_FOOT,
        sAnimTable_Following,
        gOverworldPalette_Delta_Kabutops,
        gShinyOverworldPalette_Delta_Kabutops,
        )
        .levelUpLearnset = sDELTA_KABUTOPSLevelUpLearnset,
        .teachableLearnset = sDELTA_KABUTOPSTeachableLearnset
    
   },


    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_CHARMANDER_CONNOR] =
   {
        .baseHP        = 39,
        .baseAttack    = 52,
        .baseDefense   = 43,
        .baseSpeed     = 65,
        .baseSpAttack  = 60,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 65,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Wet_Charmander"),
        .cryId = CRY_CHARMANDER_CONNOR,
        .natDexNum = NATIONAL_DEX_CHARMANDER_CONNOR,
        .categoryName = _("Test"),
        .height = 69,
        .weight = 69,
        .description = COMPOUND_STRING(
            "69.\n"
            "NICE!!!.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Wet_Charmander,
        .frontPicSize = MON_COORDS_SIZE(64),
        .frontPicYOffset = 12 : 10,
        .frontAnimFrames = sAnims_CHARMANDER_CONNOR,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 6, 
        .backPic = gMonBackPic_CHARMANDER_CONNOR,
        .backPicSize = MON_COORDS_SIZE(64),
        .backPicYOffset = 14 : 9,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .pallate = gMonPalette_CHARMANDER_CONNOR,
       .shinypallate = gMonShinyPalette_CHARMANDER_CONNOR,
        .iconeSprite = gMonIcon_CHARMANDER_CONNOR,
        .iconPalIndex = 0,
      
Dont fucking paste shit here        

    */
};

